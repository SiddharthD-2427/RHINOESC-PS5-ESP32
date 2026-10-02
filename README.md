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

