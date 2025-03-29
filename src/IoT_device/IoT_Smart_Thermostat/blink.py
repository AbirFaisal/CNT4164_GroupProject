from machine import Pin
from utime import sleep

from secrets import WIFI_SSID, WIFI_PASS

pin = Pin("LED", Pin.OUT)
pin.on()

import network
import urequests

print("Connecting to WiFi...", WIFI_SSID)

# Connect to WiFi
network.country("US")
wlan = network.WLAN(network.STA_IF)

# wlan.config(hostname='micropython')
# wlan.ifconfig(('10.0.3.31', '255.255.255.0', '10.0.3.1', '10.0.3.1'))
wlan.active(True)
wlan.connect(WIFI_SSID, WIFI_PASS)




while not wlan.isconnected() and wlan.status() >= 0:
    print("Waiting to connect:")
    sleep(1)

if wlan.status():
    print('Connecteda Successafullay', wlan.ifconfig())
    print('Connecteda Successafullay', network.country())

print("1. Querying example.com:")
r = urequests.get("http://www.example.com")
print(r.content)
r.close()

