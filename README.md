# Custom C++ Compiler

This is a custom C++ compiler that supports a set of predefined mathematical, string, and utility functions. The compiler is designed to process input code, perform lexical, syntax, and semantic analysis, and then execute the code. It supports basic operations and allows for function calls like `addInt`, `multInt`, etc.

## Features

- **Lexical Analysis**: Tokenizes the input code into keywords, operators, literals, and identifiers.
- **Syntax Analysis**: Parses the tokenized code into a valid syntax tree.
- **Semantic Analysis**: Checks for variable declarations, type mismatches, and undeclared variables.
- **Final Execution**: Executes the valid code and handles function calls like `addInt`, `multInt`, `absInt`, etc.
- **Function Support**: Supports over 50 predefined functions including mathematical operations, string manipulation, and utility functions.

### Supported Functions

Here are some of the supported functions:

- **Mathematical Functions**:
    - `addInt(int x, int y)`
    - `multInt(int x, int y)`
    - `divInt(int x, int y)`
    - `absInt(int number)`
    - `maxInteg(int x, int y)`
    - `minInteg(int x, int y)`

- **String Functions**:
    - `concat(string s1, string s2)`
    - `capitalize(string input)`
    - `title(string input)`
    - `swapCase(string input)`
    - `strCenter(string input, int width)`
    - `strLjust(string input, int width)`

- **Utility Functions**:
    - `isEven(int number)`
    - `isOdd(int number)`
    - `isPrime(int number)`
    - `factorial(int number)`
    - `gcd(int a, int b)`
    - `lcm(int a, int b)`

## Compilation and Execution

### Prerequisites

To compile and run the project, you need:
- **C++11** or later version of a C++ compiler (e.g., `g++`).
- **CMake** to build the project.

### Steps to Build and Run

1. **Clone the repository**:

    ```bash
    git clone https://github.com/yourusername/Custom-Compiler.git
    cd Custom-Compiler
    ```

2. **Build the compiler**:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the compiler**:

    The compiler takes an input file with C++ code and performs analysis and execution.

    ```bash
    ./compiler input_code.txt
    ```

### Example

Input (`input_code.txt`):

```cpp
int x = 9;
int y = 3;
int sum = addInt(x, y);
cout << sum;
```

Output:

```bash
12
```

### How it Works

1. **Lexical Analysis**: The input code is tokenized into keywords, operators, and variables.
2. **Syntax Analysis**: The tokens are parsed into a valid syntax structure.
3. **Semantic Analysis**: It checks for variable declarations, type mismatches, and undeclared variables.
4. **Execution**: The code is executed and the output is displayed.

### Error Handling

The compiler will throw errors in case of:
- **Syntax errors**: Invalid syntax or missing semicolons.
- **Semantic errors**: Undeclared variables or type mismatches.
- **Runtime errors**: Division by zero or invalid function calls.

## Contributing

If you would like to contribute to the project, please fork the repository, create a branch for your feature, and submit a pull request. We welcome improvements and new features!
