#include <ros.h>
#include <geometry_msgs/Twist.h>
//#include <string.h>
#include "configuration.h"

ros::NodeHandle nh;
float left_speed, right_speed;

void control_motor(float IN_speed, int OUT_pwmPin, int OUT_pin1, int OUT_pin2){
    if(IN_speed > 0){
        analogWrite(OUT_pwmPin, IN_speed*150);
        digitalWrite(OUT_pin1, HIGH);
        digitalWrite(OUT_pin2, LOW);
    }
    else if(IN_speed < 0){
        analogWrite(OUT_pwmPin, -IN_speed*150);
        digitalWrite(OUT_pin1, LOW);
        digitalWrite(OUT_pin2, HIGH);
    }
    else{
        digitalWrite(OUT_pin1, LOW);
        digitalWrite(OUT_pin2, LOW);
    }
}

void velocityCallback (const geometry_msgs::Twist& velocity){
  /*  
  static float speed[2];
    static char buff[30];
    int counter = 0;

    // read command from raspberry pi
    while(Serial.available()){
        buff[counter] = Serial.read();
        if (counter > 30 || buff[counter] == '*') {
            buff[counter] = '\0';
            speed[0]=atoi(strtok(buff,","));
            speed[1]=atoi(strtok(NULL,","));
        }
        else{
            counter++;
        }
    }
    */
    left_speed = vel.linear.x - vel.angular.z;
    right_speed = vel.linear.x + vel.angular.z;
    

    // control motors
    control_motor(left_speed, left_PWM, left_dir1, left_dir2);
    control_motor(right_speed, right_PWM, right_dir1, right_dir2);

    // send messages to raspberry pi
    //Serial.print(speed[0]); Serial.print(",");
    //Serial.print(speed[1]); 
    
    //delay(100);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &velocityCallback);


void setup() {
    //Serial.begin(115200);
       
    pinMode(left_dir1, OUTPUT);
    pinMode(left_dir2, OUTPUT);
    pinMode(left_PWM, OUTPUT);
    
    pinMode(right_dir1, OUTPUT);
    pinMode(right_dir2, OUTPUT);
    pinMode(right_PWM, OUTPUT);
    
    nh.initNode();
    nh.subscribe(sub);
}

// In time loop, receive from serial and control 4 motors
void loop() {
  nh.spinOnce();
  delay(10);
}

