//Dokument för funktioner som används i larmkodflyktbot.ino

//funktion som jämnar ut sensordata genom att ta medelvärdet av de senaste 10 värdena
 //Input: float med rå sensorvärde och array där den kan skriva ner och ta medelvärdet på sensorvärdena
 //Output: Flyttal som är utjämnade
float average(float value, float array[]){
  array[9] = value;
   float sum = 0;
  for(int i = 0; i < 10; i++){
    array[i] = array[i+1];
    sum = sum + array[i];
  }
  return sum/10;
}

//funktion som tar in sensordata från högra sensoren
//Input: inga
//Output: rå sensordata
float getDistance2(){
	digitalWrite(2, LOW);  
	delayMicroseconds(2);  
	digitalWrite(2, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(2, LOW);
  duration = pulseIn(A2, HIGH);  
  distance2 = (duration*.0343)/2; 
  if (distance2 > 1000){
    distance2 = getDistance2();
  }
  
  return distance2;
}

//funktion som tar in sensordata från vänstra sensoren
//Input: inga
//Output: rå sensordata
float getDistance1(){
	digitalWrite(7, LOW);  
	delayMicroseconds(2);  
	digitalWrite(7, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(7, LOW);
  duration = pulseIn(A0, HIGH);  
  distance1 = (duration*.0343)/2; 
  
  if (distance1 > 1000){
    distance1 = getDistance1();
  }
  
  return distance1;
}
