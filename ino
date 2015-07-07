


uint8_t buzzPin = 7;
uint8_t reedPin = 9;

boolean alert = false;

typedef struct event
{
  uint16_t alertTimeout = 0;
  uint16_t scanTimeout = 0;
  uint32_t lastTimeEvent = 0;
  uint32_t lastTimeScanned = 0;
  char prevState = 0;
  uint16_t cnt = 0;
};

event reed;

void setup()
{
//  pinMode(buzzPin, OUTPUT);  // silent mode
  digitalWrite(buzzPin, LOW);
  
  pinMode(reedPin, INPUT);
  digitalWrite(reedPin, HIGH);
  reed.alertTimeout = 10000;
  reed.scanTimeout = 10;
  reed.lastTimeEvent = 0;
  reed.lastTimeScanned = 0;
  reed.prevState = 1;
}

void loop()
{
  checkReed(reed);
}



void checkReed(struct event &r)
{
  if(millis() - r.lastTimeScanned > r.scanTimeout)
  {
    r.lastTimeScanned = millis();
    if(r.prevState == 1 && digitalRead(reedPin) == 0)
    {
      r.cnt++;
      if (millis() - r.lastTimeEvent < r.alertTimeout) beep();
      r.lastTimeEvent = millis();
    }
    r.prevState = digitalRead(reedPin);
  }
}



void beep()
{
  digitalWrite(buzzPin, HIGH);
  delay(50);
  digitalWrite(buzzPin, LOW);
}
