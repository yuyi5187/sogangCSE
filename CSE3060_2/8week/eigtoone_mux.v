`timescale 1ns / 1ps
/////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////


module eigtoone_mux(
input s2,s1,s0,
input d0,d1,d2,d3,d4,d5,d6,d7,
output y);
assign y=d0&(~s2)&(~s1)&(~s0)|d1&(~s2)&(~s1)&s0|d2&(~s2)&(s1)&(~s0)|d3&(~s2)&s1&s0|d4&s2&(~s1)&(~s0)|
d5&s2&s1&(s0)|d6&s2&s1&(~s0)|d7&s2&s1&s0;
endmodule
