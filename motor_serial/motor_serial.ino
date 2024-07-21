#define PWM1 10
#define DIR1 13
#define PWM2 6
#define DIR2 9

double pwmSpeed = 50;

void setup() 
{
  Serial.begin(115200);
  Serial.println("in setup");

  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2,   OUTPUT);
}

void foward() {
  pwmSpeed = 50;
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  digitalWrite(PWM1, pwmSpeed);
  digitalWrite(PWM2, pwmSpeed);
}

void reverse() {
  pwmSpeed = 50;
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  digitalWrite(PWM1, pwmSpeed);
  digitalWrite(PWM2, pwmSpeed);
}

void left() {
  pwmSpeed = 50;
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  digitalWrite(PWM1, pwmSpeed);
  digitalWrite(PWM2, 0);
}

void right() {
  pwmSpeed = 50;
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  digitalWrite(PWM1, 0);
  digitalWrite(PWM2, pwmSpeed);
}

void boost() {
  while (pwmSpeed <= 200){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    digitalWrite(PWM1, pwmSpeed);
    digitalWrite(PWM2, pwmSpeed);
    pwmSpeed += 1;
    Serial.println(pwmSpeed);
    delay(10);
  }
}

void stopAll() {
  while (pwmSpeed >= 0){
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    digitalWrite(PWM1, pwmSpeed);
    digitalWrite(PWM2, pwmSpeed);
    pwmSpeed -= 1.00;
    Serial.println(pwmSpeed);
//    delay(10);
  }
}

void loop() {
  String input = Serial.readString();
  input.trim();
  if (!(input.equals("")))
  {
    Serial.print("input change detected, input is: ");
    Serial.println(input);
    Serial.println(input.equals("1"));
    if (input.equals("1"))
    {
      Serial.println("Moving forward");
      foward();
    }
    else if(input.equals("2")){
      Serial.println("Moving reverse");
      reverse();
    }
    else if(input.equals("3")){
      Serial.println("Turn Left");
      left();
    }
    else if(input.equals("4")){
      Serial.println("Turn Right");
      right();
    }
    else if (input.equals("5")){
      Serial.println("Boost!");
      boost();
    }
    else if (input.equals("6")){
      Serial.println("STOP!");
      stopAll();
    }
  }
  input = "0";
}
