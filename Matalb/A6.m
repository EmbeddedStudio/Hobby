% clc
% clear all
% 
% FS=1;
% wp=0.2*pi;
% ws=0.3*pi;
% B=ws-wp;
% N=ceil(6.2*pi/B);
% M=N-1;
% wc=(wp+B/2)/pi;
% hn=fir1(M,wc,hanning(N));
% H=1024;
% hk=fft(hn,H);
% n=0:N-1;
% figure(1);
% subplot(2,2,1);
% stem(n,hn,'.');
% xlabel('n');ylabel('h(n)');grid on ;
% k=1:H/2+1;
% w=2*(0:H/2)/H;
% subplot(2,2,2);
% plot(w,20*log10(abs(hk(k))));%����h(k)��Ƶ��ͼ
% xlabel('��/��');ylabel('20lg|Hg(��)|');grid on ;
% wf=0:pi/511:pi;
% HK=freqz(hn,wf);
% wHz=wf*FS/(2*pi);   %ת��ΪHZ
% subplot(2,2,3);
% plot(wHz,20*log10(abs(HK))); %����Hz��Ƶ��
% xlabel('Ƶ��');ylabel('����');grid on ;
% 
% FS=1;
% H=1024;
% t=[0:1/FS:H/FS];
% S=2+3*cos(2*pi*0.08*t+pi*(-50)/180)+2*sin(2*pi*0.3*t+pi*50/180)+5*cos(2*pi*0.35*t);
% figure(2);
% subplot(2,2,1);
% plot(S);title('�˲�ǰ���ź�');
% Y=fft(S,H);
% Axx = (abs(Y));
% Axx =Axx/(H/2);
% Axx(1)=Axx(1)/2;
% F=([1:H]-1)*FS/H;
% subplot(2,2,2);
% plot(F(1:H/2),Axx(1:H/2));
% title('�˲�ǰ���ź�Ƶ��');
% 
% wp=0.2*pi;
% ws=0.3*pi;
% B=ws-wp;
% N=ceil(6.2*pi/B);
% M=N-1;
% wc=(wp+B/2)/pi;
% hn=fir1(M,wc,hanning(N));
% HK=fft(hn,H);
% YK=Y.*HK;
% y=ifft(YK);
% subplot(2,2,3);
% f=0:2*pi/100:2*pi;
% plot(f,y(1:101));
% title('�˲�����ź�');
% 
% Ayy=(abs(YK));
% Ayy=Ayy/(H/2);
% Ayy(1)=Ayy(1)/2;
% F=([1:H]-1)*FS/H;
% subplot(2,2,4);
% plot(F(1:H/2),Ayy(1:H/2));
% title('�˲����Ƶ��');
clc 
clear all

wp = 0.2*pi;
ws = 0.3*pi; 
width= ws-wp; %����
N = ceil(6.2*pi/width);%���������ȡ��
n=0:1:N-1;
wc = (ws+wp)/2;
t=(N-1)/2;
m=n-t;
hd=sin(wc*m)./(pi*m);%�弤��Ӧ
ham=(hanning(N))';%������
h=hd.*ham;
a=[1];
b=fir1(N-1,wc/pi,ham);%fir1�ǻ��ڼӴ���������ӦFIR�����˲�����ƺ�����hamΪ������
freqz(b,a,500);%�˲���Ƶ����Ӧ����,����500��ĸ�Ƶ��Ӧʸ��h��n���Ƶ������w