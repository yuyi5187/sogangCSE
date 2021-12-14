`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////////////


module full_subtractor_tb(

    );
    reg AA;
    reg BB;
    reg bb;
    wire bbn;
    wire DD;
    full_subtractor u_full_subtractor(
    .A(AA),.B(BB),.b(bb),.bn(bbn),.D(DD));
    initial begin
    AA=1'b0;
    BB=1'b0;
    bb=1'b0;
    end
    always AA=#400~AA;
    always BB=#200~BB;
    always bb=#100~bb;
    initial begin
    #2000
    $finish;
    end
endmodule
