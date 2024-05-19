import paho.mqtt.client as mqtt
import json

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
    except json.JSONDecodeError:
        print("Errore nel decodificare il messaggio MQTT")

mqtt_client = mqtt.Client()
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message
mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)

if __name__ == '__main__':
    mqtt_client.loop_forever()
