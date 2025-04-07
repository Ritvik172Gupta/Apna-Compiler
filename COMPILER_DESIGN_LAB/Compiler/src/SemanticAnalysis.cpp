#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

unordered_map<string, string> symbolTable; // var name -> type

bool is_number(const string& s) {
    return regex_match(s, regex("^-?[0-9]+(\\.[0-9]+)?$"));
}

bool is_string_literal(const string& s) {
    return s.size() >= 2 && s.front() == '"' && s.back() == '"';
}

bool is_identifier(const string& s) {
    return regex_match(s, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"));
}

bool is_bool_literal(const string& s) {
    return s == "true" || s == "false";
}

bool is_custom_function(const string& name) {
    static vector<string> funcs = {
        "addInt", "multInt", "divInt", "minInt", "maxInteg", "absInt",
        "addDouble", "multDouble", "divDouble", "minDouble", "maxDouble", "absDouble", "absFloat",
        "concat", "capitalize", "title", "swapCase", "strCenter", "strLjust", "strRjust",
        "strStartsWith", "strEndsWith", "strFind", "strRFind",
        "ord", "chr", "toBool", "toFloat",
        "complex", "divMod", "enumerate", "allTrue", "toBytes",
        "isEven", "isOdd", "isPrime", "factorial", "gcd", "lcm",
        "reverseNumber", "isPalindrome", "isVowel", "countDigits", "sumOfDigits",
        "isLeapYear", "celsiusToFahrenheit", "fahrenheitToCelsius", "strCopy"
    };
    return find(funcs.begin(), funcs.end(), name) != funcs.end();
}

string trim(const string& s) {
    size_t first = s.find_first_not_of(" \t\r\n");
    size_t last = s.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : s.substr(first, last - first + 1);
}

void error(const string& msg) {
    throw runtime_error("❌ Semantic Error: " + msg);
}

void analyze_line(const string& line) {
    string trimmed = trim(line);
    if (trimmed.empty()) return;

    if (trimmed.find("cout <<") == 0) {
        string var = trimmed.substr(7);
        var = regex_replace(var, regex(";|\\s"), "");
        if (!symbolTable.count(var)) error("Undeclared variable in cout: " + var);
        return;
    }

    smatch match;
    regex decl_assign("(int|float|double|string|bool)\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*=\\s*(.*);");

    if (regex_match(trimmed, match, decl_assign)) {
        string type = match[1];
        string var = trim(match[2]);
        string value = trim(match[3]);

        if (symbolTable.count(var)) error("Redeclaration of variable: " + var);

        if (value.find("(") != string::npos && value.back() == ')') {
            string fname = value.substr(0, value.find("("));
            fname = regex_replace(fname, regex("\\s+"), "");
            if (!is_custom_function(fname)) error("Unknown function: " + fname);

            // ✅ Trim arguments
            string args = value.substr(value.find("(") + 1);
            args.pop_back(); // remove trailing ')'
            stringstream ss(args);
            string arg;
            while (getline(ss, arg, ',')) {
                arg = trim(arg);  // ✅ TRIM added here!
                if (!regex_match(arg, regex(R"([0-9]+|\"[^\"]*\")")) && !symbolTable.count(arg)) {
                    error(type + " variable '" + arg + "' not declared.");
                }
            }

            symbolTable[var] = type;
            return;
        }

        if (type == "int" && is_number(value) && value.find('.') == string::npos) {
            symbolTable[var] = type;
        } else if ((type == "float" || type == "double") && is_number(value)) {
            symbolTable[var] = type;
        } else if (type == "string" && is_string_literal(value)) {
            symbolTable[var] = type;
        } else if (type == "bool" && is_bool_literal(value)) {
            symbolTable[var] = type;
        } else if (is_identifier(value) && symbolTable.count(value)) {
            if (symbolTable[value] != type)
                error("Type mismatch: cannot assign " + symbolTable[value] + " to " + type);
            symbolTable[var] = type;
        } else {
            error("Invalid assignment to " + type + " from value: " + value);
        }
    } else {
        error("Invalid syntax: " + trimmed);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: semantic <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }

    string line;
    try {
        while (getline(file, line)) {
            analyze_line(line);
        }
        cout << "✅ Semantic Valid" << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
