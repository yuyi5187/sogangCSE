`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module rsff(
input R,S,CP,
output Q,QC
    );
 //Front
     wire t1,t2;
     assign t1 = R & CP;
     assign t2 = S & CP;
     //Rear
     wire t3,t4;
     assign t3 = ~(t4|t1);
     assign t4 = ~(t3|t2);
     
     assign Q = t3;
     assign QC = t4;
endmodule
