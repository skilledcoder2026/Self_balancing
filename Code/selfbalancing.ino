#include <Wire.h>

const int PWMA = 5, AIN1 = 7, AIN2 = 8;
const int PWMB = 6, BIN1 = 9, BIN2 = 10;
const int STBY = 4;
const uint8_t MPU = 0x68;

float Kp = 18.0;
float Ki = 0.8;
float Kd = 0.6;

float SETPOINT = 0.0;
const float ALPHA = 0.98;
const float FALL_ANGLE = 35.0;
const float RECOVER_ANGLE = 3.0;
const int MIN_PWM = 40;
const int MAX_PWM = 255;
const int LEFT_DIR = 1;
const int RIGHT_DIR = 1;
const unsigned long LOOP_US = 5000;

float angle = 0, gyroBias = 0, integral = 0;
unsigned long lastUs = 0;
bool fallen = false;

void setMotors(int left, int right) {
  left *= LEFT_DIR;
  right *= RIGHT_DIR;
  left = constrain(left, -MAX_PWM, MAX_PWM);
  right = constrain(right, -MAX_PWM, MAX_PWM);
  digitalWrite(AIN1, left >= 0);
  digitalWrite(AIN2, left < 0);
  digitalWrite(BIN1, right >= 0);
  digitalWrite(BIN2, right < 0);
  analogWrite(PWMA, abs(left));
  analogWrite(PWMB, abs(right));
}

void stopMotors() {
  setMotors(0, 0);
}

bool readMPU(float &accAngle, float &rate) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU, (uint8_t)14) != 14) return false;
  Wire.read(); Wire.read();
  int16_t ay = Wire.read() << 8 | Wire.read();
  int16_t az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  int16_t gx = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  Wire.read(); Wire.read();
  accAngle = atan2((float)ay, (float)az) * 57.2958;
  rate = gx / 131.0 - gyroBias;
  return true;
}

void setup() {
  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT); pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  stopMotors();
  digitalWrite(STBY, HIGH);

  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
  delay(100);

  delay(3000);
  float sum = 0;
  int n = 0;
  for (int i = 0; i < 500; i++) {
    float a, r;
    if (readMPU(a, r)) { sum += r; n++; }
    delay(3);
  }
  if (n > 0) gyroBias = sum / n;

  float a, r;
  if (readMPU(a, r)) angle = a;
  lastUs = micros();
}

void loop() {
  unsigned long now = micros();
  if (now - lastUs < LOOP_US) return;
  float dt = (now - lastUs) / 1000000.0;
  lastUs = now;

  float accAngle, rate;
  if (!readMPU(accAngle, rate)) {
    stopMotors();
    return;
  }

  angle = ALPHA * (angle + rate * dt) + (1.0 - ALPHA) * accAngle;
  float error = angle - SETPOINT;

  if (fallen) {
    stopMotors();
    integral = 0;
    if (abs(error) < RECOVER_ANGLE) fallen = false;
    return;
  }
  if (abs(error) > FALL_ANGLE) {
    fallen = true;
    stopMotors();
    return;
  }

  integral += error * dt;
  integral = constrain(integral, -30, 30);

  float output = Kp * error + Ki * integral + Kd * rate;

  int pwm = (int)output;
  if (pwm > 0) pwm += MIN_PWM;
  else if (pwm < 0) pwm -= MIN_PWM;
  pwm = constrain(pwm, -MAX_PWM, MAX_PWM);

  setMotors(pwm, pwm);
}

