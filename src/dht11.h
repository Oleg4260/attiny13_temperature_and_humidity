#ifndef	_DHT11_H_
#define	_DHT11_H_

#define DHT_PIN			PB1

#define DHT_ERR_OK		(0)
#define DHT_ERR_TIMEOUT	(-1)

#define DHT_TIMEOUT		(10)

void dht_init(void);
int8_t dht_await_state(uint8_t state);
int8_t dht_read(uint8_t *temperature, uint8_t *humidity);

#endif