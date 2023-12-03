import React, { useEffect, useState } from "react";
import { ResponsiveLine } from "@nivo/line";
import { useTheme } from "@mui/material";
import { tokens } from "../theme";

const LineChartHumidity = ({ isCustomLineColors = false, isDashboard = false }) => {
  const theme = useTheme();
  const colors = tokens(theme.palette.mode);

  const [sensorData, setSensorData] = useState([]);

  useEffect(() => {
    // Fetch sensor data from your Flask API
    fetch("http://127.0.0.1:5000/api/sensor-data")  // Update the API endpoint as needed
      .then((response) => response.json())
      .then((data) => {
        if (data && data.data) {
          // Process the data if needed and set it in the state
          setSensorData(data.data);
          console.log(data.data); // Add this line to print sensor data to the console
        }
      })
      .catch((error) => {
        console.error("Error fetching sensor data:", error);
      });
  }, []); // Empty dependency array to fetch data once on component mount

  // Define the data structure for the line chart
  const dataForChart = [
    {
      id: "sensor-data",
      color: colors.grey[500],
      data: sensorData.map((entry) => {
        try {
          const timestampString = entry["sensor/humidity"]["timestamp"];
          const timestamp = new Date(timestampString).getSeconds(); // Convert to Unix timestamp
          const y = parseFloat(entry["sensor/humidity"]["data"]);
          
          if (isNaN(timestamp) || isNaN(y)) {
            console.error("Invalid data:", entry);
          }
  
          return { x: timestamp, y };
        } catch (error) {
          console.error("Error processing data:", entry, error);
          return { x: 0, y: 0 }; // Handle the error gracefully
        }
      }),
    },
  ];

  return (
    <ResponsiveLine
      data={dataForChart}
      theme={{
        axis: {
          domain: {
            line: {
              stroke: colors.grey[100],
            },
          },
          legend: {
            text: {
              fill: colors.grey[100],
            },
          },
          ticks: {
            line: {
              stroke: colors.grey[100],
              strokeWidth: 1,
            },
            text: {
              fill: colors.grey[100],
            },
          },
        },
        legends: {
          text: {
            fill: colors.grey[100],
          },
        },
        tooltip: {
          container: {
            color: colors.primary[500],
          },
        },
      }}
      colors={isDashboard ? { datum: "color" } : { scheme: "nivo" }} // added
      margin={{ top: 50, right: 110, bottom: 50, left: 60 }}
      xScale={{ type: "point" }}
      yScale={{
        type: "linear",
        min: "auto",
        max: "auto",
        stacked: true,
        reverse: false,
      }}
      yFormat=" >-.2f"
      curve="catmullRom"
      axisTop={null}
      axisRight={null}
      axisBottom={{
        orient: "bottom",
        tickSize: 0,
        tickPadding: 5,
        tickRotation: 0,
        legend: isDashboard ? undefined : "transportation", // added
        legendOffset: 36,
        legendPosition: "middle",
      }}
      axisLeft={{
        orient: "left",
        tickValues: 5, // added
        tickSize: 3,
        tickPadding: 5,
        tickRotation: 0,
        legend: isDashboard ? undefined : "count", // added
        legendOffset: -40,
        legendPosition: "middle",
      }}
      enableGridX={false}
      enableGridY={false}
      pointSize={8}
      pointColor={{ theme: "background" }}
      pointBorderWidth={2}
      pointBorderColor={{ from: "serieColor" }}
      pointLabelYOffset={-12}
      useMesh={true}
      legends={[
        {
          anchor: "bottom-right",
          direction: "column",
          justify: false,
          translateX: 100,
          translateY: 0,
          itemsSpacing: 0,
          itemDirection: "left-to-right",
          itemWidth: 80,
          itemHeight: 20,
          itemOpacity: 0.75,
          symbolSize: 12,
          symbolShape: "circle",
          symbolBorderColor: "rgba(0, 0, 0, .5)",
          effects: [
            {
              on: "hover",
              style: {
                itemBackground: "rgba(0, 0, 0, .03)",
                itemOpacity: 1,
              },
            },
          ],
        },
      ]}
    />
  );
};

export default LineChartHumidity;
