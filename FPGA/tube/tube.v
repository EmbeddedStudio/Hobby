module tube(A,LED7S,dig);
	input [3:0] A; //显示数据寄存器
	output [7:0] LED7S; //数码管段码输出
	output [7:0] dig; //数码管使能寄存器
	reg [7:0] LED7S; //数码管段码输出寄存器
    assign dig= 8'h fe ;//使能第一个数码管
	always @ (A)
	begin
		case (A)
			4'h0 : LED7S = 8'hc0; 	//显示"0"
			4'h1 : LED7S = 8'hf9;   //显示"1"
			4'h2 : LED7S = 8'ha4; 	//显示"2"
			4'h3 : LED7S = 8'hb0; 	//显示"3"
			4'h4 : LED7S = 8'h99;	//显示"4"
			4'h5 : LED7S = 8'h92; 	//显示"5"
			4'h6 : LED7S = 8'h82; 	//显示"6"
			4'h7 : LED7S = 8'hf8; 	//显示"7"
			4'h8 : LED7S = 8'h80; 	//显示"8"
			4'h9 : LED7S = 8'h90; 	//显示"9"
			4'ha : LED7S = 8'h88;   //显示"a"
			4'hb : LED7S = 8'h83; 	//显示"b"
			4'hc : LED7S = 8'hc6; 	//显示"c"
			4'hd : LED7S = 8'ha1; 	//显示"d"
			4'he : LED7S = 8'h86; 	//显示"e"
			4'hf : LED7S = 8'h8e; 	//显示"f"
			default:LED7S =8'h00;
		endcase
	end
endmodule 