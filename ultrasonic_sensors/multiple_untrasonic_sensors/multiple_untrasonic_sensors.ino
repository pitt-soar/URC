int trigPin1 = 52;
int echoPin1 = 53;
int trigPin2 = 50;
int echoPin2 = 51;
int trigPin3 = 48;
int echoPin3 = 49;
double duration, cm;
String distance = "";

void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  distance = "";
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  cm = (duration/2) / 29.1;
  distance += String(cm) + ", ";
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  cm = (duration/2) / 29.1;
  distance += String(cm) + ", ";

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  cm = (duration/2) / 29.1;
  distance += String(cm) + ", ";
  
  Serial.println(distance);
  
}
