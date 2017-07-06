module ctrll(d,num);

input d;
output reg [7:0] num;

always @ (negedge d)
begin
	if(num >= 100 || num < 1)
		num <= 1;
	else
		num <= num + 1;
end

endmodule
