// Pins dos sensores de distancia
#define pin1 A1
#define pin2 A2

// Controlo dos motores
int E1 = 5;     //M1 Speed Control
int E2 = 6;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

#define minimumDistance 7.0
#define STD_SPEED 50

int rightSpeed;
int leftSpeed;
int turnTime = 0;

void setup () {
        int i;
  
        Serial.begin (9600);

        // Pin dos sensores
        pinMode(pin1, INPUT);
        pinMode(pin2, INPUT);
        delay(300);

        // Pins dos motores
        for(i=4;i<=7;i++)
          pinMode(i, OUTPUT);
          
        advance(STD_SPEED,STD_SPEED);
        leftSpeed = STD_SPEED;
        rightSpeed = STD_SPEED;
}


double get_IR (uint16_t value) {
        //return distance (cm)
        if (value < 16)  value = 16;
        return 2076.0 / (value - 11.0);
}

/**
 * Lê a distancia de um pin enviado como parametro e envia a distancia para a 
 * consola
 * 
 * @return a distancia em cm
 */
double infraRedReadDistance(int pin) {
        uint16_t value = analogRead (pin);
        double distance = get_IR (value);
        
        Serial.print("Pin ");
        Serial.print(pin);
        Serial.print(" : ");
        Serial.print (distance);
        Serial.println (" cm"); 
        //delay(300);  
        
        return distance;
}      

/**
 * Altera o andamento dos motores
 */
void advance(char a,char b){
  leftSpeed = a;
  rightSpeed = b;
  analogWrite (E1,a); 
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);

} 

/**
 * Dá a volta
 */
void turnAround() {
  leftSpeed = rightSpeed = STD_SPEED;
  analogWrite (E2,leftSpeed); 
  digitalWrite(M2,HIGH); 
  analogWrite (E1,rightSpeed);    
  digitalWrite(M1,LOW);
  delay(turnTime);
}

void beep() {
  // piezo speaker connected to pin 8 and ground
  #define wait 1
  #define time 10
  int freq = 0;

  for (freq = 150; freq < 1800; freq += 1) {
    tone(8, freq, time);     // Beep pin, freq, time
//    delay(wait);
  }
  for (freq = 1800; freq > 150; freq -= 1) {
    tone(8, freq, time);     // Beep pin, freq, time
 //   delay(wait);
  }
}

/**
 * Anda para trás
 */
void backWards() {
  leftSpeed = rightSpeed = STD_SPEED;
  analogWrite (E2,leftSpeed); 
  digitalWrite(M2,LOW); 
  analogWrite (E1,rightSpeed);    
  digitalWrite(M1,LOW);
  delay(turnTime);
}

/**
 * Vira à esquerda parando o motor da esquerda
 */
void turnLeft() {
  leftSpeed = 0;
  analogWrite (E2,leftSpeed); 
  digitalWrite(M2,HIGH);   
}

/**
 * Vira à direita parando o motor da direita
 */
void turnRight() {
  rightSpeed = 0;
  analogWrite (E1,rightSpeed);    
  digitalWrite(M1,HIGH);
}

/**
 * Baseado nas distancias a que se encontra do lado direito ou esuqredo, ajusta a velocidade e(ou) direcçao do
 * motor correspondente
 */
void adjustMotors(double right, double left) {
  
   if ( leftSpeed == 0 && rightSpeed == 0 ) {
     backWards();
     return;
   }

   // Medir distancia
   else if ( right < minimumDistance &&  left < minimumDistance )
     turnAround();
   else if  ( right < minimumDistance )
     turnLeft();
   else if  ( left < minimumDistance )
     turnRight();
   else
    advance(STD_SPEED,STD_SPEED);
}

void loop () {
  //beep();
  leftSpeed = rightSpeed = STD_SPEED;
  adjustMotors(    
    infraRedReadDistance (pin1),
    infraRedReadDistance (pin2)
  );

}

