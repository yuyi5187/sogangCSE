`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
module rs_latch(
input R,S,
output Q,QC
    );
   wire t1,t2;
     assign t1 = ~(R & t2);
     assign t2 = ~(S & t1);
     
     assign Q = t1;
     assign QC = t2;
endmodule

module dlatch(
input D,
input enable,
output  Q,
output  QC
    );
   wire t3;
   wire t4;
   assign t3=~(D&enable);
   assign t4=~((~D)&enable);
   rs_latch rs( t3,t4,Q,QC);
endmodule
