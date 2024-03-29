set_property ALLOW_COMBINATORIAL_LOOPS true [get_nets -of_objects [get_cells Q_OBUF_inst_i_1]]
set_property SEVERITY {Warning} [get_drc_checks LUTLP-1]
set_property SEVERITY {Warning} [get_drc_checks NSTD-1]

set_property IOSTANDARD LVCMOS18 [get_ports D]
set_property IOSTANDARD LVCMOS18 [get_ports clk]
set_property IOSTANDARD LVCMOS18 [get_ports Q]
set_property IOSTANDARD LVCMOS18 [get_ports QC]

set_property PACKAGE_PIN J4 [get_ports D]
set_property PACKAGE_PIN L3 [get_ports clk]
set_property PACKAGE_PIN F15 [get_ports Q]
set_property PACKAGE_PIN F13 [get_ports QC]