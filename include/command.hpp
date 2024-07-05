#ifndef CPU_EMULATOR_COMMAND_HPP
#define CPU_EMULATOR_COMMAND_HPP

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <iostream>

#include "cpu.hpp"

class Command {
protected:
    int argument;
public:
	Command();
	Command(int arg);
	~Command() = default;

	virtual void execute(CPU& cpu) = 0;
	static Command* get_command(int id, int argument);
};

#endif // CPU_EMULATOR_COMMAND_HPP
