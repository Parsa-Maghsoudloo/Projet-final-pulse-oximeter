import matplotlib.pyplot as plt
import numpy as np
from numpy.fft import fft, fftfreq
from scipy import signal
from test import a, b, c

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
        print('Erreur : ', i)

sos = signal.butter(6, 1, 'high', fs=Fs, output='sos')
sos2 = signal.butter(6, 6, 'low', fs=Fs, output='sos')
sos3 = signal.butter(6, 0.001, 'low', fs=Fs, output='sos')
high_IR_filtered = signal.sosfilt(sos, high_IR)
high_IR_filtered = signal.sosfilt(sos2, high_IR_filtered)
high_RED_filtered = signal.sosfilt(sos, high_RED)
high_RED_filtered = signal.sosfilt(sos2, high_RED_filtered)

# mask = (-5000 < high_IR_filtered) & (high_IR_filtered < 5000)
# all_peaks_IR = signal.find_peaks(high_IR_filtered[mask], 2500)
# I_IR = np.mean(all_peaks_IR[1]['peak_heights'])
#
# mask = (-5000 < high_RED_filtered) & (high_RED_filtered < 5000)
# all_peaks_RED = signal.find_peaks(high_RED_filtered[mask], 2500)
# I_RED = np.mean(all_peaks_RED[1]['peak_heights'])


high_peaks_IR = high_IR_filtered[signal.argrelextrema(high_IR_filtered, np.greater)]
low_peaks_IR = high_IR_filtered[signal.argrelextrema(high_IR_filtered, np.less)]

high_peaks_RED = high_RED_filtered[signal.argrelextrema(high_RED_filtered, np.greater)]
low_peaks_RED = high_RED_filtered[signal.argrelextrema(high_RED_filtered, np.less)]

mask_high_IR = (4000 < high_peaks_IR) & (high_peaks_IR < 5000)
mask_low_IR = (-2500 < low_peaks_IR) & (low_peaks_IR < -1500)

mask_high_RED = (5000 < high_peaks_RED) & (high_peaks_RED < 6000)
mask_low_RED = (-2500 < low_peaks_RED) & (low_peaks_RED < -1000)

mask_test_RED = 0 < high_peaks_RED
mask_test_RED_low = low_peaks_RED < 0
mask_test_IR = 0 < high_peaks_IR
mask_test_IR_low = low_peaks_IR < 0
# AC_RED = np.mean(high_peaks_RED[mask_high_RED]) - np.mean(low_peaks_RED[mask_low_RED])
# AC_IR = np.mean(high_peaks_IR[mask_high_IR]) - np.mean(low_peaks_IR[mask_low_IR])

AC_RED = np.median(high_peaks_RED[mask_test_RED]) - np.median(low_peaks_RED[mask_test_RED_low])
AC_IR = np.median(high_peaks_IR[mask_test_IR]) - np.median(low_peaks_IR[mask_test_IR_low])

high_IR_filtered_DC = signal.sosfilt(sos3, high_IR)
high_RED_filtered_DC = signal.sosfilt(sos3, high_RED)

DC_IR = np.mean(high_IR_filtered_DC)
DC_RED = np.mean(high_RED_filtered_DC)

R = (AC_RED / DC_RED) / (AC_IR / DC_IR)
print('R : ', R)

print('%SpO2 : ', a * R ** 2 + b * R + c)


