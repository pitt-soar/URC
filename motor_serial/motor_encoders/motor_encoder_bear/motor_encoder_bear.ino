
#define channelA 22
#define channelB 23

#define DIR2 52
#define PWM2 3

int encoderCount;
int dir = 0;  // cw = 1; ccw = -1
int countA = 0;
int countB = 0;
int timePassed;
int speedCounter = 0;
int timeCounter = 0;

void setup() {
  Serial.begin(9600);

  pinMode (DIR2, OUTPUT); 
  pinMode (PWM2, OUTPUT); 
  pinMode (channelA, INPUT); 
  pinMode (channelB, INPUT);
  digitalWrite(DIR2, HIGH);
  attachInterrupt(digitalPinToInterrupt(channelA), checkQuadA, RISING);

  countA = 0;
}

//find counts per second
void loop() {
  double timePassed = micros()/1e6;
  int pwmspeed = 20;
  if(pwmspeed + speedCounter < 110) {
    if(timePassed < (10 + timeCounter)) {
      analogWrite(PWM2, pwmspeed + speedCounter);
  //    Serial.println("run");
  //    Serial.println(timePassed);
  //    Serial.println(pwmspeed + i);
    } else {
      Serial.println("Speed: ");
      Serial.println(speedCounter + pwmspeed);
      Serial.print(timePassed - 2*(timeCounter / 3));
      Serial.print('\t');
      Serial.print(countA);
      Serial.print('\t');
      Serial.println();
      countA = 0;
      speedCounter += 10;
      analogWrite(PWM2, 0);
      timeCounter += 30;
      delay(20000);
      Serial.println();
      analogWrite(PWM2, pwmspeed + speedCounter);
    }
  } else {
    analogWrite(PWM2, 0);
  }
}

double revolutions(int count) {
  //encoder count per revolution (CPR) is equal to the (PPR * 4) i think this is wrong though
        //for the gobilda motor its 3895.9 PPR
  //encoder count was 11383 at 24 volts and after 10 seconds it turned 11.5 times
  //1348 1354 1347
//  count = count*4;
  
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
