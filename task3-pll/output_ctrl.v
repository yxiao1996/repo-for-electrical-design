//module function:
//assign the output for each resultion
module output_ctrl(b1, clk,
               pd_in0, pd_in1, pd_in2, pd_in3,
					com_in0, com_in1, com_in2, com_in3,
					pd_in, com_in,
					state);
input b1, clk;
input pd_in0, pd_in1, pd_in2, pd_in3;
input com_in0, com_in1, com_in2, com_in3;
output pd_in, com_in;
output [1:0]state;

reg [1:0]stat;
reg tmp_pd_in, tmp_com_in;
assign pd_in = tmp_pd_in;
assign com_in = tmp_com_in;
assign state = stat;

always @(posedge b1)
begin
    stat <= stat + 1;
end

always @(posedge clk)
begin
    case(state)
	 2'b00: 
	     begin
	         tmp_pd_in <= pd_in0;
				tmp_com_in <=com_in0;
        end
    2'b01: 
	     begin
	         tmp_pd_in <= pd_in1;
				tmp_com_in <=com_in1;
        end
    2'b10: 
	     begin
	         tmp_pd_in <= pd_in2;
				tmp_com_in <=com_in2;
        end
	 2'b11: 
	     begin
	         tmp_pd_in <= pd_in3;
				tmp_com_in <=com_in3;
        end
    endcase
end
endmodule
