clc
clear all
[x,fs] = audioread('ѩɽ�ɺ�.mp3');
[y,fs] = audioread('ңԶ����;.mp3');
nx=length (x);
ny=length (y);
nz=ny-nx;
x=x(1:nx);
y=y(1:ny);
x1=[x,zeros(1,nz)]; 
z=x1+y;

sound(z*1.5,fs*2);  %��flipud(y);%����  sound(y,fs);
% audiowrite('ңԶѩɽ.wav',z,fs) ;