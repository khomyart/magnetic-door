#define button_state_reader 0
#define analogInput 0
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>
#include <stdbool.h>

volatile uint8_t state = 0;
uint8_t oldPINC = 0xFF;
int val;

void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // Разрешаем PCINT для указанного пина
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // Очищаем признак запроса прерывания для соответствующей группы пинов
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // Разрешаем PCINT для соответствующей группы пинов
}

ISR (PCINT1_vect) { // Обработчик запросов прерывания от пинов D8..D13
  uint8_t changedbits = PINC ^ oldPINC;
  oldPINC = PINC;

  if (changedbits & (1 << PC0)) { // Изменился D8
    state++; // Зажигаем светодиод
  }
}

void setup() {
  Serial.begin(9600);
  pciSetup(analogInput);
}

void loop() {
  Serial.println(state);
  delay(1000);


  val = analogRead(button_state_reader);
//  val = map(val,0,1023, 0, 20);
//  val = constrain(val, 0, 20);
//  Serial.println(state);
}
