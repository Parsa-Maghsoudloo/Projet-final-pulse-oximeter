import numpy as np
import matplotlib.pyplot as plt
from scipy import signal
file_normal_IR = open("SpO2_signal_normal_BPM\IR.txt", 'r')
file_normal_RED = open("SpO2_signal_normal_BPM\RED.txt")

read_size = len(file_normal_IR.read())
print(read_size)
file_normal_IR.seek(0)
Fs = 250

line_IR = file_normal_IR.read()
line_IR = line_IR.split(',')
line_RED = file_normal_RED.read()
line_RED = line_RED.split(',')
normal_IR = []
normal_RED = []
for i in range(0, len(line_IR)):
    try:
        normal_IR.append(float(line_IR[i]))
        normal_RED.append(float(line_RED[i]))
    except ValueError:
        print(i)


time = len(normal_IR) / Fs

plt.figure(1)
x = np.linspace(0, time, len(normal_IR))
plt.plot(x, normal_IR, label='IR')
plt.plot(x, normal_RED, label='RED')
plt.legend()
# plt.show()
################################################
# Fourier
# n = len(normal_IR)
# freqs = fftfreq(n)
# mask = freqs > 0
# normal_IR_fft = np.abs(fft(normal_IR)/n)*2
# normal_RED_fft = np.abs(fft(normal_RED)/n)*2
# plt.figure(2)
# plt.plot(freqs[mask], normal_IR_fft[mask], label='IR')
# plt.plot(freqs[mask], normal_RED_fft[mask], label='RED')
# plt.legend()
# plt.show()


sos = signal.butter(6, 1, 'high', fs=Fs, output='sos')

sos2 = signal.butter(6, 6, 'low', fs=Fs, output='sos')
normal_IR_filtered = signal.sosfilt(sos, normal_IR)
normal_IR_filtered = signal.sosfilt(sos2, normal_IR_filtered)
normal_RED_filtered = signal.sosfilt(sos, normal_RED)
normal_RED_filtered = signal.sosfilt(sos2, normal_RED_filtered)

mask = (-5000 < normal_IR_filtered) & (normal_IR_filtered < 5000)
all_peaks = signal.find_peaks(normal_IR_filtered[mask], 2500)
BPM = len(all_peaks[0]) / (time / 60)
plt.figure(3)
plt.plot(x[mask], normal_IR_filtered[mask], label='IR')
plt.plot(x[mask], normal_RED_filtered[mask], label='RED')
plt.legend()
plt.show()

print(BPM)


