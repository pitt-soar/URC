//Define pin numbers for motor
#define DIR1 52
#define PWM1 3

//Define pin numbmers for encoder
#define encoderPinA 22
#define encoderPinB 23

//Variable for encoder counts
volatile long encoderCount = 0;

//Variables for PID Control
long previousTime = 0;
float ePrevious = 0;
float eIntegral = 0;

void setup() { 
  Serial.begin(9600);

  //Set pin modes 
  pinMode (DIR1, OUTPUT); 
  pinMode (PWM1, OUTPUT); 
  pinMode (encoderPinA, INPUT); 
  pinMode (encoderPinB, INPUT);
  
  //Interrupt for encoder
  attachInterrupt(digitalPinToInterrupt(encoderPinA), handleEncoder, RISING);
}
void loop() {
  //Setpoint
  int target = 1000;
  
  //PID gains and computation
  float kp = 5.0;
  float kd = 0.0;
  float ki = 0.0;
  float u = pidController(target, kp, kd, ki);
  Serial.println(u);
  //Control motor
  moveMotor(DIR1, PWM1, u);


  //Print statements for debugging
  Serial.print(target);
  Serial.print(", ");
  Serial.println(encoderCount);
}

//Function called during interrupts
void handleEncoder() {
  if (digitalRead(encoderPinA) > digitalRead(encoderPinB)) {
    encoderCount++;
  }
  else{
    encoderCount--;
  }
}

//Function to move motor
void moveMotor(int dirPin, int pwmPin, float u){
  //Maximum motor speed
  float pwmspeed = fabs(u);
  if (pwmspeed > 100) {
    pwmspeed = 100;
  }
  
  //set the direction
  int motorDirection = 1;
  if (u < 0) {
    motorDirection = 0;
  }
  
  //Control the motor
  digitalWrite(dirPin, motorDirection);
  analogWrite(pwmPin, pwmspeed);
}

float pidController (int target, float kp, float kd, float ki) {
  //Measure the time elapsed since the last iteration
  long currentTime = micros(); 
  float deltaT = ((float)(currentTime - previousTime)) / 1.0E6;
  
  //Compute the error, derivative, and integral 
  int e = encoderCount - target;
  float eDerivative = (e - ePrevious) / deltaT;
  eIntegral = eIntegral + e * deltaT;
  
  //Compute the PID control signal 
  float u = (kp * e) + (kd * eDerivative) + (ki * eIntegral);
  
  //Update variables for the next iteration 
  previousTime = currentTime; 
  ePrevious = e;
  
  return u;
}
