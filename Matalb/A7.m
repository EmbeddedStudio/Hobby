clc
clear all

fp=100;fs=200;ap=2;as=15;     %�����˲���ָ��
fsa=500;T=1/fsa;              %����Ƶ������
wp=2*pi*fp/fsa;ws=2*pi*fs/fsa;  %ת��Ϊ���ֽ�Ƶ��
Wp=2/T*tan(wp/2);Ws=2/T*tan(ws/2);  %�����ֽ�Ƶ��ת��Ϊģ���Ƶ��

[N,Wc]=buttord(Wp,Ws,ap,as,'s');    %��ȡģ���˲����Ľ�����3dB��ֹƵ��    
[Z,P,K]=buttap(N);             %��һ��ģ���˲���ģ�͵��㼫����ʽ����
[B,A]=zp2tf(Z,P,K);            %��һ��ģ���˲������ݺ�����ϵ��
[Bl,Al]=lp2lp(B,A,Wc);    %��ģ���˲���ԭ��ת���ɽ���Ƶ��ΪWc�ĵ�ͨ�˲���
[b,a]=bilinear(Bl,Al,fsa);%��˫���Ա任��ʵ��ģ���˲����������˲�����ת��   
[H,w]=freqz(b,a);         %��ȡƵ����Ӧ
plot(w*fsa/(2*pi),abs(H));grid; %����Ƶ����Ӧ����
xlabel('Ƶ��(Hz)');ylabel('Ƶ����Ӧ����');
title ('������˹��ͨ�˲���');








