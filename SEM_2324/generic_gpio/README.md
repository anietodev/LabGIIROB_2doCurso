# _Generic_gpio project_

This is project consists in the application of the standard GPIO for switching on and off a LED.

## Generic_gpio folder contents

The project **generic_gpio** contains three files: two source files in C language [main.c](main/main.c) and [led.c](main/led.c), and one header file [led.h](main/led.h). The files are located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files.

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── led.c
│   ├── led.h
│   └── main.c
└── README.md                  This is the file you are currently reading
```
