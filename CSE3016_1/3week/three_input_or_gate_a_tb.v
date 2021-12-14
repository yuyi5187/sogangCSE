`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

module three_input_or_gate_a_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    wire yy;
    three_input_or_gate_a u_three_input_or_gate_a(
    .a(aa),.b(bb),.c(cc),.y(yy));
    initial begin
    $monitor(aa,bb,cc,yy);
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
