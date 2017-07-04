/*
in:
	clk: 48MHz
	num: (N/2)-1
out: 
	clkout: the new clock
*/
module freqq(clk,num,clkout);

input clk;
input [31:0] num;
output clkout;

reg [31:0] count;
reg clkout;

always @ (posedge clk)
begin
	if (count == num)
	 begin
		 clkout <= ~clkout;
		 count <= 0;
   	end
	else
		count <= count + 1;
end

endmodule