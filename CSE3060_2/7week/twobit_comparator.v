`timescale 1ns / 1ps
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


module twobit_comparator(
input a,
input b,
input c,
input d,
output f1,
output f2,
output f3 
    );
    assign f1=(b&(~c)&(~d))|(a&(~c))|(a&b&(~d));
    assign f2=(~(b^d))&(~(a^c));
    assign f3=((~a)&(~b)&d)|((~b)&c&d)|((~a)&c);
endmodule
