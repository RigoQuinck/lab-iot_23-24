# esp-mqtt

Execute mosquitto in docker
`docker run -it -p 1883:1883 -p 9001:9001 -v ./mosquitto.conf:/mosquitto/config/mosquitto.conf eclipse-mosquitto`

Add -d to detach execution
`docker run -idt -p 1883:1883 -p 9001:9001 -v ./mosquitto.conf:/mosquitto/config/mosquitto.conf eclipse-mosquitto`

