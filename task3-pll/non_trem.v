module non_trem(a0, a1, b0, b1, clk);

input a0, a1, clk;
output reg b0, b1;
wire clk_20;

freqq s0(clk,2399999,clk_20);

always @ (posedge clk_20)
begin
	b0 <= a0;
   b1 <= a1;	
end

endmodule
