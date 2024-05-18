import RPi.GPIO as GPIO
import time

# Imposta il pin GPIO
led_pin = 17

# Impostazioni GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(led_pin, GPIO.OUT)

# Funzione per lampeggiare il LED
def blink_led():
    while True:
        GPIO.output(led_pin, GPIO.HIGH)  # Accende il LED
        time.sleep(1)                   # Attende 1 secondo
        GPIO.output(led_pin, GPIO.LOW)   # Spegne il LED
        time.sleep(1)                   # Attende 1 secondo

# Esegui la funzione di blink
try:
    blink_led()
except KeyboardInterrupt:
    GPIO.cleanup()  # Pulisce i pin GPIO alla chiusura del programma
