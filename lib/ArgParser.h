#pragma once
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdint>
#include <variant>

namespace ArgumentParser {
    class Argument {
    public:
        char short_name;
        std::string long_name;
        std::string description;

        uint64_t min_args_amount = 1;
        bool is_multi_value = false;
        bool is_positional = false;
        bool is_store_value = false;
        bool is_default = false;

        virtual ~Argument() = default;
    };

    class IntArgument : public Argument {
    public:
        int64_t value;
        int64_t* store_value;

        std::vector<int64_t> values;
        std::vector<int64_t>* store_multi_values;

        IntArgument& Default(int64_t val);
        IntArgument& StoreValue(int64_t& val);
        IntArgument& StoreValues(std::vector<int64_t>& val);
        IntArgument& MultiValue();
        IntArgument& MultiValue(uint64_t min_arg_num);
        IntArgument& Positional();
    };

    class StringArgument : public Argument {
    public:
        std::string value;
        std::string* store_value;

        std::vector<std::string> values;
        std::vector<std::string>* store_multi_values;

        StringArgument& Default(const std::string& val);
        StringArgument& StoreValue(std::string& val);
        StringArgument& StoreValues(std::vector<std::string>& val);
        StringArgument& MultiValue();
        StringArgument& MultiValue(uint64_t min_arg_num);
        StringArgument& Positional();
    };

    class BoolArgument : public Argument {
    public:
        bool value;
        bool* store_multi_value;

        BoolArgument& Default(bool val);
        BoolArgument& StoreValue(bool& val);
    };

    class ArgParser {
    private:
        std::string parameters;
        std::vector<Argument*> arguments;
    public:
        explicit ArgParser(std::string str) : parameters((std::move(str))) {};
        ~ArgParser() {
            for (int i = 0; i < arguments.size(); ++i) {
                delete arguments[i];
            }
        }


        bool Parse(const std::vector<std::string>& options);
        bool Parse(int argc, char* argv[]);

        IntArgument& AddIntArgument(char short_name, const char* long_name);
        IntArgument& AddIntArgument(const char* long_name);
        IntArgument& AddIntArgument(const char* long_name, const char* description);
        int64_t GetIntValue(const std::string& name);
        int64_t GetIntValue(std::string name, uint64_t number);

        StringArgument& AddStringArgument(char short_name, const char* long_name);
        StringArgument& AddStringArgument(const char* long_name);
        StringArgument& AddStringArgument(char short_name, const char* long_name, const char* description);
        std::string GetStringValue(const std::string& name);
        std::string GetStringValue(const std::string& name, uint64_t number);

        BoolArgument& AddFlag(char short_name, const char* long_name);
        BoolArgument& AddFlag(const char* long_name);
        BoolArgument& AddFlag(char short_name, const char* long_name, const char* description);
        BoolArgument& AddFlag(const char* long_name, const char* description);
        bool GetFlag(const std::string& name);

        void AddHelp(char c, const char *string1, const char *string2);
        bool Help();
        std::string HelpDescription();
    };
} // namespace ArgumentParser