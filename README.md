# Simple CPU emulator

## Requirements
* [googletest](https://github.com/google/googletest)) test system
* Linux or Mac OS

## Installation
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
## Usage
Example programs:
- fibonacci
- factorial
- recursive_factorial
Choose the program above for the execution. For example fibonacci.
### The stage of converting a program into bytecode
```sh
make code fibonacci.lng
```
### Stage of execution
```sh
make run fibonacci.lng
```

