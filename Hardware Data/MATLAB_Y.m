xg=xlsread('telemetry_data.csv','C:C');
s=xlsread('telemetry_data.csv','A:A');
fs=100;
LL2 = length(xg);
Ts = 1/fs; %sampling time interval
t = 0:Ts:Ts*(LL2-1);
f = fs*(0:(LL2/2))/LL2;  % Frequency values
figure()
  subplot(2,3,1)
  plot(t,xg,'b');
  grid on
  set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
  xlabel('Time,sec')
  ylabel('Accx,g/s^2')
  legend('Acc X')
  title('Time-domain Spectrum') , shg
X = fft(xg); 
P2 = abs(X/LL2);
P1 = P2(1:(LL2/2)+1);
P1(2:end-1) = 2*P1(2:end-1);

subplot(2,3,2)
plot(f, P1, 'r'); % Create a plot with a logarithmic scale for the x-axis and a linear scale for the y-axis
hold on
xlim([0 max(f)]) % set the limit for x axis
grid on
set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
xlabel('Frequency (Hertz)')
ylabel('Magnitude')
title('frequency-domain Spectrum') , shg

zg=xlsread('DEMO1.csv','D:D');
s=xlsread('DEMO1.csv','A:A');
fs=100;
LL2 = length(zg);
Ts = 1/fs; %sampling time interval
t = 0:Ts:Ts*(LL2-1);
f = fs*(0:(LL2/2))/LL2;  % Frequency values
subplot(2,3,3)
plot(t,zg,'y');
grid on
set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
xlabel('Time,sec')
ylabel('AccY,g/s^2')
legend('Acc Y')
title('Time-domain Spectrum') , shg
Z = fft(zg); 
P2 = abs(Z/LL2);
P1 = P2(1:(LL2/2)+1);
P1(2:end-1) = 2*P1(2:end-1);
subplot(2,3,4)
plot(f, P1, 'g'); % Create a plot with a logarithmic scale for the x-axis and a linear scale for the y-axis
hold on
xlim([0 max(f)]) % set the limit for x axis
grid on
set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
xlabel('Frequency (Hertz)')
ylabel('Magnitude')
title('frequency-domain Spectrum') , shg

zg=xlsread('DEMO1.csv','E:E');
s=xlsread('DEMO1.csv','A:A');
fs=100;
LL2 = length(zg);
Ts = 1/fs; %sampling time interval
t = 0:Ts:Ts*(LL2-1);
f = fs*(0:(LL2/2))/LL2;  % Frequency values
subplot(2,3,5)
plot(t,zg,'k');
grid on
set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
xlabel('Time,sec')
ylabel('AccZ,g/s^2')
legend('Acc Z')
title('Time-domain Spectrum') , shg
Z = fft(zg); 
P2 = abs(Z/LL2);
P1 = P2(1:(LL2/2)+1);
P1(2:end-1) = 2*P1(2:end-1);
subplot(2,3,6)
plot(f, P1, 'm'); % Create a plot with a logarithmic scale for the x-axis and a linear scale for the y-axis
hold on
xlim([0 max(f)]) % set the limit for x axis
grid on
set(gca, 'FontName', 'Times New Roman', 'FontSize', 14)
xlabel('Frequency (Hertz)')
ylabel('Magnitude')
title('frequency-domain Spectrum') , shg