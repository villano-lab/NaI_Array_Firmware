// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Wed Apr 13 15:04:34 2022
// Host        : PHYS-NC3124-D02 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/OpenHardware/UserProject/PuBeTrigger5/output/PuBeTrigger5/PuBeTrigger5.srcs/sources_1/bd/ZynqDesign/ip/ZynqDesign_axi_amm_bridge_0_0/ZynqDesign_axi_amm_bridge_0_0_stub.v
// Design      : ZynqDesign_axi_amm_bridge_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z030fbg676-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "axi_amm_bridge_v1_0_5_top,Vivado 2017.4" *)
module ZynqDesign_axi_amm_bridge_0_0(s_axi_aclk, s_axi_aresetn, s_axi_awaddr, 
  s_axi_awvalid, s_axi_awready, s_axi_wdata, s_axi_wstrb, s_axi_wvalid, s_axi_wready, 
  s_axi_bresp, s_axi_bvalid, s_axi_bready, s_axi_araddr, s_axi_arvalid, s_axi_arready, 
  s_axi_rdata, s_axi_rresp, s_axi_rvalid, s_axi_rready, avm_address, avm_write, avm_read, 
  avm_writedata, avm_readdata, avm_readdatavalid, avm_waitrequest)
/* synthesis syn_black_box black_box_pad_pin="s_axi_aclk,s_axi_aresetn,s_axi_awaddr[31:0],s_axi_awvalid,s_axi_awready,s_axi_wdata[31:0],s_axi_wstrb[3:0],s_axi_wvalid,s_axi_wready,s_axi_bresp[1:0],s_axi_bvalid,s_axi_bready,s_axi_araddr[31:0],s_axi_arvalid,s_axi_arready,s_axi_rdata[31:0],s_axi_rresp[1:0],s_axi_rvalid,s_axi_rready,avm_address[31:0],avm_write,avm_read,avm_writedata[31:0],avm_readdata[31:0],avm_readdatavalid,avm_waitrequest" */;
  input s_axi_aclk;
  input s_axi_aresetn;
  input [31:0]s_axi_awaddr;
  input s_axi_awvalid;
  output s_axi_awready;
  input [31:0]s_axi_wdata;
  input [3:0]s_axi_wstrb;
  input s_axi_wvalid;
  output s_axi_wready;
  output [1:0]s_axi_bresp;
  output s_axi_bvalid;
  input s_axi_bready;
  input [31:0]s_axi_araddr;
  input s_axi_arvalid;
  output s_axi_arready;
  output [31:0]s_axi_rdata;
  output [1:0]s_axi_rresp;
  output s_axi_rvalid;
  input s_axi_rready;
  output [31:0]avm_address;
  output avm_write;
  output avm_read;
  output [31:0]avm_writedata;
  input [31:0]avm_readdata;
  input avm_readdatavalid;
  input avm_waitrequest;
endmodule