#define LEDT 9    //El LED esta conectado en el pin 9
#define LDR 0     //El LDR esta conectador en el pin A0

byte sensorpir = 7;
byte led = 13;

int luz = 0;       
int valor_sensor = 0;       
int valor_limite = 150;  //Este valor hara que el LED cambie de estado a una determinada luminosidad (podeis con distintos valores para ajustar la sensibilidad)

byte sensorpir1 = 3; //sensor moviemito2
byte speakerpin = 6; // led sensor 2

void setup()
{
  pinMode(sensorpir,INPUT);
  pinMode(led,OUTPUT);
  
  pinMode(sensorpir1,INPUT);
  pinMode(speakerpin, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}


void loop()
{
{
  valor_sensor = analogRead(LDR); 
  luz = (5.0 * valor_sensor * 50.0)/1024.0; //Para entender esta formula visitar: http://programarfacil.com/podcast/48-sensor-de-temperatura-en-arduino/
  //Serial.print(luz);  
  //Serial.println(" Luz");             
  delay(50);                       
  
  if (luz <= valor_limite)   //Si el valor de luz es menor o igual que el valor limite
  {
    digitalWrite (LEDT, LOW);  //El led se apaga
  }
  if (luz > valor_limite)  //Si es mayor que el valor limite
  {
    digitalWrite (LEDT, HIGH);  //El led se eniende
  }

if(digitalRead(sensorpir1) == HIGH)
  {
  Serial.println("Detectando moviemiento hace zonar alarma");
  for ( int i=0; i<1000; i++) 
  {
  digitalWrite(speakerpin,HIGH);
  delayMicroseconds(800);
  digitalWrite(speakerpin,LOW);
  delayMicroseconds(500); 
  }
 delay(1000);

  
  if(digitalRead(sensorpir) == HIGH)
  {
    Serial.println("Detectado movimiento por el sensor pir");
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,LOW);
  }

{
 // put your main code here, to run repeatedly:
    int val = analogRead(A2);
    Serial.print("Humedad de Suelo");
    Serial.println(val);
    Serial.println("%");
    delay(500);
    if(digitalRead(2)==HIGH)
    {
    Serial.println("SE ENCENDIO RIEGO AUTOMATICO ");
 
}
}
}
}  
}
