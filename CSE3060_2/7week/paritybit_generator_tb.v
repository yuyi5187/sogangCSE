`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module paritybit_generator_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    wire ee;
    paritybit_generator u_paritybit_generator(
    .a(aa),.b(bb),.c(cc),.d(dd),.e(ee));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    end
    always aa=#80~aa;
    always bb=#40~bb;
    always cc=#20~cc;
    always dd=#10~dd;
    initial begin
    #400
    $finish;
    end    
endmodule
