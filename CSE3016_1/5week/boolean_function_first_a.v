`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 

//////////////////////////////////////////////////////////////////////////////////


module boolean_function_first_a(
input a,
input b,
input c,
output y
    );
    assign y=((~a)|(~b))&(~c);
endmodule