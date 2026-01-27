#include "main.h"

pros::Motor wallstake(-9, pros::E_MOTOR_GEARSET_36, false);
pros::Motor intake1(3, pros::E_MOTOR_GEARSET_06, false);
pros::Motor intake2(14, pros::E_MOTOR_GEARSET_06, false);

pros::ADIDigitalOut middlegoal('H', false);
pros::ADIDigitalOut descore('F', false);
pros::ADIDigitalOut scraper('B', false);

pros::Motor lF(-1, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lB(-2, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor lB2(-11, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed

pros::Motor rF(10, pros::E_MOTOR_GEARSET_06); // right front motor. port 12
pros::Motor rB(8, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
pros::Motor rB2(20, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
 

// motor groups
pros::MotorGroup leftMotors({lF, lB2, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rB2, rB}); // right motor group
pros::Imu imu(8);
pros::Rotation rotation_sensor(10);
pros::Optical colorsort(7);
