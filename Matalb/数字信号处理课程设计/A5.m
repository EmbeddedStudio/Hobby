%%%%�����5��
k = 256;
num = [0.8,-0.44,0.36,0.22];
den = [1,0.7,-0.45,-0.6];
w = 0:pi/k:pi;
h = freqz(num,den,w);
subplot(2,1,1);plot(w/pi,angle(h));title('��Ƶ��Ӧ')
xlabel('\omega/\pi');ylabel('����');grid on
subplot(2,1,2);plot(w/pi,abs(h));title('������');
grid on
xlabel('\omega/\pi');ylabel('��ֵ');title('��ֵ')