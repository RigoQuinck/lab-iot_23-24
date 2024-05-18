import bluetooth

def scan_devices():
    print("Scanning for bluetooth devices...")
    devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)

    if devices:
        print(f"Found {len(devices)} devices:")
        for addr, name in devices:
            print(f"  {name} - {addr}")
    else:
        print("No devices found.")

if __name__ == "__main__":
    scan_devices()
