----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.02.2019 11:30:54
-- Design Name: 
-- Module Name: top_project_name - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

use ieee.math_real.all;
Library xpm;
use xpm.vcomponents.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity TOP_PuBeTrigger5 is
 port (
 
   DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
   DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
   DDR_cas_n : inout STD_LOGIC;
   DDR_ck_n : inout STD_LOGIC;
   DDR_ck_p : inout STD_LOGIC;
   DDR_cke : inout STD_LOGIC;
   DDR_cs_n : inout STD_LOGIC;
   DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
   DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
   DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
   DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
   DDR_odt : inout STD_LOGIC;
   DDR_ras_n : inout STD_LOGIC;
   DDR_reset_n : inout STD_LOGIC;
   DDR_we_n : inout STD_LOGIC;
   FIXED_IO_ddr_vrn : inout STD_LOGIC;
   FIXED_IO_ddr_vrp : inout STD_LOGIC;
   FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
   FIXED_IO_ps_clk : inout STD_LOGIC;
   FIXED_IO_ps_porb : inout STD_LOGIC;
   FIXED_IO_ps_srstb : inout STD_LOGIC;

    GT_REFCLK_0_clk_n : in STD_LOGIC;
    GT_REFCLK_0_clk_p : in STD_LOGIC;
    GT_RX_0_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_0_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_1_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_1_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_RX_2_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_RX_2_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_RX_3_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_RX_3_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );    
    GT_TX_0_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_0_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_1_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_1_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_TX_2_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_TX_2_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_TX_3_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    --GT_TX_3_txp : out STD_LOGIC_VECTOR ( 0 to 0 );

	

   sCLK_125 : in std_logic;
   sCLK_CH_SEL : out std_logic;
      
   ADC_SERVICE_CLK_OUT_P : out STD_LOGIC;
   ADC_SERVICE_CLK_OUT_N : out STD_LOGIC;
      
   ADC_1_CLK_A_P : in STD_LOGIC;
   ADC_1_CLK_A_N : in STD_LOGIC;
   ADC_1_CLK_B_P : in STD_LOGIC;
   ADC_1_CLK_B_N : in STD_LOGIC;
   
  
   ADC_1_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_1_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
   
   ADC_1_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_1_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
   
   SMADC_1_CSA : out std_logic;
   SMADC_1_CSB : out std_logic;
   SMADC_1_CLK : out std_logic;
   SMADC_1_MOSI : out std_logic;
   SMADC_2_MOSI : out std_logic;
   SMADC_3_MOSI : out std_logic;
   SMADC_4_MOSI : out std_logic;
     
   
   ADC_2_CLK_A_P : in STD_LOGIC;
   ADC_2_CLK_A_N : in STD_LOGIC;
   ADC_2_CLK_B_P : in STD_LOGIC;
   ADC_2_CLK_B_N : in STD_LOGIC;
       
       
   ADC_2_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_2_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
       
   ADC_2_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_2_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);

   ADC_3_CLK_A_P : in STD_LOGIC;
   ADC_3_CLK_A_N : in STD_LOGIC;
   ADC_3_CLK_B_P : in STD_LOGIC;
   ADC_3_CLK_B_N : in STD_LOGIC;
       

       
   ADC_3_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_3_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
       
   ADC_3_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_3_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);

   
   
   ADC_4_CLK_A_P : in STD_LOGIC;
   ADC_4_CLK_A_N : in STD_LOGIC;
   ADC_4_CLK_B_P : in STD_LOGIC;
   ADC_4_CLK_B_N : in STD_LOGIC;
       

       
   ADC_4_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_4_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
       
   ADC_4_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
   ADC_4_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
   
   
   SYNC_0_INb : in STD_LOGIC;
   SYNC_0_OUTb : out STD_LOGIC;

   SYNC_1_INb : in STD_LOGIC;
   SYNC_1_OUTb : out STD_LOGIC;

   SYNC_2_INb : in STD_LOGIC;
   SYNC_2_OUTb : out STD_LOGIC;

   
   SFP_DISABLE1 : out std_logic;
   SFP_DISABLE2 : out std_logic;
   
      
   Si_ClkOut_p :  out std_logic;
   Si_ClkOut_n :  out std_logic;
   
   Si_ClkIn_p :  in std_logic;
   Si_ClkIn_n :  in std_logic;
   
   SLAVE_I2C_SCL_0 : inout STD_LOGIC;
   SLAVE_I2C_SDA_0 : inout STD_LOGIC;
   
   SPI_MOSI_0 : out STD_LOGIC;
   SPI_MOSI_1 : out STD_LOGIC;
   SPI_CLK : out STD_LOGIC;
   SPI_CS : out STD_LOGIC;
   BOARDPOSITION :  in STD_LOGIC_VECTOR ( 1 downto 0 )     
   
);
end TOP_PuBeTrigger5 ;

architecture Behavioral of TOP_PuBeTrigger5 is
component ZynqDesign_wrapper is
  port (
    DDR_0_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_0_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_0_cas_n : inout STD_LOGIC;
    DDR_0_ck_n : inout STD_LOGIC;
    DDR_0_ck_p : inout STD_LOGIC;
    DDR_0_cke : inout STD_LOGIC;
    DDR_0_cs_n : inout STD_LOGIC;
    DDR_0_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_0_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_0_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_0_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_0_odt : inout STD_LOGIC;
    DDR_0_ras_n : inout STD_LOGIC;
    DDR_0_reset_n : inout STD_LOGIC;
    DDR_0_we_n : inout STD_LOGIC;
    FIXED_IO_0_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_0_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_0_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_0_ps_clk : inout STD_LOGIC;
    FIXED_IO_0_ps_porb : inout STD_LOGIC;
    FIXED_IO_0_ps_srstb : inout STD_LOGIC;
        FS_0_tdata : in STD_LOGIC_VECTOR ( 63 downto 0 );
    FS_0_tready : out STD_LOGIC;
    FS_0_tvalid : in STD_LOGIC;


    
    GT_REFCLK_0_clk_n : in STD_LOGIC;
    GT_REFCLK_0_clk_p : in STD_LOGIC;
--    GT_RX_0_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_RX_0_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_RX_1_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_RX_1_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_2_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_2_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_3_rxn : in STD_LOGIC_VECTOR ( 0 to 0 );
    GT_RX_3_rxp : in STD_LOGIC_VECTOR ( 0 to 0 );    
--    GT_TX_0_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_TX_0_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_TX_1_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
--    GT_TX_1_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_2_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_2_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_3_txn : out STD_LOGIC_VECTOR ( 0 to 0 );
    GT_TX_3_txp : out STD_LOGIC_VECTOR ( 0 to 0 );
    
      LINK0_FIFO_IN_tvalid : in STD_LOGIC;
      LINK0_FIFO_IN_tready : out STD_LOGIC;
      LINK0_FIFO_IN_tdata : in STD_LOGIC_VECTOR ( 63 downto 0 );
      LINK0_FIFO_OUT_tvalid : out STD_LOGIC;
      LINK0_FIFO_OUT_tready : in STD_LOGIC;
      LINK0_FIFO_OUT_tdata : out STD_LOGIC_VECTOR ( 63 downto 0 );
      LINK1_FIFO_IN_tvalid : in STD_LOGIC;
      LINK1_FIFO_IN_tready : out STD_LOGIC;
      LINK1_FIFO_IN_tdata : in STD_LOGIC_VECTOR ( 63 downto 0 );
      LINK1_FIFO_OUT_tvalid : out STD_LOGIC;
      LINK1_FIFO_OUT_tready : in STD_LOGIC;
      LINK1_FIFO_OUT_tdata : out STD_LOGIC_VECTOR ( 63 downto 0 );
        
    MAIN_CLOCK : out STD_LOGIC;
    MAIN_RESET : out STD_LOGIC_VECTOR ( 0 to 0 );
    
    M_AVALON_0_address : out STD_LOGIC_VECTOR ( 31 downto 0 );
    M_AVALON_0_read : out STD_LOGIC;
    M_AVALON_0_readdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    M_AVALON_0_readdatavalid : in STD_LOGIC;
    M_AVALON_0_waitrequest : in STD_LOGIC;
    M_AVALON_0_write : out STD_LOGIC;
    M_AVALON_0_writedata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    
      SMADC_1_CSA_0 : out STD_LOGIC;
      SMADC_1_CSB_0 : out STD_LOGIC;
      SMADC_2_CSA_0 : out STD_LOGIC;
      SMADC_2_CSB_0 : out STD_LOGIC;
      SMADC_3_CSA_0 : out STD_LOGIC;
      SMADC_3_CSB_0 : out STD_LOGIC;
      SMADC_4_CSA_0 : out STD_LOGIC;
      SMADC_4_CSB_0 : out STD_LOGIC;
      SMADC_CLK_0 : out STD_LOGIC;
      SMADC_MOSI_0 : out STD_LOGIC;
      cfg_abselector_0 : out STD_LOGIC;
      cfg_channel_selector_0 : out STD_LOGIC_VECTOR ( 7 downto 0 );
      cfg_pulse_bitsleep_0 : out STD_LOGIC;
      cfg_selected_prw_0 : in STD_LOGIC_VECTOR ( 15 downto 0 );
      cfg_serdes1_delay_0 : out STD_LOGIC_VECTOR ( 4 downto 0 );
      cfg_serdes1_delay_exc_0 : out STD_LOGIC;
      serdes_reset_0 : out STD_LOGIC_VECTOR ( 7 downto 0 );
      
      LINK0_RXCLK : out STD_LOGIC;
      SIRcClock : in STD_LOGIC;
      
      FW_VER_0 : in STD_LOGIC_VECTOR ( 31 downto 0 );
      FW_RELEASE_DATE_0 : in STD_LOGIC_VECTOR ( 31 downto 0 );
      FW_STRING_0 : in STD_LOGIC_VECTOR ( 127 downto 0 );
      BOARDPOSITION : in STD_LOGIC_VECTOR ( 1 downto 0 );     
	  IIC_0_scl_io : inout STD_LOGIC;
      IIC_0_sda_io : inout STD_LOGIC;
      SPI_MOSI_0_0 : out STD_LOGIC;
      SPI_MOSI_1_0 : out STD_LOGIC;
      SPI_CLK_0 : out STD_LOGIC;
      SPI_CS_0 : out STD_LOGIC;
      CLOCK_SOURCE : in STD_LOGIC_VECTOR ( 3 downto 0 );
      CLOCK_PL : in STD_LOGIC;
      CLOCK_RESET : out STD_LOGIC;
      clock_source_commutator : out STD_LOGIC;
      INVALID_EXT_CLK : in STD_LOGIC

  );
