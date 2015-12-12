#define sensorE A1
#define sensorD A2
int E1 = 5; //M1 Speed Control
int E2 = 6; //M2 Speed Control
int M1 = 4; //M1 Direction Control
int M2 = 7; //M1 Direction Control
int ME;
int MD;
double safeDist = 5;
char turnSpeed = 25;
char straitSpeed = 50;

void setup () {
  int i;
  for (i = 4; i <= 9; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600); //Set Baud Rate
  Serial.println("Run keyboard control");
}

double get_IR (uint16_t value) {
  //return distance (cm)
  if (value < 16) value = 16;
  return 2076.0 / (value - 11.0);
}

void advance(char a) {
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, a);
  digitalWrite(M2, HIGH);
}

void back(char a) {
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, a);
  digitalWrite(M2, LOW);
}

void turnLeft(char a) {
  analogWrite (E1, a);
  digitalWrite(M1, LOW);
  analogWrite (E2, a);
  digitalWrite(M2, HIGH);
}

void turnRight(char a) {
  analogWrite (E1, a);
  digitalWrite(M1, HIGH);
  analogWrite (E2, a);
  digitalWrite(M2, LOW);
}

void loop () {
  uint16_t valueE = analogRead (sensorE);
  uint16_t valueD = analogRead (sensorD);
  double distanceE = get_IR (valueE);
  double distanceD = get_IR (valueD);

   if ( (distanceE > distanceD) && (distanceD < safeDist)) {
    Serial.println("Turning left");
    turnLeft(turnSpeed);
  } else if ( (distanceE < distanceD) && (distanceE < safeDist)) {
    Serial.println("Turning right");
    turnRight(turnSpeed);
  } else if ( (distanceE == distanceD) && (distanceE > safeDist)) {
    Serial.println("equal distances and advancing");
    advance(straitSpeed);
  } else if ( (distanceE == distanceD) && (distanceE < safeDist)) {
    Serial.println("equal distances and turning");
    turnLeft(turnSpeed);
  } else {
    Serial.println("cai no else :(");
    advance(straitSpeed);
  }


 
}
