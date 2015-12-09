#define SENSOR D3
#define LIGHT_SENSOR D5
#define LED D7

int goalsA = 0;
bool goalStateA = false;

int goalsB = 0;
bool goalStateB = false;

char publishHitString[3];

void setup()
{
  Serial.begin(9600);
 	pinsInit();
}

void loop()
{
  bool hit = false;
  bool publish = false;

  bool lightSensorOff = digitalRead(LIGHT_SENSOR) == LOW;
	if(lightSensorOff)
	{
    // HIT
    goalStateA = true;
    hit = true;
	}
  if(!lightSensorOff && goalStateA) {
    // So we got Sensor HIGH and now it went LOW, mean goal was registered
    ++goalsA;
    publish = true;
    goalStateA = false;
  }


  bool sensorOff = digitalRead(SENSOR) == LOW;
	if(sensorOff)
	{
    // HIT
    goalStateB = true;
    hit = true;
	}
  if(!sensorOff && goalStateB) {
    // So we got Sensor HIGH and now it went LOW, mean goal was registered
    ++goalsB;
    publish = true;
    goalStateB = false;
  }

  if(hit) {
    digitalWrite(LED, LOW);
  } else {
    digitalWrite(LED, HIGH);
  }

  if(publish) {
    sprintf(publishHitString, "%d,%d", goalsA, goalsB);
    Particle.publish("hit", publishHitString);
  }
}
void pinsInit()
{
	pinMode(SENSOR, INPUT_PULLDOWN);
	pinMode(LIGHT_SENSOR, INPUT_PULLDOWN);
  pinMode(LED, OUTPUT);
}
