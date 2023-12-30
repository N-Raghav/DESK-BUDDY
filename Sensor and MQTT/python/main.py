import paho.mqtt.client as mqtt
from pymongo import MongoClient
from datetime import datetime


# MQTT Configuration
mqtt_broker_address = ""  # Update with your MQTT broker's IP
mqtt_topics = {
    "humidity": "sensor/humidity",
    "temperature_celsius": "sensor/temperature_celsius",
    "heat_index": "sensor/heat_index",
    "air_quality": "sensor/airQuality",
    "LDR": "sensor/LDR"
}
# MongoDB Configuration
mongo_uri = "mongodb+srv://iot:iot@iot.u7mu254.mongodb.net/"  # Update with your MongoDB Atlas connection string
mongo_db_name = "sensor"  # Update with your MongoDB database name
mongo_collection_name = "data"  # Update with your desired collection name
# MQTT Callback
mqtt_data = {}  # Dictionary to hold MQTT data

def on_message(client, userdata, message):
    message_payload = message.payload.decode("utf-8")
    topic = message.topic
    timestamp = datetime.now()  # Get the current timestamp
    mqtt_data[topic] = {"timestamp": timestamp, "data": message_payload}

# Insert data into MongoDB
def insert_data_into_mongodb(data):
    try:
        client = MongoClient(mongo_uri)
        db = client[mongo_db_name]
        collection = db[mongo_collection_name]
        collection.insert_one(data)
        print(f"Inserted data into MongoDB: {data}")
    except Exception as e:
        print("Failed to insert data into MongoDB:", {str(e)})

# Create an MQTT client
mqtt_client = mqtt.Client()
mqtt_client.on_message = on_message

# Connect to the MQTT broker and subscribe to the topics
mqtt_client.connect(mqtt_broker_address)
for topic in mqtt_topics.values():
    mqtt_client.subscribe(topic, 0)
mqtt_client.loop_start()

# Keep the script running
try:
    while True:
        if all(topic in mqtt_data for topic in mqtt_topics.values()):
            insert_data_into_mongodb(mqtt_data)
            mqtt_data = {}  # Clear the MQTT data dictionary
except KeyboardInterrupt:
    pass
