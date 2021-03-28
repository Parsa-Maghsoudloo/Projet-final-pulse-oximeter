import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, fftfreq
from scipy import signal

file_normal_IR = open("SpO2_signal_normal_BPM\IR.txt", 'r')
file_normal_RED = open("SpO2_signal_normal_BPM\RED.txt")

read_size = len(file_normal_IR.read())
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

sos = signal.butter(6, 1, 'high', fs=Fs, output='sos')
sos2 = signal.butter(6, 6, 'low', fs=Fs, output='sos')
sos3 = signal.butter(6, 0.001, 'low', fs=Fs, output='sos')
normal_IR_filtered = signal.sosfilt(sos, normal_IR)
normal_IR_filtered = signal.sosfilt(sos2, normal_IR_filtered)
normal_RED_filtered = signal.sosfilt(sos, normal_RED)
normal_RED_filtered = signal.sosfilt(sos2, normal_RED_filtered)

# mask = (-5000 < normal_IR_filtered) & (normal_IR_filtered < 5000)
# all_peaks_IR = signal.find_peaks(normal_IR_filtered[mask], 2500)
# I_IR = np.mean(all_peaks_IR[1]['peak_heights'])
#
# mask = (-5000 < normal_RED_filtered) & (normal_RED_filtered < 5000)
# all_peaks_RED = signal.find_peaks(normal_RED_filtered[mask], 2500)
# I_RED = np.mean(all_peaks_RED[1]['peak_heights'])


high_peaks_IR = normal_IR_filtered[signal.argrelextrema(normal_IR_filtered, np.greater)]
low_peaks_IR = normal_IR_filtered[signal.argrelextrema(normal_IR_filtered, np.less)]

high_peaks_RED = normal_RED_filtered[signal.argrelextrema(normal_RED_filtered, np.greater)]
low_peaks_RED = normal_RED_filtered[signal.argrelextrema(normal_RED_filtered, np.less)]

mask_high_IR = (4000 < high_peaks_IR) & (high_peaks_IR < 5000)
mask_low_IR = (-2500 < low_peaks_IR) & (low_peaks_IR < -1500)

mask_high_RED = (5000 < high_peaks_RED) & (high_peaks_RED < 6000)
mask_low_RED = (-2500 < low_peaks_RED) & (low_peaks_RED < -1000)

AC_RED = np.mean(high_peaks_RED[mask_high_RED]) - np.mean(low_peaks_RED[mask_low_RED])
AC_IR = np.mean(high_peaks_IR[mask_high_IR]) - np.mean(low_peaks_IR[mask_low_IR])

normal_IR_filtered_DC = signal.sosfilt(sos3, normal_IR)
normal_RED_filtered_DC = signal.sosfilt(sos3, normal_RED)

DC_IR = np.mean(normal_IR_filtered_DC)
DC_RED = np.mean(normal_RED_filtered_DC)

R = (AC_RED/DC_RED)/(AC_IR/DC_IR)
print(R)
print(high_peaks_RED[mask_high_RED])

a = -0.18794074
b = 1.075176295

print(a*1 + b)