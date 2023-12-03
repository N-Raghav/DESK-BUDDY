import { Box } from "@mui/material";
import Header from "../../components/Header";
import LineChartairQuality from "../../components/LineChartairQuality";

const Lineaq = () => {
  return (
    <Box m="20px">
      <Header title="Line Chart" subtitle="Simple Line Chart" />
      <Box height="75vh">
        <LineChartairQuality />
      </Box>
    </Box>
  );
};

export default Lineaq;
