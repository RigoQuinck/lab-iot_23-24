const btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort();

// Scan for devices
btSerial.on('found', function (address, name) {
    console.log(`Found: ${name} (${address})`);

    if (name === 'RIGOBT') {
        btSerial.findSerialPortChannel(address, function (channel) {
            console.log(`Found serial port channel: ${channel}`);

            // Connect to the device
            btSerial.connect(address, channel, function () {
                console.log(`Connected to ${name} (${address})`);

                // Send data
                btSerial.write(Buffer.from('PING\n', 'utf-8'), function (err, bytesWritten) {
                    if (err) console.log(err);
                    console.log(`Sent ${bytesWritten} bytes`);
                });

                // Receive data
                btSerial.on('data', function (buffer) {
                    console.log(`Received: ${buffer.toString('utf-8')}`);
                });
            }, function () {
                console.log(`Cannot connect to ${name} (${address})`);
            });

            // Close the connection
            btSerial.close();
        }, function () {
            console.log(`No serial port channel found for ${name} (${address})`);
        });
    }
});

btSerial.inquire();

// Error handling
btSerial.on('failure', function (err) {
    console.log(`Bluetooth Serial Port Error: ${err}`);
});
