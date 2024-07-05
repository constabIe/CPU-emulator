# Requirements
* [googletest](https://github.com/google/googletest)
* Linux or Mac OS

# Installation
* Test system:
  - Linux:
  ``` sh
  sudo apt-get googletest
  ```
  - Mac OS:
  ```sh
  brew install googletest
  ```
* Clone the repository
```sh
 git init
 git clone https://github.com/constabIe/CPU-emulator
```
# Usage
## Programs
Example:
- fibonacci
- factorial
- recursive_factorial

Choose the program above for the execution. For example fibonacci.
### Stage of converting a program into bytecode
```sh
make code fibonacci.lng
```
### Stage of execution
```sh
make run fibonacci.bcode
```
## Test
Tests execution via [googletest](https://github.com/google/googletest) needs library linking, thus set paths of the location of these librarys on your machine(default Mac OS).
``` sh
make test TEST_SYSTEM_INCLUDE="-I /opt/homebrew/opt/googletest/include" TEST_SYSTEM_LIB="-L /opt/homebrew/opt/googletest/lib"
```
