

filename = 'volt.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

figure;
plot(time, value, 'b-'); % Blue solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;

hold on;

filename = 'current.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

plot(time, value, 'r-'); % Red solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;

hold on;
filename = 'power.csv';
M = csvread(filename);
time = M(:, 1);  
value = M(:, 2); 

plot(time, value, 'g-','LineWidth',3); % Red solid line
xlabel('Time');
ylabel('VALUE');
title('value vs. Time');
grid on;