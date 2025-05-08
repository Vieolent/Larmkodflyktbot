 float average(float value, float array[]){
  array[9] = value;
   float sum = 0;
  for(int i = 0; i < 10; i++){
    array[i] = array[i+1];
    sum = sum + array[i];
  }
  return sum/10;
}

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
