import bluetooth
import asyncio
import time

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


class DataReceiver:
    def __init__(self, sock):
        self.buffer: str = ""
        self.sock = sock

    async def receive_data(self):
        data = self.sock.recv(1024).decode('utf-8')
        self.buffer += data

        while '\n' in self.buffer:
            line, self.buffer = self.buffer.split('\n', 1)
            if line:
                data = line.strip()
                print(f"Received {data}")

async def send_data(sock):
    ts = time.time()
    sock.send(f"Raspi timestamp: {ts}\n")
    await asyncio.sleep(5) # wait 5 seconds

async def main():
    device_name = 'RIGOBT'
    address = find_device(device_name)
    if address:
        sock = connect_bluetooth(address)
        if sock:
            try:
                receiver = DataReceiver(sock)
                while True:
                    await send_data(sock)
                    await receiver.receive_data()
            except KeyboardInterrupt:
                print("Disconnected")
            finally:
                sock.close()
        else:
            print("Could not connect to the device.")
    else:
        print(f"Device {device_name} not found.")

if __name__ == "__main__":
    asyncio.run(main())
