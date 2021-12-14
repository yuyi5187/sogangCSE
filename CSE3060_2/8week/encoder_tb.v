`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module encoder_tb(

    );
    reg aa;
    reg bb;
    reg cc;
    reg dd;
    wire ee0;
    wire ee1;
    encoder u_encdoer(
    .a(aa),.b(bb),.c(cc),.d(dd),.e0(ee0),.e1(ee1));
    initial begin
    aa=1'b0; bb=1'b0;cc=1'b0;dd=1'b0;#100
    aa=1'b0;bb=1'b0;cc=1'b0;dd=1'b1;#100
    aa=1'b0;bb=1'b0;cc=1'b1;dd=1'b0;#100
    aa=1'b0;bb=1'b1;cc=1'b0;dd=1'b0;#100
    aa=1'b1;bb=1'b0;cc=1'b0;dd=1'b0;
    end 

endmodule
