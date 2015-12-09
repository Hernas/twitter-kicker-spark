#define SENSOR D3
#define LIGHT_SENSOR D5
#define LED D7

void setup()
{
  Serial.begin(9600);
 	pinsInit();
}

void loop()
{
  bool hit = false;
	if(digitalRead(LIGHT_SENSOR) == LOW)
	{
    hit = true;
	}


	if(digitalRead(SENSOR) == LOW)
	{
    hit = true;
	}

  if(hit) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

}
void pinsInit()
{
	pinMode(SENSOR, INPUT_PULLDOWN);
	pinMode(LIGHT_SENSOR, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);
}
