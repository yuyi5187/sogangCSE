`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module foursub(
output d,bout,
input a,b,bin);
    assign bout=(~a)&b^(~a)&bin^b&bin;
    assign d=a^b^bin;
endmodule


module fourbitsub(D,bout,a,b,bin);
output bout;
output [3:0]D;
input bin;
input [3:0]a,b;
wire temp0,temp1,temp2;

foursub fa0(D[0],temp0,a[0],b[0],bin);
foursub fa1(D[1],temp1,a[1],b[1],temp0);
foursub fa2(D[2],temp2,a[2],b[2],temp1);
foursub fa3(D[3],bout,a[3],b[3],temp2);
endmodule

