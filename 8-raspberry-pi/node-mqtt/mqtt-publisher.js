const mqtt = require('mqtt');
const client = mqtt.connect('mqtt://localhost:1883'); // Sostituisci con l'indirizzo del tuo broker MQTT

client.on('connect', () => {
    console.log('Connesso al broker MQTT');
    
    setInterval(() => {
        const temperature = (Math.random() * 5 + 20).toFixed(2);
        const humidity = (Math.random() * 20 + 30).toFixed(2);
        const payload = JSON.stringify({ temperature, humidity });

        client.publish('data', payload, () => {
            console.log(`Dati pubblicati: ${payload}`);
        });
    }, 5000); // Pubblica ogni 5 secondi
});

client.on('error', (err) => {
    console.error('Errore di connessione:', err);
    client.end();
});
