# _Button project_

This is project consists in the application of the standard GPIO for switching on and off a LED using a button. When it's pressed, the light's on, when not, the light's off.

## Button folder contents

The project **button** contains three files: two source files in C language [main.c](main/main.c) and [button.c](main/button.c), and one header file [button.h](main/button.h). The files are located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files.

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   ├── button.c
│   ├── button.h
│   └── main.c
└── README.md                  This is the file you are currently reading
```

