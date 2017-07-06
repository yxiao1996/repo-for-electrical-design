module freq2(a,num,b);

input a;
input [31:0] num;
reg [31:0] count;
output reg b;

always @ (posedge a)
begin
	if(count >= num - 1)
	begin
		count <= 0;
		b <= 1;
	end
	else
	begin
		count <= count + 1;
		b <= 0;
	end
end

endmodule
