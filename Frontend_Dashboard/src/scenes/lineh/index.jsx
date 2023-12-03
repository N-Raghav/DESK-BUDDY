import { Box } from "@mui/material";
import Header from "../../components/Header";
import LineChartHumidity from "../../components/LineChartHumidity";

const Lineh = () => {
  return (
    <Box m="20px">
      <Header title="Line Chart" subtitle="Simple Line Chart" />
      <Box height="75vh">
        <LineChartHumidity />
      </Box>
    </Box>
  );
};

export default Lineh;