end component;



component adcs_top_0 is
    Port (  
          sCLK_125 : in std_logic;
   
          ADC_SERVICE_CLK_OUT_P : out STD_LOGIC;
          ADC_SERVICE_CLK_OUT_N : out STD_LOGIC;
          
          
          ADC_1_CLK_A_P : in STD_LOGIC;
          ADC_1_CLK_A_N : in STD_LOGIC;
          ADC_1_CLK_B_P : in STD_LOGIC;
          ADC_1_CLK_B_N : in STD_LOGIC;
          
          ADC_1_FRAME_A_P : in STD_LOGIC;
          ADC_1_FRAME_A_N : in STD_LOGIC;
          ADC_1_FRAME_B_P : in STD_LOGIC;
          ADC_1_FRAME_B_N : in STD_LOGIC;
          
          ADC_1_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_1_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
          
          ADC_1_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_1_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
          
          SMADC_1_CSA : out std_logic;
          SMADC_1_CSB : out std_logic;
          SMADC_1_CLK : out std_logic;
          SMADC_1_MOSI : out std_logic;
          
          
          
          ADC_2_CLK_A_P : in STD_LOGIC;
          ADC_2_CLK_A_N : in STD_LOGIC;
          ADC_2_CLK_B_P : in STD_LOGIC;
          ADC_2_CLK_B_N : in STD_LOGIC;
              
          ADC_2_FRAME_A_P : in STD_LOGIC;
          ADC_2_FRAME_A_N : in STD_LOGIC;
          ADC_2_FRAME_B_P : in STD_LOGIC;
          ADC_2_FRAME_B_N : in STD_LOGIC;
              
          ADC_2_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_2_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
              
          ADC_2_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_2_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
          
          SMADC_2_CSA : out std_logic;
          SMADC_2_CSB : out std_logic;
          
          
          
          ADC_3_CLK_A_P : in STD_LOGIC;
          ADC_3_CLK_A_N : in STD_LOGIC;
          ADC_3_CLK_B_P : in STD_LOGIC;
          ADC_3_CLK_B_N : in STD_LOGIC;
              
          ADC_3_FRAME_A_P : in STD_LOGIC;
          ADC_3_FRAME_A_N : in STD_LOGIC;
          ADC_3_FRAME_B_P : in STD_LOGIC;
          ADC_3_FRAME_B_N : in STD_LOGIC;
              
          ADC_3_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_3_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
              
          ADC_3_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_3_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
          
          SMADC_3_CSA : out std_logic;
          SMADC_3_CSB : out std_logic;

          
          ADC_4_CLK_A_P : in STD_LOGIC;
          ADC_4_CLK_A_N : in STD_LOGIC;
          ADC_4_CLK_B_P : in STD_LOGIC;
          ADC_4_CLK_B_N : in STD_LOGIC;
              
          ADC_4_FRAME_A_P : in STD_LOGIC;
          ADC_4_FRAME_A_N : in STD_LOGIC;
          ADC_4_FRAME_B_P : in STD_LOGIC;
          ADC_4_FRAME_B_N : in STD_LOGIC;
              
          ADC_4_DATA_A_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_4_DATA_A_N: in STD_LOGIC_VECTOR(7 downto 0);
              
          ADC_4_DATA_B_P: in STD_LOGIC_VECTOR(7 downto 0);
          ADC_4_DATA_B_N: in STD_LOGIC_VECTOR(7 downto 0);
          
          SMADC_4_CSA : out std_logic;
          SMADC_4_CSB : out std_logic;
          
          READOUT_CLK : in STD_LOGIC;
	      READOUT_CLK_OUT : out STD_LOGIC;
          
          CH0 : out std_logic_vector (15 downto 0);
          CH1 : out std_logic_vector (15 downto 0);
          CH2 : out std_logic_vector (15 downto 0);
          CH3 : out std_logic_vector (15 downto 0);                                            
          CH4 : out std_logic_vector (15 downto 0);
          CH5 : out std_logic_vector (15 downto 0);
          CH6 : out std_logic_vector (15 downto 0);
          CH7 : out std_logic_vector (15 downto 0);
          CH8 : out std_logic_vector (15 downto 0);                                                                                     
          CH9 : out std_logic_vector (15 downto 0);
          CH10 : out std_logic_vector (15 downto 0);
          CH11 : out std_logic_vector (15 downto 0);
          CH12 : out std_logic_vector (15 downto 0);
          CH13 : out std_logic_vector (15 downto 0);
          CH14 : out std_logic_vector (15 downto 0);
          CH15 : out std_logic_vector (15 downto 0);
          CH16 : out std_logic_vector (15 downto 0);
          CH17 : out std_logic_vector (15 downto 0);
          CH18 : out std_logic_vector (15 downto 0);
          CH19 : out std_logic_vector (15 downto 0);
          CH20 : out std_logic_vector (15 downto 0);
          CH21 : out std_logic_vector (15 downto 0);
          CH22 : out std_logic_vector (15 downto 0);
          CH23 : out std_logic_vector (15 downto 0);
          CH24 : out std_logic_vector (15 downto 0);
          CH25 : out std_logic_vector (15 downto 0);
          CH26 : out std_logic_vector (15 downto 0);
          CH27 : out std_logic_vector (15 downto 0);
          CH28 : out std_logic_vector (15 downto 0);
          CH29 : out std_logic_vector (15 downto 0);
          CH30 : out std_logic_vector (15 downto 0);
          CH31 : out std_logic_vector (15 downto 0);
          
          CHv0_7 : out STD_LOGIC;
          CHv8_15 : out STD_LOGIC;
          CHv16_23 : out STD_LOGIC;
          CHv24_31 : out STD_LOGIC;
          
          cfg_serdes1_delay : in std_logic_vector(5-1 downto 0);
          cfg_serdes1_delay_exc : in std_logic;
          cfg_pulse_bitsleep : in std_logic;
          cfg_abselector : in std_logic;                  
          cfg_channel_selector : in std_logic_vector(7 downto 0);
          cfg_selected_prw : out std_logic_vector(15 downto 0);
          serdes_reset_0 : in STD_LOGIC_VECTOR ( 7 downto 0 )
    
          );
end component;



