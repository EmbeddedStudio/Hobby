clc
clear all
[x,fs] = audioread('Ñ©É½·Éºü.mp3');
[y,fs] = audioread('Ò£Ô¶µÄÂÃÍ¾.mp3');
nx=length (x);
ny=length (y);
nz=ny-nx;
x=x(1:nx);
y=y(1:ny);
x1=[x,zeros(1,nz)]; 
z=x1*1.5+y;
sound(z,fs);  %²¥·Å     flipud(y)µ¹·Å
% audiowrite('Ò£Ô¶Ñ©É½.wav',z,fs) ;