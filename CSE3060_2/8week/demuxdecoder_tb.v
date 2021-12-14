`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////


module decoder_tb(
    );
    reg s0;
    reg s1;
    reg s2;
    reg s3;
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
    wire y10;
    wire y11;
    wire y12;
    wire y13;
    wire y14;
    wire y15;
    decoder u_decoder(
    .s0(s0),.s1(s1),.s2(s2),.s3(s3),.y0(y0),.y1(y1),.y2(y2),.y3(y3),.y4(y4),.y5(y5),.y6(y6),.y7(y7),.y8(y8),.y9(y9),.y10(y10),.y11(y11),.y12(y12),.y13(y13),.y14(y14),.y15(y15));
    initial begin
    s0=1'b0; s1=1'b0; s2=1'b0; s3=1'b0;
    end
    always s0=#80~s3;
    always s1=#40~s2;
    always s2=#20~s1;
    always s3=#10~s0;
    initial begin
    #1000
    $finish;
    end

endmodule
