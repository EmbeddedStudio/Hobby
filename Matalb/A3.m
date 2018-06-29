clear all
clc
x=[1:12];
h=[1 1 1 1 1 1];
for i=1:12
    x(i)=0.8.^x(i);
end
yl=conv(x,h)
subplot(211);
% axis([0 20 0 3]);
stem(yl,'o');grid on
title('线性卷积');
N=17;
yc=ifft(fft(x,N).*fft(h,N))
subplot(212);
stem(yc,'o');title('圆周卷积');
% axis([0 20 0 3]);
grid on


