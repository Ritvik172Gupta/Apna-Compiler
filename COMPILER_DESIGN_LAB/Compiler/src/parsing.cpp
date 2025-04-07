#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
using namespace std;

// Token types
enum TokenType
{
    TYPE,
    ID,
    ASSIGN,
    SEMICOLON,
    NUMBER,
    LPAREN,
    RPAREN,
    COMMA,
    FUNC_ID,
    STRING_LITERAL,
    COUT,
    SHIFT,
    END
};

struct Token
{
    TokenType type;
    string value;
};

vector<Token> tokens;
int current = 0;

bool match(TokenType expected)
{
    if (current < tokens.size() && tokens[current].type == expected)
    {
        cout << "[Matched] " << tokens[current].value << endl;
        current++;
        return true;
    }
    cout << "[Expected] " << expected << ", Got: " << tokens[current].value << endl;
    return false;
}

Token peek()
{
    return (current < tokens.size()) ? tokens[current] : Token{END, ""};
}

void error(const string &msg)
{
    throw runtime_error("❌ Syntax Error: " + msg);
}

// Forward declarations
void program();
void stmt_list();
void stmt();
void decl_stmt();
void assign_stmt();
void cout_stmt();
void func_call();
void arg_list();
void arg_tail();
void expr();

void program()
{
    stmt_list();
}

void stmt_list()
{
    while (peek().type != END)
    {
        cout << "[stmt_list] Parsing new statement..." << endl;
        stmt();
    }
}

void stmt()
{
    cout << "[stmt] Current token: " << peek().value << endl;
    if (peek().type == TYPE)
    {
        if (current + 4 < tokens.size() &&
            tokens[current + 1].type == ID &&
            tokens[current + 2].type == ASSIGN &&
            tokens[current + 3].type == ID &&
            tokens[current + 4].type == LPAREN)
        {
            assign_stmt(); // TYPE ID = FUNC(...);
        }
        else
        {
            decl_stmt();
        }
    }
    else if (peek().type == COUT)
    {
        cout_stmt();
    }
    else
    {
        error("Invalid structure in input.");
    }
}

void decl_stmt()
{
    if (!match(TYPE))
        error("Expected type");
    if (!match(ID))
        error("Expected identifier");
    if (!match(ASSIGN))
        error("Expected '='");
    expr();
    if (!match(SEMICOLON))
        error("Expected ';'");
}

void assign_stmt()
{
    if (!match(TYPE))
        error("Expected type");
    if (!match(ID))
        error("Expected identifier");
    if (!match(ASSIGN))
        error("Expected '='");
    func_call();
    if (!match(SEMICOLON))
        error("Expected ';'");
}

void cout_stmt()
{
    if (!match(COUT))
        error("Expected 'cout'");
    if (!match(SHIFT))
        error("Expected '<<'");
    if (!match(ID))
        error("Expected identifier after '<<'");
    if (!match(SEMICOLON))
        error("Expected ';'");
}

void func_call()
{
    if (!match(ID))
        error("Expected function name");
    if (!match(LPAREN))
        error("Expected '('");
    if (peek().type != RPAREN)
        arg_list();
    if (!match(RPAREN))
        error("Expected ')'");
}

void arg_list()
{
    expr();
    arg_tail();
}

void arg_tail()
{
    while (match(COMMA))
    {
        expr();
    }
}

void expr()
{
    Token t = peek();
    if (t.type == ID || t.type == NUMBER || t.type == STRING_LITERAL)
    {
        current++;
    }
    else
    {
        error("Expected ID, number, or string literal in expression");
    }
}

vector<Token> tokenize(const string &line)
{
    vector<Token> result;
    vector<regex> patterns = {
        regex(R"(\b(int|float|double|string|bool)\b)"), // TYPE
        regex(R"(\bcout\b)"),                           // COUT
        regex(R"(<<)"),                                 // SHIFT
        regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"),             // ID / FUNC_ID
        regex(R"(=)"),                                  // ASSIGN
        regex(R"(;)"),                                  // SEMICOLON
        regex(R"([0-9]+)"),                             // NUMBER
        regex(R"(\()"),                                 // LPAREN
        regex(R"(\))"),                                 // RPAREN
        regex(R"(,)"),                                  // COMMA
        regex(R"("[^"]*")")                             // STRING_LITERAL
    };

    smatch m;
    string s = line;
    while (!s.empty())
    {
        bool matched = false;
        s = regex_replace(s, regex("^\\s+"), ""); // strip leading whitespace
        if (s.empty())
            continue; // skip blank lines entirely

        for (int i = 0; i < patterns.size(); ++i)
        {
            if (regex_search(s, m, patterns[i], regex_constants::match_continuous))
            {
                string tok = m.str();
                switch (i)
                {
                case 0:
                    result.push_back({TYPE, tok});
                    break;
                case 1:
                    result.push_back({COUT, tok});
                    break;
                case 2:
                    result.push_back({SHIFT, tok});
                    break;
                case 3:
                    result.push_back({ID, tok});
                    break;
                case 4:
                    result.push_back({ASSIGN, tok});
                    break;
                case 5:
                    result.push_back({SEMICOLON, tok});
                    break;
                case 6:
                    result.push_back({NUMBER, tok});
                    break;
                case 7:
                    result.push_back({LPAREN, tok});
                    break;
                case 8:
                    result.push_back({RPAREN, tok});
                    break;
                case 9:
                    result.push_back({COMMA, tok});
                    break;
                case 10:
                    result.push_back({STRING_LITERAL, tok});
                    break;
                }
                s = m.suffix();
                matched = true;
                break;
            }
        }
        if (!matched)
        {
            cerr << "Remaining unparsed input: '" << s << "'" << endl;
            throw runtime_error("❌ Unknown token in input: " + s);
        }
    }
    result.push_back({END, ""});
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: parser <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file)
    {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();

    try
    {
        tokens.clear();
        stringstream ss(code);
        string line;
        while (getline(ss, line))
        {
            vector<Token> lineTokens = tokenize(line);
            tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end() - 1); // remove duplicate END token
        }
        tokens.push_back({END, ""}); // add final END

        cout << "Tokens:\n";
        for (const auto &t : tokens)
        {
            cout << t.value << " (type=" << t.type << ")\n";
        }
        program();
        cout << "✅ Syntax Valid" << endl;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}