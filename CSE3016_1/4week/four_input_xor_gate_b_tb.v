`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module four_input_xor_gate_b_tb(

    );
reg aa;
reg bb;
reg cc;
reg dd;
wire ee;
wire ff;
wire gg;

four_input_xor_gate_b u_four_input_xor_gate_b(
.a(aa),.b(bb),.c(cc),.d(dd),.e(ee),.f(ff),.g(gg));

initial begin
aa=1'b0;
bb=1'b0;
cc=1'b0;
dd=1'b0;
end
always aa=#10~aa;
always bb=#20~bb;
always cc=#40~cc;
always dd=#80~dd;

initial begin
#1000
$finish;
end

endmodule
