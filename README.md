# RoboJackets Firmware Training

**Please bookmark this page!**

Welcome to the RoboJackets Firmware training repository!

## Training Schedule 2026

* Location: Skiles 271 (Except for 9/18 (Skiles 171))
* Time: 6:00pm - 8:00pm on Thursdays or Fridays
* Bring: Your computer

Here is a breakdown of what firmware training is week-to-week:
* Week 1: What is firmware? General Arduino + Digital IO
* Week 2: Analog IO + Interrupts
* Special!: Hive Soldering Training
* Week 3: Communication Protocols
* Week 4: Driver Design
* Week 5: State Machines + RTOSes

## About this Repository

This repository will be updated each week to contain the solution to the last week's labs as well as the presentation for the current week.  All presentations will be present in the [presentations](./presentations/) folder.  Additionally, all labs will be in their respective week's directory within the [labs](./labs) folder.

## Week 1

In week 1, we will be learning what firmware is and what you can do with it.  Additionally, this lecture will discuss the basics of coding and digital inputs and outputs.

### Labs

For week 1, there is one lab, [blink](./labs/week-1/blink/).  Blink is the classic "Hello World" of the Arduino world.  In this lab, you will be learning how to interface with the Arduino Nano to blink the onboard led.

## Week 2

In week 2, we will be learning about control flow, digital inputs, and analog IO.

### Labs

For week 2, there are three labs, [switch-buttons](./labs/week-2/switch-buttons), [pwm](./labs/week-2/pwm), and [potentiometer-control](./labs/week-2/potentiometer-control).  Switch buttons teaches how to read digital inputs and use interrupts.  PWM teaches the basics of manually generating pwm signals.  Potentiometer control teaches how to control the value of analog outputs via an analog input.

## Week 3

In week 3, we will be learning about common communication protocols used in embedded systems.

### Labs

For week 3, there are two labs, [serial-control](./labs/week-3/serial-control) and [i2c-imu](./labs/week-3/i2c-imu).  Serial Control details how you can use the serial interface on the Arduino to debug and control the peripherals connected to the training board.  I2C IMU shows how to use a library to read values from the IMU over i2c and how you can use this to make a simple shake on/off switch.

## Week 4

In week 4, we will be learning about how to design and create drivers to work with peripheral devices.

### Labs

For week 4, there is one lab, [imu-driver-design](./labs/week-4/imu-driver-design).  This lab has you create a driver for the MPU6050 IMU connected to the firmware training board.  It also contains the code to complete week-3 lab 2 as a test for your IMU driver.

## Week 5

In week 5, we will be learning about state machines and I'll teach a little bit about real time operating systems.

### Labs

For week 5, there is only one lab, [state-machines](./labs/week-5/state-machines).  This lab has you creating a combination lock using inputs on the training board.


## Additional Resources

* [PlatformIO Core Installation Instructions](https://platformio.org/install/cli)
* [PlatformIO IDE for VSCode Installation Instructions](https://platformio.org/install/ide?install=vscode)
* [Wokwi for VSCode Installation Instructions](https://docs.wokwi.com/vscode/getting-started)
