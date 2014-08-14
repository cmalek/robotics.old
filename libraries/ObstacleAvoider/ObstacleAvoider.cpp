#include <ObstacleAvoider.h>

namespace rolley
{
    ObstacleAvoider::ObstacleAvoider() : 
        _state(START)
    {}

    ObstacleAvoider::setup(Servo *servo, Sonar *sonar)  
    {
        this->_robot = rolley::Rolley(servo, sonar);
    }

    void ObstacleAvoider::detect_bump()
    {
       this->_robot.bump_update();
       if (this->_robot.is_bump()) {
           this->_state = BUMP;
           if (this->_robot.is_left_bump()) {
               this->_context.obstacle_direction = LEFT;
           } else if (this->_robot.is_front_bump()) {
               this->_context.obstacle_direction = FRONT;
           } else if (this->_robot.is_right_bump()) {
               this->_context.obstacle_direction = RIGHT;
           }
        }
    }

    void ObstacleAvoider::detect()
    {
        this->detect_bump();
    }
    
    void ObstacleAvoider::start()
    {
        this->_robot.servo_set_position(90);
        this->_state = FORWARD;
    }

    void ObstacleAvoider::forward()
    {
        this->_robot.forward(100);
    }

    void ObstacleAvoider::bump()
    {
        switch(this->_context.obstacle_direction) {
            case LEFT:
                this->_robot.backward_cm(100, .30);
                // and turn
            default:
                this->_robot.stop();
        }
    }

    void ObstacleAvoider::run() 
    {
        switch(this->_state) {
            case START:
                this->start();
            case FORWARD:
                this->forward();
            case BUMP:
                this->bump();
            default:
                this->forward();
        }
        this->detect();
    }

}
