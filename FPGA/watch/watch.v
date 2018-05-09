module watch (clk50mHZ,LED7S,dig,Btn1In,Btn2In, btn3In,beep,LED,AD_CS,AD_CLK,AD_DATA);

/*--------------------���ŵĶ���-------------------------*/

	input clk50mHZ;   
	input Btn1In,Btn2In, btn3In,AD_DATA;  //����������� ADC ���ݵ�����
	output beep,AD_CS,AD_CLK;  //������ ADƬѡ��  ADʱ����
	output  [7:0] LED7S; //����ܶ������
	output  [7:0] dig; 	//�����λѡʹ�ܼĴ���
	output [7:0] LED;  //����ܶ�ѡʹ�ܼĴ���

	
/*--------------------ȫ�ּĴ����Ķ���---------------------*/
	
	wire [3:0]   modelState;	     //״̬������ʾ��ǰ״̬
	wire [11:0]  Button2State; 		 //����2��ģ�ͱ��� 
	wire 		 Button3State; 		 //����3��ģ�ͱ��� 
	wire [23:0]  TimeValueReg; 		 //����Сʱ�Ĵ���
	wire [23:0]  TubeValueReg; 		 //�����������ʾ�Ĵ���
	wire [23:0]  StopwatchValueReg;  //���Ĵ���
	wire [23:0]  AlarmValueReg;  	 //���ӼĴ���
	wire [23:0]  AdValueReg;		 //AD ���ݼĴ���
	wire twinkle; 					 //��˸��־λ
	wire beepOnValue1,beepOnValue2;  //������ʹ�ܱ�־  ���㱨ʱ������
	wire clk100HZ,clk1HZ,clk2HZ,clk1kHZ, clk10kHZ,clk10HZ; //ʱ�ӷ�Ƶ  
	
/*--------------------�����ָ���-------ģ��ĵ���------------------*/

	
	clk(clk50mHZ,clk100HZ,clk1HZ,clk2HZ,clk1kHZ,clk10HZ,twinkle);
	clockModule (clk1kHZ,TimeValueReg,modelState,Button2State,Button3State,beepOnValue2);
	tube(TubeValueReg,LED7S,dig,clk1kHZ,modelState);
	view (modelState,Button2State,clk1kHZ,AlarmValueReg,StopwatchValueReg,TubeValueReg,TimeValueReg,AdValueReg,twinkle);
	Button1Module(clk50mHZ,Btn1In, modelState);
	Button2Module(clk50mHZ,Btn2In, modelState,Button2State);
	Button3Module(clk50mHZ,clk2HZ,btn3In,modelState,Button3State);
	beepModule(clk1kHZ,beepOnValue1,beepOnValue2,beep);
	LEDModule(LED,modelState);
	AlarmModule(clk1kHZ,modelState,Button2State,Button3State,AlarmValueReg,TimeValueReg,beepOnValue1);
	StopModule(clk100HZ,modelState,Button2State,Button3State,StopwatchValueReg);
	TLC549 (clk10HZ ,AD_CS,AD_CLK,AD_DATA,AdValueReg,modelState);
	
endmodule