component avalon_wrapper is
    Generic (M_AVALON_BA : STD_LOGIC_VECTOR (31 downto 0) := x"10000000");
    Port (  clk : in STD_LOGIC;
            reset : in STD_LOGIC;
            M_AVALON_0_address : in  STD_LOGIC_VECTOR ( 31 downto 0 );
            M_AVALON_0_read : in STD_LOGIC;
            M_AVALON_0_readdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
            M_AVALON_0_readdatavalid : out  STD_LOGIC;
            M_AVALON_0_waitrequest : out STD_LOGIC;
            M_AVALON_0_write : in STD_LOGIC;
            M_AVALON_0_writedata : in STD_LOGIC_VECTOR ( 31 downto 0 );
     
    
			--test
            BUS_Test_0_READ_DATA : IN STD_LOGIC_VECTOR(31 downto 0);
            BUS_Test_0_ADDRESS : OUT STD_LOGIC_VECTOR(15 downto 0); 
            BUS_Test_0_WRITE_DATA : OUT STD_LOGIC_VECTOR(31 downto 0); 
            BUS_Test_0_W_INT : OUT STD_LOGIC_VECTOR(0 downto 0); 
            BUS_Test_0_R_INT : OUT STD_LOGIC_VECTOR(0 downto 0); 
            BUS_Test_0_VLD : IN STD_LOGIC_VECTOR(0 downto 0);               

            -- Register interface          
		REG_polarity_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_polarity_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_polarity_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_polarity_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_thrs_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_thrs_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_thrs_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_thrs_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_inhib_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_inhib_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_inhib_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_inhib_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_delay_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_delay_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_delay_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_delay_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_top_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_top_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_top_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_top_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_gate_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_gate_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_gate_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_gate_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
	BUS_RateMeter_0_READ_ADDRESS : OUT STD_LOGIC_VECTOR(15 downto 0); 
	BUS_RateMeter_0_READ_DATA : IN STD_LOGIC_VECTOR(31 downto 0); 
	BUS_RateMeter_0_WRITE_DATA : OUT STD_LOGIC_VECTOR(31 downto 0); 
	BUS_RateMeter_0_W_INT : OUT STD_LOGIC_VECTOR(0 downto 0); 
	BUS_RateMeter_0_R_INT : OUT STD_LOGIC_VECTOR(0 downto 0); 
	BUS_RateMeter_0_VLD : IN STD_LOGIC_VECTOR(0 downto 0); 
		REG_ratereset_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_ratereset_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
		INT_ratereset_RD : OUT STD_LOGIC_VECTOR(0 downto 0); 
		INT_ratereset_WR : OUT STD_LOGIC_VECTOR(0 downto 0); 
		REG_UNIQUE_RD : IN STD_LOGIC_VECTOR(31 downto 0); 
		REG_UNIQUE_WR : OUT STD_LOGIC_VECTOR(31 downto 0); 
	

            REG_FIRMWARE_UNIQUE : IN STD_LOGIC_VECTOR(31 downto 0);
            REG_FIRMWARE_BUILD : IN STD_LOGIC_VECTOR(31 downto 0)    
    );
