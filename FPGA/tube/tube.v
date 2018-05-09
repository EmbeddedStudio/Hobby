module tube(A,LED7S,dig);
	input [3:0] A; //��ʾ���ݼĴ���
	output [7:0] LED7S; //����ܶ������
	output [7:0] dig; //�����ʹ�ܼĴ���
	reg [7:0] LED7S; //����ܶ�������Ĵ���
    assign dig= 8'h fe ;//ʹ�ܵ�һ�������
	always @ (A)
	begin
		case (A)
			4'h0 : LED7S = 8'hc0; 	//��ʾ"0"
			4'h1 : LED7S = 8'hf9;   //��ʾ"1"
			4'h2 : LED7S = 8'ha4; 	//��ʾ"2"
			4'h3 : LED7S = 8'hb0; 	//��ʾ"3"
			4'h4 : LED7S = 8'h99;	//��ʾ"4"
			4'h5 : LED7S = 8'h92; 	//��ʾ"5"
			4'h6 : LED7S = 8'h82; 	//��ʾ"6"
			4'h7 : LED7S = 8'hf8; 	//��ʾ"7"
			4'h8 : LED7S = 8'h80; 	//��ʾ"8"
			4'h9 : LED7S = 8'h90; 	//��ʾ"9"
			4'ha : LED7S = 8'h88;   //��ʾ"a"
			4'hb : LED7S = 8'h83; 	//��ʾ"b"
			4'hc : LED7S = 8'hc6; 	//��ʾ"c"
			4'hd : LED7S = 8'ha1; 	//��ʾ"d"
			4'he : LED7S = 8'h86; 	//��ʾ"e"
			4'hf : LED7S = 8'h8e; 	//��ʾ"f"
			default:LED7S =8'h00;
		endcase
	end
endmodule 