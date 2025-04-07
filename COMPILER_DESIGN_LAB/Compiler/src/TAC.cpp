#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Structure for Three Address Code (TAC)
struct Quad {
    string op;
    string arg1;
    string arg2;
    string result;
};

vector<Quad> code;
int tempVarCount = 0;

// Utility to generate new temporary variable
string newTemp() {
    return "t" + to_string(++tempVarCount);
}

// ─────────────────────────────
// 1. int addInt(int x, int y)
void generateAddInt(string x, string y) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", x, "", t1 });
    code.push_back({ "=", y, "", t2 });
    code.push_back({ "+", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 2. double addDouble(double dx, double dy)
void generateAddDouble(string dx, string dy) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", dx, "", t1 });
    code.push_back({ "=", dy, "", t2 });
    code.push_back({ "+", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 3. string concat(string s1, string s2)
void generateConcat(string s1, string s2) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", s1, "", t1 });
    code.push_back({ "=", s2, "", t2 });
    code.push_back({ "concat", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 4. int multInt(int x, int y)
void generateMultInt(string x, string y) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", x, "", t1 });
    code.push_back({ "=", y, "", t2 });
    code.push_back({ "*", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 5. double multDouble(double dx, double dy)
void generateMultDouble(string dx, string dy) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", dx, "", t1 });
    code.push_back({ "=", dy, "", t2 });
    code.push_back({ "*", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 6. maxInteg(int x, int y)
void generateMaxInt(string x, string y) {
    string t = newTemp();
    string L1 = "L" + to_string(tempVarCount + 1);
    string L2 = "L" + to_string(tempVarCount + 2);
    code.push_back({ "if>", x, y, L1 });
    code.push_back({ "=", y, "", t });
    code.push_back({ "goto", "", "", L2 });
    code.push_back({ "label", "", "", L1 });
    code.push_back({ "=", x, "", t });
    code.push_back({ "label", "", "", L2 });
    code.push_back({ "return", "", "", t });
}

// 7. maxDouble(double dx, double dy)
void generateMaxDouble(string dx, string dy) {
    generateMaxInt(dx, dy); // same logic
}

// 8. divInt(int x, int y)
void generateDivInt(string x, string y) {
    string t1 = newTemp();
    string t2 = newTemp();
    string t3 = newTemp();
    code.push_back({ "=", x, "", t1 });
    code.push_back({ "=", y, "", t2 });
    code.push_back({ "/", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 9. divDouble(double dx, double dy)
void generateDivDouble(string dx, string dy) {
    generateDivInt(dx, dy); // same structure
}

// 10. minInt(int x, int y)
void generateMinInt(string x, string y) {
    string t = newTemp();
    string L1 = "L" + to_string(tempVarCount + 1);
    string L2 = "L" + to_string(tempVarCount + 2);
    code.push_back({ "if<", x, y, L1 });
    code.push_back({ "=", y, "", t });
    code.push_back({ "goto", "", "", L2 });
    code.push_back({ "label", "", "", L1 });
    code.push_back({ "=", x, "", t });
    code.push_back({ "label", "", "", L2 });
    code.push_back({ "return", "", "", t });
}

// 11. minDouble(double dx, double dy)
void generateMinDouble(string dx, string dy) {
    generateMinInt(dx, dy); // same logic as minInt
}

// 12. absInt(int number)
void generateAbsInt(string number) {
    string t = newTemp();
    string L1 = "L" + to_string(tempVarCount + 1);
    string L2 = "L" + to_string(tempVarCount + 2);
    code.push_back({ "if<", number, "0", L1 });
    code.push_back({ "=", number, "", t });
    code.push_back({ "goto", "", "", L2 });
    code.push_back({ "label", "", "", L1 });
    code.push_back({ "*", number, "-1", t });
    code.push_back({ "label", "", "", L2 });
    code.push_back({ "return", "", "", t });
}

// 13. absDouble(double number)
void generateAbsDouble(string number) {
    generateAbsInt(number); // same logic
}

// 14. absFloat(float number)
void generateAbsFloat(string number) {
    generateAbsInt(number); // same logic
}

// 15. allTrue(const Iterable &container)
// Simulated: checks if all elements are true
void generateAllTrue(string container) {
    string temp = newTemp();
    string loop = "L" + to_string(tempVarCount + 1);
    string exit = "L" + to_string(tempVarCount + 2);
    string t = newTemp(); // result holder
    code.push_back({ "label", "", "", loop });
    code.push_back({ "next", container, "", temp });        // temp = next(container)
    code.push_back({ "if==", temp, "null", exit });         // if temp == null goto exit
    code.push_back({ "if==", temp, "false", exit });        // if temp == false goto exit
    code.push_back({ "goto", "", "", loop });
    code.push_back({ "label", "", "", exit });
    code.push_back({ "=", "true", "", t });
    code.push_back({ "return", "", "", t });
}

// 16. toBytes(const string &input)
void generateToBytes(string input) {
    string t = newTemp();
    code.push_back({ "toBytes", input, "", t });
    code.push_back({ "return", "", "", t });
}

// 17. capitalize(const string &input)
void generateCapitalize(string input) {
    string t1 = newTemp();
    string t2 = newTemp();
    code.push_back({ "charAt", input, "0", t1 });          // t1 = input[0]
    code.push_back({ "toUpper", t1, "", t1 });             // t1 = toupper(t1)
    code.push_back({ "slice", input, "1", t2 });           // t2 = input[1:]
    code.push_back({ "toLower", t2, "", t2 });             // t2 = tolower(t2)
    string result = newTemp();
    code.push_back({ "concat", t1, t2, result });
    code.push_back({ "return", "", "", result });
}

// 18. title(const string &input)
void generateTitle(string input) {
    string t = newTemp();
    code.push_back({ "titleCase", input, "", t });         // simulate built-in
    code.push_back({ "return", "", "", t });
}

// 19. swapCase(const string &input)
void generateSwapCase(string input) {
    string t = newTemp();
    code.push_back({ "swapCase", input, "", t });          // simulate built-in
    code.push_back({ "return", "", "", t });
}

// 20. strCenter(const string &input, size_t width, char fillchar)
void generateStrCenter(string input, string width, string fillchar = "' '") {
    string t = newTemp();
    code.push_back({ "center", input, width + "," + fillchar, t });
    code.push_back({ "return", "", "", t });
}

// 21. strLjust(input, width, fillchar)
void generateStrLjust(string input, string width, string fillchar = "' '") {
    string t = newTemp();
    code.push_back({ "ljust", input, width + "," + fillchar, t });
    code.push_back({ "return", "", "", t });
}

// 22. strRjust(input, width, fillchar)
void generateStrRjust(string input, string width, string fillchar = "' '") {
    string t = newTemp();
    code.push_back({ "rjust", input, width + "," + fillchar, t });
    code.push_back({ "return", "", "", t });
}

// 23. strStartsWith(input, prefix)
void generateStrStartsWith(string input, string prefix) {
    string t = newTemp();
    code.push_back({ "startsWith", input, prefix, t });
    code.push_back({ "return", "", "", t });
}

// 24. strEndsWith(input, suffix)
void generateStrEndsWith(string input, string suffix) {
    string t = newTemp();
    code.push_back({ "endsWith", input, suffix, t });
    code.push_back({ "return", "", "", t });
}

// 25. strFind(input, substring)
void generateStrFind(string input, string substring) {
    string t = newTemp();
    code.push_back({ "find", input, substring, t });
    code.push_back({ "return", "", "", t });
}

// 26. strRFind(input, substring)
void generateStrRFind(string input, string substring) {
    string t = newTemp();
    code.push_back({ "rfind", input, substring, t });
    code.push_back({ "return", "", "", t });
}

// 27. ord(character)
void generateOrd(string character) {
    string t = newTemp();
    code.push_back({ "ord", character, "", t });
    code.push_back({ "return", "", "", t });
}

// 28. map(iterable, function)
void generateMap(string iterable, string function) {
    string t = newTemp();
    code.push_back({ "map", iterable, function, t });
    code.push_back({ "return", "", "", t });
}

// 29. toBool(value)
void generateToBool(string value) {
    string t = newTemp();
    code.push_back({ "toBool", value, "", t });
    code.push_back({ "return", "", "", t });
}

// 30. chr(unicode)
void generateChr(string unicode) {
    string t = newTemp();
    code.push_back({ "chr", unicode, "", t });
    code.push_back({ "return", "", "", t });
}

// 31. complex(real, imag)
void generateComplex(string real, string imag = "0.0") {
    string t = newTemp();
    code.push_back({ "complex", real, imag, t });
    code.push_back({ "return", "", "", t });
}

// 32. divMod(dividend, divisor)
void generateDivMod(string dividend, string divisor) {
    string t1 = newTemp(); // quotient
    string t2 = newTemp(); // remainder
    string t3 = newTemp(); // pair
    code.push_back({ "/", dividend, divisor, t1 });
    code.push_back({ "%", dividend, divisor, t2 });
    code.push_back({ "pair", t1, t2, t3 });
    code.push_back({ "return", "", "", t3 });
}

// 33. enumerate(iterable)
void generateEnumerate(string iterable) {
    string t = newTemp();
    code.push_back({ "enumerate", iterable, "", t });
    code.push_back({ "return", "", "", t });
}

// 34. filter(iterable, predicate)
void generateFilter(string iterable, string predicate) {
    string t = newTemp();
    code.push_back({ "filter", iterable, predicate, t });
    code.push_back({ "return", "", "", t });
}

// 35. toFloat(value)
void generateToFloat(string value) {
    string t = newTemp();
    code.push_back({ "toFloat", value, "", t });
    code.push_back({ "return", "", "", t });
}

// 36. isEven(number)
void generateIsEven(string number) {
    string t = newTemp();
    code.push_back({ "%", number, "2", t });
    string result = newTemp();
    code.push_back({ "==", t, "0", result });
    code.push_back({ "return", "", "", result });
}

// 37. isOdd(number)
void generateIsOdd(string number) {
    string t = newTemp();
    code.push_back({ "%", number, "2", t });
    string result = newTemp();
    code.push_back({ "==", t, "1", result });
    code.push_back({ "return", "", "", result });
}

// 38. isPrime(number)
void generateIsPrime(string number) {
    string result = newTemp();
    code.push_back({ "isPrime", number, "", result });
    code.push_back({ "return", "", "", result });
}

// 39. factorial(number)
void generateFactorial(string number) {
    string result = newTemp();
    code.push_back({ "factorial", number, "", result });
    code.push_back({ "return", "", "", result });
}

// 40. gcd(a, b)
void generateGCD(string a, string b) {
    string result = newTemp();
    code.push_back({ "gcd", a, b, result });
    code.push_back({ "return", "", "", result });
}

// 41. lcm(a, b)
void generateLCM(string a, string b) {
    string mul = newTemp();
    string gcd = newTemp();
    string result = newTemp();
    code.push_back({ "*", a, b, mul });
    code.push_back({ "gcd", a, b, gcd });
    code.push_back({ "/", mul, gcd, result });
    code.push_back({ "return", "", "", result });
}

// 42. reverseNumber(number)
void generateReverseNumber(string number) {
    string result = newTemp();
    code.push_back({ "reverse", number, "", result });
    code.push_back({ "return", "", "", result });
}

// 43. isPalindrome(number)
void generateIsPalindrome(string number) {
    string rev = newTemp();
    string cmp = newTemp();
    code.push_back({ "reverse", number, "", rev });
    code.push_back({ "==", number, rev, cmp });
    code.push_back({ "return", "", "", cmp });
}

// 44. isVowel(c)
void generateIsVowel(string c) {
    string result = newTemp();
    code.push_back({ "isVowel", c, "", result });
    code.push_back({ "return", "", "", result });
}

// 45. countDigits(number)
void generateCountDigits(string number) {
    string result = newTemp();
    code.push_back({ "countDigits", number, "", result });
    code.push_back({ "return", "", "", result });
}

// 46. sumOfDigits(number)
void generateSumOfDigits(string number) {
    string result = newTemp();
    code.push_back({ "sumDigits", number, "", result });
    code.push_back({ "return", "", "", result });
}

// 47. isLeapYear(year)
void generateIsLeapYear(string year) {
    string result = newTemp();
    code.push_back({ "isLeap", year, "", result });
    code.push_back({ "return", "", "", result });
}

// 48. celsiusToFahrenheit(celsius)
void generateCelsiusToFahrenheit(string celsius) {
    string mul = newTemp();
    string add = newTemp();
    code.push_back({ "*", celsius, "9", mul });
    code.push_back({ "/", mul, "5", mul }); // mul = (celsius * 9) / 5
    code.push_back({ "+", mul, "32", add });
    code.push_back({ "return", "", "", add });
}

// 49. fahrenheitToCelsius(fahrenheit)
void generateFahrenheitToCelsius(string fahrenheit) {
    string sub = newTemp();
    string mul = newTemp();
    code.push_back({ "-", fahrenheit, "32", sub });
    code.push_back({ "*", sub, "5", mul });
    code.push_back({ "/", mul, "9", mul }); // final result in mul
    code.push_back({ "return", "", "", mul });
}

// 50. strCopy(destination, source)
void generateStrCopy(string dest, string src) {
    code.push_back({ "strCopy", src, "", dest });
    code.push_back({ "return", "", "", dest });
}

void runTACGeneration(vector<string> functionCalls) {
    for (const string& func : functionCalls) {
        if (func == "addInt") generateAddInt("x", "y");
        else if (func == "addDouble") generateAddDouble("dx", "dy");
        else if (func == "concat") generateConcat("s1", "s2");
        else if (func == "multInt") generateMultInt("x", "y");
        else if (func == "multDouble") generateMultDouble("dx", "dy");
        else if (func == "maxInteg") generateMaxInt("x", "y");
        else if (func == "maxDouble") generateMaxDouble("dx", "dy");
        else if (func == "divInt") generateDivInt("x", "y");
        else if (func == "divDouble") generateDivDouble("dx", "dy");
        else if (func == "minInt") generateMinInt("x", "y");
        else if (func == "minDouble") generateMinDouble("dx", "dy");
        else if (func == "absInt") generateAbsInt("n");
        else if (func == "absDouble") generateAbsDouble("dval");
        else if (func == "absFloat") generateAbsFloat("fval");
        else if (func == "allTrue") generateAllTrue("myList");
        else if (func == "toBytes") generateToBytes("s");
        else if (func == "capitalize") generateCapitalize("word");
        else if (func == "title") generateTitle("hello world");
        else if (func == "swapCase") generateSwapCase("SwAp123");
        else if (func == "strCenter") generateStrCenter("C++", "20", "'-'");
        else if (func == "strLjust") generateStrLjust("msg", "15", "'*'");
        else if (func == "strRjust") generateStrRjust("msg", "15", "'_'");
        else if (func == "strStartsWith") generateStrStartsWith("sentence", "sent");
        else if (func == "strEndsWith") generateStrEndsWith("sentence", "ence");
        else if (func == "strFind") generateStrFind("data", "a");
        else if (func == "strRFind") generateStrRFind("data", "a");
        else if (func == "ord") generateOrd("'A'");
        else if (func == "map") generateMap("list", "square");
        else if (func == "toBool") generateToBool("num");
        else if (func == "chr") generateChr("65");
        else if (func == "complex") generateComplex("real", "imag");
        else if (func == "divMod") generateDivMod("a", "b");
        else if (func == "enumerate") generateEnumerate("myList");
        else if (func == "filter") generateFilter("nums", "isEven");
        else if (func == "toFloat") generateToFloat("strVal");
        else if (func == "isEven") generateIsEven("n");
        else if (func == "isOdd") generateIsOdd("n");
        else if (func == "isPrime") generateIsPrime("n");
        else if (func == "factorial") generateFactorial("n");
        else if (func == "gcd") generateGCD("a", "b");
        else if (func == "lcm") generateLCM("a", "b");
        else if (func == "reverseNumber") generateReverseNumber("n");
        else if (func == "isPalindrome") generateIsPalindrome("n");
        else if (func == "isVowel") generateIsVowel("c");
        else if (func == "countDigits") generateCountDigits("n");
        else if (func == "sumOfDigits") generateSumOfDigits("n");
        else if (func == "isLeapYear") generateIsLeapYear("year");
        else if (func == "celsiusToFahrenheit") generateCelsiusToFahrenheit("tempC");
        else if (func == "fahrenheitToCelsius") generateFahrenheitToCelsius("tempF");
        else if (func == "strCopy") generateStrCopy("dest", "src");
    }

    writeTACToFile();
}


// ─────────────────────────────
// Display all TAC instructions
void writeTACToFile(const string& filename = "output.tac") {
    ofstream out(filename);
    for (const auto& q : code) {
        if (q.op == "return") {
            out << "return " << q.result << endl;
        } else if (q.op == "=") {
            out << q.result << " = " << q.arg1 << endl;
        } else if (q.op == "concat") {
            out << q.result << " = " << q.arg1 << " ++ " << q.arg2 << endl;
        } else if (q.op == "label") {
            out << q.result << ":" << endl;
        } else if (q.op == "goto") {
            out << "goto " << q.result << endl;
        } else if (q.op == "if>" || q.op == "if<") {
            out << "if " << q.arg1 << " " << q.op.substr(2) << " " << q.arg2 << " goto " << q.result << endl;
        } else {
            out << q.result << " = " << q.arg1 << " " << q.op << " " << q.arg2 << endl;
        }
    }
    out.close();
}


// ─────────────────────────────
// Main
int main() {
    vector<string> allFuncs = {
        "addInt", "addDouble", "concat", "multInt", "multDouble",
        "maxInteg", "maxDouble", "divInt", "divDouble", "minInt",
        "minDouble", "absInt", "absDouble", "absFloat", "allTrue",
        "strLjust", "strRjust", "strStartsWith", "strEndsWith", "strFind",
        "strRFind", "ord", "map", "toBool", "chr", "complex", "divMod",
        "enumerate", "filter", "toFloat", "isEven", "isOdd", "isPrime",
        "factorial", "gcd", "lcm", "reverseNumber", "isPalindrome",
        "isVowel", "countDigits", "sumOfDigits", "isLeapYear",
        "celsiusToFahrenheit", "fahrenheitToCelsius", "strCopy"
    };
    runTACGeneration(allFuncs);
    return 0;
}

