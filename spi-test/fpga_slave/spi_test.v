module spi_test(clk, spi_sclk, spi_mosi, spi_miso, spi_cs);
input  clk;
input  spi_sclk;
input  spi_mosi;
input  spi_cs;
output spi_miso;

reg [7:0]test_buffer = 0;
reg [2:0]test_indice = 0;
reg      miso_buffer = 0;

assign   miso_buffer = spi_miso;

always @(posedge clk)
begin
    if(spi_cs == 1)
	begin    
		if(spi_sclk == 1)
	    begin
	        test_buffer[test_indice] <= spi_mosi;
			test_indice <= test_indice + 1;
			miso_buffer <= 1;
		end
	end
end

endmodule    