//��ͼ�����   �ڲ�ͬģʽ��ѡ����ʾ�Ǹ�����
module  view (modelState,Button2State,clk,AlarmValueReg,StopwatchValueReg,TubeValueReg,TimeValueReg,AdValueReg,twinkle);

	input [3:0]  modelState;
	input [11:0] Button2State;
	input 		 twinkle,clk;
	input [23:0] TimeValueReg;
	input [23:0] AlarmValueReg;
	input [23:0] StopwatchValueReg;
	input [23:0]  AdValueReg;
	output [23:0] TubeValueReg;
	reg [23:0] TubeValue;
	always @ (posedge clk)
	begin 
		if(modelState==4'h0)//ʱ��ģʽ
		begin 
			if(Button2State[3:0]==4'h0)//ʱ��������ʾ
				TubeValue=TimeValueReg;
				
			else if(Button2State[3:0]==4'h1) //��������
			begin 
				if(twinkle) //��8λ����ʾ
					TubeValue=TimeValueReg | 8'hff;
				else  //��8λ��ʾ
					TubeValue=TimeValueReg;
					//�������������˸
			end
		
			else if(Button2State[3:0]==4'h2) //���÷���
			begin 
				if(twinkle)
					TubeValue=TimeValueReg | 16'hff00;
				else
					TubeValue=TimeValueReg;
			end
			else if(Button2State[3:0]==4'h3) //����ʱ��
			begin 
				if(twinkle)
					TubeValue=TimeValueReg | 24'hff0000;
				else
					TubeValue=TimeValueReg;
			end
		end 
		
		else if(modelState==4'h1)   //���ģ��
			TubeValue=StopwatchValueReg;	 //���
		
		else if(modelState==4'h2)//����ģ��
		begin
		    if(Button2State[11:8]==4'h0)//����������ʾ
				TubeValue=AlarmValueReg;
			else if(Button2State[11:8]==4'h1)//��������
			begin 
				if(twinkle)
					TubeValue=AlarmValueReg|8'hff;
				else
				TubeValue=AlarmValueReg;
			end
			else if(Button2State[11:8]==4'h2) //���÷���
			begin 
				if(twinkle)
					TubeValue=AlarmValueReg|16'hff00;
				else
					TubeValue=AlarmValueReg;
			end
			else if(Button2State[11:8]==4'h3) //����ʱ��
			begin 
				if(twinkle)
					TubeValue=AlarmValueReg|24'hff0000;
				else
					TubeValue=AlarmValueReg;
			end
		end
		else if(modelState==4'h3)       //AD��ʾģ��
			TubeValue=AdValueReg;	//AD��ʾģ��
	end	
	assign TubeValueReg=TubeValue;
endmodule


/*ʱ��ģ��  ����ʱ�ӵĽ�λ�����㱨ʱ��ʱ�ӵĵ���	*/
module clockModule (clk,TimeValueReg,modelState,Button2State,Button3State,beepOnValue2);
	input [3:0]modelState;
	input [11:0]Button2State;
	input Button3State;
	output [23:0] TimeValueReg;
	output beepOnValue2;
	input clk;
	reg [11:0]cnt ;
	reg [11:0]cnt2 ;
	reg [23:0] Time ;
	reg beep2;
	always @(posedge clk)
	begin
		if(cnt>=12'd1000)
		begin
			cnt<=0;
			Time[3:0]<=Time[3:0]+4'h1;
			if(Time[3:0]>=4'd9)
			begin
				Time[3:0]<=4'h0;
				Time[7:4]<=Time[7:4]+4'h1;
				if(Time[7:4]>=4'd5)
				begin 
					Time[7:4]<=4'h0;
					Time[11:8]<=Time[11:8]+4'h1;
					if(Time[11:8]>=4'd9)
					begin
						Time[11:8]<=0;
						Time[15:12]<=Time[15:12]+4'h1;
						if(Time[15:12]>=4'd5)
						begin
							Time[15:12]<=4'h0;
							Time[19:16]<=Time[19:16]+4'h1;
							if(Time[23:20]<=4'd1 &&Time[19:16]>=4'd9)
							begin
								Time[19:16]<=4'h0;
								Time[23:20]<=Time[23:20]+4'h1;
							end
							else if(Time[23:20]==4'd2 && Time[19:16]>=4'd3)
							begin
								Time[19:16]<=4'h0;
								Time[23:20]<=4'h0;
							end 
						end 
					end 
				end 
			end
			if(Button2State[3:0]==1'b0)
			begin
				if(Time[15:0]==16'h0000)
					beep2<=1;
				else
					beep2<=0;
			end
		end	
		else 
		cnt<=cnt+1'b1;
		
		if(cnt2>=499)
		begin
			cnt2<=0;
			if(modelState==4'h0)
			begin 
				if(Button2State[3:0]==4'h1 && Button3State==4'h1 )
					Time[7:0]<=8'h00;
				if(Button2State[3:0]==4'h2 && Button3State==4'h1)
				begin
					Time[11:8]<=Time[11:8]+4'h1;
					if(Time[11:8]>=4'h9)
					begin
						Time[11:8]<=4'h0;
						Time[15:12]<=Time[15:12]+4'h1;
						if(Time[15:12]>=4'h5)
						Time[15:12]<=4'h0;
					end
				end
				if(Button2State[3:0]==4'h3 && Button3State==4'h1 )
				begin
					Time[19:16]<=Time[19:16]+4'h1;
					if(Time[23:20]<=4'h1 && Time[19:16]>=4'h9)
					begin 
						Time[19:16]<=4'h0;
						Time[23:20]<=Time[23:20]+4'h1;
					end 
					else if(Time[23:20]==4'h2 && Time[19:16]>=4'h3)
					begin
						Time[19:16]<=4'h0;
						Time[23:20]<=4'h0;
					end
				end
			end
		end
		else
		cnt2<=cnt2+1'b1;
	end 
	assign TimeValueReg=Time;
	assign beepOnValue2=beep2;
endmodule 
/*����ģ��  ������ʱ��ģ����ͬ�����������*/
module	AlarmModule (clk1kHZ,modelState,Button2State,Button3State,AlarmValueReg,TimeValueReg,beepOnValue);
	input clk1kHZ;
	input [3:0]  modelState;
	input [11:0] Button2State;
	input  		 Button3State;
	input [23:0] TimeValueReg;
	output[23:0] AlarmValueReg;
	output beepOnValue;
	reg beepValue;
	reg [23:0] Alarm;
	reg [11:0] cnt;
	always@(posedge clk1kHZ)
	begin
		if(modelState==4'h2)
		begin 
			if(cnt>=500 )
			begin
				cnt<=0;
				if(Button2State[11:8]==4'h1 && Button3State==4'h1 )
				begin
					Alarm[3:0]<=Alarm[3:0]+4'h1;
					if(Alarm[3:0]>=4'h9)
					begin
						Alarm[3:0]<=4'b0;
						Alarm[7:4]<=Alarm[7:4]+4'h1;
						if(Alarm[7:4]>=4'h5)
						Alarm[7:4]<=4'h0;
					end 
				end
				if(Button2State[11:8]==4'h2 && Button3State==4'h1)
				begin
					Alarm[11:8]<=Alarm[11:8]+4'h1;
					if(Alarm[11:8]>=4'h9)
					begin
						Alarm[11:8]<=4'h0;
						Alarm[15:12]<=Alarm[15:12]+4'h1;
						if(Alarm[15:12]>=4'h5)
						Alarm[15:12]<=4'h0;
					end
				end
				if(Button2State[11:8]==4'h3 && Button3State==4'h1 )
				begin
					Alarm[19:16]<=Alarm[19:16]+4'h1;
					if(Alarm[23:20]==4'h2 && Alarm[19:16]>=4'h3)
					begin
						Alarm[19:16]<=4'h0;
						Alarm[23:20]<=4'h0;
					end
					else if(Alarm[23:20]<=4'h1 && Alarm[19:16]>=4'h9)
					begin 
						Alarm[19:16]<=4'h0;
						Alarm[23:20]<=Alarm[23:20]+4'h1;
					end 
				end
			
			end
			else
			cnt<=cnt+1'b1;
			
		end
		if(AlarmValueReg == TimeValueReg)//һ�����ӵ�ʱ���ʵ�ʵ�ʱ�������ô���Ὺ�����ӱ�־λ
			beepValue<=1'b1;
			//��������Ϊ5��
			//������ӵ�����û�г���5��ôʱ��-����>5�Ϳ��Թر���ʾ��־��
		else if(TimeValueReg[3:0]-AlarmValueReg[3:0] >= 4'h5 && AlarmValueReg[3:0]<=4'h5)
			beepValue<=0;
//������ӵ�����û��5 ��ô ʱ��-����>5 �Ͳ����ܳ���  ���Ա��� ����-ʱ��>5 �Ϳ��Թر����ӱ�־
		else if( AlarmValueReg[3:0]>= 4'h5 && AlarmValueReg[3:0]-TimeValueReg[3:0]<=4'h5 )
			beepValue<=0;
	end
    assign beepOnValue=beepValue;
    assign 	AlarmValueReg=Alarm;
endmodule
/*���ģ���λԭ���ʱ������*/
module	StopModule(clk100HZ,modelState,Button2State,Button3State,StopwatchValueReg);
	input clk100HZ;
	input [3:0] modelState;
	input [11:0] Button2State;
	input  Button3State;
	output [23:0] StopwatchValueReg;
	reg [23:0] Stop;
	always @ (posedge clk100HZ)
	begin
		if(modelState==4'h1)
		begin
			if(Button2State[7:4]==4'b01 )
			begin
				Stop[3:0]<=Stop[3:0]+4'h1;
				if(Stop[3:0]>=4'h9)
				begin
					Stop[3:0]<=0;
					Stop[7:4]=Stop[7:4]+4'h1;
					if(Stop[7:4]>=4'h9)
					begin 
						Stop[7:4]<=4'h0;
						Stop[11:8]<=Stop[11:8]+4'h1;
						if(Stop[11:8]>=4'h9)
						begin
							Stop[11:8]<=4'h0;
							Stop[15:12]<=Stop[15:12]+4'h1;
							if(Stop[15:12]>=4'h5)
							begin
								Stop[15:12]<=4'h0;
								Stop[19:16]<=Stop[19:16]+4'h1;
								if(Stop[19:16]>=9)
								begin
									Stop[19:16]<=4'h0;
									Stop[23:20]<=Stop[23:20]+4'h1;
									if(Stop[23:20]>=4'h5)
										Stop[23:20]<=0;
								end
							end
						end
					end
				end
			end
			//��ֹͣģʽ��  ֻҪ����3����ȥ�ͻḴλ
			else if(Button2State[7:4]==4'b00)
			begin 
				if(Button3State == 1'b1)
					Stop<=24'h000000;
				else
					Stop<=Stop;
			end 
		end	
		
	end
	assign StopwatchValueReg=Stop;	
	
endmodule
//LED ��ʾģ��
module LEDModule(LED,ModelState);
	input [3:0] ModelState;
	output [7:0]LED;
	reg [7:0]LED2;
	always@(ModelState)
	begin
		case(ModelState)
			4'h0:   LED2<=8'hfe;
			4'h1:	LED2<=8'hfd;
			4'h2:   LED2<=8'hfb;
			4'h3:   LED2<=8'hf7;
			default: LED2<=8'hff;
		endcase
	end
	assign LED=LED2;
endmodule 

/*ʱ�ӷ�Ƶģ�� ����50M��ʱ�ӷֳ�100��1��ʱ��*/
module clk(clk50mHZ,clk100HZ,clk1HZ,clk2HZ,clk1kHZ,clk10HZ,twinkle);
	input clk50mHZ;
	output clk100HZ,clk1HZ,clk2HZ,clk1kHZ,clk10HZ;
	output twinkle;
	reg [18:0] count100;
	reg [27:0] count; 
	reg [23:0] count2;
	reg [15:0] count1k;
	reg [23:0] count10;
	reg clk100,clk1,clk2,clk1k,clk10;
	
	always @(posedge clk50mHZ )
	begin 
		if(count100>=19'd250000)
		begin
			count100<=0;
			clk100<=~clk100;
		end
		else  
		count100<=count100+1'b1;
		
		if(count==28'd25000000)
		begin
			count<=0;
			clk1=~clk1;
		end
		else 
		count<=count+1'b1;
		
		if(count2==24'd12500000)
		begin
			count2<=0;
			clk2=~clk2;
		end
		else 
		count2<=count2+1'b1;
		
		if(count1k==16'd25000)
		begin
			count1k<=0;
			clk1k=~clk1k;
		end
		else 
		count1k<=count1k+1'b1;
		
		if(count10==8'd2500000)
		begin
			count10<=0;
			clk10=~clk10;
		end
		else 
		count10<=count10+1'b1;
		
	end
	assign clk100HZ=clk100;
	assign clk1HZ=clk1;
	assign clk2HZ=clk2;
	assign twinkle=clk2;
	assign clk1kHZ=clk1k;
	assign clk10HZ=clk10;
endmodule 


/*�������ʾģ�� ������Ҫ�������ֵ��λѡ*/
module tube(value,LED7S,dig,clk,modelState);
	input clk;
	input [3:0] modelState;
	input  [23:0] value; 	//��ʾ���ݼĴ���
	output [7:0] LED7S; //����ܶ������
	output [7:0] dig; 	//�����λѡ�Ĵ���
	reg [3:0] sele;   //�����λѡ����
	reg [7:0] dula;
	reg [7:0] segment;
    reg[3:0] num;
    reg[3:0]   i;
    always @(posedge clk)//����ܵ�λѡ��̬ɨ��
	begin 
		sele=sele+1'b1;
		if(sele>=8)
		sele=0;
	end 
    
	always @(sele)//һ��λѡ�����˱仯�ͻᴥ��
	begin 
		if(modelState==4'h3)
		begin//����� ADC ģʽ��Ӧ����ܵ�λ�ý�����ʾADC    ���㼸��
			case (sele)
				4'h0 :begin segment = 8'hfe; num=value[3:0] ; end
				4'h1 :begin segment = 8'hfd; num=value[7:4]  ; end
				4'h2 :begin segment = 8'hfb; num=value[11:8]; end
				4'h3 :begin segment = 8'hf7; num=4'hf  ; end
				4'h4 :begin segment = 8'hef; num=4'hf  ; end
				4'h5 :begin segment = 8'hdf; num=4'hc  ; end
				4'h6 :begin segment = 8'hbf; num=4'hd  ; end
				4'h7 :begin segment = 8'h7f; num=4'ha  ; end
			default:  begin segment = 8'hdf; num=4'hf  ; end
			endcase
		end
		else
		begin
			case (sele)//һ��λѡ�����˱仯�ͻᴥ��
			//*�������ͨģʽ������ʾxx-xx-xx*/
				4'h0 :begin segment = 8'hfe; num=value[3:0]  ; end
				4'h1 :begin segment = 8'hfd; num=value[7:4]  ; end
				4'h2 :begin segment = 8'hfb; num=4'he	     ; end
				4'h3 :begin segment = 8'hf7; num=value[11:8] ; end
				4'h4 :begin segment = 8'hef; num=value[15:12]; end
				4'h5 :begin segment = 8'hdf; num=4'he        ; end
				4'h6 :begin segment = 8'hbf; num=value[19:16]; end
				4'h7 :begin segment = 8'h7f; num=value[23:20]; end
			default:  begin segment = 8'hdf; num=4'he        ; end
			endcase
		end
	end
	//����ܶ�ѡ�ķ���
	always @ (num)
	begin
		//�����ADCģʽ��ɨ�赽�˸�λ��ô�ͼ�С����
		if(sele==4'h2 && modelState==4'h3)//��С����
		begin
			case (num)
				4'h0 : dula = 8'h40; 	//��ʾ"0"
				4'h1 : dula = 8'h79;    //��ʾ"1"
				4'h2 : dula = 8'h24; 	//��ʾ"2"
				4'h3 : dula = 8'h30; 	//��ʾ"3"
				default:dula =8'hff;    //����ʾ
			endcase
		end	
		//ͨ�ö�ѡ���
		else
		begin 
			case (num)
				4'h0 : dula = 8'hc0; 	//��ʾ"0"
				4'h1 : dula = 8'hf9;    //��ʾ"1"
				4'h2 : dula = 8'ha4; 	//��ʾ"2"
				4'h3 : dula = 8'hb0; 	//��ʾ"3"
				4'h4 : dula = 8'h99;	//��ʾ"4"
				4'h5 : dula = 8'h92; 	//��ʾ"5"
				4'h6 : dula = 8'h82; 	//��ʾ"6"
				4'h7 : dula = 8'hf8; 	//��ʾ"7"
				4'h8 : dula = 8'h80; 	//��ʾ"8"
				4'h9 : dula = 8'h90; 	//��ʾ"9"
				4'ha : dula = 8'h88;	//��ʾ"a"
				4'hb : dula = 8'h83;	//��ʾ"b"
				4'hc : dula = 8'hc6;	//��ʾ"c"
				4'hd : dula = 8'ha1;	//��ʾ"d"
				4'he : dula = 8'hbf;	//��ʾ"-"
				default:dula =8'hff;    //����ʾ
			endcase
		end 
	end
	assign LED7S=dula;
	assign dig=segment;
endmodule 
//����1�л�ģʽ
module Button1Module(clk,btn1In,ModelState); // button1
	input clk,btn1In;
	output[3:0] ModelState;
	reg[3:0] ModelState2;
	wire btn1Out;
	switch(clk,btn1In,btn1Out);
	always@(negedge btn1Out)
	begin
		if(ModelState2 < 4'h3) ModelState2 <= ModelState2+4'h1;
		else ModelState2 <= 4'h0;	
	end
	assign ModelState=ModelState2;
endmodule 
//����2�ڰ���1�Ĳ�ͬģʽ�»��в�ͬ�ı仯�͹���
module Button2Module(clk,btn2In,ModelState,Button2State); // button2
	input clk,btn2In;
	input[3:0] ModelState;
	output[11:0] Button2State; 
	reg[11:0] Button2State2;
	wire btn2Out;
	switch(clk,btn2In,btn2Out);
	always@(negedge btn2Out)
	begin
		if(ModelState == 4'h0) //time set
		begin
			if(Button2State2[3:0] < 4'b11) Button2State2[3:0]<=Button2State2[3:0]+4'b1;
			else Button2State2[3:0]<=0;
		end
		else if(ModelState == 4'h1) // stopwatch set
		begin
			if(Button2State2[7:4] == 4'b00) Button2State2[7:4] <= 2'b01;
			else Button2State2[7:4] <= 2'b00;
		end
		else if(ModelState == 4'h2) // alarm set
		begin
			if(Button2State2[11:8] < 4'b11) Button2State2[11:8]<=Button2State2[11:8]+4'b1;
			else Button2State2[11:4]<=0;		
		end	
	end

	assign Button2State=Button2State2;
endmodule 

//����3 ֻ��ʹ��ʧ�ܵ�����
module Button3Module(clk50MHZ,clk2HZ,btn3In,ModelState,Button3State); // button3
	input clk50MHZ,clk2HZ,btn3In;
	input[1:0] ModelState;
	output Button3State;
	reg Button3State2;
	wire btn3Out;
	switch(clk50MHZ,btn3In,btn3Out);
	assign Button3State=~btn3Out;
endmodule 
//��������ģ��  ��ʱ6����
module switch(clk,keyin,keyout);
	parameter LENGTH=8;
	input clk,keyin;
	output keyout;
	reg keyout2;
	reg[19:0] count;
	always@(posedge clk)
	begin
		if(keyin) //high
		begin
			count <= 0;
			keyout2 <= keyin;
		end
		if(!keyin)  //low
		begin
			count <= count+1'b1;
			if(count >= 20'd300000)
				keyout2<=keyin;
			if(count >= 20'h51000)
				count<=20'h50000;
		end
	end
	assign keyout=keyout2;
endmodule 
//������ģ��
module beepModule(clk,on1,on2,out);
	parameter soundspace=300;
	parameter shotstopspace=200;
	parameter longstopspace=500;
	input clk,on1,on2;
	output reg out;
	reg sound;
	always@(posedge clk)
		sound<=~sound;
	reg[10:0] mscount;
	always@(posedge clk)
	begin
		if(mscount==(soundspace*3+shotstopspace*2+longstopspace-1)) mscount <= 0;
		else mscount<=mscount+1'b1;
	end
	always@(negedge clk)
	begin
		if(on1||on2)
		begin
			if((mscount>=0)&&(mscount<soundspace)) out<=sound;
			else if((mscount>=soundspace) && (mscount<(soundspace+shotstopspace))) out<=0;
			else if((mscount>=(soundspace+shotstopspace)) && (mscount<(soundspace+shotstopspace)+soundspace)) out<=sound;
			else if((mscount>=(soundspace+shotstopspace)+soundspace) && (mscount<(soundspace+shotstopspace)*2)) out<=0;
			else if((mscount>=(soundspace+shotstopspace)*2) && (mscount<((soundspace+shotstopspace)*2+soundspace))) out<=sound;
			else out<=0;
		end
		else out<=0;
	end
endmodule
//ADC���ѹģ��
module TLC549 (clk ,AD_CS,AD_CLK,AD_DATA,AdValueReg,modelState);
	input clk;
	input [3:0] modelState;
	input AD_DATA;
	output AD_CS,AD_CLK;
	output [23:0] AdValueReg;
	reg [11:0] advalue;	
	reg [4:0] T;
	reg cs;
	reg adclk;
	reg [7:0] BUF;
	reg [7:0] BUF2;
	reg [3:0] cnt;
	always @ (posedge clk) //2us
	begin 
		if(!cs && modelState==4'h3)
			T<=T+1'b1;
		else 
			T<=1'b0;
	end 
	always @ (posedge clk)
	begin
		if(modelState==4'h3)
		begin
			case (T)//����ʱ����Ҫ�ȴ�2���ڲ�ʱ��  ���ڵڰ˸�ʱ������Ƭѡ�߱���Ϊ�ߵ�ƽ
				0,1: begin cs<=1'b0;adclk<=1'b0;end
				/*5'd2:begin cs<=1'b0;adclk<=1'b1;end
				5'd3:begin cs<=1'b0;adclk<=1'b0;end
				5'd4:begin cs<=1'b0;adclk<=1'b1;end
				5'd5:begin cs<=1'b0;adclk<=1'b0;end
				5'd6:begin cs<=1'b0;adclk<=1'b1;end
				5'd7:begin cs<=1'b0;adclk<=1'b0;end
				5'd8:begin cs<=1'b0;adclk<=1'b1;end
				5'd9:begin cs<=1'b0;adclk<=1'b0;end
				5'd10:begin cs<=1'b0;adclk<=1'b1;end
				5'd11:begin cs<=1'b0;adclk<=1'b0;end
				5'd12:begin cs<=1'b0;adclk<=1'b1;end
				5'd13:begin cs<=1'b0;adclk<=1'b0;end
				5'd14:begin cs<=1'b0;adclk<=1'b1;end
				5'd15:begin cs<=1'b0;adclk<=1'b0;end
				5'd16:begin cs<=1'b0;adclk<=1'b1;end
				5'd17:begin cs<=1'b0;adclk<=1'b0;end*/
				5'd17:begin cs<=1'b1;adclk<=1'b0;end
				5'd19:begin cs<=1'b1;adclk<=1'b0;end
				5'd20:begin cs<=1'b1;adclk<=1'b0;end
				default:begin cs<=1'b0;adclk<=~T[0];end
			endcase
		end 
	end 
	always @( posedge  adclk)
	begin
		if(!cs)
		begin 
			if(cnt==4'h7)   //8λ�������
			begin
				BUF2<=BUF;
				cnt<=4'h0;
			end	
			else
			begin  //8λ��������
				BUF[0]=AD_DATA;
				BUF=BUF<<1;
				cnt<=cnt+1'b1;
			end 
		end 
			
	end
	//��8λ������ת��Ϊx.xx���洢����Ȼ��ͨ���������ʾ����
	always @ (BUF2)
	begin
		case(BUF2)
			8'h00 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=0;end
			8'h01 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=1;end
			8'h02 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=3;end
			8'h03 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=4;end
			8'h04 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=5;end
			8'h05 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=7;end
			8'h06 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=8;end
			8'h07 :begin  advalue[11:8]<=0; advalue[7:4]<=0;advalue[3:0]<=9;end
			8'h08 :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=1;end
			8'h09 :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=2;end
			8'h0a :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=3;end
			8'h0b :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=4;end
			8'h0c :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=6;end
			8'h0d :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=7;end
			8'h0e :begin  advalue[11:8]<=0; advalue[7:4]<=1;advalue[3:0]<=8;end
			8'h0f :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=0;end
			8'h10 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=1;end
			8'h11 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=2;end
			8'h12 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=3;end
			8'h13 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=5;end
			8'h14 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=6;end
			8'h15 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=7;end
			8'h16 :begin  advalue[11:8]<=0; advalue[7:4]<=2;advalue[3:0]<=9;end
			8'h17 :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=0;end
			8'h18 :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=1;end
			8'h19 :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=3;end
			8'h1a :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=4;end
			8'h1b :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=5;end
			8'h1c :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=6;end
			8'h1d :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=8;end
			8'h1e :begin  advalue[11:8]<=0; advalue[7:4]<=3;advalue[3:0]<=9;end
			8'h1f :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=0;end
			8'h20 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=2;end
			8'h21 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=3;end
			8'h22 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=4;end
			8'h23 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=6;end
			8'h24 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=7;end
			8'h25 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=8;end
			8'h26 :begin  advalue[11:8]<=0; advalue[7:4]<=4;advalue[3:0]<=9;end
			8'h27 :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=0;end
			8'h28 :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=2;end
			8'h29 :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=3;end
			8'h2a :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=5;end
			8'h2b :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=6;end
			8'h2c :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=7;end
			8'h2d :begin  advalue[11:8]<=0; advalue[7:4]<=5;advalue[3:0]<=9;end
			8'h2e :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=0;end
			8'h2f :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=1;end
			8'h30 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=2;end
			8'h31 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=4;end
			8'h32 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=5;end
			8'h33 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=6;end
			8'h34 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=8;end
			8'h35 :begin  advalue[11:8]<=0; advalue[7:4]<=6;advalue[3:0]<=9;end
			8'h36 :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=0;end
			8'h37 :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=2;end
			8'h38 :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=3;end
			8'h39 :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=4;end
			8'h3a :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=5;end
			8'h3b :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=7;end
			8'h3c :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=8;end
			8'h3d :begin  advalue[11:8]<=0; advalue[7:4]<=7;advalue[3:0]<=9;end
			8'h3e :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=0;end
			8'h3f :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=2;end
			8'h40 :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=3;end
			8'h41 :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=5;end
			8'h42 :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=6;end
			8'h43 :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=7;end
			8'h44 :begin  advalue[11:8]<=0; advalue[7:4]<=8;advalue[3:0]<=8;end
			8'h45 :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=0;end
			8'h46 :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=1;end
			8'h47 :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=2;end
			8'h48 :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=4;end
			8'h49 :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=5;end
			8'h4a :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=6;end
			8'h4b :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=8;end
			8'h4c :begin  advalue[11:8]<=0; advalue[7:4]<=9;advalue[3:0]<=9;end
			8'h4d :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=0;end
			8'h4e :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=1;end
			8'h4f :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=3;end
			8'h50 :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=4;end
			8'h51 :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=5;end
			8'h52 :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=7;end
			8'h53 :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=8;end
			8'h54 :begin  advalue[11:8]<=1; advalue[7:4]<=0;advalue[3:0]<=9;end
			8'h55 :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=1;end
			8'h56 :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=2;end
			8'h57 :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=3;end
			8'h58 :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=4;end
			8'h59 :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=6;end
			8'h5a :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=7;end
			8'h5b :begin  advalue[11:8]<=1; advalue[7:4]<=1;advalue[3:0]<=8;end
			8'h5c :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=0;end
			8'h5d :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=1;end
			8'h5e :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=2;end
			8'h5f :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=3;end
			8'h60 :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=5;end
			8'h61 :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=6;end
			8'h62 :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=7;end
			8'h63 :begin  advalue[11:8]<=1; advalue[7:4]<=2;advalue[3:0]<=9;end
			8'h64 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=0;end
			8'h65 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=1;end
			8'h66 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=3;end
			8'h67 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=4;end
			8'h68 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=5;end
			8'h69 :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=6;end
			8'h6a :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=8;end
			8'h6b :begin  advalue[11:8]<=1; advalue[7:4]<=3;advalue[3:0]<=9;end
			8'h6c :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=0;end
			8'h6d :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=2;end
			8'h6e :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=3;end
			8'h6f :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=4;end
			8'h70 :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=6;end
			8'h71 :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=7;end
			8'h72 :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=8;end
			8'h73 :begin  advalue[11:8]<=1; advalue[7:4]<=4;advalue[3:0]<=9;end
			8'h74 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=0;end
			8'h75 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=2;end
			8'h76 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=3;end
			8'h77 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=5;end
			8'h78 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=6;end
			8'h79 :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=7;end
			8'h7a :begin  advalue[11:8]<=1; advalue[7:4]<=5;advalue[3:0]<=9;end
			8'h7b :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=0;end
			8'h7c :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=1;end
			8'h7d :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=2;end
			8'h7e :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=4;end
			8'h7f :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=5;end
			8'h80 :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=6;end
			8'h81 :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=8;end
			8'h82 :begin  advalue[11:8]<=1; advalue[7:4]<=6;advalue[3:0]<=9;end
			8'h83 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=0;end
			8'h84 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=2;end
			8'h85 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=3;end
			8'h86 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=4;end
			8'h87 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=5;end
			8'h88 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=7;end
			8'h89 :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=8;end
			8'h8a :begin  advalue[11:8]<=1; advalue[7:4]<=7;advalue[3:0]<=9;end
			8'h8b :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=0;end
			8'h8c :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=2;end
			8'h8d :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=3;end
			8'h8e :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=5;end
			8'h8f :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=6;end
			8'h90 :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=7;end
			8'h91 :begin  advalue[11:8]<=1; advalue[7:4]<=8;advalue[3:0]<=8;end
			8'h92 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=0;end
			8'h93 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=1;end
			8'h94 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=2;end
			8'h95 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=4;end
			8'h96 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=5;end
			8'h97 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=6;end
			8'h98 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=8;end
			8'h99 :begin  advalue[11:8]<=1; advalue[7:4]<=9;advalue[3:0]<=9;end
			8'h9a :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=0;end
			8'h9b :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=1;end
			8'h9c :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=3;end
			8'h9d :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=4;end
			8'h9e :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=5;end
			8'h9f :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=7;end
			8'ha0 :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=8;end
			8'ha1 :begin  advalue[11:8]<=2; advalue[7:4]<=0;advalue[3:0]<=9;end
			8'ha2 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=1;end
			8'ha3 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=2;end
			8'ha4 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=3;end
			8'ha5 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=4;end
			8'ha6 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=6;end
			8'ha7 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=7;end
			8'ha8 :begin  advalue[11:8]<=2; advalue[7:4]<=1;advalue[3:0]<=8;end
			8'ha9 :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=0;end
			8'haa :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=1;end
			8'hab :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=2;end
			8'hac :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=3;end
			8'had :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=5;end
			8'hae :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=6;end
			8'haf :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=7;end
			8'hb0 :begin  advalue[11:8]<=2; advalue[7:4]<=2;advalue[3:0]<=9;end
			8'hb1 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=0;end
			8'hb2 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=1;end
			8'hb3 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=3;end
			8'hb4 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=4;end
			8'hb5 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=5;end
			8'hb6 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=6;end
			8'hb7 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=8;end
			8'hb8 :begin  advalue[11:8]<=2; advalue[7:4]<=3;advalue[3:0]<=9;end
			8'hb9 :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=0;end
			8'hba :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=2;end
			8'hbb :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=3;end
			8'hbc :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=4;end
			8'hbd :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=6;end
			8'hbe :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=7;end
			8'hbf :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=8;end
			8'hc0 :begin  advalue[11:8]<=2; advalue[7:4]<=4;advalue[3:0]<=9;end
			8'hc1 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=0;end
			8'hc2 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=2;end
			8'hc3 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=3;end
			8'hc4 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=5;end
			8'hc5 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=6;end
			8'hc6 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=7;end
			8'hc7 :begin  advalue[11:8]<=2; advalue[7:4]<=5;advalue[3:0]<=9;end
			8'hc8 :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=0;end
			8'hc9 :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=1;end
			8'hca :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=2;end
			8'hcb :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=4;end
			8'hcc :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=5;end
			8'hcd :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=6;end
			8'hce :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=8;end
			8'hcf :begin  advalue[11:8]<=2; advalue[7:4]<=6;advalue[3:0]<=9;end
			8'hd0 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=0;end
			8'hd1 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=2;end
			8'hd2 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=3;end
			8'hd3 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=4;end
			8'hd4 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=5;end
			8'hd5 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=7;end
			8'hd6 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=8;end
			8'hd7 :begin  advalue[11:8]<=2; advalue[7:4]<=7;advalue[3:0]<=9;end
			8'hd8 :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=0;end
			8'hd9 :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=2;end
			8'hda :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=3;end
			8'hdb :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=5;end
			8'hdc :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=6;end
			8'hdd :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=7;end
			8'hde :begin  advalue[11:8]<=2; advalue[7:4]<=8;advalue[3:0]<=8;end
			8'hdf :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=0;end
			8'he0 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=1;end
			8'he1 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=2;end
			8'he2 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=4;end
			8'he3 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=5;end
			8'he4 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=6;end
			8'he5 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=8;end
			8'he6 :begin  advalue[11:8]<=2; advalue[7:4]<=9;advalue[3:0]<=9;end
			8'he7 :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=0;end
			8'he8 :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=1;end
			8'he9 :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=3;end
			8'hea :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=4;end
			8'heb :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=5;end
			8'hec :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=7;end
			8'hed :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=8;end
			8'hee :begin  advalue[11:8]<=3; advalue[7:4]<=0;advalue[3:0]<=9;end
			8'hef :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=1;end
			8'hf0 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=2;end
			8'hf1 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=3;end
			8'hf2 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=4;end
			8'hf3 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=6;end
			8'hf4 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=7;end
			8'hf5 :begin  advalue[11:8]<=3; advalue[7:4]<=1;advalue[3:0]<=8;end
			8'hf6 :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=0;end
			8'hf7 :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=1;end
			8'hf8 :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=2;end
			8'hf9 :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=3;end
			8'hfa :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=5;end
			8'hfb :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=6;end
			8'hfc :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=7;end
			8'hfd :begin  advalue[11:8]<=3; advalue[7:4]<=2;advalue[3:0]<=9;end
			8'hfe :begin  advalue[11:8]<=3; advalue[7:4]<=3;advalue[3:0]<=0;end
			8'hff :begin  advalue[11:8]<=3; advalue[7:4]<=3;advalue[3:0]<=1;end			
		default:advalue=12'h000;
		endcase
	end
	assign AD_CS=cs;
	assign AdValueReg=advalue|24'h000000;//��advalueת��Ϊͨ�õ�24λ�����ʽ �����������ʾ����
	assign AD_CLK=adclk;
endmodule 














