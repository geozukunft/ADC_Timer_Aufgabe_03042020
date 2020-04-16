#include <avr/io.h>
#include "K:\DriverLibHW\DriverLibHW\ADC.h"
#include "K:\DriverLibHW\DriverLibHW\USART.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include "K:\DriverLibHW\DriverLibHW\ADC.c"
#include "K:\DriverLibHW\DriverLibHW\USART.c"

volatile uint16_t counter = 0;
volatile uint16_t measure = 0;

ISR(TIMER1_OVF_vect)
{
	counter++;
	measure = 1;
	TCNT1 = 3036;
	printf("ISR");
}

void main()
{
	USARTInit(0, 9600, 1, 0, 1, 0);
	ADCInit(ADC_VREF_TYPE_EXTERNAL_AVCC);
	TIMSK1 = 0x01;
	TCCR1A = 0;
	TCCR1B = 0x04;
	TCCR1C = 0;
	TCNT1 = 3036;
	sei();
	while (1)
	{
		printf("%i\n", counter);
	}

	uint16_t adc_values[10];
	printf("HALLO BIP BUP");
	if (measure == 1)
	{
		adc_values[counter - 1] = ADCReadChannel(0);
		measure = 0;
		printf("measure");
	}

	if (counter == 10)
	{
		for (int i = 0; i < 9; i++)
		{
			printf("Wert%i:%i,", i, adc_values[i]);
		}
		printf("Wert9:%i\n\n", adc_values[9]);

		counter = 0;

	}

}
