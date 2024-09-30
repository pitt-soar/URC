#define channelA 22
#define channelB 23

#define DIR2 52
#define PWM2 3

int encoderCount;
int dir = 0;  // cw = 1; ccw = -1
int countA = 0;
int countB = 0;
int timePassed;
void setup() {
  Serial.begin(9600);

  pinMode (DIR2, OUTPUT); 
  pinMode (PWM2, OUTPUT); 
  pinMode (channelA, INPUT); 
  pinMode (channelB, INPUT);
  digitalWrite(DIR2, HIGH);
  attachInterrupt(digitalPinToInterrupt(channelA), checkQuadA, RISING);
}

//find counts per second
void loop() {
  double timePassed = micros()/1e6;
  if(timePassed < 2.30769) {
    //Serial.print(digitalRead(encoderA));      // uncomment to see squarewave output
    Serial.print('\t');
    //Serial.print(digitalRead(encoderB));
    Serial.print('\t');
    //Serial.print(dir);
    Serial.print('\t');
    Serial.print(countA);
    Serial.print('\t');
    Serial.println(); 
    analogWrite(PWM2, 255);
    Serial.println(timePassed);
    Serial.println();
    double rps = revolutions(countA);
  } else {
    analogWrite(PWM2, 0);
  }
  
  //Serial.print(digitalRead(encoderA));      // uncomment to see squarewave output
//  Serial.print('\t');
//  //Serial.print(digitalRead(encoderB));
//  Serial.print('\t');
//  //Serial.print(dir);
//  Serial.print('\t');
//  Serial.print(countA);
//  Serial.print('\t');
//  Serial.println(); 
//  analogWrite(PWM2, 255);
//  Serial.println(timePassed);
//  Serial.println();
}

double revolutions(int count) {
  //encoder count per revolution (CPR) is equal to the (PPR * 4) i think this is wrong though
        //for the gobilda motor its 3895.9 PPR
  //encoder count was 11383 at 24 volts and after 10 seconds it turned 11.5 times
  //1348 1354 1347
  return count;
}
void checkDirection() {
  if(digitalRead(channelB) == HIGH) {
    dir = 1;
  } else {
    dir = -1;
  }
}

void checkQuadA() {
  checkDirection();
  countA += dir;
}
