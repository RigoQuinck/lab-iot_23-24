from flask import Flask, jsonify
import paho.mqtt.client as mqtt
import multiprocessing
import json

app = Flask(__name__)

# Configurazione MQTT
MQTT_BROKER = "localhost"
MQTT_PORT = 1883
MQTT_TOPIC = "data"

def on_connect(client, userdata, flags, rc):
    print(f"Connesso al broker MQTT con codice {rc}")
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    try:
        data = json.loads(msg.payload.decode())
        print(f"Dati aggiornati: {data}")
        userdata['data'].update(data)
    except json.JSONDecodeError:
        print("Errore nel decodificare il messaggio MQTT")

def mqtt_loop(shared_data):
    mqtt_client = mqtt.Client(userdata={'data': shared_data})
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message
    mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
    mqtt_client.loop_forever()

@app.route('/data', methods=['GET'])
def get_data():
    global shared_data
    return jsonify(shared_data.copy())  # Copia dei dati per evitare problemi di concorrenza

def run_flask(shared_data):
    shared_data = shared_data
    app.run(host='0.0.0.0', port=3000)

if __name__ == '__main__':
    manager = multiprocessing.Manager()
    shared_data = manager.dict()

    # Avvia il processo MQTT
    mqtt_process = multiprocessing.Process(target=mqtt_loop, args=(shared_data,))
    mqtt_process.start()

    # Avvia il server Flask
    run_flask(shared_data)

    # Termina il processo MQTT quando il server Flask si ferma
    mqtt_process.join()
