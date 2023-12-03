import { Box } from "@mui/material";
import Header from "../../components/Header";
import LineChartLDR from "../../components/LineChartLDR";

const Lineli = () => {
  return (
    <Box m="20px">
      <Header title="Line Chart" subtitle="Simple Line Chart" />
      <Box height="75vh">
        <LineChartLDR />
      </Box>
    </Box>
  );
};

export default Lineli;
