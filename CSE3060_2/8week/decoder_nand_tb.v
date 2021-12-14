`timescale 1ns / 1ps
///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module decoder_nand_tb(
    );
    reg aa;
    reg bb;
    wire dd0;
    wire dd1;
    wire dd2;
    wire dd2;
    decoder_nand u_decoder_nand(
    .a(aa),.b(bb),.d0(dd0),.d1(dd1),.d2(dd2),.d3(dd3));
    initial begin
    aa=1'b0;
    bb=1'b0;
    end
    always aa=#200~aa;
    always bb=#100~bb;
    initial begin 
    #1000
    $finish;
    end
endmodule
