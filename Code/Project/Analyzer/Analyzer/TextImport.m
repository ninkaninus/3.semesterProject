impH = load('Afstand.txt');
xH = 0:10:length(impH)*10 - 1;

figure(1)
subplot(2,1,1)
plot(xH,impH)
title('1633 Hz [A, B, C, D]')
xlabel('Offset')
ylabel('Goertzel Magnitude')
grid on

impL = load('TestH.txt');
xL = 0:1:length(impL) - 1;

subplot(2,1,2)
plot(xL,impL)
title('1633 Hz, First Character')
xlabel('Offset')
ylabel('Goertzel Magnitude')
grid on
%%
figure(2)
plot(load('Fon.txt'))
xlabel('Frequency [Hz]')
ylabel('Goertzel Magnitude')