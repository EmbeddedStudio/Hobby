x=0:0.01:12*pi;
y=sawtooth(x);
n=length(x);
for i=1:n
    x(i)=x(i)/12/pi;
end
subplot(2,2,1);
plot(x,y);
title('��ݲ�');

x=0:0.01:12*pi;
y=sawtooth(x,0.5);
for i=1:n
    x(i)=x(i)/12/pi;
end
subplot(2,2,2);
plot(x,y);
title('���ǲ�');


t=0:0.00001:0.1;
y=square(2*pi*50*t,50);%2*pi*50*t,50  ����2 pi 50 HZ Ƶ��   50%ռ�ձ� 
subplot(2,2,3);
plot(t,y);
axis([0,0.1,-1.2,1.2])


title('����');

x=-5:0.1:5;

y=sinc(x);
subplot(2,2,4);
plot(x,y);

title('��������');


