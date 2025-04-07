from flask import Flask, render_template, request, jsonify
from compiler_engine.compile import compile_code


app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/readme')
def readme():
    return render_template('readme.html')

@app.route('/run', methods=['POST'])
def run_code():
    code = request.json.get('code', '')
    output = compile_code(code)
    return jsonify({'output': output})


if __name__ == '__main__':
    app.run(debug=True)
