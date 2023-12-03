import React, { useEffect, useState } from "react";

function SensorData() {
  const [sensorData, setSensorData] = useState([]);

  useEffect(() => {
    fetch("/api/sensor-data") // Replace with the actual API URL
      .then((response) => response.json())
      .then((data) => {
        setSensorData(data.data);
      })
      .catch((error) => console.error("Error fetching data: ", error));
  }, []);

  return (
    <div>
      <h1>Sensor Data</h1>
      <ul>
        {sensorData.map((data, index) => (
          <li key={index}>
            <strong>{data._id}</strong>
            <ul>
              <li>Humidity: {data["sensor/humidity"]}</li>
              <li>Temperature (Celsius): {data["sensor/temperature_celsius"]}</li>
              <li>Heat Index: {data["sensor/heat_index"]}</li>
              <li>Air Quality: {data["sensor/airQuality"]}</li>
              <li>LDR: {data["sensor/LDR"]}</li>
            </ul>
          </li>
        ))}
      </ul>
    </div>
  );

}

export default SensorData;
