clc
clear all
[y,fs] = audioread('ңԶ����;.mp3');

fp=1600;fc=1700;As=1000;Ap=3;   %fp=1500   fc=1700
%(����Ϊ��ͨ�˲���������ָ�꣩

wc=2*pi*fc/fs; wp=2*pi*fp/fs;
wdel=wc-wp;
beta=0.112*(As-8.7);
N=ceil((As-8)/2.285/wdel);
wn= kaiser(N+1,beta);
ws=(wp+wc)/2/pi;
b=fir1(N,ws,wn);

x=fftfilt(b,y);

z=y+3*x;   %�ص���

sound(z,fs);  












