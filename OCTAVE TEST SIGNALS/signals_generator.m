%% SIGNALS GENERATORS
% SINE WAVE
t = linspace(0, 1, 1000)';  % Time vector from 0 to 1 with 1000 samples
f = 50;                   % Signal frequency in Hz
A = 220;                     % Signal amplitude
signal = A * sin(2 * pi * f * t);  % Generate the sinusoidal signal


data = [t,signal];
csvwrite('../bin/signals/sine1.csv', data);