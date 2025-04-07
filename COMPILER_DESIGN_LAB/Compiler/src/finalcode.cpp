#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}


// ==== Function Definitions (1–30) ====

int addInt(int x, int y) { return x + y; }
string concat(string s1, string s2) { return s1 + s2; }
int multInt(int x, int y) { return x * y; }
double addDouble(double dx, double dy) { return dx + dy; }
double multDouble(double dx, double dy) { return dx * dy; }
int maxInteg(int x, int y) { return (x > y) ? x : y; }
double maxDouble(double dx, double dy) { return (dx > dy) ? dx : dy; }
int divInt(int x, int y) { return x / y; }
double divDouble(double dx, double dy) { return dx / dy; }
int minInt(int x, int y) { return (x < y) ? x : y; }
double minDouble(double dx, double dy) { return (dx < dy) ? dx : dy; }
int absInt(int number) { return (number < 0) ? -number : number; }
double absDouble(double number) { return (number < 0) ? -number : number; }
float absFloat(float number) { return (number < 0.0f) ? -number : number; }

bool allTrue(const vector<bool> &container)
{
    for (bool val : container)
    {
        if (!val)
            return false;
    }
    return true;
}

vector<unsigned char> toBytes(const string &input)
{
    vector<unsigned char> byteSequence;
    for (char c : input)
    {
        byteSequence.push_back(static_cast<unsigned char>(c));
    }
    return byteSequence;
}

string capitalize(const string &input)
{
    if (input.empty())
        return input;
    string result = input;
    result[0] = toupper(result[0]);
    for (size_t i = 1; i < result.length(); ++i)
        result[i] = tolower(result[i]);
    return result;
}

string title(const string &input)
{
    string result = input;
    bool cap = true;
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (isspace(result[i]))
            cap = true;
        else if (cap)
        {
            result[i] = toupper(result[i]);
            cap = false;
        }
        else
        {
            result[i] = tolower(result[i]);
        }
    }
    return result;
}

string swapCase(const string &input)
{
    string result = input;
    for (char &c : result)
    {
        if (islower(c))
            c = toupper(c);
        else if (isupper(c))
            c = tolower(c);
    }
    return result;
}

string strCenter(const string &input, size_t width, char fillchar = ' ')
{
    if (input.size() >= width)
        return input;
    size_t padding = width - input.size();
    size_t left = padding / 2;
    size_t right = padding - left;
    return string(left, fillchar) + input + string(right, fillchar);
}

string strLjust(const string &input, size_t width, char fillchar = ' ')
{
    if (input.size() >= width)
        return input;
    return input + string(width - input.size(), fillchar);
}

string strRjust(const string &input, size_t width, char fillchar = ' ')
{
    if (input.size() >= width)
        return input;
    return string(width - input.size(), fillchar) + input;
}

bool strStartsWith(const string &input, const string &prefix)
{
    return input.rfind(prefix, 0) == 0;
}

