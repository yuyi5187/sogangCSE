`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module three_input_or_gate_b_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    wire dd;
    wire yy;
    three_input_or_gate_b u_three_input_or_gate_b(
    .a(aa),.b(bb),.c(cc),.d(dd),.y(yy));
    initial begin
    $monitor(aa,bb,cc,dd,yy);
    aa=1'b0; bb=1'b0; cc=1'b0;
    #100
    aa=1'b0; bb=1'b0; cc=1'b1;
    #100
    aa=1'b0; bb=1'b1; cc=1'b0;
    #100
    aa=1'b0; bb=1'b1; cc=1'b1;
    #100
    aa=1'b1; bb=1'b0; cc=1'b0;
    #100
    aa=1'b1; bb=1'b0; cc=1'b1;
    #100
    aa=1'b1; bb=1'b1; cc=1'b0;
    #100
    aa=1'b1; bb=1'b1; cc=1'b1;
    end
endmodule
