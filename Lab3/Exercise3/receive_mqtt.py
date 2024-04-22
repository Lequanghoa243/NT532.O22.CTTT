import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected successfully.")
        client.subscribe("nt533/o22/group2/led")
    else:
        print(f"Failed to connect, return code {rc}")

def on_message(client, userdata, msg):
    print(f"Received message '{msg.payload.decode()}' on topic '{msg.topic}'")

def on_disconnect(client, userdata, rc):
    if rc != 0:
        print("Unexpected disconnection.")
    else:
        print("Disconnected successfully.")

client = mqtt.Client("member")
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect

try:
    client.connect("172.31.11.48", 1883, 60)
    client.loop_forever()
except Exception as e:
    print(f"An error occurred: {e}")
