`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module bcd_to_decimal_tb(
    );
    reg a;
    reg b;
    reg c;
    reg d;
    wire y0;
    wire y1;
    wire y2;
    wire y3;
    wire y4;
    wire y5;
    wire y6;
    wire y7;
    wire y8;
    wire y9;
    BCD_to_decimal u_BCD_to_decimal(
    .a(a),.b(b),.c(c),.d(d),.y0(y0),.y1(y1),.y2(y2),.y3(y3),.y4(y4),.y5(y5),.y6(y6),.y7(y7),.y8(y8),.y9(y9));
    initial begin 
    a=1'b0;
    b=1'b0;
    c=1'b0; 
    d=1'b0;
    end
    always a=#80~a;
    always b=#40~b;
    always c=#20~c;
    always d=#10~d;
    initial begin 
    #1000
    $finish;
    end
endmodule
