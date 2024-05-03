

filename = 'sine1.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

figure(1);
plot(time, value, 'b-'); % Blue solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;

hold on;

filename = 'sine2.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

figure(1);
plot(time, value, 'r-'); % Red solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;