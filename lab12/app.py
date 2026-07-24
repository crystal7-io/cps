from flask import Flask, jsonify, render_template
import serial, threading

PORT='COM16'  # Change to your COM port
ser=serial.Serial(PORT,9600,timeout=1)
gesture='Waiting...'

def reader():
    global gesture
    while True:
        if ser.in_waiting:
            gesture=ser.readline().decode(errors='ignore').strip()

threading.Thread(target=reader,daemon=True).start()
app=Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/gesture')
def g():
    return jsonify({'gesture':gesture})

app.run(debug=True, use_reloader=False)
