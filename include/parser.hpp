#ifndef CPU_EMULATOR_PARSER_HPP
#define CPU_EMULATOR_PARSER_HPP

#include <regex>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <set>

#define MAX_LINE_SIZE 100

class Parser {
    private:
        std::ifstream file_;

        const char* pos_;
        const char* end_;
        char line_[MAX_LINE_SIZE];
        int command_line_number;
        std::map<std::string, int> declared_labels;
        std::map<long int, std::string> used_labels;

        bool parse_pattern(std::regex regexp);
        bool parse_pattern(std::regex regexp, std::string& ret);

        void read_line_from_file();

        bool parse_space_sequence();
        bool parse_newline_sequence();

        bool parse_label_declaration();

        int parse_number();

        int parse_command();
        int parse_register();
        std::string parse_label();
    public:
        Parser(const std::string& filename);
        ~Parser();

        void parse(const std::string& outfile);
};

#endif // CPU_EMULATOR_PARSER_HPP
