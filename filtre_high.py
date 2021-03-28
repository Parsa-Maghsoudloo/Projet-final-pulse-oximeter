import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, fftfreq
from scipy import signal

#### Lecture ##################################################
file_high_IR = open("SpO2_signal_high_BPM\IR.txt", 'r')
file_high_RED = open("SpO2_signal_high_BPM\RED.txt")

read_size = len(file_high_IR.read())
file_high_IR.seek(0)
Fs = 250

line_IR = file_high_IR.read()
line_IR = line_IR.split(',')
line_RED = file_high_RED.read()
line_RED = line_RED.split(',')
high_IR = []
high_RED = []
for i in range(0, len(line_IR)):
    try:
        high_IR.append(float(line_IR[i]))
        high_RED.append(float(line_RED[i]))
    except ValueError:
        print(i)

################################################
####Affichage###################################
time = len(high_IR) / Fs
plt.figure(1)
x = np.linspace(0, time, len(high_IR))
plt.plot(x, high_IR, label='IR')
plt.plot(x, high_RED, label='RED')
plt.legend()
plt.show()
################################################
#Fourier
n = len(high_IR)
freqs = fftfreq(n)
mask = freqs > 0
high_IR_fft = np.abs(fft(high_IR)/n)*2
high_RED_fft = np.abs(fft(high_RED)/n)*2
plt.figure(2)
plt.plot(freqs[mask], high_IR_fft[mask], label='IR')
plt.plot(freqs[mask], high_RED_fft[mask], label='RED')
plt.legend()
plt.show()

Fc = 1
Wn = Fc / (Fs / 2)
sos = signal.butter(6, 1, 'high', fs=Fs, output='sos')
Fc = 60
Wn = Fc / (Fs / 2)
sos2 = signal.butter(6, 6, 'low', fs=Fs, output='sos')
high_IR_filtered = signal.sosfilt(sos, high_IR)
high_IR_filtered = signal.sosfilt(sos2, high_IR_filtered)
high_RED_filtered = signal.sosfilt(sos, high_RED)
high_RED_filtered = signal.sosfilt(sos2, high_RED_filtered)

mask = (-5000 < high_IR_filtered) & (high_IR_filtered < 5000)
all_peaks = signal.find_peaks(high_IR_filtered[mask], 2500)
BPM = len(all_peaks[0]) / (time / 60)
plt.figure(3)
plt.plot(x[mask], high_IR_filtered[mask], label='IR')
#plt.plot(x[mask], high_RED_filtered[mask], label='RED')
plt.legend()
plt.show()

print(BPM)


