`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

// 
//////////////////////////////////////////////////////////////////////////////////


module half_adder_tb(
    );
    reg aa;
    reg bb;
    wire ss;
    wire cc;
    half_adder u_half_adder(
    .a(aa),.b(bb),.s(ss),.c(cc));
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
