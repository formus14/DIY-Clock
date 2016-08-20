// Connect your buzz signal pin to digital pin 8
int flag=0; 
void setup()
{
  pinMode(D6,OUTPUT);
}

void loop()
{
  int i;
  if ( flag== 0){
    for(i=0;i<255;i++) // output sound of one frequency
    {
      digitalWrite(D6,HIGH);// Buzz sound
      delay(1);//delay 1ms
      digitalWrite(D6,LOW);// silent
      delay(1);//delay 1ms
    }
    flag=1;
    digitalWrite(D6,LOW);// silent
  }
}