clc
clear all

figure(1);
[y,fs] = audioread('1.mp3');
n = length (y) ;    %��������źŵĳ���
%sound(y,fs);  %����     flipud(y)����
Y=fft(y,n);       %����Ҷ�任
f=fs*(0:n/2-1)/n;         % ��Ӧ���Ƶ��
subplot(2,1,1);plot(y);title('ԭʼ�źŲ���');
subplot(2,1,2);plot(f,abs(Y(1:n/2)));title('ԭʼ�ź�Ƶ��')


figure(2);
delay=0.5*fs;
x=y(1:n);
x1=[x,zeros(1,delay*2)];     %zeros(1,4000)����1��3000��ȫ�����ӵ�x1����
x2=[zeros(1,delay),x*0.4,zeros(1,delay)];
x3=[zeros(1,delay*2),x*0.1];
z=x1+x2+x3;
subplot(2,1,1);
plot(z);
Z=fft(z,n);       %����Ҷ�任
subplot(2,1,2);plot(f,abs(Z(1:n/2)));title('�ص��ź�Ƶ��')
sound(z*5,fs);  %����     flipud(y)����























