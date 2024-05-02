pkg load signal

%% SIGNALS GENERATORS
% SINE WAVE
%TIME VECTOR
TIME_START = 0
TIME_END = 0.5
samplingRate = 10000 %in sample/second
numSamples = samplingRate*(TIME_END - TIME_START);
phase_angle = pi;

Time = linspace(TIME_START, TIME_END, numSamples)';  
freq = 10;                  % Signal frequency in Hz
Amp = 220;                     % Signal amplitude
signal1 = Amp * sin(2 * pi * freq * Time + phase_angle);  % Generate the sinusoidal signal

data = [Time,signal1];
csvwrite('sine1.csv', data);



%% SIGNALS GENERATORS
% SINE WAVE
%TIME VECTOR
TIME_START = 0
TIME_END = 2
samplingRate = 10000 %in sample/second
numSamples = samplingRate*(TIME_END - TIME_START)
phase_angle = -pi/3 + pi/2;


Time = linspace(TIME_START, TIME_END, numSamples)';  
freq = 10;                  % Signal frequency in Hz
Amp = 220;                     % Signal amplitude
signal2 = Amp * sin(2 * pi * freq * Time + phase_angle);  % Generate the sinusoidal signal

data = [Time,signal2];
csvwrite('sine2.csv', data);