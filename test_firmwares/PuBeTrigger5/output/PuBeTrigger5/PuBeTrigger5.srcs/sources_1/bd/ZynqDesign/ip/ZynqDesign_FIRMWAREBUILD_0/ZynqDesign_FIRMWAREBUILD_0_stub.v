// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Wed Apr 13 15:04:25 2022
// Host        : PHYS-NC3124-D02 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/OpenHardware/UserProject/PuBeTrigger5/output/PuBeTrigger5/PuBeTrigger5.srcs/sources_1/bd/ZynqDesign/ip/ZynqDesign_FIRMWAREBUILD_0/ZynqDesign_FIRMWAREBUILD_0_stub.v
// Design      : ZynqDesign_FIRMWAREBUILD_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z030fbg676-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "xlconstant_v1_1_3_xlconstant,Vivado 2017.4" *)
module ZynqDesign_FIRMWAREBUILD_0(dout)
/* synthesis syn_black_box black_box_pad_pin="dout[31:0]" */;
  output [31:0]dout;
endmodule