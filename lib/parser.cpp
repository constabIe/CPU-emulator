#include "../include/parser.hpp"
#include "../include/command.hpp"
#include "../include/cpu.hpp"
#include "../include/utils.hpp"

const std::map<std::string, int> str_to_reg {
        {"AX", 0},
        {"BX", 1},
        {"CX", 2},
        {"DX", 3},
        {"EX", 4},
        {"FX", 5}
};

int get_register_id(const std::string& name) {
    VERIFY_CONTRACT(str_to_reg.contains(name), "Invalid register");
    return str_to_reg.at(name);
}

const std::map<std::string, int> command_name_to_id {
        {"BEGIN", 10},
        {"POP", 11},
        {"ADD", 12},
        {"SUB", 13},
        {"MUL", 14},
        {"DIV", 15},
        {"OUT", 16},
        {"IN",  17},
        {"RET", 18},
        {"END", 19},
        {"CALL", 20},
        {"JMP", 21},
        {"JEQ", 22},
        {"JNE", 23},
        {"JA",  24},
        {"JAE", 25},
        {"JB",  26},
        {"JBE", 27},
        {"PUSH", 30},
        {"POPR", 40},
        {"PUSHR", 41}
};

int get_command_id(std::string& name) {
    VERIFY_CONTRACT(command_name_to_id.contains(name), "Invalid command");
    return command_name_to_id.at(name);
}

Parser::Parser(const std::string& filename) :
        file_ (std::ifstream(filename, std::ios::in)),
        command_line_number(0)
{
    VERIFY_CONTRACT(file_.good(), "Unable to open file");
    read_line_from_file();
}

Parser::~Parser() {
    declared_labels.clear();
    used_labels.clear();
}

void Parser::read_line_from_file() {
    file_.getline(line_, MAX_LINE_SIZE);
    pos_ = line_;
    end_ = line_ + std::strlen(line_);
}

bool Parser::parse_pattern(std::regex regexp) {
    std::cmatch match_result {};
    bool ismatch = std::regex_search(pos_, end_, match_result, regexp, std::regex_constants::match_continuous);

    if (ismatch) {
        pos_ = match_result[0].second;
    }

    return ismatch;
}

bool Parser::parse_pattern(std::regex regexp, std::string& ret) {
    std::cmatch match_result {};
    bool match_status = std::regex_search(pos_, end_, match_result, regexp, std::regex_constants::match_continuous);


    if (match_status) {
        pos_ = match_result[0].second;
        ret = std::string(match_result[0].first, match_result[0].second);
    }

    return match_status;
}

bool Parser::parse_space_sequence() {
    std::regex pattern{"[ \t]+"};
    return parse_pattern(pattern);
}

bool Parser::parse_newline_sequence() {
    parse_space_sequence();
    bool success = pos_ == end_;
    while (pos_ == end_ && !file_.eof()) {
        read_line_from_file();
        parse_space_sequence();
    }
    return success;
}

bool Parser::parse_label_declaration() {
    std::regex pattern{"[A-Za-z_\\-]+:"};

    parse_space_sequence();

    std::string label_str;
    bool flag = parse_pattern(pattern, label_str);
    if (!flag) {
        return false;
    }

    label_str.pop_back();
    declared_labels[label_str] = command_line_number;

    return true;
}

int Parser::parse_command() {
    std::regex pattern{"[A-Z]+"};
    parse_space_sequence();

    std::string cmd_name;
    VERIFY_CONTRACT(parse_pattern(pattern, cmd_name), "Unable to parse command");
    return get_command_id(cmd_name);
}

int Parser::parse_register() {
    std::regex pattern{"[A-Z]+"};

    VERIFY_CONTRACT(parse_space_sequence(), "Unable to parse register");

    std::string reg_name;
    VERIFY_CONTRACT(parse_pattern(pattern, reg_name), "Unable to parse register");

    return get_register_id(reg_name);
}

int Parser::parse_number() {
    std::regex pattern { "(\\+|-)?(0|[1-9][0-9]*)" };

    VERIFY_CONTRACT(parse_space_sequence(), "Unable to parse integer");

    std::string val_str;
    VERIFY_CONTRACT(parse_pattern(pattern, val_str), "Unable to parse integer");

    return std::atoi(val_str.c_str());
}

std::string Parser::parse_label() {
    std::regex pattern{"[A-Za-z_\\-]+"};

    VERIFY_CONTRACT(parse_space_sequence(), "Unable to parse label");

    std::string label_str;
    VERIFY_CONTRACT(parse_pattern(pattern, label_str), "Unable to parse label");

    return label_str;
}

void Parser::parse(const std::string& outfile) {
    std::ofstream out;
    out.open(outfile);

    if (out.is_open()) {
        while (!file_.eof()) {
            parse_newline_sequence();
            if (parse_label_declaration()) {
                continue;
            }
            else {
                int cmd_id = parse_command();
                switch (cmd_id / 10) {
                    case 1 :
                        out << cmd_id << ' ' << 0;
                        break;
                    case 2 :
                        out << cmd_id << ' ';
                        used_labels[out.tellp()] = parse_label();
                        out << std::string(50, ' ');
                        break;
                    case 3 :
                        out << cmd_id << ' ' << parse_number();
                        break;
                    case 4 :
                        out << cmd_id << ' ' << parse_register();
                        break;
                    default:
                        VERIFY_CONTRACT(0, "Unexpected error");
                        break;
                }

                ++command_line_number;

                if (!file_.eof()) {
                    out << std::endl;
                }
            }
        }

        for (const auto& [key, value] : used_labels) {
            VERIFY_CONTRACT(declared_labels.contains(value), "Invalid label");
            out.seekp(key);
            out << declared_labels.at(value);
        }
    }
}
