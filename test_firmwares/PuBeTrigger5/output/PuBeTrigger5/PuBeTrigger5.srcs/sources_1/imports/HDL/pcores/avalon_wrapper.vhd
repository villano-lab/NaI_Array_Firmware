----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07.03.2019 15:43:42
-- Design Name: 
-- Module Name: avalon_wrapper - Behavioral
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity avalon_wrapper is
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
end avalon_wrapper;

architecture Behavioral of avalon_wrapper is
    --DA FPGA A PC
	signal f_BUS_INT_RD 	 :  STD_LOGIC;						--INTERRUPT DI LETTURA
	signal f_BUS_DATASTROBE  :  STD_LOGIC;						--CONFERMA CHE I DATI RICHIESTI SONO DISPONIBILI
	signal f_BUS_DATASTROBE_REG  :  STD_LOGIC;						--CONFERMA CHE I DATI RICHIESTI SONO DISPONIBILI (REGISTRI)
	signal f_BUS_DATA_RD	 :  STD_LOGIC_VECTOR(31 downto 0);	--DATI DA INVIARE AL PC
	signal f_BUS_DATA_RD_REG :  STD_LOGIC_VECTOR(31 downto 0);	--DATI DA INVIARE AL PC (REGISTRI)
	signal BUS_ADDR :  STD_LOGIC_VECTOR(31 downto 0);	         --INDIRIZZI
	
	--DA PC A FPGA
	signal f_BUS_INT_WR 	 :  STD_LOGIC;						--INTERRUPT DI SCRITTURA
	signal f_BUS_DATA_WR	 :  STD_LOGIC_VECTOR(31 downto 0);	--DATI DA INVIATI DAL PC
	signal wreg				 :  STD_LOGIC_VECTOR(31 downto 0);
	signal addr 			 : STD_LOGIC_VECTOR(31 downto 0);
	
	attribute keep : string;  
	attribute keep of BUS_ADDR: signal is "true"; 
	
begin


--    BUS_Test_0_R_INT(0) <= f_BUS_INT_RD when (addr >= x"03FE0000" And addr < x"03FEFFFF") else '0';
    BUS_Test_0_ADDRESS  <=  BUS_ADDR(15 downto 0) when (addr >= x"03FE0000" And addr < x"03FEFFFF") else (others => '0');
    BUS_Test_0_WRITE_DATA  <= f_BUS_DATA_WR;    
    BUS_Test_0_W_INT (0) <=  f_BUS_INT_WR when (addr >= x"03FE0000" And addr < x"03FEFFFF") else '0';
--    f_BUS_DATA_RD    <=     BUS_Test_0_READ_DATA when  (addr >= x"03FE0000" And addr < x"03FEFFFF") else 
--                             f_BUS_DATA_RD_REG;  
    
BUS_RateMeter_0_R_INT(0) <= f_BUS_INT_RD when (addr >= x"00010000" And addr < x"00020000") else '0';
BUS_RateMeter_0_READ_ADDRESS <= BUS_ADDR(15 downto 0) when (addr >= x"00010000" And addr < x"00020000") else (others => '0');
f_BUS_DATA_RD <= BUS_Test_0_READ_DATA when  (addr >= x"03FE0000" And addr < x"03FEFFFF") else 
BUS_RateMeter_0_READ_DATA  when  addr >= x"00010000" and addr < x"00020000" else 
 f_BUS_DATA_RD_REG;
 f_BUS_DATASTROBE <=BUS_Test_0_VLD(0) when  (addr >= x"03FE0000" And addr < x"03FEFFFF") else 
 BUS_RateMeter_0_VLD(0) when  addr >= x"00010000" and addr < x"00020000" else 
 f_BUS_DATASTROBE_REG;    

        
    addr <= BUS_ADDR;
    wreg <= f_BUS_DATA_WR;
        
        register_manager : process(clk)
            variable rreg    :  STD_LOGIC_VECTOR(31 downto 0);
        begin
            if reset='1' then
