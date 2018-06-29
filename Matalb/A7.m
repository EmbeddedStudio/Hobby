clc
clear all

fp=100;fs=200;ap=2;as=15;     %数字滤波器指标
fsa=500;T=1/fsa;              %采样频率与间隔
wp=2*pi*fp/fsa;ws=2*pi*fs/fsa;  %转换为数字角频率
Wp=2/T*tan(wp/2);Ws=2/T*tan(ws/2);  %由数字角频率转换为模拟角频率

[N,Wc]=buttord(Wp,Ws,ap,as,'s');    %获取模拟滤波器的阶数和3dB截止频率    
[Z,P,K]=buttap(N);             %归一化模拟滤波器模型的零极点形式参数
[B,A]=zp2tf(Z,P,K);            %归一化模拟滤波器传递函数的系数
[Bl,Al]=lp2lp(B,A,Wc);    %把模拟滤波器原型转换成截至频率为Wc的低通滤波器
[b,a]=bilinear(Bl,Al,fsa);%用双线性变换法实现模拟滤波器到数字滤波器的转换   
[H,w]=freqz(b,a);         %获取频率响应
plot(w*fsa/(2*pi),abs(H));grid; %绘制频率响应曲线
xlabel('频率(Hz)');ylabel('频率响应幅度');
title ('巴特沃斯低通滤波器');








