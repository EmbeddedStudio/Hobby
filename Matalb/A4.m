clear all
clc
x=[1:12];
h=[1 1 1 1 1 1];
for i=1:12
    x(i)=0.8.^x(i);
end
xn=length(x);
hn=length(h);
N=hn+xn-1;
X=fft(x,N);
H=fft(h,N);
Y=X.*H;
y=ifft(Y,N);
stem (y,'o'); grid on 












