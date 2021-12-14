`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////
module de_morgan_first_a_tb(

    );
    reg aa;
    reg bb;
    wire yy;
    de_morgan_first_a u_de_morgan_first_a(
    .a(aa),.b(bb),.y(yy));
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
