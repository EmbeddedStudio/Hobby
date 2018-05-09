module CNT27B(clkin, rst0, ena0, out) ;  
	input clkin,rst0,ena0;
	//input rst0; 
	//input ena0;        
	output [3:0] out; 

	reg [3:0] out;  
	reg [26:0] sout; 
	//同步使能，异步清零 
	always @ (posedge clkin or negedge rst0)   
		begin     
			if(!rst0)       
			sout <= 27'h0000000;  
			else if(ena0)
			sout<=sout+1;
			else
			sout<=sout;
			
			
			out<=sout[26:23];
		end   
 endmodule 
 
 
 
 
 
 
 