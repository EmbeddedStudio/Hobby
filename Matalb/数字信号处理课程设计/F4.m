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
z=x1+y;

sound(z*1.5,fs*2);  %²¥flipud(y);%µ¹·Å  sound(y,fs);
% audiowrite('Ò£Ô¶Ñ©É½.wav',z,fs) ;