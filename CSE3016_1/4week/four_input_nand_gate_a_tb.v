`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module four_input_nand_gate_a_tb(

    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    wire ee;
    four_input_nand_gate_a u_four_input_nand_gate_a(
    .a(aa),.b(bb),.c(cc),.d(dd),.e(ee));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    end
    always dd=#10~dd;
    always cc=#20~cc;
    always bb=#40~bb;
    always aa=#80~aa;
    initial begin
    #1000
    $finish;
    end
endmodule
