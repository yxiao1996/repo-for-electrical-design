//module function: 
// provide phase detector with reference frequency
// divide the output of VCO at the specific ratio
module diviser(vco_out, clk, num, pd_in, com_in);
input vco_out;
input clk;
input [7:0]num;
output pd_in;
output com_in;

freqq s0(clk,23999,com_in);      //squ_1khz_standred
freq2 s1(vco_out,num,pd_in);     //pulse

endmodule
