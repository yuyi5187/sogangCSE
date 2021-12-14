`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 

// 
//////////////////////////////////////////////////////////////////////////////////


module twobit_comparator_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    wire ff1;
    wire ff2;
    wire ff3;
    twobit_comparator u_twobit_comparator(
    .a(aa),.b(bb),.c(cc),.d(dd),.f1(ff1),.f2(ff2),.f3(ff3));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    end
    always aa=#400~aa;
    always bb=#200~bb;
    always cc=#100~cc;
    always dd=#50~dd;
    initial begin
    #1000
    $finish;
    end
    
endmodule
