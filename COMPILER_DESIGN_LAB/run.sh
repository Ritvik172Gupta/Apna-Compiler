#!/bin/bash
echo "🔨 Building Compiler..."
cd Compiler
make

echo "🚀 Launching Web UI..."
cd ../UI
python3 app.py
