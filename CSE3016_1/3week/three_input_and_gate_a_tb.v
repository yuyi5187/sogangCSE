`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module three_input_and_gate_a_tb(
    );
    reg t_a;
    reg t_b;
    reg t_c;
    wire t_y;
    
    three_input_and_gate_a u_three_input_and_gate_a(
    .a(t_a),.b(t_b),.c(t_c),.y(t_y));

    initial begin
    $monitor(t_a,t_b,t_c,t_y);
       t_a=1'b0;t_b=1'b0;t_c=1'b0;
       #100
       t_a=1'b0;t_b=1'b0;t_c=1'b1;
       #100
       t_a=1'b0;t_b=1'b1;t_c=1'b0;
       #100
       t_a=1'b0;t_b=1'b1;t_c=1'b1;
       #100
       t_a=1'b1;t_b=1'b0;t_c=1'b0;
       #100
       t_a=1'b1;t_b=1'b0;t_c=1'b1;
       #100
       t_a=1'b1;t_b=1'b1;t_c=1'b0;
       #100
       t_a=1'b1;t_b=1'b1;t_c=1'b1;
    end
endmodule
