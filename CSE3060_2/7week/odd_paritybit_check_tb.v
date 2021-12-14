`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module odd_paritybit_check_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    reg pp;
    wire ee;
    odd_paritybit_check u_odd_paritybit_check(
    .a(aa),.b(bb),.c(cc),.d(dd),.p(pp),.e(ee));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    pp=1'b0;
    end
    always aa=#80~aa;
    always bb=#40~bb;
    always cc=#20~cc;
    always dd=#10~dd;
    always pp=#5~pp;
    initial begin
    #2000
    $finish;
    end
    
endmodule
