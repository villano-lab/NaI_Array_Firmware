Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use ieee.std_logic_unsigned.all;

-- Clock -- for testing.
entity U2_UserHDL_Clock_Tx is
port (
 clock_in: in STD_LOGIC;
 clock_out: buffer STD_LOGIC
);
end U2_UserHDL_Clock_Tx;

architecture behavioural of U2_UserHDL_Clock_Tx is
begin
 clock_out <= clock_in;
end behavioural;