#pragma once

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <regex>

#include "stack.hpp"

#define MAX_LINE 100
#define REGS 6

class Command;
class Parser;

class CPU {
    private:
        const char* pos_;
        const char* next_;
        char line_[MAX_LINE];
        unsigned int begin;
        unsigned int end;
    public:
        CPU(const std::string& filename);
        ~CPU();

        void run();

        std::ifstream file_;
        stack_::Stack<int> stack;
        stack_::Stack<int> call_stack;
        std::vector<Command*> commands;

        int* registers;
        int pc_register;
};
