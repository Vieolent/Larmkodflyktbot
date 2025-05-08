#include <Servo.h>
#include <Keypad.h>

const int hoger = 8;
const int vanster = 9;
const byte ROWS = 4;
const byte COLS = 3;

int index = 0;
int code[] = { 7, 2, 5 };
int inputCode[3] = {};
int code_Attempts = 0;
float duration, distance1, distance2, average1, average2;
float array1[10] = {};
float array2[10] = {};
float temp = 0;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[ROWS] = { 10, 0, 5, 11 };
byte colPins[COLS] = { 12, 13, 4 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo myservo;


void setup() {
  pinMode(6, OUTPUT);
  myservo.attach(3);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(7, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(2, OUTPUT);
  pinMode(hoger, OUTPUT);
  pinMode(vanster, OUTPUT);
  myservo.write(0);
}

void loop() {

  char customKey = customKeypad.getKey();

  if (customKey) {
    inputCode[index] = customKey - '0';
    index++;
  }

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


  while (code_Attempts > 3) {
    

    distance1 = getDistance1();
    distance2 = getDistance2();
    average1 = average(distance1, array1);
    average2 = average(distance2, array2);

    //Serial.print(400);
    //Serial.print(" ");
    Serial.print(average1);
    Serial.print(" ");
    Serial.print(average2);
    Serial.println(" ");

    digitalWrite(hoger, HIGH);
    digitalWrite(vanster, HIGH);

    if (average1 < 15 && average2 < 15){
      digitalWrite(vanster, LOW); 
      digitalWrite(hoger, LOW);
    }

    else if (average1 < 50 && average2 < 50 && average1 < average2) {
      digitalWrite(vanster, LOW); 
      digitalWrite(hoger, HIGH);
    }
    else if (average1 < 50 && average2 < 50 && average1 > average2) {
      digitalWrite(vanster, HIGH); 
      digitalWrite(hoger, LOW);
    }

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
