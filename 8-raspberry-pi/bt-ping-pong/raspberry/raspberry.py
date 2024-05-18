import bluetooth

def find_device(device_name):
    print("Scanning for Bluetooth devices...")
    devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)

    if devices:
        print(f"Found {len(devices)} devices:")
        for addr, name in devices:
            print(f"  {name} - {addr}")
            if name == device_name:
                print(f"Device {device_name} found with address {addr}")
                return addr
    else:
        print("No devices found.")
    return None

def connect_bluetooth(address):
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    try:
        print(f"Connecting to {address}...")
        sock.connect((address, port))
        print("Connected successfully!")
        return sock
    except bluetooth.btcommon.BluetoothError as err:
        print(f"Failed to connect: {err}")
        return None

def main():
    device_name = 'RIGOBT'  # Replace with your HC-05 device name
    address = find_device(device_name)
    if address:
        sock = connect_bluetooth(address)
        if sock:
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
            print("Could not connect to the device.")
    else:
        print(f"Device {device_name} not found.")

if __name__ == "__main__":
    main()
