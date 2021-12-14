`timescale 1ns / 1ps

module bcd_adder_sim();

reg [3:0] x;
reg [3:0] y;
reg cin;
wire [3:0] sum;

bcd_adder u_bcd_adder(.sum(sum),.C0(cin),.A(x),.B(y));    
initial begin
 x = 4'b0011;y=4'b0011;cin = 1'b0; #100;
 x = 4'b1011;y=4'b0111;cin = 1'b1; #100;
 x = 4'b1111;y=4'b1111;cin = 1'b0; #100;
end
endmodule
