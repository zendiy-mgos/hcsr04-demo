# Mongoose OS demo firmware for using HC-SR04 sensor
## Overview
This is a [Mongoose-OS](https://mongoose-os.com/) demo firmware for using HC-SR04, a popular ultrasonic distance sensor. This firmware uses the native [hcsr04 library](https://github.com/zendiy-mgos/hcsr04).
## GET STARTED
Build up your device in few minutes just downloading, compiling and flashing this demo.

Clone the repo:
```bash
$ git clone https://github.com/zendiy-mgos/hcsr04-demo.git my-hcsr04-demo
$ cd my-hcsr04-demo
```
Enable JavaScript demo (skip to continue with C/C++ demo) :
```yaml
sources:
# - src
  - src_js
libs:
  - origin: https://github.com/mongoose-os-libs/mjs
  - ...
```
Build the binary:
```bash
$ mos build --platform <device_platform>
```
Flash the firmware:
```bash
$ mos flash --port <port_name>
```
## Hardware
### Compatible sensors
You can use one of the following sensors.
|Model||Notes|
|--|--|--|
|![hc-sr04 sensor](docs/hc-sr04.jpg)|HC-SR04|This sensor usually runs on 5V. If your MCU's GPIOs run on 3.3V (like ESP8266 GPIOs), **you must use the newer version** that natively supports 3.3V voltage. Otherwise, you must hack the circuit according this [anjoschu's post](https://www.instructables.com/id/Modify-Ultrasonic-Sensors-for-3-Volts-Logic-prepar/).|
|![rcw-0001 sensor](docs/rcw-0001-small.png)|RCW-0001|This sensor natively supports both 3.3V and 5V voltages. It is fully equivalent to the HC-SR04 sensor.|
### Wiring schema
This example shows how to wire a **Wemos D1 mini** board with a **RCW-0001** sensor.
![hc-sr04 wiring schema](docs/hcsr04-demo-sketch_bb.png)