--                		REG_polarity_WR <= (others => '0');
		INT_polarity_WR <= "0";
		INT_polarity_RD <= "0";
		REG_thrs_WR <= (others => '0');
		INT_thrs_WR <= "0";
		INT_thrs_RD <= "0";
		REG_inhib_WR <= (others => '0');
		INT_inhib_WR <= "0";
		INT_inhib_RD <= "0";
		REG_delay_WR <= (others => '0');
		INT_delay_WR <= "0";
		INT_delay_RD <= "0";
		REG_top_WR <= (others => '0');
		INT_top_WR <= "0";
		INT_top_RD <= "0";
		REG_gate_WR <= (others => '0');
		INT_gate_WR <= "0";
		INT_gate_RD <= "0";
	BUS_RateMeter_0_W_INT <= "0";
		REG_ratereset_WR <= (others => '0');
		INT_ratereset_WR <= "0";
		INT_ratereset_RD <= "0";
            
                f_BUS_DATASTROBE_REG <= '0';
                M_AVALON_0_readdatavalid <= '0';
            elsif rising_edge(clk) then
            
            M_AVALON_0_readdatavalid <= '0';
    		INT_polarity_WR <= "0";
		INT_polarity_RD <= "0";
		INT_thrs_WR <= "0";
		INT_thrs_RD <= "0";
		INT_inhib_WR <= "0";
		INT_inhib_RD <= "0";
		INT_delay_WR <= "0";
		INT_delay_RD <= "0";
		INT_top_WR <= "0";
		INT_top_RD <= "0";
		INT_gate_WR <= "0";
		INT_gate_RD <= "0";
	BUS_RateMeter_0_W_INT <= "0";
		INT_ratereset_WR <= "0";
		INT_ratereset_RD <= "0";
  
                f_BUS_DATASTROBE_REG <= '0';
                
               if f_BUS_INT_WR = '1' then
        
        
    		if addr = x"00000000" then
			REG_polarity_WR <= wreg; 
			INT_polarity_WR <= "1"; 
		end if;
		if addr = x"00000001" then
			REG_thrs_WR <= wreg; 
			INT_thrs_WR <= "1"; 
		end if;
		if addr = x"00000002" then
			REG_inhib_WR <= wreg; 
			INT_inhib_WR <= "1"; 
		end if;
		if addr = x"00000003" then
			REG_delay_WR <= wreg; 
			INT_delay_WR <= "1"; 
		end if;
		if addr = x"00000004" then
			REG_top_WR <= wreg; 
			INT_top_WR <= "1"; 
		end if;
		if addr = x"00000005" then
			REG_gate_WR <= wreg; 
			INT_gate_WR <= "1"; 
		end if;
		If addr >= x"00010000" And addr < x"00020000" Then
			BUS_RateMeter_0_WRITE_DATA <= wreg; 
			BUS_RateMeter_0_W_INT <= "1"; 
		End If;
		if addr = x"00020000" then
			REG_ratereset_WR <= wreg; 
			INT_ratereset_WR <= "1"; 
		end if;

                end if;
        
        
                if f_BUS_INT_RD = '1' then
                    f_BUS_DATASTROBE_REG <= '1';
                    rreg := x"DEADBEEF";
    
    		if addr = x"00000000" then
			rreg := REG_polarity_RD; 
		End If;
		if addr = x"00000001" then
			rreg := REG_thrs_RD; 
		End If;
		if addr = x"00000002" then
			rreg := REG_inhib_RD; 
		End If;
		if addr = x"00000003" then
			rreg := REG_delay_RD; 
		End If;
		if addr = x"00000004" then
			rreg := REG_top_RD; 
		End If;
		if addr = x"00000005" then
			rreg := REG_gate_RD; 
		End If;
		if addr = x"00020000" then
			rreg := REG_ratereset_RD; 
		End If;
    
                   
                    if addr = x"03FFFFFF" then
                        rreg := x"00556000"; 
                    End If;    
                    if addr = x"03FFFFFE" then
                        rreg := REG_FIRMWARE_BUILD; 
                    End If; 
                    if addr = x"03FFFFFD" then
                        rreg := REG_FIRMWARE_UNIQUE; 
                    End If; 

                    f_BUS_DATA_RD_REG <= rreg;
                    
                    M_AVALON_0_readdatavalid <= '1';
                end if;
    
            end if;
        end process;
            
    M_AVALON_0_waitrequest <= '0';
    
    BUS_ADDR <= M_AVALON_0_address - M_AVALON_BA;
    f_BUS_INT_RD <= M_AVALON_0_read;
    f_BUS_INT_WR <= M_AVALON_0_write;
    M_AVALON_0_readdata <= f_BUS_DATA_RD;
    f_BUS_DATA_WR <= M_AVALON_0_writedata;
    
--    test_reg_process : process (clk)
--    begin
--        if rising_edge(clk) then
            
            
--            if M_AVALON_0_write= '1' then
--                TEST_REG <= M_AVALON_0_writedata +1;
--            end if;
            
--            M_AVALON_0_readdatavalid <= '0';
            
--            if M_AVALON_0_read= '1' then
--                M_AVALON_0_readdata <= M_AVALON_0_address;
--                if M_AVALON_0_address=x"10000000" then
                
--                else
--                    M_AVALON_0_readdatavalid <= '1';
--                end if;
--            end if;
--        end if;
--    end process;

end Behavioral;
