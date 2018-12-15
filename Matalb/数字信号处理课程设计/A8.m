clc
clear all

%原始声音信号
figure(1);
[y,Fs] = audioread('雪山飞狐.mp3');
% sound(y,Fs);  %播放     flipud(y)倒放
n = length (y) ;    %求出语音信号的长度
Y=fft(y,n);       %傅里叶变换
PY=fftn(y);
f=Fs*(0:n/2-1)/n;         % 对应点的频率
subplot(2,1,1);plot(y);title('原始信号波形');
subplot(2,1,2);plot(f,abs(Y(1:n/2)));title('原始信号频谱')

%加噪语音信号程序

s = awgn(y,20);  %信噪比
% sound(s,Fs);  %播放     flipud(y)倒放
S=fft(s,n);       %傅里叶变换
figure(2);
subplot(2,1,1);plot(s);title('加噪声后的信号波形');
subplot(2,1,2);plot(f,abs(S(1:n/2)));title('加噪声后的信号频谱');

%滤波后的信号程序
figure(3);
fp=1600;fc=2000;As=1000;Ap=3;   %fp=1500   fc=1700
%(以上为低通滤波器的性能指标）

wc=2*pi*fc/Fs; wp=2*pi*fp/Fs;
wdel=wc-wp;
beta=0.112*(As-8.7);
N=ceil((As-8)/2.285/wdel);
wn= kaiser(N+1,beta);
ws=(wp+wc)/2/pi;   
b=fir1(N,ws,wn);
         
%（此前为低通滤波器设计阶段）——接下来为去除噪声信号的程序——
x=fftfilt(b,s);
X=fft(x,n);

subplot(2,1,1);plot(x);title('降噪后的波形');
subplot(2,1,2);plot(f,abs(X(1:n/2)));title('降噪声后的信号频谱');
sound(x*2,Fs)  %回放滤波后的音频

%维纳滤波
% figure(3);
% Rz=xcorr(s);
% Gz=fft(Rz,n);
% Rsz=xcorr(s,y);
% Gsz=fft(Rsz.n);
% H=Gsz./Gz;
% X=H.*PY;
% figure;
% plot(abs(X));
% x=real(ifft(X));
% x=x(1:n);
% plot(x);
% sound(x,Fs);






