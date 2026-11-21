# Self-Balancing Robot

A small two-wheel robot that stands upright on its own. It is like balancing a broom on your hand: the robot leans, and the wheels drive under it to catch it. I wanted to design the whole thing myself: the body, the wiring and the code. An MPU6050 measures how far the robot is leaning, and an Arduino Nano turns that angle into motor speed with a PID controller. Both wheels drive through a TB6612FNG motor driver, forward when it leans forward and backward when it leans back. The body is a three-layer frame (battery at the bottom, electronics in the middle, the Nano on top) that I'm building for 3D printing. I'm building it to learn how CAD, electronics and control code work together on a small robot.

## Status
The CAD, the circuit plan and the code are done. The robot is not built yet and the code has not run on real hardware, so every number in the code (Kp, Ki, Kd, the balance angle) is a starting guess. The first version of the chassis is based on a photo of a similar robot. I imported it into Fusion 360 and I'm checking and fixing the sizes against my real parts.

## Built With
- Arduino Nano (CH340 clone)
- MPU6050 (GY-521) gyroscope and accelerometer module
- TB6612FNG motor driver module
- 2 TT gear motors with 65 mm wheels
- 6 x AA cells with a buck converter set to 6V for the motors
- Fusion 360 for the chassis, Arduino IDE for the code

## Bill Of Materials

## Bill Of Materials

