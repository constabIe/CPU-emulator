#include "cpu.hpp"
#include "command.hpp"

#define ANY_ARG_COMMAND(name) \
    class name##Command : public Command { \
        public: \
            name##Command(int arg) : Command(arg) {} \
            ~name##Command() = default;    \
                              \
            static Command* get_command(int arg) { \
                return new name##Command(arg); \
            } \
            void execute(CPU& cpu) override; \
    };

#define GET_COMMAND_FUNC(name) name##Command::get_command


Command::Command() : argument(0) {}
Command::Command(int arg) : argument(arg) {}

ANY_ARG_COMMAND(BEGIN)
void BEGINCommand::execute(CPU& cpu) {
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(END)
void ENDCommand::execute(CPU& cpu) {
    cpu.pc_register = 0;
}

ANY_ARG_COMMAND(POP)
void POPCommand::execute(CPU& cpu) {
    cpu.stack.pop();
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(ADD)
void ADDCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    cpu.stack.push(rhs + lhs);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(SUB)
void SUBCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    cpu.stack.push(rhs - lhs);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(MUL)
void MULCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    cpu.stack.push(rhs * lhs);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(DIV)
void DIVCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    cpu.stack.push(rhs / lhs);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(IN)
void INCommand::execute(CPU& cpu) {
    int tmp;
    std::cin >> tmp;
    cpu.stack.push(tmp);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(OUT)
void OUTCommand::execute(CPU& cpu) {
    std::cout << cpu.stack.top() << std::endl;
    cpu.stack.pop();
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(RET)
void RETCommand::execute(CPU& cpu) {
    cpu.pc_register = cpu.call_stack.top();
    cpu.call_stack.pop();
    cpu.pc_register += 1;
}

////////////////////////////
// COMMAND TYPES: INT ARG //
////////////////////////////

ANY_ARG_COMMAND(PUSH)
void PUSHCommand::execute(CPU& cpu) {
    cpu.stack.push(argument);
    cpu.pc_register += 1;
}

/////////////////////////////////
// COMMAND TYPES: REGISTER ARG //
/////////////////////////////////

ANY_ARG_COMMAND(PUSHR)
void PUSHRCommand::execute(CPU& cpu) {
    VERIFY_CONTRACT((argument >= 0) && (argument <= REGS), "Invalid register");
    int tmp = cpu.registers[argument];
    cpu.stack.push(tmp);
    cpu.pc_register += 1;
}

ANY_ARG_COMMAND(POPR)
void POPRCommand::execute(CPU& cpu) {
    VERIFY_CONTRACT((argument >= 0) && (argument <= REGS), "Invalid register");
    cpu.registers[argument] = cpu.stack.top();
    cpu.stack.pop();
    cpu.pc_register += 1;
}

//////////////////////////////
// COMMAND TYPES: LABEL ARG //
//////////////////////////////

ANY_ARG_COMMAND(JMP)
void JMPCommand::execute(CPU& cpu) {
    cpu.pc_register = argument;
}

ANY_ARG_COMMAND(JEQ)
void JEQCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs == lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(JNE)
void JNECommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs != lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(JA)
void JACommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs > lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(JAE)
void JAECommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs >= lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(JB)
void JBCommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs < lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(JBE)
void JBECommand::execute(CPU& cpu) {
    auto rhs = cpu.stack.top();
    cpu.stack.pop();
    auto lhs = cpu.stack.top();
    cpu.stack.pop();
    if (rhs <= lhs) {
        cpu.pc_register = argument;
    }
    else {
        cpu.pc_register += 1;
    }
}

ANY_ARG_COMMAND(CALL)
void CALLCommand::execute(CPU& cpu) {
    cpu.call_stack.push(cpu.pc_register);
    cpu.pc_register = argument;
}

const std::map<int, std::function<Command*(int)>> command_id_to_function {
        {10, GET_COMMAND_FUNC(BEGIN)},
        {11, GET_COMMAND_FUNC(POP)},
        {12, GET_COMMAND_FUNC(ADD)},
        {13, GET_COMMAND_FUNC(SUB)},
        {14, GET_COMMAND_FUNC(MUL)},
        {15, GET_COMMAND_FUNC(DIV)},
        {16, GET_COMMAND_FUNC(OUT)},
        {17, GET_COMMAND_FUNC(IN)},
        {18, GET_COMMAND_FUNC(RET)},
        {19, GET_COMMAND_FUNC(END)},
        {20, GET_COMMAND_FUNC(CALL) },
        {21, GET_COMMAND_FUNC(JMP) },
        {22, GET_COMMAND_FUNC(JEQ) },
        {23, GET_COMMAND_FUNC(JNE) },
        {24, GET_COMMAND_FUNC(JA) },
        {25, GET_COMMAND_FUNC(JAE) },
        {26, GET_COMMAND_FUNC(JB) },
        {27, GET_COMMAND_FUNC(JBE) },
        {30, GET_COMMAND_FUNC(PUSH) },
        {40, GET_COMMAND_FUNC(POPR)},
        {41, GET_COMMAND_FUNC(PUSHR)}
};

Command* Command::get_command(int id, int arg) {
    VERIFY_CONTRACT(command_id_to_function.contains(id), "Iinvalid command");

    switch (id / 10) {
        case 1:
            VERIFY_CONTRACT(arg == 0, "Non-zero argument");
        case 2:
            VERIFY_CONTRACT(arg >= 0, "Label don't exists");
        case 5:
            break;
            VERIFY_CONTRACT((arg >= 0) && (arg <= REGS), "Iinvalid register");
        default:
            break;
    }

    return command_id_to_function.at(id)(arg);
}
