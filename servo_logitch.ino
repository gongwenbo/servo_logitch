/*
gongwenbo at tarsbot 
2015.9.13
*/
#include <Servo.h> 
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <serve_logitech/all_sensor.h>

Servo servo;
ros::NodeHandle  nh;
serve_logitech::all_sensor servo_1;
serve_logitech::all_sensor str_msg;
//ros::Publisher chatter("chatter_1", &str_msg);

void servo_cb ( const serve_logitech::all_sensor& msg)
{
  servo_1.a_f=(msg.a_f + 0.5)*100;
  servo_1.a_f = map(servo_1.a_f, 0, 100, 0, 180); 
  servo.write(servo_1.a_f); //set servo angle, should be from 0-180  
  str_msg.a_f=servo_1.a_f;
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
  
}

ros::Subscriber<serve_logitech::all_sensor> sub("server_logitech", servo_cb);

void setup()
{
  Serial.begin(9600);	//设置通讯的波特率为9600
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  //nh.advertise(chatter);
  servo.attach(9); //attach it to pin 9
}

 void loop()
 {
  nh.spinOnce();
  //chatter.publish( &str_msg );
  delay(1);
}
