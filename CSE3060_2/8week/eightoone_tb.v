`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module eightoone_tb(
    );

reg s2,s1,s0;
reg d0,d1,d2,d3,d4,d5,d6,d7;
wire y;
eigtoone_mux u_eigtoone_mux(.s2(s2), .s1(s1),.s0(s0),.d0(d0),.d1(d1),.d2(d2),.d3(d3),.d4(d4),.d5(d5),.d6(d6),.d7(d7),.y(y));

initial begin
s2=1'b0; s1=1'b0;s0=1'b0;
d0=1'b1; d1=1'b0; d2=1'b0;
d3=1'b0; d4=1'b1; d5=1'b0;
d6=1'b0; d7=1'b0;
end

always s2=#400~s2;
always s1=#200~s1;
always s0=#100~s0;

initial begin 
#1000
$finish;
end
    
endmodule
