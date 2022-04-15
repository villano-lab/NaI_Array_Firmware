library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_MISC.ALL;
use ieee.numeric_std.all;
use ieee.math_real.all;



entity SUBPAGE_TriggerWindow is
    Port (	
		AIN : in std_logic_vector(15 downto 0);
TRIGOUT : out std_logic_vector(0 downto 0);
delay : in std_logic_vector(15 downto 0);
gate : in std_logic_vector(15 downto 0);
polarity : in std_logic_vector(0 downto 0);
thrs : in std_logic_vector(15 downto 0);
top : in std_logic_vector(15 downto 0);
inhib : in std_logic_vector(15 downto 0);

		async_clk : in std_logic_vector (0 downto 0);
		CLK_ACQ : in std_logic_vector (0 downto 0);
		BUS_CLK : in std_logic_vector (0 downto 0);
		CLK_40 : in std_logic_vector (0 downto 0);
		CLK_50 : in std_logic_vector (0 downto 0);
		CLK_80 : in std_logic_vector (0 downto 0);
		clk_160 : in std_logic_vector (0 downto 0);
		clk_320 : in std_logic_vector (0 downto 0);
		CLK_125 : in std_logic_vector(0 downto 0);
		FAST_CLK_100 : in std_logic_vector (0 downto 0);
		FAST_CLK_200 : in std_logic_vector (0 downto 0);
		FAST_CLK_250 : in std_logic_vector (0 downto 0);
		FAST_CLK_250_90 : in std_logic_vector (0 downto 0);
		FAST_CLK_500 : in std_logic_vector (0 downto 0);
		FAST_CLK_500_90 : in std_logic_vector (0 downto 0);
		GlobalClock : in std_logic_vector (0 downto 0);
		GlobalReset : in std_logic_vector (0 downto 0)
		
 );
end SUBPAGE_TriggerWindow;

architecture Behavioral of SUBPAGE_TriggerWindow is

COMPONENT TRIGGER_LEADING
Generic (	wordWidth : integer := 16;
			noise_filter : integer := 0;
			data_delay : integer := 1);
port (
	RESET: IN STD_LOGIC_VECTOR(0 DOWNTO 0);
	CLK : IN STD_LOGIC_VECTOR (0 DOWNTO 0);
	CE : IN STD_LOGIC_VECTOR (0 DOWNTO 0);
	POLARITY: IN STD_LOGIC_VECTOR(0 DOWNTO 0);
	PORT_IN: IN STD_LOGIC_VECTOR(wordWidth-1 DOWNTO 0);
	THRESHOLD: IN STD_LOGIC_VECTOR(wordWidth-1 DOWNTO 0);
	TRIGGER_INIB: IN INTEGER;
	DELAYED_DATA: OUT STD_LOGIC_VECTOR(wordWidth-1 DOWNTO 0);
	TOT: OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
	TRIGGER_OUT: OUT STD_LOGIC_VECTOR(0 DOWNTO 0)
);
END COMPONENT;
signal U0_trigger_out : std_logic_vector(0 downto 0) := (others => '0');
signal U1_trigger_out : std_logic_vector(0 downto 0) := (others => '0');
signal U2_b : STD_LOGIC_VECTOR (15 DOWNTO 0);
COMPONENT polinvert
  GENERIC( 
	A_SIZE : INTEGER := 16;
	SIGN : STRING := "UNSIGNED";
	AN_SIZE : INTEGER := 16 );
PORT( 
	a : in STD_LOGIC_VECTOR(A_SIZE-1 downto 0);
	pol : in STD_LOGIC_VECTOR(0 downto 0);
	b : out STD_LOGIC_VECTOR(A_SIZE-1 downto 0) );
END COMPONENT;
signal U3_OUT : STD_LOGIC_VECTOR (0 DOWNTO 0);
signal U4_AIN : std_logic_vector(15 downto 0);

