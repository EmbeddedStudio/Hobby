clc
clear all

%ԭʼ�����ź�
figure(1);
[y,Fs] = audioread('ѩɽ�ɺ�.mp3');
% sound(y,Fs);  %����     flipud(y)����
n = length (y) ;    %��������źŵĳ���
Y=fft(y,n);       %����Ҷ�任
PY=fftn(y);
f=Fs*(0:n/2-1)/n;         % ��Ӧ���Ƶ��
subplot(2,1,1);plot(y);title('ԭʼ�źŲ���');
subplot(2,1,2);plot(f,abs(Y(1:n/2)));title('ԭʼ�ź�Ƶ��')

%���������źų���

s = awgn(y,20);  %�����
% sound(s,Fs);  %����     flipud(y)����
S=fft(s,n);       %����Ҷ�任
figure(2);
subplot(2,1,1);plot(s);title('����������źŲ���');
subplot(2,1,2);plot(f,abs(S(1:n/2)));title('����������ź�Ƶ��');

%�˲�����źų���
figure(3);
fp=1600;fc=2000;As=1000;Ap=3;   %fp=1500   fc=1700
%(����Ϊ��ͨ�˲���������ָ�꣩

wc=2*pi*fc/Fs; wp=2*pi*fp/Fs;
wdel=wc-wp;
beta=0.112*(As-8.7);
N=ceil((As-8)/2.285/wdel);
wn= kaiser(N+1,beta);
ws=(wp+wc)/2/pi;   
b=fir1(N,ws,wn);
         
%����ǰΪ��ͨ�˲�����ƽ׶Σ�����������Ϊȥ�������źŵĳ��򡪡�
x=fftfilt(b,s);
X=fft(x,n);

subplot(2,1,1);plot(x);title('�����Ĳ���');
subplot(2,1,2);plot(f,abs(X(1:n/2)));title('����������ź�Ƶ��');
sound(x*2,Fs)  %�ط��˲������Ƶ

%ά���˲�
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






