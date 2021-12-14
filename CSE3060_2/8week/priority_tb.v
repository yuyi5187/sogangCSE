`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////


module priority_tb(

    );
    reg a3;
    reg a2;
    reg a1;
    reg a0;
    wire s0;
    wire s1;
   
   priority u_priority(.a3(a3),.a2(a2),.a1(a1),.a0(a0),.s0(s0),.s1(s1));
   initial begin 
   a3=1'b0; a2=1'b0; a1=1'b0; a0=1'b0;
   end
   always a3=#400~a3;
   always a2=#300~a2;
   always a1=#200~a1;
   always a0=#100~a0;
   initial begin
   #1000
   $finish;
   end 
    
endmodule
