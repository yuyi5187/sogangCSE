`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module three_input_and_gate_a(
input a,
input b,
input c,
output y
    );
    assign y=(a&b&c);
endmodule
