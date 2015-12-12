// --- PINOS DE CONTROLO ---
int E1 = 5;  // M1 Speed Control
int E2 = 6;  // M2 Speed Control
int M1 = 4;  // M1 Direction Control
int M2 = 7;  // M1 Direction Control

int IRD = 2; // INFRAVERMELHO DIREITO
int IRE = 1; // INFRAVERMELHO ESQUERDO

// --- Constantes de calibracao ---

int velE = 50;
int velD = 50;
int velMax = 80;

int ME = 150;
int MD = 150;

int max_sensor_D = 739 - 50; // max lido - margem de 50
int max_sensor_E = 721 - 50; // max lido - margem de 50


// --- setup ---
void setup(void)
{ 
  Serial.begin(9600);
  
  
  int i;  
  for(i=4;i<=7;i++) { pinMode(i, OUTPUT); }

  pinMode(IRD, INPUT);
  pinMode(IRE, INPUT);
}

void advance(char a,char b)
{
  analogWrite (E1,a); 
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}

void turnaround()
{
  
}

double getDistance(uint16_t value)
{
  if (value < 16) value = 16;
  return 2076.0/(value - 11.0); // 2076.0 / ( 1024 - 11 ) tem de dar no min 2
                                // 2076.0 / ( 16 - 11 )   tem de dar no max 415,2
}


// -----------------------------------------------------------------------------------------
void loop ()
{  
    int sensorD = analogRead(IRD);
    int sensorE = analogRead(IRE);
    
    Serial.print(sensorE);
    Serial.print(" | ");
    Serial.print(sensorD);
    Serial.print(" | ");

//  double proxD = getDistance(sensorD);
//  double proxE = getDistance(sensorE);
//    Serial.print(proxE);
//    Serial.print(" | ");
//    Serial.print(proxD);
//    Serial.print(" | ");

  int ME;
  int MD;

if (sensorE > max_sensor_E) MD = 0; else MD = velMax;
if (sensorD > max_sensor_D) ME = 0; else ME = velMax;


//  if (proxE < 5 || proxD < 5)
//  {
//    int ME = min(velMax, proxD);
//    int MD = min(velMax, proxE);
//  }
//  else
//  {
//    ME = 150;
//    MD = 150;
//  }
  
  // Serve apenas para ler os maximos dos sensores
//  if ( sensorD > max_sensor_D ) max_sensor_D = sensorD;
//  if ( sensorE > max_sensor_E ) max_sensor_E = sensorE;

  Serial.print(ME);
  Serial.print(" | ");
  Serial.print(MD);
  Serial.print(" | ");
  Serial.print(max_sensor_E);
  Serial.print(" | ");
  Serial.print(max_sensor_D);
  Serial.println();
  

  advance(ME,MD);
}

