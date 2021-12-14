`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////////////


module boolean_function_first_a_tb(

    );
    reg aa;
    reg bb;
    reg cc;
    wire yy;
    boolean_function_first_a u_boolean_function_first_a(
    .a(aa),.b(bb),.c(cc),.y(yy));
    initial begin 
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    end
    always aa=#400~aa;
    always bb=#200~bb;
    always cc=#100~cc;
    initial begin
    #1000
    $finish;
    end
endmodule
