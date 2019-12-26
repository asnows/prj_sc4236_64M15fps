-- (c) Copyright 1995-2019 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:hls:sobel_filter:1.0
-- IP Revision: 1812031336

-- The following code must appear in the VHDL architecture header.

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT sobel_filter_1
  PORT (
    video_in_TVALID : IN STD_LOGIC;
    video_in_TREADY : OUT STD_LOGIC;
    video_in_TDATA : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    video_in_TKEEP : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_in_TSTRB : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_in_TUSER : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_in_TLAST : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_in_TID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_in_TDEST : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TVALID : OUT STD_LOGIC;
    video_out_TREADY : IN STD_LOGIC;
    video_out_TDATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    video_out_TKEEP : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TSTRB : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TLAST : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    video_out_TDEST : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    ap_clk : IN STD_LOGIC;
    ap_rst_n : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : sobel_filter_1
  PORT MAP (
    video_in_TVALID => video_in_TVALID,
    video_in_TREADY => video_in_TREADY,
    video_in_TDATA => video_in_TDATA,
    video_in_TKEEP => video_in_TKEEP,
    video_in_TSTRB => video_in_TSTRB,
    video_in_TUSER => video_in_TUSER,
    video_in_TLAST => video_in_TLAST,
    video_in_TID => video_in_TID,
    video_in_TDEST => video_in_TDEST,
    video_out_TVALID => video_out_TVALID,
    video_out_TREADY => video_out_TREADY,
    video_out_TDATA => video_out_TDATA,
    video_out_TKEEP => video_out_TKEEP,
    video_out_TSTRB => video_out_TSTRB,
    video_out_TUSER => video_out_TUSER,
    video_out_TLAST => video_out_TLAST,
    video_out_TID => video_out_TID,
    video_out_TDEST => video_out_TDEST,
    ap_clk => ap_clk,
    ap_rst_n => ap_rst_n,
    ap_start => ap_start,
    ap_done => ap_done,
    ap_ready => ap_ready,
    ap_idle => ap_idle
  );
-- INST_TAG_END ------ End INSTANTIATION Template ---------

-- You must compile the wrapper file sobel_filter_1.vhd when simulating
-- the core, sobel_filter_1. When compiling the wrapper file, be sure to
-- reference the VHDL simulation library.

