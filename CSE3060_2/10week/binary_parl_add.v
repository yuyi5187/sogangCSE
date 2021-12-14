`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
module my_full_adder(
input a,b,cin,
output s,cout
);    
    assign s=(a^b)^cin;
    assign cout=(a&b)|(cin&(a^b));
endmodule

module bcd_adder( 
    input [3:0]A,
    input [3:0] B,
    input C0,
    output [3:0]sum
    );
    wire Cout;
    wire [3:0]S;
    wire C1,C2,C3,C4;
    wire C5,C6,C7,C8;

    my_full_adder fa0 (A[0],B[0],C0,S[0],C1);
    my_full_adder fa1 (A[1],B[1],C1,S[1],C2);
    my_full_adder fa2 (A[2],B[2],C2,S[2],C3);
    my_full_adder fa3 (A[3],B[3],C3,S[3],C4);
    
    assign Cout = ((S[1]|S[2])&S[3])|C4;

my_full_adder sfa1(S[0],0,C0,sum[0],C5);
my_full_adder sfa2(S[1],Cout,C5,sum[1],C6);
my_full_adder sfa3(S[2],Cout,C6,sum[2],C7);
my_full_adder sfa4(S[3],0,C7,sum[3],C8);





endmodule
