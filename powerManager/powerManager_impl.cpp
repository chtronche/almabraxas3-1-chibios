#include "ch.h"
#include "hal.h"

#include "calibration.h"
#include "LinearMapper.h"
#include "powerManager.h"

static thread_t *sampler = NULL;

static void _conversionCallBack(ADCDriver *adcg, adcsample_t *t, size_t n) {
  (void)adcg;
  (void)n;
  chThdResumeI(&sampler, (msg_t)t);
}

static LinearMapper voltageMapper(CALIBRATION_VOLTAGE_0_READING, CALIBRATION_VOLTAGE_0,
				  CALIBRATION_VOLTAGE_1_READING, CALIBRATION_VOLTAGE_1);

static LinearMapper currentMapper(CALIBRATION_CURRENT_0_READING, CALIBRATION_CURRENT_0,
				  CALIBRATION_CURRENT_1_READING, CALIBRATION_CURRENT_1);

volatile uint16_t currentReading;

static THD_WORKING_AREA(waSampler, 128);
static THD_FUNCTION(Sampler, arg) {
  (void)arg;
  for(;;) {
    adcsample_t *p = (adcsample_t *)chThdSuspendS(&sampler);
    uint32_t v = 0;
    uint32_t c = 0;
    for(int n = CALIBRATION_OVERSAMPLING; n; n--) {
      v += *p++;
      c += *p++;
    }
    currentReading = c / CALIBRATION_OVERSAMPLING;
    powerManager_loop(voltageMapper.convert(v / CALIBRATION_OVERSAMPLING) * 10,
		      currentMapper.convert(currentReading) * 10);
  }
}

static ADCConfig _adcConfig = { };

static ADCConversionGroup _adccg = {
  true, // circular
  2, // 2 channels
  _conversionCallBack,
  NULL, // error callback
  0, // CR1
  ADC_CR2_SWSTART, // Start conversion on regular channels ?
  ADC_SMPR1_SMP_AN10(CALIBRATION_SAMPLING_CYCLES)|ADC_SMPR1_SMP_AN11(CALIBRATION_SAMPLING_CYCLES),
  0, // SMPR2
  0, // SQR1
  0, // SQR2
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN11) // SQR3 = 1st = ADC123_IN10 (PC0), 2nd = ADC123_IN11 (PC1)
};

#define NUM_CHANNEL (2)

static adcsample_t data[NUM_CHANNEL * 2 * CALIBRATION_OVERSAMPLING]; // 2 because we switch between half-buffers

void powerManager_impl_setup() {
  chThdCreateStatic(waSampler, sizeof(waSampler), NORMALPRIO, Sampler, NULL);

  palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_ANALOG);
  palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_ANALOG);

  adcStart(&ADCD1, &_adcConfig);
  adcStartConversion(&ADCD1, &_adccg, data, CALIBRATION_OVERSAMPLING * 2);
}
