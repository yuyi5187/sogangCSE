set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets {clk_IBUF}]


set_property IOSTANDARD LVCMOS18 [get_ports j]
set_property IOSTANDARD LVCMOS18 [get_ports k]
set_property IOSTANDARD LVCMOS18 [get_ports clk]
set_property IOSTANDARD LVCMOS18 [get_ports Q]
set_property IOSTANDARD LVCMOS18 [get_ports QC]

set_property PACKAGE_PIN J4 [get_ports j]
set_property PACKAGE_PIN L3 [get_ports k]
set_property PACKAGE_PIN K3 [get_ports clk]
set_property PACKAGE_PIN F15 [get_ports Q]
set_property PACKAGE_PIN F13 [get_ports QC]