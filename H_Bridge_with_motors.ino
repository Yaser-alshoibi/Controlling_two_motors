int enableA = 3;
int enableB = 5;
int in1 = 2;
int in2 = 4;
int in3 = 7;
int in4 = 6;

int PotVert = A0; // Vertical  
int PotHorz = A1; // Horizontal
  
int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
  
int PositionVert = 512;
int PositionHorz = 512;  
 
 
void setup()
{ 
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
   
  // Start with motors disabled and direction forward
  
  digitalWrite(enableA, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(enableB, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
 
void loop()
{
  
  PositionVert = analogRead(PotVert); 
  PositionHorz = analogRead(PotHorz);
 
  // Determine if this is a forward or backward motion
  
  if (PositionVert < 460)
  {
    // This is Backward
  
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
 
    //Determine Motor Speeds
  
    PositionVert = PositionVert - 460; 
    PositionVert = (PositionVert * (-1)); // Make the number positive
 
    MotorSpeed1 = map(PositionVert, 0, 460, 0, 255);
    MotorSpeed2 = map(PositionVert, 0, 460, 0, 255);
 
  }
  
  else if (PositionVert > 564)
  {
    // This is Forward
  
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 
    //Determine Motor Speeds
 
    MotorSpeed1 = map(PositionVert, 564, 1023, 0, 255);
    MotorSpeed2 = map(PositionVert, 564, 1023, 0, 255); 
 
  }
  else
  {
    // Stop
 
    MotorSpeed1 = 0;
    MotorSpeed2 = 0; 
 
  }
  
  // For left and right movements
  
  if (PositionHorz < 460)
  {
    // Move Left
 
    
    PositionHorz = PositionHorz - 460;
    PositionHorz = (PositionHorz * -1);  // Make the number positive
  
    PositionHorz = map(PositionHorz, 0, 460, 0, 255);
 
    MotorSpeed1 = MotorSpeed1 - PositionHorz;
    MotorSpeed2 = MotorSpeed2 + PositionHorz;
 
    // to keep speed inside motor range 0-255 for motor speeds
 
    if (MotorSpeed1 < 0)MotorSpeed1 = 0;
    if (MotorSpeed2 > 255)MotorSpeed2 = 255;
 
  }
  else if (PositionHorz > 564)
  {
    // Move Right

 
    PositionHorz = map(PositionHorz, 564, 1023, 0, 255);
        
    MotorSpeed1 = MotorSpeed1 + PositionHorz;
    MotorSpeed2 = MotorSpeed2 - PositionHorz;
  
    if (MotorSpeed1 > 255)MotorSpeed1 = 255;
    if (MotorSpeed2 < 0)MotorSpeed2 = 0;      
 
  }
 
 
  // to avoid the sound of 'buzzing' at low speed
 
  if (MotorSpeed1 < 8)MotorSpeed1 = 0;
  if (MotorSpeed2 < 8)MotorSpeed2 = 0;
  
  analogWrite(enableA, MotorSpeed1);
  analogWrite(enableB, MotorSpeed2);
 
}
