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
z=x1*1.5+y;
sound(z,fs);  %����     flipud(y)����
% audiowrite('ңԶѩɽ.wav',z,fs) ;