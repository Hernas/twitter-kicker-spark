#define SENSOR D3
#define SENSOR_2 A3
#define LED D7
#define LED_2 D1

#define GOAL_A_ADDRESS 10
#define GOAL_B_ADDRESS 11

int goalsA = 0;
bool goalStateA = false;

int goalsB = 0;
bool goalStateB = false;

char publishHitString[3];
int resetAll(String command);


void setup()
{
  Serial.begin(9600);
 	pinsInit();

  Particle.function("resetAll", resetAll);

  /*goalsA = EEPROM.read(GOAL_A_ADDRESS);
  goalsB = EEPROM.read(GOAL_B_ADDRESS);*/
}

int resetAll(String command)
{
  goalsA = 0;
  /*EEPROM.write(GOAL_A_ADDRESS, goalsA);*/

  goalsB = 0;
  /*EEPROM.write(GOAL_B_ADDRESS, goalsB);*/
}

void loop()
{
  bool hit = false;
  bool publish = false;

  bool sensor2Off = analogRead(SENSOR_2) > 1000;
	if(sensor2Off)
	{
    // HIT
    goalStateA = true;
    hit = true;
    digitalWrite(LED_2, LOW);
	} else {
      digitalWrite(LED_2, HIGH);
  }
  if(!sensor2Off && goalStateA) {
    // So we got Sensor HIGH and now it went LOW, mean goal was registered
    ++goalsA;
    /*EEPROM.write(GOAL_A_ADDRESS, goalsA);*/
    publish = true;
    goalStateA = false;
  }


  bool sensorOff = digitalRead(SENSOR) == LOW;
	if(sensorOff)
	{
    // HIT
    goalStateB = true;
    hit = true;
    digitalWrite(LED, LOW);
	} else {
    digitalWrite(LED, HIGH);
  }
  if(!sensorOff && goalStateB) {
    // So we got Sensor HIGH and now it went LOW, mean goal was registered
    ++goalsB;
    /*EEPROM.write(GOAL_B_ADDRESS, goalsB);*/
    publish = true;
    goalStateB = false;
  }


  if(publish) {
    sprintf(publishHitString, "%d,%d", goalsA, goalsB);
    Particle.publish("hit", publishHitString);
  }
  delay(100);
}
void pinsInit()
{
	pinMode(SENSOR, INPUT_PULLDOWN);
	pinMode(SENSOR_2, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED_2, OUTPUT);
}
