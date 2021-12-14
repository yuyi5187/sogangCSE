`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////


module demux(
input D,a,b,
output z0,z1,z2,z3
    );
    assign z0=(~a)&(~b)&D;
    assign z1=(~a)&b&D;
    assign z2=a&(~b)&D;
    assign z3=a&b&D;
endmodule

module decoder(
input s0,s1,s2,s3,
output y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,
output y12,y13,y14,y15);
wire A;
wire demux_0,demux_1,demux_2,demux_3;
assign A = 1;
  demux entry(A,s0,s1,demux_0,demux_1,demux_2,demux_3);
  demux d0(demux_0,s2,s3,y0,y1,y2,y3);
  demux d1(demux_1,s2,s3,y4,y5,y6,y7);
  demux d2(demux_2,s2,s3,y8,y9,y10,y11);
  demux d3(demux_3,s2,s3,y12,y13,y14,y15);
  
endmodule