end component;

    attribute keep            : string;
    
    signal CHA0 :  std_logic_vector (15 downto 0);
    signal CHA1 :  std_logic_vector (15 downto 0);
    signal CHA2 :  std_logic_vector (15 downto 0);
    signal CHA3 :  std_logic_vector (15 downto 0);                                            
    signal CHA4 :  std_logic_vector (15 downto 0);
    signal CHA5 :  std_logic_vector (15 downto 0);
    signal CHA6 :  std_logic_vector (15 downto 0);
    signal CHA7 :  std_logic_vector (15 downto 0);
    signal CHA8 :  std_logic_vector (15 downto 0);                                                                                     
    signal CHA9 :  std_logic_vector (15 downto 0);
    signal CHA10 :  std_logic_vector (15 downto 0);
    signal CHA11 :  std_logic_vector (15 downto 0);
    signal CHA12 :  std_logic_vector (15 downto 0);
    signal CHA13 :  std_logic_vector (15 downto 0);
    signal CHA14 :  std_logic_vector (15 downto 0);
    signal CHA15 :  std_logic_vector (15 downto 0);
    signal CHA16 :  std_logic_vector (15 downto 0);
    signal CHA17 :  std_logic_vector (15 downto 0);
    signal CHA18 :  std_logic_vector (15 downto 0);
    signal CHA19 :  std_logic_vector (15 downto 0);
    signal CHA20 :  std_logic_vector (15 downto 0);
    signal CHA21 :  std_logic_vector (15 downto 0);
    signal CHA22 :  std_logic_vector (15 downto 0);
    signal CHA23 :  std_logic_vector (15 downto 0);
    signal CHA24 :  std_logic_vector (15 downto 0);
    signal CHA25 :  std_logic_vector (15 downto 0);
    signal CHA26 :  std_logic_vector (15 downto 0);
    signal CHA27 :  std_logic_vector (15 downto 0);
    signal CHA28 :  std_logic_vector (15 downto 0);
    signal CHA29 :  std_logic_vector (15 downto 0);
    signal CHA30 :  std_logic_vector (15 downto 0);
    signal CHA31 :  std_logic_vector (15 downto 0);
    
	
	
    signal CH0 :  std_logic_vector (15 downto 0);
    signal CH1 :  std_logic_vector (15 downto 0);
    signal CH2 :  std_logic_vector (15 downto 0);
    signal CH3 :  std_logic_vector (15 downto 0);                                            
    signal CH4 :  std_logic_vector (15 downto 0);
    signal CH5 :  std_logic_vector (15 downto 0);
    signal CH6 :  std_logic_vector (15 downto 0);
    signal CH7 :  std_logic_vector (15 downto 0);
    signal CH8 :  std_logic_vector (15 downto 0);                                                                                     
    signal CH9 :  std_logic_vector (15 downto 0);
    signal CH10 :  std_logic_vector (15 downto 0);
    signal CH11 :  std_logic_vector (15 downto 0);
    signal CH12 :  std_logic_vector (15 downto 0);
    signal CH13 :  std_logic_vector (15 downto 0);
    signal CH14 :  std_logic_vector (15 downto 0);
    signal CH15 :  std_logic_vector (15 downto 0);
    signal CH16 :  std_logic_vector (15 downto 0);
    signal CH17 :  std_logic_vector (15 downto 0);
    signal CH18 :  std_logic_vector (15 downto 0);
    signal CH19 :  std_logic_vector (15 downto 0);
    signal CH20 :  std_logic_vector (15 downto 0);
    signal CH21 :  std_logic_vector (15 downto 0);
    signal CH22 :  std_logic_vector (15 downto 0);
    signal CH23 :  std_logic_vector (15 downto 0);
    signal CH24 :  std_logic_vector (15 downto 0);
    signal CH25 :  std_logic_vector (15 downto 0);
    signal CH26 :  std_logic_vector (15 downto 0);
    signal CH27 :  std_logic_vector (15 downto 0);
    signal CH28 :  std_logic_vector (15 downto 0);
    signal CH29 :  std_logic_vector (15 downto 0);
    signal CH30 :  std_logic_vector (15 downto 0);
    signal CH31 :  std_logic_vector (15 downto 0);
    
	
    signal CHv0_7 : STD_LOGIC;
    signal CHv8_15 : STD_LOGIC;
    signal CHv16_23 : STD_LOGIC;
    signal CHv24_31 : STD_LOGIC;


    attribute keep of CHA0  : signal is "true";
    attribute keep of CHA1  : signal is "true";
    attribute keep of CHA2  : signal is "true";
    attribute keep of CHA3  : signal is "true";
    attribute keep of CHA4  : signal is "true";
    attribute keep of CHA5  : signal is "true";
    attribute keep of CHA6  : signal is "true";
    attribute keep of CHA7  : signal is "true";
    attribute keep of CHA8  : signal is "true";
    attribute keep of CHA9  : signal is "true";
    attribute keep of CHA10  : signal is "true";
    attribute keep of CHA11  : signal is "true";
    attribute keep of CHA12  : signal is "true";
    attribute keep of CHA13  : signal is "true";
    attribute keep of CHA14  : signal is "true";
    attribute keep of CHA15  : signal is "true";
    attribute keep of CHA16  : signal is "true";
    attribute keep of CHA17  : signal is "true";
    attribute keep of CHA18  : signal is "true";
    attribute keep of CHA19  : signal is "true";
    attribute keep of CHA20  : signal is "true";
    attribute keep of CHA21  : signal is "true";
    attribute keep of CHA22  : signal is "true";
    attribute keep of CHA23  : signal is "true";
    attribute keep of CHA24  : signal is "true";
    attribute keep of CHA25  : signal is "true";
    attribute keep of CHA26  : signal is "true";
    attribute keep of CHA27  : signal is "true";
    attribute keep of CHA28  : signal is "true";
    attribute keep of CHA29  : signal is "true";
    attribute keep of CHA30  : signal is "true";
    attribute keep of CHA31  : signal is "true";

    
    signal M_AVALON_0_address :  STD_LOGIC_VECTOR ( 31 downto 0 );
    signal M_AVALON_0_read :  STD_LOGIC;
    signal M_AVALON_0_readdata :  STD_LOGIC_VECTOR ( 31 downto 0 );
    signal M_AVALON_0_readdatavalid :  STD_LOGIC;
    signal M_AVALON_0_waitrequest :  STD_LOGIC;
    signal M_AVALON_0_write : STD_LOGIC;
    signal M_AVALON_0_writedata : STD_LOGIC_VECTOR ( 31 downto 0 );
    
	    
    attribute keep of M_AVALON_0_address  : signal is "true";
    attribute keep of M_AVALON_0_read  : signal is "true";        
    attribute keep of M_AVALON_0_readdata  : signal is "true";
    attribute keep of M_AVALON_0_write  : signal is "true";
    attribute keep of M_AVALON_0_writedata  : signal is "true";

    signal MOSI : STD_LOGIC;
    
    
    signal  cfg_serdes1_delay :  std_logic_vector(5-1 downto 0) := (others => '0');
    signal  cfg_serdes1_delay_exc :  std_logic := '0';
    signal  cfg_pulse_bitsleep :  std_logic := '0';
    signal  cfg_abselector :  std_logic := '0';       
    signal  cfg_channel_selector :  std_logic_vector(7 downto 0)  := (others => '0');
    signal  cfg_selected_prw :  std_logic_vector(15 downto 0)  := (others => '0');
    
    signal serdes_reset_0 : STD_LOGIC_VECTOR ( 7 downto 0 );    
    
    signal BOARD_CLOCK : STD_LOGIC;
	signal MAIN_RESET : STD_LOGIC_VECTOR ( 0 to 0 );
    
    signal TEST_REG : STD_LOGIC_VECTOR ( 31 downto 0 );
    
    signal HLINK0_FIFO_IN_tdata :  STD_LOGIC_VECTOR ( 63 downto 0 );
    signal HLINK0_FIFO_IN_tready :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK0_FIFO_IN_tvalid :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK0_FIFO_OUT_tdata :  STD_LOGIC_VECTOR ( 63 downto 0 );
    signal HLINK0_FIFO_OUT_tready :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK0_FIFO_OUT_tvalid :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK1_FIFO_IN_tdata :  STD_LOGIC_VECTOR ( 63 downto 0 );
    signal HLINK1_FIFO_IN_tready :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK1_FIFO_IN_tvalid :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK1_FIFO_OUT_tdata :  STD_LOGIC_VECTOR ( 63 downto 0 );
    signal HLINK1_FIFO_OUT_tready :  STD_LOGIC_VECTOR (0 downto 0) := "0";
    signal HLINK1_FIFO_OUT_tvalid :  STD_LOGIC_VECTOR (0 downto 0) := "0"; 

	
	signal BUS_Test_0_READ_DATA :  STD_LOGIC_VECTOR(31 downto 0);
    signal BUS_Test_0_ADDRESS :  STD_LOGIC_VECTOR(15 downto 0); 
    signal BUS_Test_0_WRITE_DATA :  STD_LOGIC_VECTOR(31 downto 0); 
    signal BUS_Test_0_W_INT :  STD_LOGIC_VECTOR(0 downto 0); 
    signal BUS_Test_0_R_INT :  STD_LOGIC_VECTOR(0 downto 0); 
    signal BUS_Test_0_VLD :  STD_LOGIC_VECTOR(0 downto 0);   
    
    signal REG_FIRMWARE_UNIQUE : STD_LOGIC_VECTOR(31 downto 0) := x"11111111";
    signal REG_FIRMWARE_BUILD :  STD_LOGIC_VECTOR(31 downto 0) := x"19030700";    
    signal FW_VER_0 :  STD_LOGIC_VECTOR ( 31 downto 0 );        
    signal FW_RELEASE_DATE_0 :  STD_LOGIC_VECTOR ( 31 downto 0 );
    signal FW_STRING_0 :  STD_LOGIC_VECTOR ( 127 downto 0 );
            
     
	signal CLK_LINK : std_logic_vector (0 downto 0) := "0";
	
	signal	CLK_40 :  std_logic_vector (0 downto 0);
	signal	CLK_80 :  std_logic_vector (0 downto 0);
	signal	clk_160 :  std_logic_vector (0 downto 0);
	signal	clk_320 :  std_logic_vector (0 downto 0);
	signal CLK_125 : std_logic_vector(0 downto 0);	
    signal FAST_CLK_100 : std_logic_vector (0 downto 0) := "0";
    signal FAST_CLK_200 : std_logic_vector (0 downto 0) := "0";
    signal FAST_CLK_250 : std_logic_vector (0 downto 0) := "0";
    signal FAST_CLK_250_90 : std_logic_vector (0 downto 0) := "0";
    signal FAST_CLK_500 : std_logic_vector (0 downto 0) := "0";
    signal FAST_CLK_500_90 : std_logic_vector (0 downto 0) := "0";
    
    signal async_clk : std_logic_vector (0 downto 0) := "0";
    signal GlobalClock : std_logic_vector (0 downto 0) := "0";
    signal BUS_CLK : std_logic_vector (0 downto 0) := "0";
    signal GlobalReset : std_logic_vector (0 downto 0) := "0";         

    signal CLK_ACQ : std_logic_vector (0 downto 0) := "0";
	
	signal SYNC_0_OUT : std_logic_vector(0 downto 0) := "0";
	signal SYNC_1_OUT : std_logic_vector(0 downto 0) := "0";
	signal SYNC_2_OUT : std_logic_vector(0 downto 0) := "0";

	signal SYNC_0_IN : std_logic_vector(0 downto 0) := "0";
	signal SYNC_1_IN : std_logic_vector(0 downto 0) := "0";
	signal SYNC_2_IN : std_logic_vector(0 downto 0) := "0";
	
	signal FS_0_tdata : STD_LOGIC_VECTOR ( 63 downto 0 ) := (others => '0');
    signal FS_0_tready :  STD_LOGIC_VECTOR(0 downto 0) := "0";
    signal FS_0_tvalid :  STD_LOGIC_VECTOR(0 downto 0) := "0";
	
	signal FS_1_tdata : STD_LOGIC_VECTOR ( 63 downto 0 ) := (others => '0');
    signal FS_1_tready :  STD_LOGIC_VECTOR(0 downto 0) := "0";
    signal FS_1_tvalid :  STD_LOGIC_VECTOR(0 downto 0) := "0";

	signal FS_2_tdata : STD_LOGIC_VECTOR ( 63 downto 0 ) := (others => '0');
    signal FS_2_tready :  STD_LOGIC_VECTOR(0 downto 0) := "0";
    signal FS_2_tvalid :  STD_LOGIC_VECTOR(0 downto 0) := "0";

	signal FS_3_tdata : STD_LOGIC_VECTOR ( 63 downto 0 ) := (others => '0');
    signal FS_3_tready :  STD_LOGIC_VECTOR(0 downto 0) := "0";
    signal FS_3_tvalid :  STD_LOGIC_VECTOR(0 downto 0) := "0";
	

    signal iSiClkOut : std_logic;
    signal iSiClkIn : std_logic;
	
signal U0_TRIGOUT_0 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_1 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_2 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_3 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_4 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_5 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_6 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_7 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_8 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_9 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_10 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_11 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_12 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_13 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_14 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_15 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_16 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_17 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_18 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_19 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_20 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_21 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_22 : std_logic_vector(0 downto 0);
signal U0_TRIGOUT_23 : std_logic_vector(0 downto 0);

COMPONENT SUBPAGE_TriggerWindow
PORT(
	AIN : IN std_logic_vector(15 downto 0);
	TRIGOUT : OUT std_logic_vector(0 downto 0);
	polarity : IN std_logic_vector(0 downto 0);
	thrs : IN std_logic_vector(15 downto 0);
	inhib : IN std_logic_vector(15 downto 0);
	delay : IN std_logic_vector(15 downto 0);
	top : IN std_logic_vector(15 downto 0);
	gate : IN std_logic_vector(15 downto 0);
    GlobalReset: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    CLK_ACQ: in std_logic_vector (0 downto 0); 
    BUS_CLK: in std_logic_vector (0 downto 0); 
    CLK_40: in std_logic_vector (0 downto 0); 
    CLK_50: in std_logic_vector (0 downto 0); 
    CLK_80: in std_logic_vector (0 downto 0); 
    clk_160: in std_logic_vector (0 downto 0); 
    clk_320: in std_logic_vector (0 downto 0); 
    clk_125: in std_logic_vector (0 downto 0); 
    FAST_CLK_100: in std_logic_vector (0 downto 0); 
    FAST_CLK_200: in std_logic_vector (0 downto 0); 
    FAST_CLK_250: in std_logic_vector (0 downto 0); 
    FAST_CLK_250_90: in std_logic_vector (0 downto 0); 
    FAST_CLK_500: in std_logic_vector (0 downto 0); 
    FAST_CLK_500_90: in std_logic_vector (0 downto 0); 
    GlobalClock: in std_logic_vector (0 downto 0); 
    async_clk: IN STD_LOGIC_VECTOR(0 DOWNTO 0)); 