| Component | Qty | Purpose | Purchase link |
|---|---|---|---|
| Arduino Nano (CH340, soldered) | 1 | Main controller: reads the MPU6050, runs the PID code, drives the motor driver | https://probots.co.in/arduino-nano-v3-atmega328p-ch340-mini-usb.html |
| Mini-USB cable for the Nano | 1 | Uploads code and powers the board on the bench | https://robocraze.com/products/mini-usb-cable-1-metre |
| MPU6050 (GY-521) gyro and accelerometer module | 1 | Measures how far the robot is leaning | https://probots.co.in/mpu6050-6dof-imu-sensor-module-gyroscope-accelerometer-gy521.html |
| TB6612FNG motor driver module | 1 | Drives the left and right motors and wastes far less power than an L298N | https://robocraze.com/products/tb6612fng-dual-dc-motor-driver |
| TT gear motor with 65 mm rubber wheel | 2 | Drive wheels, both turn the same way to catch the lean | https://colgroad.com/product/tt-gear-motor-with-65mm-rubber-wheel |
| Adjustable buck converter (MP1584, 3A) | 1 | Steps the battery down to a steady 6V for the motors | https://www.rytronics.in/product/mini-mp1584-dc-dc-3a-adjustable-buck-module/ |
| 6 x AA battery holder with DC jack | 1 | Holds the six cells (about 9V in series) | https://zbotic.in/product/6-x-1-5v-aa-battery-holder-with-dc-2-1-power-jack/) |
| AA alkaline cells | 6 | Battery power (buy alkaline, not zinc) | https://robocraze.com/products/aa-battery |
| Sub-miniature SPDT toggle switch, 3A (pack of 5) | 1 | Main on/off switch on the battery positive wire | https://robocraze.com/products/sub-miniature-toggle-switchpack-of-5 |
| Capacitor kit (needs 100 uF, 10 uF and 0.1 uF) | 1 | 100 uF on the motor supply, 10 uF on the 5V line, 0.1 uF at the MPU6050 and across each motor | (https://www.theengineerstore.in/products/orange-500pcs-0-1uf-1000uf-plug-in-electrolytic-capacitor-kit |
| Breadboard (400 points) | 1 | Test the wiring before soldering | https://probots.co.in/breadboard-for-electronics-solderless-prototyping-400-points.html |
| Jumper wires, male to male, 40 pcs | 1 | Test wiring | https://probots.co.in/male-to-male-jumper-wires-40-pcs-20-cm.html |
| Silicone wire 22AWG (buy red and black) | 1 | Power and motor wiring | https://zbotic.in/product/22awg-extrasoft-silicone-wirecolor-red-pack-of-2/ |
| Male header pins, 1x40 | 1 strip | The MPU6050 comes with headers that are not soldered on | https://www.theengineerstore.in/products/40x1-pin-2-54mm-pitch-male-berg-strip |
| M3 x 10 mm screws | 1 pack | Boards and mounts on the chassis | https://www.amazon.in/Rpi-shop-Phillip-Phillips-Quantity/dp/B08FG7DL3T/ |
| Nylon cable ties, 100 mm | 10 | Hold the battery holder and the motors | https://probots.co.in/100mm-length-2-5mm-width-nylon-cable-tie-tag-white.html |
| Heat shrink tubing set | 1 set | Cover soldered joints | https://zbotic.in/product/colorful-heat-shrink-tubing-insulation-set-168pcs/ |
| PLA filament, 1.75 mm, 1 kg | 1 | The chassis, only if you print it yourself | https://www.theengineerstore.in/products/1-75mm-natural-pla-filament-1kg |
| Digital multimeter (DT830D) | 1 | Set the buck converter to 6V, check for shorts | https://robocraze.com/products/digital-multimeter |
| Soldering iron kit (iron, stand, solder, wick) | 1 | Joins wires and header pins | https://robocraze.com/products/noel-7-in-1-soldering-iron-kit-25w-gold |
| Wire cutter and stripper (included in the soldering kit) | 1 | Prepares the wires | https://robocraze.com/products/noel-7-in-1-soldering-iron-kit-25w-gold |
| Digital vernier caliper | 1 | Measure every part before finalising the CAD | https://robocraze.com/products/gripx-digital-vernier-caliper-electronic-measuring-tool |
## Circuit Diagram
<img width="656" height="431" alt="Screenshot 2026-11-21 at 5 35 49 PM" src="https://github.com/user-attachments/assets/43ef5cf8-55d7-405f-9927-9880c0ba4466" />

This is a planned wiring diagram. The tool I drew it in shows the battery as a 4 x AA holder, but the real build uses 6 x AA. I'm still checking every connection against the pin map below.

## Pin Map
Board: Arduino Nano.

| Arduino pin | Connects to | Purpose |
|---|---|---|
| A4 | MPU6050 SDA | I2C data |
| A5 | MPU6050 SCL | I2C clock |
| D2 | MPU6050 INT | Interrupt (optional) |
| D5 | Driver PWMA | Left motor speed |
| D7 | Driver AIN1 | Left motor direction |
| D8 | Driver AIN2 | Left motor direction |
| D6 | Driver PWMB | Right motor speed |
| D9 | Driver BIN1 | Right motor direction |
| D10 | Driver BIN2 | Right motor direction |
| D4 | Driver STBY | Turns the driver on |
| 5V | Driver VCC, MPU6050 VCC | Logic power |
| VIN | Battery after the switch | Powers the Nano |
| GND | All grounds | Common ground |

MPU6050 AD0 goes to GND.

## Power and load connections

| From | To |
|---|---|
| Battery negative | Common GND |
| Battery positive | Power switch |
| Power switch | Nano VIN and buck converter input |
| Buck converter output (6V) | Driver VM |
| Driver AO1 and AO2 | Left motor |
| Driver BO1 and BO2 | Right motor |
| 100 uF capacitor | Across driver VM and GND |
| 10 uF capacitor | Across the 5V line and GND, near the MPU6050 |
| 0.1 uF capacitor | Across MPU6050 VCC and GND |
| 0.1 uF capacitor | Across each motor's terminals |

## Before wiring
- Set the buck converter to 6.0V with a multimeter before the driver touches it.
- With the switch off, the buck input and the driver VM should read 0V.
- Unplug the battery before connecting USB to the Nano.

## Assembly guide
This is the order I plan to build it in. I haven't done it yet, so it may change.

1. Measure every part with calipers (motors, battery holder, boards) and compare the numbers with the parameters in the Fusion file.
2. Print the chassis and check that the posts, the plates and the battery holder fit.
3. Solder wires to the motors and put a 0.1 uF capacitor across each one.
4. Solder the header pins on the MPU6050.
5. Fit the motors beside the bottom plate with cable ties and put the wheels on.
6. Wire the battery holder, the switch and the buck converter only. Set the output to 6.0V, then switch off.
7. Mount the battery on the bottom plate, the driver, IMU and buck converter on the middle plate, and the Nano on the top plate.
8. Wire the rest using the pin map. Keep the motor wires away from the MPU6050 wires.
9. Mount the MPU6050 flat and firmly, as close to the wheel axle as I can. If it wobbles, the angle readings will be noisy.
10. Test with the wheels lifted off the ground. Both wheels should turn the same way when I tilt the robot. If one turns the wrong way, change `LEFT_DIR` or `RIGHT_DIR` in the code.

## Calibration
1. Upload `self_balancing.ino`, hold the robot still for the first 3 seconds, then let it go. The code measures the gyro's resting drift during that time.
2. Start with Ki and Kd at 0. Raise Kp until the robot starts to oscillate, then back off a little.
3. Raise Kd until the wobble calms down.
4. Add a small Ki at the end to stop the slow drift in one direction.
5. If it always leans one way, change `SETPOINT` by a degree at a time.
6. If the wheels drive away from the lean, flip `LEFT_DIR` and `RIGHT_DIR` to -1.
7. If the angle doesn't change when I tip it forward and back, the MPU6050 axis in the code needs changing.

## Things that might go wrong
I haven't built it yet, so these are things I expect, not things I have seen.

- The battery holder doesn't fit. A flat 6 x AA holder is about 92 x 56 x 15 mm, and my first chassis was drawn for a smaller box, so the plate size needs checking.
- The robot falls straight away. Usually the motors push the wrong way, so flip `LEFT_DIR` and `RIGHT_DIR`.
- The motors don't move. The STBY pin must be HIGH, and the driver needs power on both VM and VCC.
- The Arduino resets when the motors start. A bigger capacitor on the motor supply is the likely fix.
- The motors get too much voltage. TT motors are rated for about 3 to 6V, which is why the buck converter is set to 6V and not the full 9V.
- The angle drifts or jumps. A loose MPU6050 or noisy wiring is the likely cause, so mount it firmly and keep its wires short.
- The robot oscillates faster and faster. Kp is too high or Kd is too low.
- The Nano doesn't show up on the computer. The CH340 chip may need a driver.

## Safety
Use fresh alkaline cells and don't mix old and new ones. Take them out if the robot will sit unused for a long time. Ask an adult to help with soldering.

## CAD Models
1. The first model which was made using wrong measurements 

<img width="1088" height="724" alt="Screenshot 2026-11-18 at 9 45 32 AM" src="https://github.com/user-attachments/assets/6a5af2ad-c40b-495f-90ac-9df180895e9e" />

2. The body with correct measurements  and all the dummies without motors and wheel

<img width="1112" height="866" alt="Screenshot 2026-11-18 at 1 13 26 PM" src="https://github.com/user-attachments/assets/e2122900-9328-40eb-b202-880ef3272983" />

3. The final model with all the things attached  

<img width="1512" height="874" alt="Screenshot 2026-11-18 at 1 22 34 PM" src="https://github.com/user-attachments/assets/c74a1f99-d230-465f-a536-1c7e9c608f0b" />

4. No interferences

<img width="1120" height="718" alt="Screenshot 2026-11-18 at 9 40 51 PM" src="https://github.com/user-attachments/assets/84972149-d643-472c-9602-1a72a973b767" />







