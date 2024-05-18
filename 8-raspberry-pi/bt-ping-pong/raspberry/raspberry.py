import bluetooth

def find_device(device_name):
    print(f"Scanning for Bluetooth devices with name {device_name}...")
    devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)

    for addr, name in devices:
        if name == device_name:
            print(f"Found device {name} with address {addr}")
            return addr

    print(f"Device {device_name} not found.")
    return None

def connect_bluetooth(address):
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((address, port))
    return sock

def main():
    address = find_device(device_name='RIGOBT')
    if address:
        sock = connect_bluetooth(address)

        try:
            while True:
                data = input("Enter data to send: ")
                if data.lower() == "exit":
                    break
                sock.send(data)
                received = sock.recv(1024)
                print(f"Received: {received.decode('utf-8')}")
        except KeyboardInterrupt:
            print("Disconnected")
        finally:
            sock.close()
    else:
        print("Device not found")

if __name__ == "__main__":
    main()
