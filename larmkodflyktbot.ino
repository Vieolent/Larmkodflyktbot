/*
Namn: Miranda Bache
Projekt: Larmkodflyktbot
Senast uppdaterad: 2025-05-08
*/


//Bibliotek för servo
#include <Servo.h>
//Bibliotek för keypad
#include <Keypad.h>

//konstanter definiteras, första två är pins och andra två definerar storleken på min keypad
const int hoger = 8;
const int vanster = 9;
const byte ROWS = 4;
const byte COLS = 3;

//variabler defineras
int index = 0; 
int code[] = { 7, 2, 5 }; //korrekt kod
int inputCode[3] = {};
int code_Attempts = 0;
float duration, distance1, distance2, average1, average2; //variabler för sensordata
float array1[10] = {};
float array2[10] = {};

//keypadens layout
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

//pins för keypad
byte rowPins[ROWS] = { 10, 0, 5, 11 };
byte colPins[COLS] = { 12, 13, 4 };

//keypad definerars
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo myservo;


void setup() {
  //servo och seriellmonitor sätts igång i rätt läge
  myservo.attach(3);
  Serial.begin(9600);
  myservo.write(0);

  //fler pins defineras
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(7, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(2, OUTPUT);
  pinMode(hoger, OUTPUT);
  pinMode(vanster, OUTPUT);

}

void loop() {
  //skriver ner vad för key har tryckts på
  char customKey = customKeypad.getKey();

//lägger till tangenten som tryckts på i en liten array
  if (customKey) {
    inputCode[index] = customKey - '0';
    index++;
  }

//räknar ut ifall man har skrivit in rätt kod
  if (index == 3) {
    index = 0;
    if (code[0] == inputCode[0] && code[1] == inputCode[1] && code[2] == inputCode[2]) {
      Serial.println("Access granted");
      myservo.write(90);
      code_Attempts = 0;
    } else {
      myservo.write(0);
      code_Attempts++;
      Serial.println(code_Attempts);
    }
  }

//om man ta för många försök på sig att gissa koden börjar den köra
  while (code_Attempts > 3) {
    
    //sensordata räknas ut
    distance1 = getDistance1();
    distance2 = getDistance2();
    average1 = average(distance1, array1);
    average2 = average(distance2, array2);

    //sensordata skrivs upp i ett format som fungerar med seriell plottern
    Serial.print(average1);
    Serial.print(" ");
    Serial.print(average2);
    Serial.println(" ");

    //utgångsläget defineras som att bilen kör framåt
    digitalWrite(hoger, HIGH);
    digitalWrite(vanster, HIGH);

    //om bilen är allt för nära något står den still
    if (average1 < 15 && average2 < 15){
      digitalWrite(vanster, LOW); 
      digitalWrite(hoger, LOW);
    }

    // om bilen är relativt nära något kör den åt det håll där det är mest troligt att den kommer kunna undvika hindret
    else if (average1 < 50 && average2 < 50 && average1 < average2) {
      digitalWrite(vanster, LOW); 
      digitalWrite(hoger, HIGH);
    }
    else if (average1 < 50 && average2 < 50 && average1 > average2) {
      digitalWrite(vanster, HIGH); 
      digitalWrite(hoger, LOW);
    }

    //om bara en av sensorerna tycker den kommer krasha svänger den 
    else if (average2 < 50) {
      digitalWrite(vanster, LOW);
    }
    else if (average1 < 50) {
      digitalWrite(hoger, LOW);
    }

  }
}
/*

*/
