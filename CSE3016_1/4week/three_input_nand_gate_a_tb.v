`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


module three_input_nand_gate_a_tb(
    );
    reg aa;
    reg bb;
    reg cc;
    wire dd;
    
    three_input_nand_gate_a u_three_input_nand_gate_a(
    .a(aa),.b(bb),.c(cc),.d(dd));
    
    initial begin
    aa=1'b0;
    bb=1'b0;
    cc=1'b0;
    end
    
    always cc=#100~cc;
    always bb=#200~bb;
    always aa=#400~aa;
  
    initial begin
    #1000
    $finish;
    end 
endmodule
