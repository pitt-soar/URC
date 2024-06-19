#include <ros.h>
#include <ArduinoHardware.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8.h>
#include<string.h>

/*-----Left Motors-----*/
#define LF_DIR 13 // Left-Front
#define LM_DIR 12 // Left-Middle
#define LB_DIR 11 // Left-Back
#define L_PWM  10  // Left-PWM
/*-----Right Motors-----*/
#define RF_DIR 9 // Right-Front
#define RM_DIR 8 // Right-Middle
#define RB_DIR 7 // Right-Back
#define R_PWM  6  // Right-PWM

// ROS Setup
uint8_t input = 0;

int pwmSpeed = 50;

ros::NodeHandle nh;

void messageCb( const std_msgs::UInt8& toggle_msg){
  Serial.println("Message is: " );
  Serial.println(toggle_msg.data);
  input = toggle_msg.data;
}
ros::Subscriber<std_msgs::UInt8> sub("motor_controller_publisher", &messageCb );

std_msgs::String msg;
ros::Publisher topic_pub("MotorRosPublisher", &msg);

void setup() 
{
  Serial.begin(115200);
  Serial.println("in setup");
  nh.initNode();
  //nh.getHardware()->setBaud(115200);
  nh.subscribe(sub);
  nh.advertise(topic_pub);

  pinMode(LF_DIR, OUTPUT);
  pinMode(LM_DIR, OUTPUT);
  pinMode(LB_DIR, OUTPUT);
  pinMode(L_PWM,   OUTPUT);

  pinMode(RF_DIR, OUTPUT);
  pinMode(RM_DIR, OUTPUT);
  pinMode(RB_DIR, OUTPUT);
  pinMode(R_PWM,   OUTPUT);
}

void foward() {
  digitalWrite(LF_DIR, HIGH);
  digitalWrite(LM_DIR, HIGH);
  digitalWrite(LB_DIR, HIGH);
  digitalWrite(R_PWM, pwmSpeed);

  digitalWrite(RF_DIR, HIGH);
  digitalWrite(RM_DIR, HIGH);
  digitalWrite(RB_DIR, HIGH);
  digitalWrite(L_PWM, pwmSpeed);
}

void reverse() {
  digitalWrite(LF_DIR, LOW);
  digitalWrite(LM_DIR, LOW);
  digitalWrite(LB_DIR, LOW);
  digitalWrite(R_PWM, pwmSpeed);
  
  digitalWrite(RF_DIR, LOW);
  digitalWrite(RM_DIR, LOW);
  digitalWrite(RB_DIR, LOW);
  digitalWrite(L_PWM, pwmSpeed);
}

void left() {
  digitalWrite(LF_DIR, LOW);
  digitalWrite(LM_DIR, LOW);
  digitalWrite(LB_DIR, LOW);
  digitalWrite(R_PWM, pwmSpeed);

  digitalWrite(RF_DIR, HIGH);
  digitalWrite(RM_DIR, HIGH);
  digitalWrite(RB_DIR, HIGH);
  digitalWrite(L_PWM, pwmSpeed);
}

void right() {
  digitalWrite(LF_DIR, HIGH);
  digitalWrite(LM_DIR, HIGH);
  digitalWrite(LB_DIR, HIGH);
  digitalWrite(R_PWM, pwmSpeed);

  digitalWrite(RF_DIR, LOW);
  digitalWrite(RM_DIR, LOW);
  digitalWrite(RB_DIR, LOW);
  digitalWrite(L_PWM, pwmSpeed); 
}

void boost() {
  while (pwmSpeed < 200){
    analogWrite(L_PWM, pwmSpeed);
    analogWrite(R_PWM, pwmSpeed);
    pwmSpeed += 0.01;
  }
}

void stopAll() {
    while (pwmSpeed > 0){
    analogWrite(L_PWM, pwmSpeed);
    analogWrite(R_PWM, pwmSpeed);
    pwmSpeed -= 0.01;
  }
}

void loop() {
  String output_string = "NO";
  if (input != 0)
  {
    Serial.print("input change detected, input is:");
    Serial.println(input);
    char o_string[20];
    if (input == 1)
    {
      Serial.println("Moving forward");
      output_string = "Moving forward";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      foward();
    }
    else if(input == 2){
      output_string = "Moving reverse";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      reverse();
    }
    else if(input == 3){
      output_string = "Turn Left";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      left();
    }
    else if(input == 4){
      output_string = "Turn Right";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      right();
    }
    else if (input == 5){
      output_string = "Boost!";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      boost();
    }
    else if (input == 6){
      output_string = "STOP!";
      output_string.toCharArray(o_string, output_string.length()+1);
      msg.data = o_string;
      stopAll();
    }
    topic_pub.publish(&msg);
  }
  input = 0;
  nh.spinOnce();
}
