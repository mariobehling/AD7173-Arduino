/*
=================================================
example to configure and get data from AD7173 ADC
=================================================
*/
#include <SPI.h>
#include <AD7173.h>

void setup() {
	/* initiate serial communication */
	Serial.begin(230400);

	/* initialize SPI connection to the ADC */
	AD7173.init();

	/* sync the ADC */
	AD7173.sync();

	/* reset the ADC registers to default */
	AD7173.reset();

	/* resync the ADC */
	AD7173.sync();

	/* check if the ID register of the ADC is valid */
	if (AD7173.is_valid_id()) Serial.println("AD7173 ID is valid");
	else Serial.println("AD7173 ID is invalid");

	/* set the ADC data and clock mode */
	/* CONTINUOUS_CONVERSION_MODE, SINGLE_CONVERSION_MODE */
	/* INTERNAL_CLOCK, INTERNAL_CLOCK_OUTPUT, EXTERNAL_CLOCK_INPUT, EXTERNAL_CRYSTAL */
	AD7173.set_adc_mode_config(CONTINUOUS_CONVERSION_MODE, INTERNAL_CLOCK);

	/* enable the ADC CONTINUOUS_READ_MODE */
	/* true/false to enamble/disable CONTINUOUS_READ_MODE */
	AD7173.set_interface_mode_config(true);

	/* set ADC input channel configuration */
	/* enable channel 0 and channel 1 and connect each to 2 analog inputs for bipolar input */
	/* CH0 - CH15 */
	/* true/false to enable/disable channel */
	/* SETUP0 - SETUP7 */
	/* AIN0 - AIN16 */
	AD7173.set_channel_config(CH0, true, SETUP0, AIN0, AIN1);
	AD7173.set_channel_config(CH1, true, SETUP0, AIN2, AIN3);

	/* set the ADC SETUP0 coding mode to BIPLOAR output */
	/* SETUP0 - SETUP7 */
	/* BIPOLAR, UNIPOLAR */
	AD7173.set_setup_config(SETUP0, BIPOLAR);

	/* set the ADC FILTER0 ac_rejection to false and samplingrate to 1007 Hz */
	/* FILTER0 - FILTER7 */
	/* true/false to enable/disable 50/60 Hz AC rejection filters */
	/* SPS_1, SPS_2, SPS_5, SPS_10, SPS_16, SPS_20, SPS_49, SPS_59, SPS_100, SPS_200 */
	/* SPS_381, SPS_503, SPS_1007, SPS_2597, SPS_5208, SPS_10417, SPS_15625, SPS_31250 */
	AD7173.set_filter_config(FILTER0, false, SPS_1007);

	/* wait for ADC */
	delay(10);
}

/* ADC conversion data */
byte data[3];

void loop() {
	/* when ADC conversion is finished */
	if (DATA_READY) {
		/* get ADC conversion result */
		AD7173.get_data(data);

		/* send result via serial */
		Serial.print(data[0], HEX);
		Serial.print(data[1], HEX);
		Serial.println(data[2], HEX);
		delay(100);
	}
}