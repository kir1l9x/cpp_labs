#include "ArgParser.h"

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& options) {
    if (options.empty() || options[0] != "app") {
        return false;
    }
    for (auto* argPtr : arguments) {
        if (auto* intArg = dynamic_cast<IntArgument*>(argPtr)) {
            if (intArg->is_positional && intArg->is_multi_value && intArg->is_store_value) {
                for (int j = 1; j < options.size(); ++j) {
                    intArg->store_multi_values->push_back(std::stoll(options[j]));
                }
                return true;
            }
        }
    }
    for (int i = 1; i < options.size(); ++i) {
        std::string arg = options[i];
        bool isLongArg = arg.rfind("--", 0) == 0;
        bool isShortArg = arg.rfind("-", 0) == 0 && !isLongArg;

        std::string name;
        std::string value;
        size_t equalPos = arg.find('=');
        if (isLongArg) {
            name = arg.substr(2, equalPos - 2);
        } else {
            name = arg.substr(1, equalPos - 1);
        }

        if (equalPos != std::string::npos) {
            value = arg.substr(equalPos + 1);
        }

        bool found = false;
        for (auto* argPtr : arguments) {
            if ((isLongArg && argPtr->long_name == name) ||
                (isShortArg && argPtr->short_name == name[0])) {
                found = true;

                if (auto* intArg = dynamic_cast<IntArgument*>(argPtr)) {
                    int64_t intValue = std::stoll(value);
                    if (intArg->is_multi_value) {
                        intArg->values.push_back(intValue);
                        if (intArg->store_multi_values) {
                            intArg->store_multi_values->push_back(intValue);
                        }
                    } else {
                        intArg->value = intValue;
                        if (intArg->store_value) {
                            *(intArg->store_value) = intValue;
                        }
                    }
                } else if (auto* strArg = dynamic_cast<StringArgument*>(argPtr)) {
                    if (strArg->is_multi_value) {
                        strArg->values.push_back(value);
                        if (strArg->store_multi_values) {
                            strArg->store_multi_values->push_back(value);
                        }
                    } else {
                        strArg->value = value;
                        if (strArg->store_value) {
                            *(strArg->store_value) = value;
                        }
                    }
                } else if (auto* boolArg = dynamic_cast<BoolArgument*>(argPtr)) {
                    boolArg->value = true;
                    if (boolArg->store_multi_value) {
                        *(boolArg->store_multi_value) = true;
                    }
                }
                break;
            }
        }
    }

    for (auto* argPtr : arguments) {
        if (auto* intArg = dynamic_cast<IntArgument*>(argPtr)) {
            if (intArg->is_multi_value && intArg->values.size() < intArg->min_args_amount) {
                return false;
            }
        }
    }
    for (auto* argPtr : arguments) {
        if (auto* strArg = dynamic_cast<StringArgument*>(argPtr)) {
            if (!strArg->is_default && strArg->value.empty() && strArg->description.empty()) {
                return false;
            }
        }
    }

    return true;
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> opt_string;
    for (int i = 0; i < argc; ++i) {
        opt_string.emplace_back(argv[i]);
    }
    bool is_okay = Parse(opt_string);
    return is_okay;
}

//----------------------------------------INT----------------------------------------

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(char short_name, const char *long_name) {
    IntArgument* arg = new IntArgument();
    arg->short_name = short_name;
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *arg;
}

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(const char* long_name) {
    IntArgument* arg = new IntArgument();
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *dynamic_cast<IntArgument*>(arg);
}

ArgumentParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument(const char* long_name, const char* description) {
    IntArgument* arg = new IntArgument();
    arg->long_name = long_name;
    arg->description = description;
    arguments.push_back(arg);
    return *dynamic_cast<IntArgument*>(arg);
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::Default(int64_t val) {
    value = val;
    is_default = true;
    return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::StoreValue(int64_t& val) {
    store_value = &val;
    is_store_value = true;
    return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::StoreValues(std::vector<int64_t>& val) {
    store_multi_values = &val;
    is_multi_value = true;
    is_store_value = true; // TODO: mistake may be
    return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::Positional() {
    is_positional = true;
    return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::MultiValue() {
    is_multi_value = true;
    return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::MultiValue(uint64_t min_arg_num) {
    is_multi_value = true;
    min_args_amount = min_arg_num;
    return *this;
}

int64_t ArgumentParser::ArgParser::GetIntValue(const std::string& name) {
    for (auto* argPtr : arguments) {
        if (auto* intArg = dynamic_cast<IntArgument*>(argPtr)) {
            if (intArg->long_name == name) {
                return intArg->value;
            }
        }
    }
    return 0;
}

int64_t ArgumentParser::ArgParser::GetIntValue(std::string name, uint64_t number) {
    for (auto* argPtr : arguments) {
        if (auto* intArg = dynamic_cast<IntArgument*>(argPtr)) {
            if (intArg->long_name == name) {
                std::vector<int64_t> search = *intArg->store_multi_values;
                return search[number];
            }
        }
    }
    return 0;
}

//----------------------------------------STRING----------------------------------------
ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(char short_name, const char* long_name) {
    StringArgument* arg = new StringArgument();
    arg->short_name = short_name;
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *dynamic_cast<StringArgument*>(arg);
}

ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(char short_name, const char* long_name, const char* description) {
    StringArgument* arg = new StringArgument();
    arg->short_name = short_name;
    arg->long_name = long_name;
    arg->description = description;
    arguments.push_back(arg);
    return *dynamic_cast<StringArgument*>(arg);
}

ArgumentParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument(const char* long_name) {
    StringArgument* arg = new StringArgument();
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *dynamic_cast<StringArgument*>(arg);
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::Default(const std::string& val) {
    value = val;
    is_default = true;
    return *this;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::StoreValue(std::string& val) {
    store_value = &val;
    is_store_value = true;
    return *this;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::StoreValues(std::vector<std::string>& val) {
    store_multi_values = &val;
    is_store_value = true;
    is_multi_value = true;
    return *this;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::Positional() {
    is_positional = true;
    return *this;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::MultiValue() {
    is_multi_value = true;
    return *this;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::MultiValue(uint64_t min_arg_num) {
    is_multi_value = true;
    min_args_amount = min_arg_num;
    return *this;
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& name) {
    for (auto* argPtr : arguments) {
        if (auto* stringArg = dynamic_cast<StringArgument*>(argPtr)) {
            if (stringArg->long_name == name) {
                return stringArg->value;
            }
        }
    }
    return "";
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& name, uint64_t number) {
    for (auto* argPtr : arguments) {
        if (auto* stringArg = dynamic_cast<StringArgument*>(argPtr)) {
            if (stringArg->long_name == name) {
                std::vector<std::string> search = *stringArg->store_multi_values;
                return search[number];
            }
        }
    }
    return "";
}

//----------------------------------------BOOL----------------------------------------
ArgumentParser::BoolArgument& ArgumentParser::ArgParser::AddFlag(char short_name, const char* long_name) {
    BoolArgument* arg = new BoolArgument();
    arg->short_name = short_name;
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *dynamic_cast<BoolArgument*>(arg);
}

ArgumentParser::BoolArgument& ArgumentParser::ArgParser::AddFlag(char short_name, const char* long_name, const char* description) {
    BoolArgument* arg = new BoolArgument();
    arg->short_name = short_name;
    arg->long_name = long_name;
    arg->description = description;
    arguments.push_back(arg);
    return *dynamic_cast<BoolArgument*>(arg);
}

ArgumentParser::BoolArgument& ArgumentParser::ArgParser::AddFlag(const char* long_name) {
    BoolArgument* arg = new BoolArgument();
    arg->long_name = long_name;
    arguments.push_back(arg);
    return *dynamic_cast<BoolArgument*>(arg);
}

ArgumentParser::BoolArgument& ArgumentParser::ArgParser::AddFlag(const char* long_name, const char* description) {
    BoolArgument* arg = new BoolArgument();
    arg->long_name = long_name;
    arg->description = description;
    arguments.push_back(arg);
    return *dynamic_cast<BoolArgument*>(arg);
}

ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::Default(bool val) {
    value = val;
    is_default = true;
    return *this;
}

ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::StoreValue(bool& val) {
    is_store_value = true;
    if (is_default) {
        value = val;
    } else {
        val = true;
    }

    return* this;
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& name) {
    for (auto* argPtr : arguments) {
        if (auto* boolArg = dynamic_cast<BoolArgument*>(argPtr)) {
            if (boolArg->long_name == name) {
                return boolArg->value;
            }
        }
    }
    return false;
}

void ArgumentParser::ArgParser::AddHelp(char c, const char *string1, const char *string2) {

}

bool ArgumentParser::ArgParser::Help() {
    return true;
}

std::string ArgumentParser::ArgParser::HelpDescription() {
    return std::string();
}