END COMPONENT;
signal U2_out_0 : std_logic_vector(0 downto 0);
signal U3_out_0 : std_logic_vector(15 downto 0);
signal U4_out_0 : std_logic_vector(15 downto 0);
signal U5_out_0 : std_logic_vector(15 downto 0);
signal U6_out_0 : std_logic_vector(15 downto 0);
signal U7_out_0 : std_logic_vector(15 downto 0);
signal U8_A0 : std_logic_vector(15 downto 0);
signal U9_A1 : std_logic_vector(15 downto 0);
signal U10_A2 : std_logic_vector(15 downto 0);
signal U11_A3 : std_logic_vector(15 downto 0);
signal U12_A4 : std_logic_vector(15 downto 0);
signal U13_A5 : std_logic_vector(15 downto 0);
signal U14_A6 : std_logic_vector(15 downto 0);
signal U15_A7 : std_logic_vector(15 downto 0);
signal U16_A8 : std_logic_vector(15 downto 0);
signal U17_A9 : std_logic_vector(15 downto 0);
signal U18_A10 : std_logic_vector(15 downto 0);
signal U19_A11 : std_logic_vector(15 downto 0);
signal U20_A12 : std_logic_vector(15 downto 0);
signal U21_A13 : std_logic_vector(15 downto 0);
signal U22_A14 : std_logic_vector(15 downto 0);
signal U23_A15 : std_logic_vector(15 downto 0);
signal U24_A16 : std_logic_vector(15 downto 0);
signal U25_A17 : std_logic_vector(15 downto 0);
signal U26_A18 : std_logic_vector(15 downto 0);
signal U27_A19 : std_logic_vector(15 downto 0);
signal U28_A20 : std_logic_vector(15 downto 0);
signal U29_A21 : std_logic_vector(15 downto 0);
signal U30_A22 : std_logic_vector(15 downto 0);
signal U31_A23 : std_logic_vector(15 downto 0);
signal U32_OUT : STD_LOGIC_VECTOR (0 DOWNTO 0);
signal U34_clk : STD_LOGIC_VECTOR(0 downto 0) := (others => '0'); 
signal BUS_RateMeter_0_READ_DATA : STD_LOGIC_VECTOR (31 DOWNTO 0);
signal BUS_RateMeter_0_VLD : STD_LOGIC_VECTOR (0 DOWNTO 0);
COMPONENT MCRateMeter
  GENERIC( 
	CHANNEL_COUNT : INTEGER := 1;
	CLK_FREQ : INTEGER := 125000000 );
PORT( 
	trigger : in STD_LOGIC_VECTOR(CHANNEL_COUNT-1 downto 0);
	VETO : in STD_LOGIC;
	START : in STD_LOGIC;
	CLK : in STD_LOGIC;
	CLK_READ : in STD_LOGIC_VECTOR(0 downto 0);
	READ_ADDRESS : in STD_LOGIC_VECTOR(15 downto 0);
	READ_DATA : out STD_LOGIC_VECTOR(31 downto 0);
	READ_DATAVALID : out STD_LOGIC_VECTOR(0 downto 0) );
END COMPONENT;
signal U37_out_0 : std_logic_vector(0 downto 0);
	signal BUS_RateMeter_0_READ_ADDRESS : STD_LOGIC_VECTOR(15 downto 0);
	signal BUS_RateMeter_0_WRITE_DATA : STD_LOGIC_VECTOR(31 downto 0);
	signal BUS_RateMeter_0_W_INT : STD_LOGIC_VECTOR(0 downto 0);
	signal BUS_RateMeter_0_R_INT : STD_LOGIC_VECTOR(0 downto 0);
	signal REG_polarity_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_polarity_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_polarity_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_polarity_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_thrs_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_thrs_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_thrs_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_thrs_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_inhib_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_inhib_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_inhib_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_inhib_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_delay_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_delay_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_delay_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_delay_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_top_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_top_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_top_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_top_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_gate_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_gate_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_gate_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_gate_RD : STD_LOGIC_VECTOR(0 downto 0); 
	signal REG_ratereset_RD : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal REG_ratereset_WR : STD_LOGIC_VECTOR(31 downto 0) := x"00000000"; 
	signal INT_ratereset_WR : STD_LOGIC_VECTOR(0 downto 0); 
	signal INT_ratereset_RD : STD_LOGIC_VECTOR(0 downto 0); 
	
	component main_clock 
     port (
      clk_board : in std_logic;
      clk_adc : in std_logic;
      clk_in_sel : in std_logic;
     
      clk_out1 : out std_logic;
      clk_out2 : out std_logic;
      clk_out3 : out std_logic;
      clk_out4 : out std_logic;
      clk_out5 : out std_logic;
      clk_out6 : out std_logic;
      clk_out7 : out std_logic;
      
      reset : in std_logic;
      input_clk_stopped : out std_logic;
      locked : out std_logic
     );
     end component;

	signal NO_CLOCK_FLAG : std_logic := '0';
    signal CLOCK_INPUT_SEL : std_logic := '1';
    signal clock_source_commutator : std_logic := '0';
    signal CLOCK_ADC : std_logic := '0';
    signal CLOCK_MAIN : std_logic := '0';

	signal CLOCK_SOURCE : STD_LOGIC_VECTOR ( 3 downto 0 ) := x"0";
    signal CLOCK_SOURCE_EXT : STD_LOGIC_VECTOR ( 3 downto 0 ) := x"1";
    signal CLOCK_PL : STD_LOGIC;
    signal clock_source_commutator_b : std_logic;
    signal CLOCK_RESET :  STD_LOGIC;
    signal INVALID_CLOCK :  STD_LOGIC;
    signal CLOCK_TEST_COUNTER : STD_LOGIC_VECTOR(15 downto 0);
    signal CLOCK_TEST_OS1 : STD_LOGIC;
    signal CLOCK_TEST_OS2 : STD_LOGIC;
    
begin

ext_clock_verifier_2 : process(CLOCK_ADC) 
begin
    if rising_edge(CLOCK_ADC) then
        CLOCK_TEST_COUNTER <= CLOCK_TEST_COUNTER + 1;
    end if;    
end process;


XPM_CLK_VER: xpm_cdc_single
  generic map (
     DEST_SYNC_FF   => 4, 
     INIT_SYNC_FF   => 0,
     SIM_ASSERT_CHK => 0,
     SRC_INPUT_REG  => 1 
  )
  port map (
     src_clk  => CLOCK_ADC,
     src_in   => CLOCK_TEST_COUNTER(15),
     dest_clk => CLOCK_MAIN,
     dest_out => CLOCK_TEST_OS1
  );
  
ext_clock_verifier : process(CLOCK_MAIN) 
variable counter_int : integer;
begin
    if rising_edge(CLOCK_MAIN) then
        CLOCK_TEST_OS2 <= CLOCK_TEST_OS1;
        if CLOCK_TEST_OS1 /= CLOCK_TEST_OS2 then
            INVALID_CLOCK <= '0';
            counter_int := 0;
        else
            if counter_int = 12500000 then
                INVALID_CLOCK <= '1';
            else
                counter_int := counter_int + 1;
            end if;
        end if;
    end if;
    
end process;

  
    CLOCK_INPUT_SEL <= ((not clock_source_commutator) or INVALID_CLOCK) when CLOCK_SOURCE_EXT = x"1" else '1';
    CLOCK_SOURCE <= x"0" when CLOCK_INPUT_SEL = '1' else  CLOCK_SOURCE_EXT;

    main_clock_gen : main_clock 
     port map(
      clk_board     => CLOCK_MAIN,
      clk_adc       => CLOCK_ADC,
      clk_in_sel    => CLOCK_INPUT_SEL,
     
      clk_out1      => FAST_CLK_100(0) ,
      clk_out2      => CLOCK_PL,
      clk_out3      => FAST_CLK_200(0),
      clk_out4      => FAST_CLK_250(0),
      clk_out5      => FAST_CLK_250_90(0),
      clk_out6      => FAST_CLK_500(0),
      clk_out7      => FAST_CLK_500_90(0),
      
      reset                  => CLOCK_RESET,
      input_clk_stopped      => NO_CLOCK_FLAG, 
      locked                 => open
     );
     
     
    BOARD_CLOCK <= CLOCK_PL;


	async_clk(0) <= BOARD_CLOCK;
	CLK_ACQ(0) <= BOARD_CLOCK;
	GlobalClock(0) <= BOARD_CLOCK;
	BUS_CLK(0) <= BOARD_CLOCK;
	CLK_125(0) <= BOARD_CLOCK;
	
	GlobalReset(0) <= '0';
	
SFP_DISABLE1 <= '1';
SFP_DISABLE2 <= '1';

	SYNC_0_OUTb <= SYNC_0_OUT(0);
	SYNC_1_OUTb <= SYNC_1_OUT(0);
	SYNC_2_OUTb <= SYNC_2_OUT(0);

	SYNC_0_IN(0) <= SYNC_0_INb;
	SYNC_1_IN(0) <= SYNC_1_INb;
	SYNC_2_IN(0) <= SYNC_2_INb;
	
