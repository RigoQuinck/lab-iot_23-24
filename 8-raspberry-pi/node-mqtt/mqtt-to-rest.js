const mqtt = require('mqtt');
const fastify = require('fastify');

let sensorData = {};

const startMqttClient = async () => {
    const client = mqtt.connect('mqtt://localhost:1883');

    client.on('connect', () => {
        console.log('Connesso al broker MQTT');
        client.subscribe('data', (err) => {
            if (err) {
                console.error('Errore nella sottoscrizione:', err);
            }
        });
    });
    
    client.on('message', (topic, message) => {
        try {
            sensorData = JSON.parse(message.toString());
            console.log('Dati ricevuti:', sensorData);
        } catch (e) {
            console.error('Errore nel parsing dei dati:', e);
        }
    });
    
    client.on('error', (err) => {
        console.error('Errore di connessione:', err);
        client.end();
    });
}

const startRestApi = async () => {
    const app = fastify({ logger: true })

    app.get('/data', async (request, reply) => {
        return sensorData;
    });

    await app.listen({host: '0.0.0.0', port: 3000})
};

const start = async () => {
    await Promise.all([
        startMqttClient(),
        startRestApi()
    ])
}

start()
