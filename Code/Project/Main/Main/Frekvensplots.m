in697 = load('697.txt');
in770 = load('770.txt');
in852 = load('852.txt');
in941 = load('941.txt');
in1209 = load('1209.txt');
in1336 = load('1336.txt');
in1477 = load('1477.txt');
in1633 = load('1633.txt');

x = 0:10:length(in697)*10 - 1;

figure(1)
subplot(4,1,1)
plot(x,in697)
title('697 Hz [1,2,3,A]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,10000])
grid on

subplot(4,1,2)
plot(x,in770)
title('770 Hz [4,5,6,B]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,10000])
grid on

subplot(4,1,3)
plot(x,in852)
title('852 Hz [7,8,9,C]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,10000])
grid on

subplot(4,1,4)
plot(x,in941)
title('941 Hz [*,0,#,D]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,10000])
grid on

figure(2)
subplot(4,1,1)
plot(x,in1209)
title('1209 Hz [1,4,7,*]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,15000])
grid on

subplot(4,1,2)
plot(x,in1336)
title('1336 Hz [2,5,8,0]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,15000])
grid on

subplot(4,1,3)
plot(x,in1477)
title('1477 Hz [3,6,9,#]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,15000])
grid on

subplot(4,1,4)
plot(x,in1633)
title('1633 Hz [A,B,C,D]')
xlabel('Samples')
ylabel('Goertzel Magnitude')
ylim([0,15000])
grid on