/*  
in:	 
	clk: 48MHz
	num: the 4 numbers to be displayed from left to right
out:
	com: 54 53 52 51 (pins)
	seg: 74~68,65 (pins)
*/
module displ(clk,num,com,seg);  

input clk;
input [15:0] num;
output [3:0] com;
output [7:0] seg;
reg [1:0] flag;
reg [3:0] com;
reg [7:0] num_one;
wire clk_1khz;

always @ (num)
begin
	if(num > 999)
			flag <= 3;
		else if(num > 99)
				flag <= 2;
				else if(num > 9)
						flag <= 1;
						else
							flag <= 0;
end

always @ (posedge clk_1khz)
begin
	case(com)
	4'b0001: begin
					com <= 4'b1000;
					if(flag == 3)
						num_one <= num / 1000;
					else
						num_one <= 20;
				end
	4'b1000: begin
					com <= 4'b0100;
					if(flag > 1)
						num_one <= num / 100 % 10;
					else
						num_one <= 20;
				end
	4'b0100: begin
					com <= 4'b0010;
					if(flag > 0)
						num_one <= num / 10 % 10;
					else
						num_one <= 20;
				end
	4'b0010: begin
					com <= 4'b0001;
					num_one <= num % 10 + 10;
				end
	default: com <= 4'b1000;
	endcase
end

decoo de_0(num_one,seg);
freqq fre_0(clk,23999,clk_1khz);

endmodule