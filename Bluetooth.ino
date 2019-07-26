char junk;
String inputString="";

void setup()                    // run once, when the sketch starts
{
 Serial.begin(9600);            // set the baud rate to 9600, same should be of your Serial Monitor
 //pinMode(8, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(10, OUTPUT);
}

void loop()
{
  if(Serial.available()){
  while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      // clear the serial buffer
    
    
    if(inputString == "A"){         //in case of 'A' turn the Fan On
      digitalWrite(11,LOW);  
    }
    
    else if(inputString == "B"){   //incase of 'B' turn the Fan Off
      digitalWrite(11,HIGH);
    }


if(inputString == "C"){         //in case of 'C' turn the Bulb On
      digitalWrite(10,LOW);  
    }
    
    else if(inputString == "D"){   //incase of 'b' turn the Bulb Off
      digitalWrite(10,HIGH);
    }


    inputString = "";
  }
}