zynq_subsystem : component ZynqDesign_wrapper
     port map (
         DDR_0_addr(14 downto 0) => DDR_addr(14 downto 0),
         
         DDR_0_ba(2 downto 0) => DDR_ba(2 downto 0),
         DDR_0_cas_n => DDR_cas_n,
         DDR_0_ck_n => DDR_ck_n,
         DDR_0_ck_p => DDR_ck_p,
         DDR_0_cke => DDR_cke,
         DDR_0_cs_n => DDR_cs_n,
         DDR_0_dm(3 downto 0) => DDR_dm(3 downto 0),
         DDR_0_dq(31 downto 0) => DDR_dq(31 downto 0),
         DDR_0_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
         DDR_0_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
         DDR_0_odt => DDR_odt,
         DDR_0_ras_n => DDR_ras_n,
         DDR_0_reset_n => DDR_reset_n,
         DDR_0_we_n => DDR_we_n,
         FIXED_IO_0_ddr_vrn => FIXED_IO_ddr_vrn,
         FIXED_IO_0_ddr_vrp => FIXED_IO_ddr_vrp,
         FIXED_IO_0_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
         FIXED_IO_0_ps_clk => FIXED_IO_ps_clk,
         FIXED_IO_0_ps_porb => FIXED_IO_ps_porb,
         FIXED_IO_0_ps_srstb => FIXED_IO_ps_srstb,
         
         FS_0_tdata  => FS_0_tdata,
         FS_0_tready => FS_0_tready(0),
         FS_0_tvalid => FS_0_tvalid(0),

         
         GT_REFCLK_0_clk_n => GT_REFCLK_0_clk_n,
         GT_REFCLK_0_clk_p => GT_REFCLK_0_clk_p,
         GT_RX_2_rxn(0) => GT_RX_0_rxn(0),
         GT_RX_2_rxp(0) => GT_RX_0_rxp(0),
         GT_RX_3_rxn(0) => GT_RX_1_rxn(0),
         GT_RX_3_rxp(0) => GT_RX_1_rxp(0),
         --GT_RX_2_rxn(0) => GT_RX_2_rxn(0),
         --GT_RX_2_rxp(0) => GT_RX_2_rxp(0),
         --GT_RX_3_rxn(0) => GT_RX_3_rxn(0),
         --GT_RX_3_rxp(0) => GT_RX_3_rxp(0),         
         GT_TX_2_txn(0) => GT_TX_0_txn(0),
         GT_TX_2_txp(0) => GT_TX_0_txp(0),
         GT_TX_3_txn(0) => GT_TX_1_txn(0),
         GT_TX_3_txp(0) => GT_TX_1_txp(0),
         --GT_TX_2_txn(0) => GT_TX_2_txn(0),
         --GT_TX_2_txp(0) => GT_TX_2_txp(0),
         --GT_TX_3_txn(0) => GT_TX_3_txn(0),
         --GT_TX_3_txp(0) => GT_TX_3_txp(0),
         
         LINK0_FIFO_IN_tdata => HLINK0_FIFO_IN_tdata, 
         LINK0_FIFO_IN_tready => HLINK0_FIFO_IN_tready(0),
         LINK0_FIFO_IN_tvalid => HLINK0_FIFO_IN_tvalid(0),
         LINK0_FIFO_OUT_tdata => HLINK0_FIFO_OUT_tdata,
         LINK0_FIFO_OUT_tready => HLINK0_FIFO_OUT_tready(0),
         LINK0_FIFO_OUT_tvalid => HLINK0_FIFO_OUT_tvalid(0),
         LINK1_FIFO_IN_tdata => HLINK1_FIFO_IN_tdata,
         LINK1_FIFO_IN_tready => HLINK1_FIFO_IN_tready(0),
         LINK1_FIFO_IN_tvalid => HLINK1_FIFO_IN_tvalid(0),
         LINK1_FIFO_OUT_tdata => HLINK1_FIFO_OUT_tdata,
         LINK1_FIFO_OUT_tready => HLINK1_FIFO_OUT_tready(0),
         LINK1_FIFO_OUT_tvalid => HLINK1_FIFO_OUT_tvalid(0),
         
         INVALID_EXT_CLK => INVALID_CLOCK,       
         clock_source_commutator => clock_source_commutator,
         CLOCK_RESET => CLOCK_RESET,
         
         CLOCK_PL => CLOCK_PL,
         CLOCK_SOURCE => CLOCK_SOURCE,
         MAIN_CLOCK => CLOCK_MAIN,
         MAIN_RESET => MAIN_RESET,
         
         M_AVALON_0_address => M_AVALON_0_address,
         M_AVALON_0_read => M_AVALON_0_read,
         M_AVALON_0_readdata => M_AVALON_0_readdata,
         M_AVALON_0_readdatavalid => M_AVALON_0_readdatavalid,
         M_AVALON_0_waitrequest => M_AVALON_0_waitrequest,
         M_AVALON_0_write => M_AVALON_0_write,
         M_AVALON_0_writedata => M_AVALON_0_writedata,         
         cfg_abselector_0 => cfg_abselector,
         cfg_channel_selector_0 => cfg_channel_selector,
         cfg_pulse_bitsleep_0 => cfg_pulse_bitsleep,
         cfg_selected_prw_0 => cfg_selected_prw,
         cfg_serdes1_delay_0 => cfg_serdes1_delay,
         cfg_serdes1_delay_exc_0 => cfg_serdes1_delay_exc,
         SMADC_1_CSA_0 => SMADC_1_CSA,
         SMADC_1_CSB_0 => SMADC_1_CSB,
         SMADC_2_CSA_0 => open,
         SMADC_2_CSB_0 => open,
         SMADC_3_CSA_0 => open,
         SMADC_3_CSB_0 => open,
         SMADC_4_CSA_0 => open,
         SMADC_4_CSB_0 => open,
         SMADC_CLK_0 => SMADC_1_CLK,
         SMADC_MOSI_0 => MOSI,
         serdes_reset_0 => serdes_reset_0,
         
         LINK0_RXCLK => iSiClkOut,
         SIRcClock =>  iSiClkIn,
         FW_VER_0 =>  FW_VER_0,       
         FW_RELEASE_DATE_0 => FW_RELEASE_DATE_0,
         FW_STRING_0 => FW_STRING_0,
         BOARDPOSITION => BOARDPOSITION,
    
 		 IIC_0_scl_io => SLAVE_I2C_SCL_0,
         IIC_0_sda_io => SLAVE_I2C_SDA_0,

        SPI_MOSI_0_0 => SPI_MOSI_0,
        SPI_MOSI_1_0 => SPI_MOSI_1,
        SPI_CLK_0 => SPI_CLK,
        SPI_CS_0 => SPI_CS          );

   FW_VEr_0 <= REG_FIRMWARE_UNIQUE;
   FW_RELEASE_DATE_0 <= REG_FIRMWARE_BUILD;
   
   
   SMADC_1_MOSI <= MOSI;
   SMADC_2_MOSI <= MOSI;
   SMADC_3_MOSI <= MOSI;
   SMADC_4_MOSI <= MOSI;

sCLK_CH_SEL <= '1';

