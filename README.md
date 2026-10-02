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
## Software Requirements

### Arduino IDE

This project was developed and tested using:

* Arduino IDE
* ESP32 Arduino Core **2.0.17**
* ESP32 DevKit / ESP32-WROOM-32

### PS5 Controller Library

This project uses the **ps5-esp32** library by Rodney Bakiskan.

Repository:

https://github.com/rodneybakiskan/ps5-esp32

The library was downloaded from the repository's `main` branch.

### Required Library Modification

When compiling the PS5 library with ESP32 Arduino Core **2.0.17**, the following header was added to the library source file:

```cpp
#include <esp_mac.h>
```

File location:

```text
Arduino/libraries/ps5Controller/src/ps5.c
```

The line was added near the beginning of `ps5.c`:

```cpp
#include <esp_mac.h>
```

This modification is required for the library to compile correctly with the ESP32 Arduino Core version used in this project.

### Important

If the PS5 library is installed manually, make sure the library folder is named:

```text
ps5Controller
```

and that the modified file is located at:

```text
ps5Controller/src/ps5.c
```

The project currently uses the following PS5 connection method:

```cpp
ps5.begin("1a:2b:3c:01:01:01");
```

Replace the MAC address with the appropriate controller/pairing address when setting up the project on another ESP32.

