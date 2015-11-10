 #include "ros/ros.h"
 #include <geometry_msgs/Twist.h>
 #include <serve_logitech/all_sensor.h>
 
 serve_logitech::all_sensor x;

 void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
   {
     ROS_INFO("linear.x [%f]", msg->linear.x);
     ROS_INFO("linear.y [%f]", msg->linear.y);
     ROS_INFO("linear.z [%f]", msg->linear.z);
     ROS_INFO("------------------------------");
     ROS_INFO("angular.x [%f]", msg->angular.x);
     ROS_INFO("angular.y [%f]", msg->angular.y);
     ROS_INFO("angular.z [%f]", msg->angular.z);
     ROS_INFO("******************************");
     x.a_f=msg->linear.x;
     ROS_INFO("x.a_f=%f",x.a_f);
     

    


   }
   
 int main(int argc, char **argv)
   {
     
     ros::init(argc, argv, "test");
   
     ros::NodeHandle n;
   
     ros::Subscriber sub = n.subscribe("teleop_velocity_smoother/raw_cmd_vel", 1, chatterCallback);      //"teleop_velocity_smoother/raw_cmd_vel”为罗技手柄话题

     ros::Publisher chatter_pub = n.advertise<serve_logitech::all_sensor>("server_logitech", 1);
   
     ros::Rate loop_rate(10);

  while (ros::ok())

{

  chatter_pub.publish(x);
  ros::spinOnce();
  loop_rate.sleep();

}
    
     //ros::spin();
     
     return 0;
   }
