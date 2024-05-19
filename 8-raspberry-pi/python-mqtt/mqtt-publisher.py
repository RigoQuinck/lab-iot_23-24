import time
import paho.mqtt.client as mqtt
import json
import random

# Configurazione MQTT
MQTT_BROKER = "localhost"  # Sostituisci con l'indirizzo del tuo broker MQTT
MQTT_PORT = 1883
MQTT_TOPIC = "data"

# Funzione per connettersi al broker MQTT
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connesso al broker MQTT!")
    else:
        print(f"Errore di connessione. Codice: {rc}")

# Funzione principale
def main():
    # Creazione del client MQTT
    client = mqtt.Client()
    client.on_connect = on_connect

    # Connessione al broker MQTT
    client.connect(MQTT_BROKER, MQTT_PORT, 60)

    # Avvio del loop in background
    client.loop_start()

    try:
        while True:
            # Simulazione della raccolta dei dati
            temperature = round(random.uniform(20.0, 25.0), 2)
            humidity = round(random.uniform(30.0, 50.0), 2)
            
            # Creazione del payload JSON
            payload = {
                "temperature": temperature,
                "humidity": humidity
            }

            # Conversione del payload in stringa JSON
            payload_str = json.dumps(payload)

            # Pubblicazione dei dati sul topic MQTT
            client.publish(MQTT_TOPIC, payload_str)
            print(f"Dati pubblicati: {payload_str}")

            # Attesa di 5 secondi prima di pubblicare nuovamente
            time.sleep(5)

    except KeyboardInterrupt:
        print("Interruzione del programma")
    finally:
        # Disconnessione dal broker MQTT
        client.loop_stop()
        client.disconnect()

if __name__ == "__main__":
    main()
