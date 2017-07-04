/*
in:
	num: 0~9 to be displayed without '.' or 10~19 with '.'
out:
	seg: 74~68,65 (pins)
*/
module decoo(num,seg);

input [7:0] num;
output [7:0] seg;
reg [7:0] seg;

always
begin
	case (num)
	0: seg = 8'b11111100;
	1: seg = 8'b01100000;
	2: seg = 8'b11011010;
	3: seg = 8'b11110010;
	4: seg = 8'b01100110;
	5: seg = 8'b10110110;
	6: seg = 8'b10111110;
	7: seg = 8'b11100000;
	8: seg = 8'b11111110;
	9: seg = 8'b11110110;
	10: seg = 8'b11111101;
	11: seg = 8'b01100001;
	12: seg = 8'b11011011;
	13: seg = 8'b11110011;
	14: seg = 8'b01100111;
	15: seg = 8'b10110111;
	16: seg = 8'b10111111;
	17: seg = 8'b11100001;
	18: seg = 8'b11111111;
	19: seg = 8'b11110111;
	20: seg = 8'b00000000;
	default: seg = 8'b00000001;
	endcase
end

endmodule