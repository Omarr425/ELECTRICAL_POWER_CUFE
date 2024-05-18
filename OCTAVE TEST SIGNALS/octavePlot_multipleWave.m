

pkg load signal

figure;

%%subplot(1,3,1);

filename = 'Voltage2.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 
plot(time, value, 'b-'); % Blue solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;


printf('voltage\n');
rms(value)
mean(value)

%%subplot(1,3,2);
hold on;
filename = 'Current2.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 
plot(time, value, 'r-'); % Blue solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;

printf('current\n');
rms(value)
mean(value)
hold on;

%%subplot(1,3,3);

hold on;
filename = 'Power2.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

plot(time, value, 'g-','LineWidth',3); % Red solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;

printf('power\n');
rms(value)
mean(value)

print("power_plot");