COMPONENT SW_GATE_AND_DELAY
Generic (	maxDelay : integer := 16);
PORT(
    RESET: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    CLK: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    PORT_IN: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    DELAY: IN INTEGER; 
    GATE: IN INTEGER; 
    PORT_OUT: OUT STD_LOGIC_VECTOR(0 DOWNTO 0)); 
END COMPONENT;
signal U7_out : std_logic_vector(0 downto 0) := (others => '0');
signal U8_CONST : INTEGER := 0;

COMPONENT SYNC_DELAY
Generic (	maxDelay : integer := 16;
        	busWidth : integer := 1);
PORT(
    RESET: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    CLK: IN STD_LOGIC_VECTOR(0 DOWNTO 0); 
    PORT_IN: IN STD_LOGIC_VECTOR(busWidth-1 DOWNTO 0); 
    DELAY: IN INTEGER; 
    PORT_OUT: OUT STD_LOGIC_VECTOR(busWidth-1 DOWNTO 0)); 
END COMPONENT;
signal U9_out : std_logic_vector(0 downto 0) := (others => '0');
signal U10_delay : std_logic_vector(15 downto 0);
signal U11_int : integer range 0 to 65535 := 0;
signal U12_gate : std_logic_vector(15 downto 0);
signal U13_int : integer range 0 to 65535 := 0;
signal U14_polarity : std_logic_vector(0 downto 0);
signal U15_thrs : std_logic_vector(15 downto 0);
signal U16_top : std_logic_vector(15 downto 0);
signal U17_inhib : std_logic_vector(15 downto 0);
signal U18_int : integer range 0 to 65535 := 0;

begin

U0:TRIGGER_LEADING
Generic Map(	wordWidth =>16,
			noise_filter =>0,
			data_delay =>1)
port Map(
	RESET =>GlobalReset,
	CLK =>async_clk,
	CE =>"1",
	POLARITY =>U14_polarity,
	PORT_IN =>U2_b,
	THRESHOLD =>U15_thrs,
	TRIGGER_INIB =>U18_int,
	DELAYED_DATA =>open,
	TOT =>open,
	TRIGGER_OUT =>U0_trigger_out
);

U1:TRIGGER_LEADING
Generic Map(	wordWidth =>16,
			noise_filter =>0,
			data_delay =>1)
port Map(
	RESET =>GlobalReset,
	CLK =>async_clk,
	CE =>"1",
	POLARITY =>"0",
	PORT_IN =>U2_b,
	THRESHOLD =>U16_top,
	TRIGGER_INIB =>U18_int,
	DELAYED_DATA =>open,
	TOT =>open,
	TRIGGER_OUT =>U1_trigger_out
);
U2 : polinvert
  Generic map(
	A_SIZE => 	16,
	SIGN => 	"UNSIGNED",
	AN_SIZE => 	16)
PORT MAP(
	a => U4_AIN,
	pol => U14_polarity,
	b => U2_b );
U3_OUT <= U9_out AND ( NOT sxt(U7_out,1));
U4_AIN <= AIN;
TRIGOUT <= U3_OUT;

U7:SW_GATE_AND_DELAY
GENERIC MAP(
    maxDelay => 1024)
PORT MAP(
    RESET => GlobalReset,
    CLK => async_clk,
    PORT_IN => U1_trigger_out,
    DELAY => U8_CONST,
    GATE => U13_int,
    PORT_OUT => U7_out
);
U8_CONST <= 0;

U9:SYNC_DELAY
GENERIC MAP(
    maxDelay => 1024,
    busWidth => 1)
PORT MAP(
    RESET => GlobalReset,
    CLK => async_clk,
    PORT_IN => U0_trigger_out,
    DELAY => U11_int,
    PORT_OUT => U9_out
);
U10_delay <= delay;
U11_int <= conv_integer(U10_delay);
U12_gate <= gate;
U13_int <= conv_integer(U12_gate);
U14_polarity <= polarity;
U15_thrs <= thrs;
U16_top <= top;
U17_inhib <= inhib;
U18_int <= conv_integer(U17_inhib);

end Behavioral;
