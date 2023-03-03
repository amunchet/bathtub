// Bathtub code

#include <EEPROM.h>

//// Variables
const int button1 = 8;
const int button2 = 9;

const int led1 = 3;
const int led2 = 4;

int button1_state = 0;
int button2_state = 0;

int button1_latch = 0; //This will be 1 while the button is pressed

int button1_last_state = LOW;
int button2_last_state = LOW;

unsigned long button1_last_state_time = 0;
unsigned long button1_bounce_delay = 16000;

unsigned long button2_last_state_time = 0;
unsigned long button2_bounce_delay = 16000;

int solonoid1 = 12;
int solonoid2 = 13;

int enabled = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  pinMode(solonoid1, OUTPUT);
  pinMode(solonoid2, OUTPUT);

  EEPROM.get(10, button1_last_state);
  EEPROM.get(20, button2_last_state);

  Serial.print("Restarting...");

  
}

void loop() {
  // put your main code here, to run repeatedly:


  button1_state = digitalRead(button1);
  button2_state = digitalRead(button2);

  /*
  
  Serial.print(button1_last_state_time);
  Serial.print(" ");
  Serial.print(button1_state);

  Serial.print("; ");
  Serial.print(button2_state);
  Serial.print(" " );
  Serial.print(button2_last_state_time);
  
  Serial.println();
  */
  
  
  if(button1_state != button1_last_state){
    
    if(button1_last_state_time > button1_bounce_delay){
      
      button1_last_state = button1_state;
      button1_last_state_time = 0;
    }else{
      
      button1_state = button1_last_state;
      button1_last_state_time += 1;
    }
  }else{
    button1_last_state_time = 0;
  }

   if(button2_state != button2_last_state){
    
    if(button2_last_state_time > button2_bounce_delay){
      
      button2_last_state = button2_state;
      button2_last_state_time = 0;
    }else{
      
      button2_state = button2_last_state;
      button2_last_state_time += 1;
    }
  }else{
    button2_last_state_time = 0;
  }
  

  /*
  if(button1_state == HIGH){
    if(button1_latch == 0){
      if(enabled == 0){
        enabled = 1;
        
      }else{
        enabled = 0;
      }
      button1_latch = 1;
    }
  }else{
    button1_latch = 0;
  }
  */

  
  if(button1_state  == HIGH){
    digitalWrite(led1, HIGH);
    digitalWrite(solonoid1, HIGH);
    
  }else{
    digitalWrite(led1, LOW);
    digitalWrite(solonoid1, LOW);
  }

  if(button2_state == HIGH){
      digitalWrite(led2, HIGH);
      digitalWrite(solonoid2, HIGH);
  }else{
     digitalWrite(led2, LOW);
     digitalWrite(solonoid2, LOW);
  }

  EEPROM.put(10, button1_state);
  EEPROM.put(20, button2_state);
  

}
