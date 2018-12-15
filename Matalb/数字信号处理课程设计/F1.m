
clc
clear all
[y,fs] = audioread('雪山飞狐.mp3');
%sound(flipud(y),fs)
sound(y,fs*1.5);   %快放
% 
% sound(y,fs*0.8);%慢放
% 
%sound(y*1.5,fs);%放大

% sound(y*0.3,fs);%衰减



