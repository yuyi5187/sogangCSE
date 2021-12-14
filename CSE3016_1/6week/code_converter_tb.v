`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////


module code_converter_tb(

    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    wire xx;
    wire yy;
    wire zz;
    wire ww;
    code_converter u_code_converter(
    .a(aa),.b(bb),.c(cc),.d(dd),.x(xx),.y(yy),.z(zz),.w(ww));
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    dd=1'b0;
    end
    always aa=#800~aa;
    always bb=#400~bb;
    always cc=#200~cc;
    always dd=#100~dd;
    initial begin
    #2000
    $finish;
    end    
endmodule
