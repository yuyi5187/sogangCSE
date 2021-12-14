`timescale 1ns / 1ps
module bcd_adder(sum, s, cout, A, cin, x, y);

output [3:0]sum, s;
output  cout, A;
input  cin;
input  [3:0]x,y;
wire C1,C2,C3,C4;

four_bit_adder FFA1 (.Sum(s), .Cout(A), .Cin(cin), .X(x), .Y(y));

assign cout = ((s[1]|s[2])&s[3])|A;

full_adder SFA1(.S(sum[0]),.Cout(C1),.A(s[0]),.B(0),.Cin(cin));
full_adder SFA2(.S(sum[1]),.Cout(C2),.A(s[1]),.B(cout),.Cin(C1));
full_adder SFA3(.S(sum[2]),.Cout(C3),.A(s[2]),.B(cout),.Cin(C2));
full_adder SFA4(.S(sum[3]),.Cout(C4),.A(s[3]),.B(0),.Cin(C3));

endmodule
