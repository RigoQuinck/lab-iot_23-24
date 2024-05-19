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
    
buffer: str = ""
async def receive_data(sock):
    data = sock.recv(1024).decode('utf-8')
    buffer += data

    while '\n' in buffer:
        line, buffer = buffer.split('\n', 1)
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
                while True:
                    await send_data(sock)
                    await receive_data(sock)
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
