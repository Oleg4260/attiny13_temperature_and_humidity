#include <avr/io.h>
#include <util/delay.h>
#include "dht11.h"

#define DHT_PIN_INPUT()    (DDRB &= ~_BV(DHT_PIN))
#define DHT_PIN_OUTPUT()   (DDRB |= _BV(DHT_PIN))
#define DHT_PIN_LOW()      (PORTB &= ~_BV(DHT_PIN))
#define DHT_PIN_HIGH()     (PORTB |= _BV(DHT_PIN))
#define DHT_PIN_READ()     (PINB & _BV(DHT_PIN))

void dht_init(void)
 {
	 DHT_PIN_INPUT();
	 DHT_PIN_HIGH();
 }
 
int8_t dht_await_state(uint8_t state)
 {
	 uint8_t counter = 0;
	 while ((DHT_PIN_READ() != state) && (++counter < DHT_TIMEOUT)) { _delay_us(1); };
	 return counter;
 }
 
int8_t dht_read(uint8_t *temperature, uint8_t *humidity)
 {
	 uint8_t i, j, data[5] = {0, 0, 0, 0, 0};
	 /* send start sequence */
	 DHT_PIN_OUTPUT();
	 DHT_PIN_LOW();
	 _delay_ms(20);
	 DHT_PIN_INPUT();
	 DHT_PIN_HIGH();
	 /* read response sequence */
	 if (dht_await_state(0) < 0 || dht_await_state(1) < 0 || dht_await_state(0) < 0) {
		 return DHT_ERR_TIMEOUT;
	 }
	 /* read data */
	 for (i = 0; i < 5; ++i) {
		 for (j = 0; j < 8; ++j) {
			 data[i] <<= 1;
			 data[i] |= !!(dht_await_state(1) > 0 && dht_await_state(0) > 1);
		 }
	 }
	 *temperature = data[2];
	 *humidity = data[0];
	 return DHT_ERR_OK;
 }



