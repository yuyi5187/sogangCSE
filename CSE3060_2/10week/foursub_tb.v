`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


module foursub_tb(
    );
     reg [3:0] a;
     reg [3:0] b;
     reg b0;
     wire [3:0] D;
     wire b4;
     fourbitsub u_fourbitsub(.a(a),.b(b),.bin(b0),.D(D),.bout(b4));
     initial begin
     a = 4'b0011;b=4'b0011;b0 = 1'b0; #10;
     a = 4'b1011;b=4'b0111;b0 = 1'b1; #10;
     a = 4'b1111;b=4'b1111;b0 = 1'b1; #10;
     end

endmodule
