`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
module jkff(
  input  j,
  input  k,
  input  clk,
  output  reg Q,
  output  QC );
  

  assign QC=~Q;
  always @(posedge clk)
  begin
  case({j,k})
  2'b00:Q<=Q;
  2'b01:Q<=1'b0;
  2'b10:Q<=1'b1;
  2'b11:Q<=~Q;
  default:Q<=1'b0;
  endcase  
  
  end
    
endmodule
