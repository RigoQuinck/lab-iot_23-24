import asyncio
import bluetooth
from enum import Enum
from typing import Dict, Tuple, Any

# Events
EventType = Enum('EventType', ['device_found','device_connected', 'device_connection_failed'])
Event = Tuple[EventType, Dict[str,Any]]
def event(event_type: EventType, data: Dict[str,str]) -> Event:
    return (event_type, data)

# Define event loop and event handlers
class EventLoop:
    def __init__(self):
        self.event_queue = asyncio.Queue()

    async def run(self):
        while True:
            if not self.event_queue.empty():
                event = await self.event_queue.get()
                if event:
                    await self.handle_event(event)
            await asyncio.sleep(10)

    async def handle_event(self, event):
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
                connect_bluetooth(self, address)
    
    async def handle_device_connected_event(self, sock):
        print(f"Device connected")
    
    async def handle_device_connection_failed_event(self, data):
        match data:
            case (err, address):
                print(f"Device with address {address} failed to connect")
                print(err)

async def connect_bluetooth(event_loop: EventLoop, address: str):
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    try:
        sock.connect((address, port))
        await event_loop.event_queue.put(Event(EventType.device_connected,sock))
    except bluetooth.btcommon.BluetoothError as err:
        await event_loop.event_queue.put(Event(EventType.device_connection_failed,(err,address)))
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
