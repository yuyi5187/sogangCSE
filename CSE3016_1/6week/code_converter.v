`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module code_converter(
input a,
input b,
input c,
input d,
output x,
output y,
output z,
output w
    );
    assign x=(a|(b&c))|(b&d);
    assign y=(a|(b&c))|((~d)&b);
    assign z=a|((~b)&c)|((~c)&b&d);
    assign w=d;
endmodule
