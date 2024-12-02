# filediff-gui
A GUI application showing the capabilities of the library [libfilediff](https://github.com/qualimock/libfilediff)

## Prerequisites
To build the application you should use [CMake](https://cmake.org)

It can be installed on your ALT distro via apt-get:
```
apt-get install cmake
```

## Build and install
Clone the repository:
```
git clone https://github.com/qualimock/filediff-gui.git
cd filediff-gui
```

Setup build directory:
```
mkdir build
cmake -B build
```

Compile the application:
```
cmake --build build
```

Install the application:
```
cmake --install build
```

## How to use
Run the application
```
filediff-gui
```

The main window consists of two file input lines and two buttons aside of them.

Click any of 'Browse...' buttons to choose directory to load.

'Compare' button will not be available until two not empty directories are loaded.

'Compare' button will compare two directories and will load the difference.

'Show diff' button opens the compare window.

Compare window consists of dropdown menu where differing files can be chosen,
two text browsers for showing difference, amount of bytes around differing chunk selector
and button switching view from text to hex and vice versa.

When directories are compared using 'Compare' button, difference will be available in compare window.

To view a file difference, choose it in dropdown menu.

To change amount of bytes around differing chunk, select the number in box at the bottom of the window
and press 'Submit' button.

To change view press 'To Hex', press it again (it'll change their name to 'To Text') to change view back.
