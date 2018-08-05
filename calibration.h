// Part of the Almabraxas 3-1 project https://tronche.com/wiki/
// (c) Ch. Tronche 2018 (ch@tronche.com)
// MIT License

#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

#define CALIBRATION_OVERSAMPLING (128) // average 128 samples (which is ~180 / s)
#define CALIBRATION_SAMPLING_CYCLES (ADC_SAMPLE_480) // 480 cycles per sample. Combined with CALIBRATION_OVERSAMPLING, this gives ~180/s on the STM32F446RE

#define CALIBRATION_VOLTAGE_0 (6.5)
#define CALIBRATION_VOLTAGE_0_READING (1008)
#define CALIBRATION_VOLTAGE_1 (22.7)
#define CALIBRATION_VOLTAGE_1_READING (4045)

#define CALIBRATION_CURRENT_0 (0.046)
#define CALIBRATION_CURRENT_0_READING (3014)
#define CALIBRATION_CURRENT_1 (4.85)
#define CALIBRATION_CURRENT_1_READING (2370)

#define CALIBRATION_MAX_PWM (1000)

#endif // _CALIBRATION_H_