bool strEndsWith(const string &input, const string &suffix)
{
    if (suffix.size() > input.size())
        return false;
    return input.compare(input.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int strFind(const string &input, const string &substring)
{
    size_t pos = input.find(substring);
    return (pos == string::npos) ? -1 : (int)pos;
}

int strRFind(const string &input, const string &substring)
{
    size_t pos = input.rfind(substring);
    return (pos == string::npos) ? -1 : (int)pos;
}

int ord(char character)
{
    return static_cast<int>(character);
}

char chr(int unicode)
{
    return static_cast<char>(unicode);
}

bool toBool(int value)
{
    return value != 0;
}

// ==== Symbol Tables ====

unordered_map<string, int> intVars;
unordered_map<string, double> doubleVars;
unordered_map<string, float> floatVars;
unordered_map<string, string> stringVars;
unordered_map<string, bool> boolVars;

// ==== Helper Resolvers ====

bool isInt(const string &s)
{
    return !s.empty() && (isdigit(s[0]) || (s[0] == '-' && isdigit(s[1])));
}

bool isDouble(const string &s)
{
    return s.find('.') != string::npos;
}

int resolveInt(const string &token)
{
    if (isInt(token))
        return stoi(token);
    if (intVars.count(token))
        return intVars[token];
    throw runtime_error("Int variable '" + token + "' not declared.");
}

double resolveDouble(const string &token)
{
    if (isInt(token))
        return stod(token);
    if (doubleVars.count(token))
        return doubleVars[token];
    if (intVars.count(token))
        return intVars[token];
    throw runtime_error("Double variable '" + token + "' not declared.");
}

float resolveFloat(const string &token)
{
    if (isInt(token))
        return stof(token);
    if (floatVars.count(token))
        return floatVars[token];
    if (doubleVars.count(token))
        return doubleVars[token];
    throw runtime_error("Float variable '" + token + "' not declared.");
}

string resolveString(const string &token)
{
    if (token.front() == '"' && token.back() == '"')
        return token.substr(1, token.length() - 2);
    if (stringVars.count(token))
        return stringVars[token];
    throw runtime_error("String variable '" + token + "' not declared.");
}

pair<double, double> makeComplex(double real, double imag = 0.0)
{
    return make_pair(real, imag);
}

pair<int, int> divMod(int dividend, int divisor)
{
    return make_pair(dividend / divisor, dividend % divisor);
}

vector<pair<int, char>> enumerate(const string &s)
{
    vector<pair<int, char>> result;
    for (int i = 0; i < s.length(); ++i)
        result.push_back({i, s[i]});
    return result;
}

double toFloat(const string &value)
{
    return stod(value);
}

bool isEven(int number)
{
    return number % 2 == 0;
}

bool isOdd(int number)
{
    return number % 2 != 0;
}

bool isPrime(int number)
{
    if (number <= 1)
        return false;
    for (int i = 2; i * i <= number; ++i)
        if (number % i == 0)
            return false;
    return true;
}

int factorial(int number)
{
    int result = 1;
    for (int i = 1; i <= number; ++i)
        result *= i;
    return result;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

int reverseNumber(int number)
{
    int reversed = 0;
    while (number != 0)
    {
        reversed = reversed * 10 + number % 10;
        number /= 10;
    }
    return reversed;
}

bool isPalindrome(int number)
{
    return number == reverseNumber(number);
}

bool isVowel(char c)
{
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int countDigits(int number)
{
    int count = 0;
    do
    {
        number /= 10;
        count++;
    } while (number != 0);
    return count;
}

int sumOfDigits(int number)
{
    int sum = 0;
    while (number != 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

double celsiusToFahrenheit(double celsius)
{
    return (celsius * 9.0 / 5.0) + 32;
}

double fahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}

string strCopySim(const string &src)
{
    return src;
}

// ==== Execution ====

void processLine(const string &line)
{
    stringstream ss(line);
    string type, varName, eq, expr;
    ss >> type >> varName >> eq;
    getline(ss, expr);
    expr.erase(remove(expr.begin(), expr.end(), ';'), expr.end());

    // Handle cout << var;
    if (line.find("cout <<") == 0) {
        string var = line.substr(7); // after 'cout <<'
        var.erase(remove(var.begin(), var.end(), ';'), var.end());
        var.erase(remove_if(var.begin(), var.end(), ::isspace), var.end());

        if (intVars.count(var)) cout << intVars[var] << endl;
        else if (doubleVars.count(var)) cout << doubleVars[var] << endl;
        else if (floatVars.count(var)) cout << floatVars[var] << endl;
        else if (stringVars.count(var)) cout << stringVars[var] << endl;
        else if (boolVars.count(var)) cout << (boolVars[var] ? "true" : "false") << endl;
        else throw runtime_error("❌ Error: Variable '" + var + "' not declared.");
        return;
    }

    // Process function calls and store result in respective variables
    if (expr.find('(') != string::npos)
    {
        size_t start = expr.find("(");
        string funcName = expr.substr(0, start);
        funcName = trim(funcName);
        string args = expr.substr(start + 1, expr.find(")") - start - 1);
        vector<string> argList;
        stringstream argStream(args);
        string arg;
        while (getline(argStream, arg, ','))
        {
            arg.erase(remove_if(arg.begin(), arg.end(), ::isspace), arg.end());
            argList.push_back(arg);
        }

        // Dispatcher (Functions 1–30)
        if (funcName == "addInt")
            intVars[varName] = addInt(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        else if (funcName == "multInt")
            intVars[varName] = multInt(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        else if (funcName == "divInt")
            intVars[varName] = divInt(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        else if (funcName == "minInt")
            intVars[varName] = minInt(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        else if (funcName == "maxInteg")
            intVars[varName] = maxInteg(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        else if (funcName == "absInt")
            intVars[varName] = absInt(resolveInt(trim(argList[0])));
        else if (funcName == "absFloat")
            floatVars[varName] = absFloat(resolveFloat(trim(argList[0])));

        else if (funcName == "addDouble")
            doubleVars[varName] = addDouble(resolveDouble(trim(argList[0])), resolveDouble(trim(argList[1])));
        else if (funcName == "multDouble")
            doubleVars[varName] = multDouble(resolveDouble(trim(argList[0])), resolveDouble(trim(argList[1])));
        else if (funcName == "divDouble")
            doubleVars[varName] = divDouble(resolveDouble(trim(argList[0])), resolveDouble(trim(argList[1])));
        else if (funcName == "minDouble")
            doubleVars[varName] = minDouble(resolveDouble(trim(argList[0])), resolveDouble(trim(argList[1])));
        else if (funcName == "maxDouble")
            doubleVars[varName] = maxDouble(resolveDouble(trim(argList[0])), resolveDouble(trim(argList[1])));
        else if (funcName == "absDouble")
            doubleVars[varName] = absDouble(resolveDouble(trim(argList[0])));

        else if (funcName == "concat")
            stringVars[varName] = concat(resolveString(trim(argList[0])), resolveString(trim(argList[1])));
        else if (funcName == "capitalize")
            stringVars[varName] = capitalize(resolveString(trim(argList[0])));
        else if (funcName == "title")
            stringVars[varName] = title(resolveString(trim(argList[0])));
        else if (funcName == "swapCase")
            stringVars[varName] = swapCase(resolveString(trim(argList[0])));
        else if (funcName == "strCenter")
        {
            int width = resolveInt(trim(argList[1]));
            char fill = (argList.size() > 2) ? trim(argList[2])[1] : ' ';
            stringVars[varName] = strCenter(resolveString(trim(argList[0])), width, fill);
        }
        else if (funcName == "strLjust")
        {
            int width = resolveInt(trim(argList[1]));
            char fill = (argList.size() > 2) ? trim(argList[2])[1] : ' ';
            stringVars[varName] = strLjust(resolveString(trim(argList[0])), width, fill);
        }
        else if (funcName == "strRjust")
        {
            int width = resolveInt(trim(argList[1]));
            char fill = (argList.size() > 2) ? trim(argList[2])[1] : ' ';
            stringVars[varName] = strRjust(resolveString(trim(argList[0])), width, fill);
        }
        else if (funcName == "strStartsWith")
        {
            boolVars[varName] = strStartsWith(resolveString(trim(argList[0])), resolveString(trim(argList[1])));
        }
        else if (funcName == "strEndsWith")
        {
            boolVars[varName] = strEndsWith(resolveString(trim(argList[0])), resolveString(trim(argList[1])));
        }
        else if (funcName == "strFind")
        {
            intVars[varName] = strFind(resolveString(trim(argList[0])), resolveString(trim(argList[1])));
        }
        else if (funcName == "strRFind")
        {
            intVars[varName] = strRFind(resolveString(trim(argList[0])), resolveString(trim(argList[1])));
        }
        else if (funcName == "ord")
        {
            intVars[varName] = ord(resolveString(trim(argList[0]))[0]);
        }
        else if (funcName == "chr")
        {
            stringVars[varName] = string(1, chr(resolveInt(trim(argList[0]))));
        }
        else if (funcName == "toBool")
        {
            boolVars[varName] = toBool(resolveInt(trim(argList[0])));
        }
        else if (funcName == "complex")
        {
            double real = resolveDouble(trim(argList[0]));
            double imag = (argList.size() > 1) ? resolveDouble(trim(argList[1])) : 0.0;
            auto comp = makeComplex(real, imag);
        }
        else if (funcName == "divMod")
        {
            auto res = divMod(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        }
        else if (funcName == "enumerate")
        {
            auto result = enumerate(resolveString(trim(argList[0])));
            for (const auto &[i, ch] : result)
            {
                cout << i << ": " << ch << endl;
            }
        }
        else if (funcName == "toFloat")
        {
            doubleVars[varName] = toFloat(resolveString(trim(argList[0])));
        }
        else if (funcName == "isEven")
        {
            boolVars[varName] = isEven(resolveInt(trim(argList[0])));
        }
        else if (funcName == "isOdd")
        {
            boolVars[varName] = isOdd(resolveInt(trim(argList[0])));
        }
        else if (funcName == "isPrime")
        {
            boolVars[varName] = isPrime(resolveInt(trim(argList[0])));
        }
        else if (funcName == "factorial")
        {
            intVars[varName] = factorial(resolveInt(trim(argList[0])));
        }
        else if (funcName == "gcd")
        {
            intVars[varName] = gcd(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        }
        else if (funcName == "lcm")
        {
            intVars[varName] = lcm(resolveInt(trim(argList[0])), resolveInt(trim(argList[1])));
        }
        else if (funcName == "reverseNumber")
        {
            intVars[varName] = reverseNumber(resolveInt(trim(argList[0])));
        }
        else if (funcName == "isPalindrome")
        {
            boolVars[varName] = isPalindrome(resolveInt(trim(argList[0])));
        }
        else if (funcName == "isVowel")
        {
            boolVars[varName] = isVowel(resolveString(trim(argList[0]))[0]);
        }
        else if (funcName == "countDigits")
        {
            intVars[varName] = countDigits(resolveInt(trim(argList[0])));
        }
        else if (funcName == "sumOfDigits")
        {
            intVars[varName] = sumOfDigits(resolveInt(trim(argList[0])));
        }
        else if (funcName == "isLeapYear")
        {
            boolVars[varName] = isLeapYear(resolveInt(trim(argList[0])));
        }
        else if (funcName == "celsiusToFahrenheit")
        {
            doubleVars[varName] = celsiusToFahrenheit(resolveDouble(trim(argList[0])));
        }
        else if (funcName == "fahrenheitToCelsius")
        {
            doubleVars[varName] = fahrenheitToCelsius(resolveDouble(trim(argList[0])));
        }
        else if (funcName == "strCopy")
        {
            stringVars[varName] = strCopySim(resolveString(trim(argList[0])));
        }
        else
        {
            throw runtime_error("Function not supported: " + funcName);
        }
    }
    else
    {
        if (type == "int")
            intVars[varName] = resolveInt(trim(expr));
        else if (type == "double")
            doubleVars[varName] = resolveDouble(trim(expr));
        else if (type == "float")
            floatVars[varName] = resolveFloat(trim(expr));
        else if (type == "string")
            stringVars[varName] = resolveString(trim(expr));
        else if (type == "bool")
            boolVars[varName] = (expr == "true");
    }
}




// ==== Main ====

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: finalcode <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file)
    {
        cerr << "Cannot open input file.\n";
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        try
        {
            processLine(line);
        }
        catch (const exception &e)
        {
            cerr << "Runtime Error: " << e.what() << endl;
            return 1;
        }
    }

    return 0;
}
