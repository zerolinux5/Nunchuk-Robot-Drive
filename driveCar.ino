#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
int needSetUpA = 0;
int needSetUpB = 0;
int needSetUpC = 0;
int needSetUpD = 0;

void setup()
{
    //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  nunchuk.init();
}

void loop()
{
  nunchuk.update();

  while(nunchuk.analogY > 135){
    if(needSetUpA == 0){
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A
        digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpA = 1;
        needSetUpB = 0;
        needSetUpC = 0;
        needSetUpD = 0;
        nunchuk.update();
    } else {
        int maxSpeed = (nunchuk.analogY - 130) * 3;
        if (maxSpeed > 255){
          maxSpeed = 255;
        }
        analogWrite(3, maxSpeed); 
        analogWrite(11, maxSpeed);    
        nunchuk.update();
    }
  }
  
  while( nunchuk.analogY < 120){
    if(needSetUpB == 0){
        digitalWrite(12, LOW); //Establishes backward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 1;
        needSetUpA = 0;
        needSetUpC = 0;
        needSetUpD = 0;
        nunchuk.update();
    } else {
      int maxSpeed = (120 - nunchuk.analogY) * 3;
      if (maxSpeed > 255){
        maxSpeed = 255;  
      }
      analogWrite(3, maxSpeed);  
      analogWrite(11, maxSpeed);    
      nunchuk.update();
    }
  }
  
  while (nunchuk.analogX > 130){
      if(needSetUpC == 0){
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 0;
        needSetUpA = 0;
        needSetUpC = 1;
        needSetUpD = 0;
        nunchuk.update();
      } else {
        int maxSpeed = (nunchuk.analogX - 130) * 3;
        if (maxSpeed > 255){
          maxSpeed = 255;
        }
        analogWrite(3, maxSpeed); 
        analogWrite(11, maxSpeed);   
        nunchuk.update();
    }
  }
  
  while( nunchuk.analogX < 120){
    if(needSetUpD == 0){
        digitalWrite(12, LOW); //Establishes backward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 0;
        needSetUpA = 0;
        needSetUpC = 0;
        needSetUpD = 1;
        nunchuk.update();
    } else {
      int maxSpeed = (120 - nunchuk.analogX) * 3;
      if (maxSpeed > 255){
        maxSpeed = 255;  
      }
      analogWrite(3, maxSpeed); 
      analogWrite(11, maxSpeed);  
      nunchuk.update();
    }
  }
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B
  needSetUpA = 0;
  needSetUpB = 0;
  needSetUpC = 0;
  needSetUpD = 0;
}
