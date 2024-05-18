import bluetooth

def discover_devices():
    print("Ricerca di dispositivi Bluetooth in corso...")
    devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)
    print(f"Trovati {len(devices)} dispositivi.")

    for addr, name in devices:
        print(f"Indirizzo: {addr}, Nome: {name}")

def main():
    discover_devices()

if __name__ == "__main__":
    main()
