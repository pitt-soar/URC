#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>

//run using rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200
ros::NodeHandle nh;
int trigPin = 6;
int echoPin = 7;
double duration, cm, inches;
String distance = "";
char distanceChar[29];

std_msgs::String msg;
ros::Publisher topic_pub("Ultrasonic_Publisher", &msg);

void setup() {
  nh.initNode();
  nh.advertise(topic_pub);

  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  delay(500);

  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74;
  distance = String(inches) + "in, " + String(cm) + " cm" + "\n";
  
  distance.toCharArray(distanceChar,distance.length()+1);
  msg.data = distanceChar;

  //msg.data = distance;
  Serial.print(distanceChar);

  topic_pub.publish(&msg);
  nh.spinOnce();
}