adcs: component adcs_top_0 
Port map(  
      sCLK_125 => sCLK_125,

      ADC_SERVICE_CLK_OUT_P => ADC_SERVICE_CLK_OUT_P,
      ADC_SERVICE_CLK_OUT_N => ADC_SERVICE_CLK_OUT_N,

      
      
      ADC_1_CLK_A_P => ADC_1_CLK_A_P,
      ADC_1_CLK_A_N => ADC_1_CLK_A_N,
      ADC_1_CLK_B_P => ADC_1_CLK_B_P,
      ADC_1_CLK_B_N => ADC_1_CLK_B_N,
      
      ADC_1_FRAME_A_P => '0',
      ADC_1_FRAME_A_N => '0',
      ADC_1_FRAME_B_P => '0',
      ADC_1_FRAME_B_N => '0',
      
      ADC_1_DATA_A_P => ADC_1_DATA_A_P,
      ADC_1_DATA_A_N => ADC_1_DATA_A_N,
      
      ADC_1_DATA_B_P => ADC_1_DATA_B_P,
      ADC_1_DATA_B_N => ADC_1_DATA_B_N,
      
      SMADC_1_CSA => open,
      SMADC_1_CSB => open,
      SMADC_1_CLK => open,
      SMADC_1_MOSI => open,
      
      
      
      ADC_2_CLK_A_P => ADC_2_CLK_A_P,
      ADC_2_CLK_A_N => ADC_2_CLK_A_N,
      ADC_2_CLK_B_P => ADC_2_CLK_B_P,
      ADC_2_CLK_B_N => ADC_2_CLK_B_N,
          
      ADC_2_FRAME_A_P => '0',
      ADC_2_FRAME_A_N => '0',
      ADC_2_FRAME_B_P => '0',
      ADC_2_FRAME_B_N => '0',
          
      ADC_2_DATA_A_P => ADC_2_DATA_A_P,
      ADC_2_DATA_A_N => ADC_2_DATA_A_N,
          
      ADC_2_DATA_B_P => ADC_2_DATA_B_P,
      ADC_2_DATA_B_N => ADC_2_DATA_B_N,
      
--          SMADC_2_CSA  => SMADC_2_CSA,
--          SMADC_2_CSB  => SMADC_2_CSB,
      
      
      
      ADC_3_CLK_A_P  => ADC_3_CLK_A_P,
      ADC_3_CLK_A_N  => ADC_3_CLK_A_N,
      ADC_3_CLK_B_P  => ADC_3_CLK_B_P,
      ADC_3_CLK_B_N  => ADC_3_CLK_B_N,
          
      ADC_3_FRAME_A_P  => '0',
      ADC_3_FRAME_A_N  => '0',
      ADC_3_FRAME_B_P  => '0',
      ADC_3_FRAME_B_N  => '0',
          
      ADC_3_DATA_A_P => ADC_3_DATA_A_P,
      ADC_3_DATA_A_N => ADC_3_DATA_A_N,
          
      ADC_3_DATA_B_P => ADC_3_DATA_B_P,
      ADC_3_DATA_B_N => ADC_3_DATA_B_N,
      
--          SMADC_3_CSA  => SMADC_3_CSA,
--          SMADC_3_CSB  => SMADC_3_CSB,

      
      ADC_4_CLK_A_P  => ADC_4_CLK_A_P,
      ADC_4_CLK_A_N  => ADC_4_CLK_A_N,
      ADC_4_CLK_B_P  => ADC_4_CLK_B_P,
      ADC_4_CLK_B_N  => ADC_4_CLK_B_N,
          
      ADC_4_FRAME_A_P  => '0',
      ADC_4_FRAME_A_N  => '0',
      ADC_4_FRAME_B_P  => '0',
      ADC_4_FRAME_B_N  => '0',
          
      ADC_4_DATA_A_P  => ADC_4_DATA_A_P,
      ADC_4_DATA_A_N  => ADC_4_DATA_A_N,
          
      ADC_4_DATA_B_P => ADC_4_DATA_B_P,
      ADC_4_DATA_B_N => ADC_4_DATA_B_N,
      
--          SMADC_4_CSA  => SMADC_4_CSA,
--          SMADC_4_CSB  => SMADC_4_CSB,
      
      READOUT_CLK  => CLK_ACQ(0),
      
      CH0  =>  CH0,
      CH1  =>  CH1,
      CH2  =>  CH2,
      CH3  =>  CH3,                                            
      CH4  =>  CH4,
      CH5  =>  CH5,
      CH6  =>  CH6,
      CH7  =>  CH7,
      CH8  =>  CH8,                                                                                     
      CH9  =>  CH9,
      CH10  => CH10,
      CH11  => CH11,
      CH12  => CH12,
      CH13  => CH13,
      CH14  => CH14,
      CH15  => CH15,
      CH16  => CH16,
      CH17  => CH17,
      CH18  => CH18,
      CH19  => CH19,
      CH20  => CH20,
      CH21  => CH21,
      CH22  => CH22,
      CH23  => CH23,
      CH24  => CH24,
      CH25  => CH25,
      CH26  => CH26,
      CH27  => CH27,
      CH28  => CH28,
      CH29  => CH29,
      CH30  => CH30,
      CH31  => CH31,
      CHv0_7  => CHv0_7,
      CHv8_15  => CHv8_15,
      CHv16_23  => CHv16_23,
      CHv24_31  => CHv24_31,
      
      cfg_abselector => cfg_abselector,
      cfg_channel_selector => cfg_channel_selector,
      cfg_pulse_bitsleep => cfg_pulse_bitsleep,
      cfg_selected_prw => cfg_selected_prw,
      cfg_serdes1_delay => cfg_serdes1_delay,
      cfg_serdes1_delay_exc => cfg_serdes1_delay_exc,
      
      serdes_reset_0 => serdes_reset_0        

      );


	CHA0<=CH23;
	CHA1<=CH22;
	CHA2<=CH21;
	CHA3<=CH20;
	CHA4<=CH19;
	CHA5<=CH18;
	CHA6<=CH17;
	CHA7<=CH16;
	CHA8<=CH7;
	CHA9<=CH6;
	CHA10<=CH5;
	CHA11<=CH4;
	CHA12<=CH3;
	CHA13<=CH2;
	CHA14<=CH1;
	CHA15<=CH0;
	CHA16<=CH31;
	CHA17<=CH30;
	CHA18<=CH29;
	CHA19<=CH28;
	CHA20<=CH27;
	CHA21<=CH26;
	CHA22<=CH25;
	CHA23<=CH24;
	CHA24<=CH15;
	CHA25<=CH14;
	CHA26<=CH13;
	CHA27<=CH12;
	CHA28<=CH11;
	CHA29<=CH10;
	CHA30<=CH9;
	CHA31<=CH8;


AW_MEMORY_MANAGER : avalon_wrapper 
    Generic Map (M_AVALON_BA  => x"14000000")
    Port Map(  clk => BUS_CLK(0),
            reset => '0',
            M_AVALON_0_address => M_AVALON_0_address,
            M_AVALON_0_read => M_AVALON_0_read,
            M_AVALON_0_readdata => M_AVALON_0_readdata,
            M_AVALON_0_readdatavalid => M_AVALON_0_readdatavalid,
            M_AVALON_0_waitrequest => M_AVALON_0_waitrequest,
            M_AVALON_0_write => M_AVALON_0_write,
            M_AVALON_0_writedata => M_AVALON_0_writedata,
     
    
			--test
            BUS_Test_0_READ_DATA => BUS_Test_0_READ_DATA,
            BUS_Test_0_ADDRESS => BUS_Test_0_ADDRESS, 
            BUS_Test_0_WRITE_DATA => BUS_Test_0_WRITE_DATA, 
            BUS_Test_0_W_INT => BUS_Test_0_W_INT, 
            BUS_Test_0_R_INT => BUS_Test_0_R_INT, 
            BUS_Test_0_VLD => BUS_Test_0_VLD,               

            -- Register interface          
		REG_polarity_RD => REG_polarity_RD,
		REG_polarity_WR => REG_polarity_WR,
		INT_polarity_RD => INT_polarity_RD,
		INT_polarity_WR => INT_polarity_WR,
		REG_thrs_RD => REG_thrs_RD,
		REG_thrs_WR => REG_thrs_WR,
		INT_thrs_RD => INT_thrs_RD,
		INT_thrs_WR => INT_thrs_WR,
		REG_inhib_RD => REG_inhib_RD,
		REG_inhib_WR => REG_inhib_WR,
		INT_inhib_RD => INT_inhib_RD,
		INT_inhib_WR => INT_inhib_WR,
		REG_delay_RD => REG_delay_RD,
		REG_delay_WR => REG_delay_WR,
		INT_delay_RD => INT_delay_RD,
		INT_delay_WR => INT_delay_WR,
		REG_top_RD => REG_top_RD,
		REG_top_WR => REG_top_WR,
		INT_top_RD => INT_top_RD,
		INT_top_WR => INT_top_WR,
		REG_gate_RD => REG_gate_RD,
		REG_gate_WR => REG_gate_WR,
		INT_gate_RD => INT_gate_RD,
		INT_gate_WR => INT_gate_WR,
	BUS_RateMeter_0_READ_ADDRESS => BUS_RateMeter_0_READ_ADDRESS,
	BUS_RateMeter_0_READ_DATA => BUS_RateMeter_0_READ_DATA,
	BUS_RateMeter_0_WRITE_DATA => BUS_RateMeter_0_WRITE_DATA,
	BUS_RateMeter_0_W_INT => BUS_RateMeter_0_W_INT,
	BUS_RateMeter_0_R_INT => BUS_RateMeter_0_R_INT,
	BUS_RateMeter_0_VLD => BUS_RateMeter_0_VLD,
		REG_ratereset_RD => REG_ratereset_RD,
		REG_ratereset_WR => REG_ratereset_WR,
		INT_ratereset_RD => INT_ratereset_RD,
		INT_ratereset_WR => INT_ratereset_WR,
		REG_UNIQUE_RD => x"00112233",
		REG_UNIQUE_WR => open,
   

            REG_FIRMWARE_UNIQUE => REG_FIRMWARE_UNIQUE,
            REG_FIRMWARE_BUILD => REG_FIRMWARE_BUILD    
    );


