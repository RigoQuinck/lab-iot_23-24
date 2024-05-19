import asyncio
import bluetooth
from enum import Enum
from typing import Dict, Tuple, Any
import json

# Events
EventType = Enum('EventType', ['device_found','device_connected', 'device_connection_failed', 'data_received'])
Event = Tuple[EventType, Dict[str,Any]]
def event(event_type: EventType, data: Dict[str,str]) -> Event:
    return (event_type, data)

Status = Enum('Status', ['connected','not_connected'])

# Define event loop and event handlers
class EventLoop:
    def __init__(self):
        self.event_queue = asyncio.Queue()
        self.status = Status.not_connected

    async def run(self):
        while True:
            if not self.event_queue.empty():
                event = await self.event_queue.get()
                if event:
                    await self.handle_event(event)
            await asyncio.sleep(10)

    async def handle_event(self, event):
        match self.status:
            case Status.not_connected:
                await self.not_connected_handler(event)

    async def connected_handler(self, event):
        match event:
            case (EventType.data_received, json_data):
                print(f"Received: {json_data}")

    async def not_connected_handler(self, event):
        match event:
            case (EventType.device_found, data):
                await self.handle_device_found_event(data)
            case (EventType.device_connected, data):
                await self.handle_device_connected_event(data)
            case (EventType.device_connection_failed, data):
                await self.handle_device_connection_failed_event(data)

    async def handle_device_found_event(self, data):
        match data:
            case {"address": address, "name": name}:
                print(f"Device {name} found with address {address}")
                await connect_bluetooth(self, address)
    
    async def handle_device_connected_event(self, sock):
        self.status = Status.connected
        receive_data(self, sock)
    
    async def handle_device_connection_failed_event(self, data):
        match data:
            case (err, address):
                print(f"Device with address {address} failed to connect")
                print(err)


async def receive_data(event_loop: EventLoop, sock):
    try:
        buffer = ""
        while True:
            data = sock.recv(1024).decode('utf-8')
            buffer += data

            # Cerca il carattere di nuova linea
            while '\n' in buffer:
                line, buffer = buffer.split('\n', 1)
                if line:
                    try:
                        json_data = json.loads(line.strip())
                        await event_loop.event_queue.put(event(EventType.data_received,json_data))
                        # Puoi aggiungere ulteriori elaborazioni qui
                    except json.JSONDecodeError:
                        print(f"Errore nel decodificare JSON: {line}")
    except:
        sock.close()
    finally:
        sock.close()

async def connect_bluetooth(event_loop: EventLoop, address: str):
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    try:
        sock.connect((address, port))
        await event_loop.event_queue.put(event(EventType.device_connected,sock))
    except bluetooth.btcommon.BluetoothError as err:
        await event_loop.event_queue.put(event(EventType.device_connection_failed,(err,address)))
    return None

# Bluetooth scanner
async def bluetooth_scanner(event_loop: EventLoop):
    while True:
        devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)
        for addr, name in devices:
            await event_loop.event_queue.put(event(EventType.device_found,{'address': addr, 'name': name}))
        await asyncio.sleep(10)

async def main():
    event_loop = EventLoop()

    await asyncio.gather(
        event_loop.run(),
        bluetooth_scanner(event_loop)
    )

if __name__ == "__main__":
    asyncio.run(main())
