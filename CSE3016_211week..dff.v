`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
 
module dff(
input D,
input clk,
output reg Q,
output QC
);
assign QC=~Q;
always@(posedge clk)
begin 
Q<=D;
end
endmodule
