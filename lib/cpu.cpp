#include "command.hpp"
#include "cpu.hpp"
#include "stack.hpp"
#include "utils.hpp"

CPU::CPU(const std::string& filename) :
        begin(0),
        end(0)
{
    std::regex format {"[A-Za-z_\\/\\-]+\\.bcode"};
    VERIFY_CONTRACT(std::regex_match(filename, format), "Invalid file format");

    file_ = std::ifstream(filename);
    registers = new int[REGS];
    pc_register = 0;
}

CPU::~CPU() {
    delete[] registers;
    file_.close();
}

void CPU::run() {
    unsigned current_line = 0;
    while(!file_.eof()) {
        file_.getline(line_, MAX_LINE);

        pos_ = line_;
        next_ = line_ + std::strlen(line_);

        int command_id, argument;
        VERIFY_CONTRACT(sscanf(line_, "%d %d", &command_id, &argument), "Invalid symbols");
        commands.push_back(Command::get_command(command_id, argument));

        if (command_id == 10) {
            begin = current_line;
        }
        if (command_id == 19) {
            end = current_line;
        }

        ++current_line;
    }

    pc_register = begin;
    while (pc_register != static_cast<int>(end)) {
        int size = (int) commands.size();
        VERIFY_CONTRACT((pc_register < size) && (pc_register >= 0), "Non-existing label");
        commands[pc_register]->execute(*this);
    }
}
