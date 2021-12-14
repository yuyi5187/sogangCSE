`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module de_morgan_first_b_tb(

    );
    reg aa;
    reg bb;
    wire yy;
    de_morgan_first_b u_de_morgan_first_b(
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
