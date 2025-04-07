#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct Token {
    string type;
    string value;
};

bool isKeyword(const string& word) {
    static vector<string> keywords = {"int", "float", "bool", "string", "char", "double", "void"};
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

bool isFunction(const string& word) {
    static vector<string> functions = {
        "addInt", "multInt", "divInt", "addDouble", "multDouble", "divDouble", "maxInteg", "minInt", "absInt",
        "absDouble", "capitalize", "title", "swapCase", "concat", "isEven", "isOdd", "isPrime", "factorial", "gcd",
        "lcm", "reverseNumber", "isPalindrome", "isVowel", "countDigits", "sumOfDigits", "chr", "ord", "toBool",
        "toFloat"
    };
    return find(functions.begin(), functions.end(), word) != functions.end();
}

vector<Token> tokenize(const string& code) {
    vector<Token> tokens;
    regex tokenRegex(R"((\bint\b|\bfloat\b|\bdouble\b|\bbool\b|\bstring\b|\bchar\b|\bvoid\b)|([A-Za-z_][A-Za-z0-9_]*)|([0-9]+(?:\.[0-9]+)?)|(\"[^\"]*\")|([=;,()]))");
    auto words_begin = sregex_iterator(code.begin(), code.end(), tokenRegex);
    auto words_end = sregex_iterator();

    for (auto i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        if (match[1].matched) tokens.push_back({"KT", match[1]});
        else if (match[2].matched) {
            string val = match[2];
            if (isFunction(val)) tokens.push_back({"KT", val});
            else tokens.push_back({"ID", val});
        }
        else if (match[3].matched) tokens.push_back({"NUM", match[3]});
        else if (match[4].matched) tokens.push_back({"STR", match[4]});
        else if (match[5].matched) tokens.push_back({"OP", match[5]});
    }

    return tokens;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: lexer <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Cannot open input file!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    infile.close();

    vector<Token> tokens = tokenize(code);

    for (const auto& token : tokens) {
        cout << token.type << " : " << token.value << endl;
    }

    return 0;
}
