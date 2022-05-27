#define echoPin 8 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04
int temppin=0;//temperature pin port 
int lightpin=3;//light sensor pin port 
int ledpin=13;//LED pin port 
int graypin=5;//grayscale sensor pin port 
int vibrationpin=4;//vibration sensor pib port
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(temppin, INPUT);// Sets the temppin as an INPUT
  pinMode(lightpin,INPUT);// Sets the lightpin as an INPUT
  pinMode(graypin,INPUT);// Sets the graypin as an INPUT
  pinMode(vibrationpin,INPUT);// Sets the vibrationpin as an INPUT
  pinMode(ledpin,OUTPUT);// Sets the ledpin as an OUTPUT
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial3.begin(9600);// Serial3 Communication is starting with 9600 of baudrate speed
}
void loop() {
  char command = Serial3.read();// choosing the command 

  light();//if entering '3' from telephone using (bluetooth electronics) app all other loops will break and will make opportunity to work and activate light sensor 
  //if brightness is low then LED will light 
  if (command == '1'){//if entering '1' from telephone using (bluetooth electronics) app then thos loop work and activate ultrasonic sensor 
      ultrasound();
    }
    
  if (command == '2'){//if entering '2' from telephone using (bluetooth electronics) app then thos loop work and activate temperature sensor 
    temperature();
  }
  if(command=='4'){//if entering '4' from telephone using (bluetooth electronics) app then thos loop work and activate grayskale sensor
    grayscale();
  }
  
  if(command=='5'){//if entering '5' from telephone using (bluetooth electronics) app then thos loop work and activate vibration sensor
    vibration();
  }
    
 
}

void light(){//LED's 
  int light = analogRead(lightpin);//reads analog data from lightpin location
  Serial.println(light*0.0976);// 100% persentage converter 
  
  if (light<31){
    analogWrite(ledpin,HIGH);//light switch on
    delay(200);++
  }
  else if (light>=31){
    analogWrite(ledpin,LOW);//light switch off
  }
  
}
void ultrasound(){//ultrasound function 
  while (true){
      if (command == '2'){// using command parameter for breaking loop
        break;
      }
      if (command == '3'){// using command parameter for breaking loop
          break;
        }
        
      if (command == '4'){// using command parameter for breaking loop
          break;
        }
      if (command == '5'){//using command parameter for breaking loop
          break;
      }
  
      // Clears the trigPin condition
      digitalWrite(trigPin, LOW);
      delay(200);
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delay(200);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      // Displays the distance on the Serial Monitor
      if (distance<30){// if distance is shorter than 30 cm then printing ddistance and warning  
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");//printing on terminal of arduino app's terminal with "\n"
        Serial3.println("so close ");
        Serial3.print("Distance: ");
        Serial3.println(distance);// printing on tertminal of "bluetooth electronics" app's terminal (phone terminal) with "\n"
      }
      else{// if distance is shorter than 30 cm then just print
        Serial3.println(distance);
      }
      command=Serial3.read();//reading command value for breaking loop if needed
  }      
}
void temperature(){
  while(true){
      if (command == '1'){// using command parameter for breaking loop
        break;
      }
      if (command == '3'){// using command parameter for breaking loop
          break;
      }
      
      if (command == '4'){// using command parameter for breaking loop
          break;
        }
      if (command == '5'){// using command parameter for breaking loop
          break;
      }
      
      
      float temperature = analogRead(temppin);// geting analog value from port temppin
      temperature = ((temperature *3.3)/1023)*100;//finding value of temperature 
      //3.3 is the max voltag eof arduino 
      //1023 is max resolution
      //100 for sensivity unit convertion 
      Serial3.println(temperature);//printing 
      Serial.println(temperature);//printing 
      command=Serial3.read();// getting value of command for breaking loop 
      delay(2000);
    }
}
void grayscale(){
  while (true){
      
      if (command == '1'){// using command parameter for breaking loop 
          break;
        }
      if (command == '2'){// using command parameter for breaking loop
        break;
      }
      if (command == '3'){// using command parameter for breaking loop
          break;
        }
      if (command == '5'){// using command parameter for breaking loop
          break;
      }
      int valid = analogRead(graypin);//reading analog value of graypin
      Serial.println(valid);//printing the value of valid for test case 
      if (valid <1000){//if valid's value is lower than 1000 it means sensor is out of way 
        Serial3.println("OUT of your way");//warning part 
      }
      else{
        Serial3.println("SAFE");//safe 
      }
      delay(200);
      command=Serial3.read();//taking value of command to break while loop 
    }
  }
}
void vibration(){
  while (true){
      
      if (command == '1'){// using command parameter for breaking loop
          break;
        }
      if (command == '2'){// using command parameter for breaking loop
        break;
      }
      if (command == '3'){// using command parameter for breaking loop
          break;
        }
      if (command == '4'){// using command parameter for breaking loop
          break;
      }
      int vibration = digitalRead(vibrationpin);//geting digital value of vibration 
      if (vibration==0){// if there is an vibration then returns warning 
        Serial3.println("Caution!!!!!");
      }
      Serial.println(vibration);
      delay(200);
      command=Serial3.read();//taking value of command to break while loop 
    } 
  }
}
