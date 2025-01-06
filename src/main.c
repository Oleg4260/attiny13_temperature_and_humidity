#define F_CPU 1200000

#define DISPLAY_BRIGHTNESS 0 // 0-7

#include <stdint.h>
#include <util/delay.h>
#include "tm1637.h"
#include "dht11.h"

uint8_t temperature, humidity, timer, colonstate;

void displaytemperature(const uint8_t temp) {
	TM1637_display_digit(0,temp/10%10);
	TM1637_display_digit(1,temp%10);
	TM1637_display_segments(2,0b01100011); // degree symbol
	TM1637_display_segments(3,0b00111001); // C symbol
}

void displayhumidity(const uint8_t hum) {
	TM1637_display_digit(0,hum/10%10);
	TM1637_display_digit(1,hum%10);
	TM1637_display_segments(2,0b01100011); // so this is like percent symbol... but actually just 2 circles lol
	TM1637_display_segments(3,0b01011100);
}

int main(void) {
	
	TM1637_init(1, DISPLAY_BRIGHTNESS);
	TM1637_clear();
	
	for(uint8_t i = 0; i < TM1637_POSITION_MAX; i++) // Starting animation. Delay is needed for DHT11 sensor initialization 
	{
		TM1637_display_segments(i, 0xFF);
		_delay_ms(500);
	}
	dht_init();
	
	while (1) {
		if(timer == 0)
		{
			dht_read(&temperature, &humidity);
			displaytemperature(temperature);
		}
		if(timer == 5)
		{
			displayhumidity(humidity);
		}
		TM1637_display_colon(colonstate);
		colonstate = !colonstate;
		timer++;
		if (timer == 10) {
			timer = 0;
		}
		_delay_ms(1000);
	}
}