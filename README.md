# RHINOESC 80A + PS5 Controller + ESP32

ESP32-based wireless control of a RHINOESC 80A crawler ESC using a PS5 DualSense controller.

## Hardware

- ESP32 DevKit V1
- PS5 DualSense Controller
- RHINOESC 80A ESC
- BLDC/Brushed motor compatible with the ESC
- Battery suitable for the ESC

## Control

The PS5 DualSense left stick controls the ESC.

| Controller | ESC command |
|---|---|
| Stick UP | Forward |
| Stick CENTER | Neutral / Stop |
| Stick DOWN | Reverse |

## ESC PWM

- Frequency: 50 Hz
- Minimum: 1000 µs
- Neutral: 1500 µs
- Maximum: 2000 µs
- ESP32 GPIO: 18

## Software

- Arduino IDE
- ESP32 Arduino Core
- PS5 Controller library

## Safety

Test the ESC with the motor/rover wheels safely lifted from the ground before applying high throttle.
