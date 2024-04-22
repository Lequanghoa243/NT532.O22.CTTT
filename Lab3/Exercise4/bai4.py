import paho.mqtt.client as mqtt
import time

# Configuration
broker_address = "172.31.11.48"  # Replace with your Raspberry Pi's IP address
port = 1883
topic = "nt533/o22/group2/led"

# Create a client instance
client = mqtt.Client("member2")

# Connect to the broker
client.connect(broker_address, port=port)

def send_message(state):
    """Function to send a message to the MQTT broker."""
    client.publish(topic, state)
    print(f"Message '{state}' sent to topic '{topic}'")

# Example usage
try:
    while True:
        # User input to control the LED
        state = input("Enter 'ON' to turn on the LED or 'OFF' to turn it off (type 'exit' to quit): ")
        if state.lower() == 'exit':
            break
        elif state.upper() in ['ON', 'OFF']:
            send_message(state.upper())
        else:
            print("Invalid input. Please enter 'ON', 'OFF', or 'exit'.")
finally:
    client.disconnect()
