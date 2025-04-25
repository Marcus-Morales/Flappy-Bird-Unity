#include <iostream>
#include <chrono>
#include "BehaviorTree.CPP-master/include/behaviortree_cpp/action_node.h"
#include "BehaviorTree.CPP-master/include/behaviortree_cpp/bt_factory.h"
#include <rclcpp/rclcpp.hpp>


using namespace std::chrono_literals;
using namespace std;
using namespace rclcpp;

    // node class
    class MovementAction {
        public MovementAction(const string &name, const string &action); 
        : Node(name + "_node"), action_(acion), message_sent_(false) {} 
        
        // publisher for the movement_command topic (basically an object that allows for communication between command nodes
        publisher_ = this->create_publisher<MovementAction::MovementAction>("movement)action", 10);

        // service client for /navigator status
        client_ = this->create_client<CascadeStatus::CascadeStatus>("/navigator_status");

        // wait for the service to be available 
        while(!client_->wait_for_service(1s)) {
            RCLPP_INFO(this->get_logger()), ("Service /navigator_status not available, waiting again fro %s...", name.c_str());
        }
        // function of setup that'll estasblish communication and make sure parts are ready to carry out commands
        void setup() {
            RCLPP_DEBUG(get_logger(), "%s::setup", get_name().c.str());
        }
        // function initialize that'll like set positions, velocity, etc.
        void initialise() {
            RCLPP_DEBUG(get_logger(), "%s::initialise", get_name().c.str());
        }
        // function of update publishes movement command and checks the status of the system
        void update() {
            RCLPP_DEBUG(get_logger(), "%s::update", get_name().c.str());
            // check if movement command has been sent
            if(!message_sent) {
                publish_movement_action();
                message_sent_ = true;
            }
            // request for CascadeStatus service
            auto request = make_shared<robot_control::srv::CascadeStatus::Request>();
            future_ = client_->async_send_request(request);
            
            // wait until the service response is complete
            spin_until_future_complete(shared_from_this(), future_);

            // check if result from service response is something 

        }


        

        }

int main()
{
    BT::BehaviorTreeFactory factory;


    return 0;
}