from flask import Flask
from pymongo import MongoClient
from flask_cors import CORS 

app = Flask(__name__)
CORS(app)  # Enable CORS for your Flask app

client = MongoClient("mongodb+srv://iot:iot@iot.u7mu254.mongodb.net/")
db = client["sensor"]
collection = db["data"]

@app.route("/api/sensor-data", methods=["GET"])
def get_sensor_data():
    sensor_data = list(collection.find())
    if len(sensor_data)>10:
        sensor_data = sensor_data[-10:]
    for i in sensor_data:
        i["_id"] = str(i["_id"])
    return {"data" : sensor_data}

if __name__ == "__main__":
    app.run(debug=True)
