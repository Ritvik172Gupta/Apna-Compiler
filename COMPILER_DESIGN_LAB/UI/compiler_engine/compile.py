import os
import subprocess

def run_phase(label, exec_name, cpp_path, args=["input_code.txt"]):
    # Always compile with C++11
    compile_cmd = ["g++", "-std=c++11", "-o", exec_name, cpp_path]
    compile_result = subprocess.run(compile_cmd, capture_output=True, text=True)
    if compile_result.returncode != 0:
        return f"{label} Compilation Error:\n{compile_result.stderr}", False

    run_result = subprocess.run([f"./{exec_name}"] + args, capture_output=True, text=True)
    if run_result.returncode != 0:
        return f"{label} Execution Error:\n{run_result.stderr.strip()}", False

    return run_result.stdout.strip(), True

def compile_code(user_code):
    # Check that code ends in semicolon (not strict per-line anymore)
    if not user_code.strip().endswith(';'):
        return "❌ Error: Each statement must end with a semicolon (;)"

    # Write the entire user input into the file as-is
    with open("input_code.txt", "w") as f:
        f.write(user_code.strip())

    base_dir = os.path.abspath("../Compiler/src")

    outputs = []

    # Phase 1: Lexical Analysis
    out, ok = run_phase("Lexical Analysis", "lexer", os.path.join(base_dir, "LexicalAnalysis.cpp"))
    if not ok:
        return out

    # Phase 2: Syntax Analysis
    out, ok = run_phase("Syntax Analysis", "parser", os.path.join(base_dir, "Parsing.cpp"))
    if not ok:
        return out

    # Phase 3: Semantic Analysis
    out, ok = run_phase("Semantic Analysis", "semantic", os.path.join(base_dir, "SemanticAnalysis.cpp"))
    if not ok:
        return out

    # Phase 4: Final Code Execution
    out, ok = run_phase("Final Code Execution", "finalcode", os.path.join(base_dir, "finalcode.cpp"))
    if not ok:
        return out

    return out
