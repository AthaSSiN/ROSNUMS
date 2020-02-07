#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <chrono>	
#include "std_srvs/Empty.h"

#define PI 3.1415							

ros::Publisher velocity_publisher; //Publisher

geometry_msgs::Twist vel_msg;	//holds velocity data								
int distance = 2;
float angle = 1.30;

void move(int a=1)
{

    vel_msg.linear.x = 2*a;
    int speed = 2*a;
    float current_distance = 0.0;

        std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();

        while(a*current_distance < distance)
        {
            //Publish the velocity
            velocity_publisher.publish(vel_msg);
            
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            
            current_distance= speed*(std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count());
        }
        
        vel_msg.linear.x = 0;
        velocity_publisher.publish(vel_msg);

}

void rot(float a)
{
    float angular_speed = a/2.0;
    vel_msg.angular.z = a/2.0;
    float current_angle = 0.0;

        std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();

        while(a*current_angle < angle)
        {
            //Publish the velocity
            velocity_publisher.publish(vel_msg);
            
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            
            current_angle = angular_speed*(std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count());
        }
        
        vel_msg.angular.z = 0;

        std::cout<<"Angle rotated = "<<current_angle*180/3.14159265<<std::endl;
        
        velocity_publisher.publish(vel_msg);
}

int main(int argc, char **argv)
{
	// connect to roscore
    
    ros::init(argc, argv, "numsserve");
    ros::NodeHandle n;	

    //connet to service to reset
    ros::ServiceClient client = n.serviceClient<std_srvs::Empty>("reset");	
    ros::Rate loop_rate(10);

    velocity_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    std_srvs::Empty srv;

    int x;

    do
    {
        
        std::cout<<"Enter number to print (-1 to quit): ";
        std::cin>>x;

        client.call(srv);

        switch(x)
        {
            case 1:
                rot(1);
                move(1);
                move(1);
                break;
            case 2:
                move(-1);
                rot(1);
                move(1);
                rot(-1);
                move();
                rot(1);
                move();
                rot(1);
                move();
                break;
            case 3:
                move();
                rot(1);
                move();
                rot(1);
                move();
    
                move(-1);
                rot(-1);
                move();
                rot(1);
                move();
                break;
            case 4:
                rot(1);
                move();
                move();
                
                move(-1);
                rot(1);
                move();
                rot(-1);
                move();
                break;
            case 5:
                move();
                rot(1);
                move();
                rot(1);
                move();
                rot(-1);
                move();
                rot(-1);
                move();
                break;
        }
    } while (x >= 0 && x < 10);		
}


