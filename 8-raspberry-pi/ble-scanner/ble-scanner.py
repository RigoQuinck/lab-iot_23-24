import asyncio
from bleak import BleakScanner

async def scan_devices():
    print("Scanning for BLE devices...")
    devices = await BleakScanner.discover()
    if devices:
        print(f"Found {len(devices)} devices:")
        for device in devices:
            print(f"  {device.name} - {device.address}")
    else:
        print("No devices found.")

if __name__ == "__main__":
    asyncio.run(scan_devices())
