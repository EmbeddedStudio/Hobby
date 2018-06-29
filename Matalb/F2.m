clc
clear all

figure(1);
[y,fs] = audioread('1.mp3');
n = length (y) ;    %求出语音信号的长度
%sound(y,fs);  %播放     flipud(y)倒放
Y=fft(y,n);       %傅里叶变换
f=fs*(0:n/2-1)/n;         % 对应点的频率
subplot(2,1,1);plot(y);title('原始信号波形');
subplot(2,1,2);plot(f,abs(Y(1:n/2)));title('原始信号频谱')


figure(2);
delay=0.5*fs;
x=y(1:n);
x1=[x,zeros(1,delay*2)];     %zeros(1,4000)产生1行3000列全零矩阵加到x1后面
x2=[zeros(1,delay),x*0.4,zeros(1,delay)];
x3=[zeros(1,delay*2),x*0.1];
z=x1+x2+x3;
subplot(2,1,1);
plot(z);
Z=fft(z,n);       %傅里叶变换
subplot(2,1,2);plot(f,abs(Z(1:n/2)));title('重叠信号频谱')
sound(z*5,fs);  %播放     flipud(y)倒放























