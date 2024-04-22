import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected successfully.")
    else:
        print(f"Failed to connect, return code {rc}")

def on_publish(client, userdata, mid):
    print("Message published")

broker_address = "172.31.11.48"
port = 1883
topic = 'nt533/o22/group2/led'
message = "Hello World, It's Group 2. Helloooo"

client = mqtt.Client("PythonPublisher")
client.on_connect = on_connect
client.on_publish = on_publish

client.connect(broker_address, port)
client.loop_start() 

client.publish(topic, message)
time.sleep(1) 

client.loop_stop()
client.disconnect()
