// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sun May 22 16:31:09 2022
// Host        : PHYS-NC3124-D02 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest3/output/TrigTest3/TrigTest3.srcs/sources_1/ip/main_clk_gen/main_clk_gen_stub.v
// Design      : main_clk_gen
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7s25csga225-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module main_clk_gen(sample_clk, clk_out2, locked, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="sample_clk,clk_out2,locked,clk_in1" */;
  output sample_clk;
  output clk_out2;
  output locked;
  input clk_in1;
endmodule
