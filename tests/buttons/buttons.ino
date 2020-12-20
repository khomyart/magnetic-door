#include <GyverTimers.h>

#define analogInput 0

#define BUTTON_1 735
#define BUTTON_2 205

volatile int value, counter;
volatile byte analogValuesWindow = 5;
volatile unsigned long timer;

void setup()
{
  Serial.begin(9600);
  Timer2.setFrequency(100);
  Timer2.enableISR(CHANNEL_A);
}

ISR(TIMER2_A)
{
  value = analogRead(analogInput);

  if ((value >= BUTTON_1 - analogValuesWindow) && 
      (value <= BUTTON_1 + analogValuesWindow))
  {
    counter++;
  }

  if ((value >= BUTTON_2 - analogValuesWindow) && 
      (value <= BUTTON_2 + analogValuesWindow))
  {
    counter--;
  }
}

void loop()
{
  Serial.println(counter);
  delay(5000);
}
