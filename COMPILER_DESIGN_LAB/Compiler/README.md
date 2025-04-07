
## 🧠Custom C++ Compiler + Web UI

This project is a single-pass C++ compiler that extends C++ with Python-like functions such as `map()`, `chr()`, `title()`, `allTrue()` etc. It includes all major stages of compilation and integrates a modern Flask-based UI for interactive usage.

---

### 🗂️ Project Structure

```
COMPILER DESIGN LAB/
├── Compiler/
│   ├── src/               # All compiler phase files (*.cpp)
│   ├── bin/               # Compiled binaries
│   ├── Makefile           # Compilation instructions
│   └── README.md          # Compiler usage docs
├── UI/
│   ├── app.py             # Flask server
│   ├── compiler_engine/
│   │   └── compile.py     # Calls compiled backend
│   ├── static/            # JS + CSS
│   ├── templates/         # HTML frontend
│   └── requirements.txt   # Python dependencies
├── run.sh                 # Build + Launch Script
```

---

## 🔧 Compiler Features

- ✅ **Lexical Analysis**  
- ✅ **Syntax Parsing** (SLR(1))
- ✅ **Semantic Analysis + Symbol Table**
- ✅ **Three Address Code Generation**
- ✅ **Final C++ Code Generation**
- ✅ **50+ Predefined Python-like Functions**

---

## 🚀 How to Run

### Step 1: Compile the Compiler

```bash
cd Compiler
make
```

### Step 2: Launch the Web UI

```bash
cd ../UI
python3 app.py
```

### 🔁 OR simply

```bash
./run.sh
```

---

## 🌐 Web UI Features

- Beautiful, minimal interface
- Submit custom code snippets using the new language
- View generated C++ code
- Learn syntax from embedded Readme/manual
- Real-time output and error display

---

## 🧪 Sample Function

```cpp
// Sample custom function
int addInt(int x, int y);
```

You can use this in your compiler UI like:
```cpp
addInt(5, 10);
```

---

## 📦 Python Dependencies

Install all required packages with:

```bash
pip install -r UI/requirements.txt
```

---

## 📂 Output Files

- Final generated code: `Compiler/finalcode.cpp`
- Intermediate output (TAC): `Compiler/TAC.cpp`
- Symbol table (console dump)
- Output is displayed in UI as well

---

## 🧑‍💻 Developer Notes

- Make sure all `.cpp` files are placed in `Compiler/src`
- Use the UI's Readme tab for syntax guidelines
- Template support is enabled for functions like:
```cpp
template <typename T>
T maxFunc(T a, T b);
```

---

## 📌 Future Scope

- Add code optimization phase
- Support file-level compilation (not just snippets)
- Expand to support object-oriented constructs

