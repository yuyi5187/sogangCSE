`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module full_adder_tb(

    );
    reg aa;
    reg bb;
    reg cci;
    wire ss;
    wire cco;
    full_adder u_full_adder(
    .a(aa),.b(bb),.ci(cci),.s(ss),.co(cco));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cci=1'b0;
    end
    always aa=#400~aa;
    always bb=#200~bb;
    always cci=#100~cci;
    initial begin 
    #2000
    $finish;
    end
endmodule
