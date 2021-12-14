`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////


module half_subtractor_tb(

    );
    reg AA;
    reg BB;
    wire bb;
    wire DD;
    half_subtractor u_half_subtractor(
    .A(AA),.B(BB),.b(bb),.D(DD));
    initial begin
    AA=1'b0;
    BB=1'b0;
    end
    always AA=#200~AA;
    always BB=#100~BB;
    initial begin
    #1000
    $finish;
    end
endmodule
