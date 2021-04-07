# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\arnau\Documents\Projet-final-pulse-oximeter\Communication BMI160\MotionSensor.cydsn\MotionSensor.cyprj
# Date: Wed, 31 Mar 2021 19:35:44 GMT
#set_units -time ns
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyClk_LF} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {I2Cm_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 3 7} [list [get_pins {ClockBlock/ff_div_3}]]
create_generated_clock -name {DEBUG_UART_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyPeriClk_App} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\arnau\Documents\Projet-final-pulse-oximeter\Communication BMI160\MotionSensor.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\arnau\Documents\Projet-final-pulse-oximeter\Communication BMI160\MotionSensor.cydsn\MotionSensor.cyprj
# Date: Wed, 31 Mar 2021 19:35:16 GMT
