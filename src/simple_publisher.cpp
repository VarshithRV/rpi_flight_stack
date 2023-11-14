# include <iostream>
# include "rclcpp/rclcpp.hpp"
# include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class simple_pub : public rclcpp::Node
{
    private:
        // declare the private variables like the timerbase publisher and the count
        size_t _count;
        // create a publisher object
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _publisher; // what is the shared ptr?
        rclcpp::TimerBase::SharedPtr _timer;

        void timerCallBack() // this gets called back every time the timer sets to the specified freq
        {
            auto message=std_msgs::msg::String(); //create a message type
            // initialize the message data
            message.data="Hello world"+std::to_string(_count++);
            RCLCPP_INFO(this->get_logger(),"Publishing '%s'",message.data.c_str());// convert to char array and log
            _publisher->publish(message); // publish the message
        }

    public:
        simple_pub() : Node("simplepub") ,_count(0)
        {
            // bind the publisher to the topic, initialize the publisher
            _publisher=this->create_publisher<std_msgs::msg::String>("topic",10);
            // bind the timerbase with a timer value and the callback
            _timer=this->create_wall_timer(
                500ms, std::bind(&simple_pub::timerCallBack,this)
            );// what does the std::bind do ?
        }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv); // what does this do? is it overloaded?
    rclcpp::spin(std::make_shared<simple_pub>());
    rclcpp::shutdown();
    return 0;
}