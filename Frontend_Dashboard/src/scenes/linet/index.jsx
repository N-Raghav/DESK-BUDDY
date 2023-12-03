import { Box } from "@mui/material";
import Header from "../../components/Header";
import LineChartTemp from "../../components/LineChartTemp";

const Linet = () => {
  return (
    <Box m="20px">
      <Header title="Line Chart" subtitle="Simple Line Chart" />
      <Box height="75vh">
        <LineChartTemp />
      </Box>
    </Box>
  );
};

export default Linet;
