# _Test_sht31 project_

This is project consists in the application of the standard GPIO for reading the values of a Humiture-Temperature sensor sht31.

## Test_sht31 folder contents

The project **test_sht31** contains five files: three source files in C language [main.c](main/main.c), [i2c_bus.c](main/i2c_bus.c) and [sht3x.c](main/sht3x.c), and two header file [i2c_bus.h](main/i2c_bus.h) and [sht3x.h](main/sht3x.h). The files are located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files.

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── i2c_bus.c
│   ├── sht3x.c
│   ├── i2c_bus.h
│   ├── sht3x.h
│   └── main.c
└── README.md                  This is the file you are currently reading
```
