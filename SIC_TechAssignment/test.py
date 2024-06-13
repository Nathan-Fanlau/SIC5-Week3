from flask import Flask, request

app = Flask(__name__)

table = []

@app.route('/temperature', methods=['POST'])
def temperature():
    data = request.get_json()
    temperature = data['temperature']
    humidity = data['humidity']
    subTable = [temperature, humidity]
    table.append(subTable)
    return "status: success", 200

@app.route('/temperature', methods=['GET'])
def get():
    return table

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)