--xpm_memory_spram_inst : xpm_memory_spram
--    generic map (
--        -- Common module generics
--        MEMORY_SIZE => 2048, --positive integer
--        MEMORY_PRIMITIVE => "auto", --string; "auto", "distributed", "block" or "ultra" ;
--        MEMORY_INIT_FILE => "none", --string; "none" or "<filename>.mem"
--        MEMORY_INIT_PARAM => "", --string;
--        USE_MEM_INIT => 1, --integer; 0,1
--        WAKEUP_TIME => "disable_sleep",--string; "disable_sleep" or "use_sleep_pin"
--        MESSAGE_CONTROL => 0, --integer; 0,1
--        -- Port A module generics
--        WRITE_DATA_WIDTH_A => 32, --positive integer
--        READ_DATA_WIDTH_A => 32, --positive integer
--        BYTE_WRITE_WIDTH_A => 32, --integer; 8, 9, or WRITE_DATA_WIDTH_A value
--        ADDR_WIDTH_A => 6, --positive integer
--        READ_RESET_VALUE_A => "0", --string
--        READ_LATENCY_A => 1, --non-negative integer
--        WRITE_MODE_A => "write_first" --string; "write_first", "read_first", "no_change"
--    )
--    port map (
--        -- Common module ports
--        sleep => '0',
--        -- Port A module ports
--        clka => BUS_CLK(0),
--        rsta => '0',
--        ena => '1',
--        regcea => '1',
--        wea => BUS_Test_0_W_INT,
--        addra => BUS_Test_0_ADDRESS(5 downto 0),
--        dina => BUS_Test_0_WRITE_DATA,
--        injectsbiterra => '0', --do not change
--        injectdbiterra => '0', --do not change
--        douta => BUS_Test_0_READ_DATA,
--        sbiterra => open, --do not change
--        dbiterra => open --do not change
--);	  


   SiClkIn : IBUFDS
   generic map (
      DIFF_TERM => TRUE, -- Differential Termination 
      IBUF_LOW_PWR => TRUE, -- Low power (TRUE) vs. performance (FALSE) setting for referenced I/O standards
      IOSTANDARD => "DEFAULT")
   port map (
      O => iSiClkIn,  -- Buffer output
      I => Si_ClkIn_p,  -- Diff_p buffer input (connect directly to top-level port)
      IB => Si_ClkIn_n -- Diff_n buffer input (connect directly to top-level port)
   );

   SiClkOut : OBUFDS
   generic map (
      IOSTANDARD => "DEFAULT", -- Specify the output I/O standard
      SLEW => "SLOW")          -- Specify the output slew rate
   port map (
      O => Si_ClkOut_p,     -- Diff_p output (connect directly to top-level port)
      OB => Si_ClkOut_n,   -- Diff_n output (connect directly to top-level port)
      I => iSiClkOut      -- Buffer input 
   );
  
  
  CLK_LINK(0) <= iSiClkIn;

	  
U0_0:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U8_A0,
	TRIGOUT => U0_TRIGOUT_0,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_1:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U9_A1,
	TRIGOUT => U0_TRIGOUT_1,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_2:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U10_A2,
	TRIGOUT => U0_TRIGOUT_2,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_3:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U11_A3,
	TRIGOUT => U0_TRIGOUT_3,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_4:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U12_A4,
	TRIGOUT => U0_TRIGOUT_4,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_5:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U13_A5,
	TRIGOUT => U0_TRIGOUT_5,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_6:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U14_A6,
	TRIGOUT => U0_TRIGOUT_6,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_7:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U15_A7,
	TRIGOUT => U0_TRIGOUT_7,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_8:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U16_A8,
	TRIGOUT => U0_TRIGOUT_8,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_9:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U17_A9,
	TRIGOUT => U0_TRIGOUT_9,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_10:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U18_A10,
	TRIGOUT => U0_TRIGOUT_10,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_11:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U19_A11,
	TRIGOUT => U0_TRIGOUT_11,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_12:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U20_A12,
	TRIGOUT => U0_TRIGOUT_12,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_13:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U21_A13,
	TRIGOUT => U0_TRIGOUT_13,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_14:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U22_A14,
	TRIGOUT => U0_TRIGOUT_14,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_15:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U23_A15,
	TRIGOUT => U0_TRIGOUT_15,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_16:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U24_A16,
	TRIGOUT => U0_TRIGOUT_16,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_17:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U25_A17,
	TRIGOUT => U0_TRIGOUT_17,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_18:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U26_A18,
	TRIGOUT => U0_TRIGOUT_18,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_19:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U27_A19,
	TRIGOUT => U0_TRIGOUT_19,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_20:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U28_A20,
	TRIGOUT => U0_TRIGOUT_20,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_21:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U29_A21,
	TRIGOUT => U0_TRIGOUT_21,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_22:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U30_A22,
	TRIGOUT => U0_TRIGOUT_22,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);

U0_23:SUBPAGE_TriggerWindow
PORT MAP(
	AIN => U31_A23,
	TRIGOUT => U0_TRIGOUT_23,
	polarity => U2_out_0,
	thrs => U3_out_0,
	inhib => U4_out_0,
	delay => U5_out_0,
	top => U6_out_0,
	gate => U7_out_0,
    GlobalReset => GlobalReset,
    CLK_ACQ=>CLK_ACQ ,
    BUS_CLK=>BUS_CLK ,
    CLK_40=>CLK_40 ,
    CLK_50 => "0" ,
    CLK_80=>CLK_80 ,
    clk_160=>clk_160 ,
    clk_320=>clk_320 ,
    clk_125=>clk_125 ,
    FAST_CLK_100=>FAST_CLK_100 ,
    FAST_CLK_200=>FAST_CLK_200 ,
    FAST_CLK_250=>FAST_CLK_250 ,
    FAST_CLK_250_90=>FAST_CLK_250_90 ,
    FAST_CLK_500=>FAST_CLK_500 ,
    FAST_CLK_500_90=>FAST_CLK_500_90 ,
    GlobalClock=>GlobalClock ,
    async_clk => async_clk 
);
U2_out_0 <= REG_polarity_WR(0 downto 0);
U3_out_0 <= REG_thrs_WR(15 downto 0);
U4_out_0 <= REG_inhib_WR(15 downto 0);
U5_out_0 <= REG_delay_WR(15 downto 0);
U6_out_0 <= REG_top_WR(15 downto 0);
U7_out_0 <= REG_gate_WR(15 downto 0);
U8_A0 <= CHA0;
U9_A1 <= CHA1;
U10_A2 <= CHA2;
U11_A3 <= CHA3;
U12_A4 <= CHA4;
U13_A5 <= CHA5;
U14_A6 <= CHA6;
U15_A7 <= CHA7;
U16_A8 <= CHA8;
U17_A9 <= CHA9;
U18_A10 <= CHA10;
U19_A11 <= CHA11;
U20_A12 <= CHA12;
U21_A13 <= CHA13;
U22_A14 <= CHA14;
U23_A15 <= CHA15;
U24_A16 <= CHA16;
U25_A17 <= CHA17;
U26_A18 <= CHA18;
U27_A19 <= CHA19;
U28_A20 <= CHA20;
U29_A21 <= CHA21;
U30_A22 <= CHA22;
U31_A23 <= CHA23;
U32_OUT <= U0_TRIGOUT_0 OR U0_TRIGOUT_1 OR U0_TRIGOUT_2 OR U0_TRIGOUT_3 OR U0_TRIGOUT_4 OR U0_TRIGOUT_5 OR U0_TRIGOUT_6 OR U0_TRIGOUT_7 OR U0_TRIGOUT_8 OR U0_TRIGOUT_9 OR U0_TRIGOUT_10 OR U0_TRIGOUT_11 OR U0_TRIGOUT_12 OR U0_TRIGOUT_13 OR U0_TRIGOUT_14 OR U0_TRIGOUT_15 OR U0_TRIGOUT_16 OR U0_TRIGOUT_17 OR U0_TRIGOUT_18 OR U0_TRIGOUT_19 OR U0_TRIGOUT_20 OR U0_TRIGOUT_21 OR U0_TRIGOUT_22 OR U0_TRIGOUT_23;
SYNC_0_OUT <= U32_OUT;

U34_clk <= CLK_ACQ;
U36 : MCRateMeter
  Generic map(
	CHANNEL_COUNT => 	1,
	CLK_FREQ => 	125000000)
PORT MAP(
	trigger => U32_OUT,
	VETO => '0',
	START => U37_out_0(0),
	CLK => U34_clk(0),
	CLK_READ => BUS_CLK,
	READ_ADDRESS => BUS_RateMeter_0_READ_ADDRESS,
	READ_DATA => BUS_RateMeter_0_READ_DATA,
	READ_DATAVALID => BUS_RateMeter_0_VLD );
U37_out_0 <= REG_ratereset_WR(0 downto 0);
REG_FIRMWARE_BUILD <= x"20220413";
FW_STRING_0 <= x"50754265547269676765723500000000";

end Behavioral;