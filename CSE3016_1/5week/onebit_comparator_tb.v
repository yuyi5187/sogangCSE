`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// 
//////////////////////////////////////////////////////////////////////////////////


module onebit_comparator_tb(

    );
    reg aa;
    reg bb;
    wire F1;
    wire F2;
    wire F3;
    wire F4;
    onebit_comparator u_onebit_comparator(
    .a(aa),.b(bb),.f1(F1),.f2(F2),.f3(F3),.f4(F4));
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
