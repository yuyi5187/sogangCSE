`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////////////


module BCD_to_decimal(
input a,
input b,
input c,
input d,
output y0,y1,y2,y3,y4,y5,y6,y7,y8,y9
    );
    assign y0=a|b|c|d;
    assign y1=(a|b|c|(~d));
    assign y2=b|d|(~c);
    assign y3=b|(~c)|(~d);
    assign y4=c|(~b)|d;
    assign y5=c|(~b)|(~d);
    assign y6=(~b)|(~c)|d;
    assign y7=(~b)|(~c)|(~d);
    assign y8=(~a)|d;
    assign y9=(~a)|(~d);
endmodule
