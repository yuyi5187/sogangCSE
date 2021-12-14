`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 

//////////////////////////////////////////////////////////////////////////////////


module bool_func_second_a_tb(

    );
    reg aa;
    reg bb;
    reg cc;
    wire yy;
    bool_func_second_a u_bool_func_second_a(
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
