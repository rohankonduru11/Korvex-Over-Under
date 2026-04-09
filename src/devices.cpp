#include "main.h"

pros::Motor topstage(2, pros::E_MOTOR_GEARSET_18, false);
pros::Motor middlestage(1, pros::E_MOTOR_GEARSET_18, false);
pros::Motor bottomstage(-10, pros::E_MOTOR_GEARSET_06, false);


pros::ADIDigitalOut hood('A', false);
pros::ADIDigitalOut descore('B', false);
pros::ADIDigitalOut scraper('C', false);
pros::ADIDigitalOut middescore('E', false);

pros::Motor lF(-1, pros::E_MOTOR_GEARSET_06); // left front motor. port 9, reversed
pros::Motor lB(-2, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed
pros::Motor lB2(-11, pros::E_MOTOR_GEARSET_06); // left back motor. port 21, reversed

pros::Motor rF(10, pros::E_MOTOR_GEARSET_06); // right front motor. port 12
pros::Motor rB(8, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
pros::Motor rB2(19, pros::E_MOTOR_GEARSET_06); // right back motor. port 16
 

// motor groups
pros::MotorGroup leftMotors({lF, lB2, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rB2, rB}); // right motor group
pros::Imu imu(14);
