`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////


module paritybit_checker_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    reg pp;
    wire ee;
    paritybit_checker u_paritybit_checker(
    .a(aa),.b(bb),.c(cc),.d(dd),.p(pp),.e(ee));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    pp=1'b0;
    end
    
    always pp=#5~pp;
    always aa=#80~aa;
    always bb=#40~bb;
    always cc=#20~cc;
    always dd=#10~dd;
    
    initial begin
    #1000
    $finish;
    end
    
endmodule
