#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include <queue>

std::queue<sensor_msgs::CompressedImageConstPtr> image_buf;

void imgCallback(const sensor_msgs::CompressedImageConstPtr &img)
{
  //ROS_INFO("Image Received");
  image_buf.push(img);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bag_to_img");
  ros::NodeHandle nh;

  std::string topicName, path, fileName;
  nh.param<std::string>("topic",topicName,"/camera/infra1/image_rect_raw");
  nh.param<std::string>("path",path,"~/");
  nh.param<std::string>("fileName",fileName,"image");

  ROS_INFO("%s", topicName.c_str());
  ROS_INFO("%s", path.c_str());
  ROS_INFO("%s", fileName.c_str());

  ros::Subscriber image_sub = nh.subscribe(topicName, 1000, imgCallback);

  ros::Rate loop_rate(60);

  double time_prev = 0;
  int count = 1;
  while(ros::ok()){
    if(!image_buf.empty()){

      double time_img = image_buf.front()->header.stamp.toSec();

      if(time_img -time_prev > 0.99){
        cv_bridge::CvImageConstPtr ptr_l;

        ptr_l = cv_bridge::toCvCopy(image_buf.front(), sensor_msgs::image_encodings::MONO8);

        cv::Mat image;
        image = ptr_l->image.clone();
        image_buf.pop();


        cv::imwrite(path + "/" + fileName +std::to_string(count)+".jpg", image);

        ROS_INFO("Image%d Saved!",count++);
        time_prev = time_img;
      }
      else{
        image_buf.pop();
      }
    }
    else{
      //ROS_INFO("Wait Images");
    }


    ros::spinOnce();
  }

  return 0;
}
