#include "main.h"
/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 127; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 127;
const int SWING_SPEED = 90;
//make sure these are in centidegrees (1 degree = 100 centidegrees)
///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}

void solowp(){
  intake1.move_voltage(-12000);
  chassis.set_drive_pid(14, DRIVE_SPEED, true);
  chassis.wait_until(12);
  //geos to the bot and picks up ball and pushes the bot
  //pros::delay(50); //200
  chassis.set_drive_pid(-56, DRIVE_SPEED, true);
  chassis.wait_drive();
  //comes back for the scrapper
  scraper.set_value(true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(10, 40, true);
  chassis.wait_drive();
  //chassis.set_drive_pid(-3, 90, true);
  //chassis.wait_until(-2);
  //chassis.set_drive_pid(3, 90, true);
  //chassis.wait_until(2);
  //scrapes
  // chassis.set_drive_pid(-2, 80, true);
  // chassis.wait_until(-1);
  // chassis.set_drive_pid(2, 80, true);
  // chassis.wait_until(1);
  pros::delay(375); //adjusts 300 beforepro
  chassis.set_drive_pid(-28, 60, true);
  chassis.wait_until(-26); //comes back to score
  intake2.move_voltage(12000);
  scraper.set_value(false);
  pros::delay(1200); //1300
  intake2.move_voltage(0);
  chassis.set_drive_pid(14, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(42, TURN_SPEED);
  chassis.wait_drive();
  //turns for the 3 blocks
  scraper.set_value(true);
  chassis.set_drive_pid(26, DRIVE_SPEED, true);
  chassis.wait_until(24);
  pros::delay(200);
  //intakes the 3 blocks
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_until(2);
  scraper.set_value(false);
  chassis.set_drive_pid(26, DRIVE_SPEED, true);
  chassis.wait_until(23);
  scraper.set_value(true);
  chassis.set_drive_pid(29, DRIVE_SPEED, true);
  chassis.wait_drive();
  pros::delay(100);
  //intakes the other 3
  chassis.set_turn_pid(-49, TURN_SPEED);
  chassis.wait_until(-41);
  chassis.set_drive_pid(-18, DRIVE_SPEED, true);
  chassis.wait_drive();
  //middle goal
  middlegoal.set_value(true);
  pros::delay(300);
  intake2.move_voltage(4000);
  pros::delay(500);
  intake2.move_voltage(0);
  middlegoal.set_value(false);
  chassis.set_turn_pid(-38, TURN_SPEED);
  chassis.wait_until(-36);
  chassis.set_drive_pid(49, DRIVE_SPEED, true);
  chassis.wait_until(47);
  scraper.set_value(false); 
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //scraper.set_value(true);
  //chassis.set_drive_pid(20, DRIVE_SPEED, true);
  //chassis.wait_until(18);
  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_until(-10);
  intake2.move_voltage(12000);
  chassis.wait_until(-12);
  intake1.move_voltage(12000);
  pros::delay(100);
  intake1.move_voltage(-12000);
  //scraper.set_value(false);
}
void sevenball(){
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_until(8);
  intake1.move_voltage(-12000);
  chassis.set_turn_pid(45, TURN_SPEED);
  //turns for the 3 blokcs near middle goal
  chassis.wait_drive();
  scraper.set_value(true);
  chassis.set_drive_pid(15, DRIVE_SPEED, true); 
  chassis.wait_until(13);
  pros::delay(300); 
  //gets the 3 blocks from mid
  chassis.set_turn_pid(120, 70);
  chassis.wait_drive();
  chassis.set_drive_pid(38, DRIVE_SPEED, true);  
  chassis.wait_until(36);
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-18, DRIVE_SPEED, true);  
  chassis.wait_until(-16);
  intake2.move_voltage(12000);  
  pros::delay(1000);
  //scores on long goal
  intake2.move_voltage(0);
  chassis.set_drive_pid(30, 55, true);  
  chassis.wait_until(28);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 80, true);
  chassis.wait_until(2);
  pros::delay(900); //adjusts
  chassis.set_drive_pid(-30, DRIVE_SPEED, true);  
  chassis.wait_until(-28);
  intake2.move_voltage(12000);
  pros::delay(2000);
  intake2.move_voltage(0); 
  scraper.set_value(false);
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED); //turn for the 3 blocks and get control
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 65, true);
  chassis.wait_until(-28);
  }
void midandlong(){
  intake1.move_voltage(-12000);
  chassis.set_drive_pid(-43, DRIVE_SPEED, true);
  chassis.wait_until(-41);
  //comes back for the scrapper
  scraper.set_value(true);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(11, 50, true);
  chassis.wait_until(9);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2);
  pros::delay(500); //adjusts
  chassis.set_drive_pid(-30, 64, true);
  chassis.wait_until(-28); //comes back to score
  intake2.move_voltage(12000);
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
  intake2.move_voltage(0);
  chassis.set_drive_pid(16, DRIVE_SPEED, true);
  chassis.wait_until(14);
  chassis.set_turn_pid(-42, TURN_SPEED);
  chassis.wait_drive();
  //turns for the 3 blocks
  chassis.set_drive_pid(10, 90, true);
  chassis.wait_until(8);
  scraper.set_value(true);
  chassis.set_drive_pid(22, 90, true);
  chassis.wait_until(20);
  pros::delay(350);
  chassis.set_turn_pid(139, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-22, 60, true);
  chassis.wait_until(-20);
  middlegoal.set_value(true);
  pros::delay(300);
  intake2.move_voltage(6000);
  pros::delay(1700);
  intake2.move_voltage(0);
  middlegoal.set_value(false);
  chassis.set_drive_pid(34, DRIVE_SPEED, true);
  chassis.wait_until(32);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-23, 75, true);
  chassis.wait_until(-21);
  scraper.set_value(false);
  }


void RedRush(){
  intake1.move_voltage(-12000);
  //goes to the bot and picks up ball and pushes the bot
  chassis.set_drive_pid(-43, DRIVE_SPEED, true);
  chassis.wait_drive();
  //comes back for the scrapper
  scraper.set_value(true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(10.5, 22, true);
  chassis.wait_drive();
  //chassis.set_drive_pid(-3, 22, true);
  //chassis.wait_until(-2);
  //chassis.set_drive_pid(3, 22, true);
  //chassis.wait_until(2);
  //scrapes
  //chassis.set_drive_pid(-3, 80, true);
  //chassis.wait_until(-2);
  //chassis.set_drive_pid(3, 80, true);
  //chassis.wait_until(2);
  pros::delay(600); //adjusts
  chassis.set_drive_pid(-28, 64, true);
  chassis.wait_until(-26); //comes back to score
  intake2.move_voltage(12000);
  scraper.set_value(false); //pulls scraper up
  pros::delay(2000);
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_until(11);
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, DRIVE_SPEED, true); 
  chassis.wait_until(-12);
  chassis.set_turn_pid(-90, TURN_SPEED); //turn for the 3 blocks and get control
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 80, true);
  chassis.wait_until(-28);
  }

void BlueRush(){
  intake1.move_voltage(-12000);
  chassis.set_drive_pid(-43, DRIVE_SPEED, true);
  chassis.wait_until(-41);
  //comes back for the scrapper
  scraper.set_value(true);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(8, 30, true);
  chassis.wait_drive();
  pros::delay(300);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2);
  pros::delay(500); //adjusts
  chassis.set_drive_pid(-30, 64, true);
  chassis.wait_until(-28); //comes back to score
  intake2.move_voltage(12000);
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
  intake2.move_voltage(0);
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(12.3, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED); //turn for the 3 blocks and get control
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 60, true);
  chassis.wait_until(-28);
  }


void test(){
    
  }

void Skills(){
  intake1.move_voltage(-12000);
  chassis.set_drive_pid(31, DRIVE_SPEED, true); 
  chassis.wait_until(30);
  scraper.set_value(true);
  chassis.set_turn_pid(90, TURN_SPEED); //turns for the scraper
  chassis.wait_until(88);
  chassis.set_drive_pid(8, 60, true); 
  chassis.wait_drive();
  pros::delay(800);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2); // adjusts
  pros::delay(1000);
  chassis.set_drive_pid(-15, 64, true);
  chassis.wait_until(-13);
  scraper.set_value(false); //pulls scraper up
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  intake1.move_voltage(12000);
  pros::delay(300);
  intake1.move_voltage(-12000);
  chassis.set_drive_pid(16, DRIVE_SPEED, true); 
  chassis.wait_until(14);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_until(-88);
  chassis.set_drive_pid(80, DRIVE_SPEED, true); 
  chassis.wait_until(78); // goes for the other side
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_until(-178);
  chassis.set_drive_pid(12, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_until(-88);
  chassis.set_drive_pid(-10, DRIVE_SPEED, true); 
  chassis.wait_until(-8);
  intake1.move_voltage(12000);
  pros::delay(400);
  intake1.move_voltage(-12000);
  intake2.move_voltage(12000);
  scraper.set_value(true);
  pros::delay(2000); //intakes on the right side all 6 blocks
  intake2.move_voltage(0);
  chassis.set_drive_pid(27, 60, true); 
  chassis.wait_drive();
  pros::delay(600);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2); //adjusts for the scrapper
  pros::delay(1000);
  chassis.set_drive_pid(-30, DRIVE_SPEED, true); 
  chassis.wait_until(-28);
  intake1.move_voltage(12000);
  pros::delay(300);
  intake1.move_voltage(-12000);
  intake2.move_voltage(12000);
  pros::delay(2000); //scores the 6 blocks
  intake2.move_voltage(0);
  chassis.set_drive_pid(15, DRIVE_SPEED, true); 
  chassis.wait_until(13);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_until(-178);
  chassis.set_drive_pid(97, DRIVE_SPEED, true); 
  chassis.wait_drive(); //goes for the other side
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_until(-88);
  chassis.set_drive_pid(18, 60, true); 
  chassis.wait_drive();
  pros::delay(700);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2); //adjust for the scrapper
  pros::delay(1000);
  chassis.set_drive_pid(-15, 64, true);
  chassis.wait_until(-13);
  scraper.set_value(false); //pulls scraper up
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive(); //turns for the other side
  chassis.set_drive_pid(17, DRIVE_SPEED, true); 
  chassis.wait_until(15);
  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(80, DRIVE_SPEED, true); 
  chassis.wait_until(78); // goes for the other side
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, DRIVE_SPEED, true); 
  chassis.wait_until(-8);
  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_until(88);
  chassis.set_drive_pid(-13, DRIVE_SPEED, true); 
  chassis.wait_until(-11);
  intake1.move_voltage(12000);
  pros::delay(300);
  intake1.move_voltage(-12000);
  intake2.move_voltage(12000);
  scraper.set_value(true);
  pros::delay(2000); //intakes on the right side all 6 blocks
  intake2.move_voltage(0);
  chassis.set_drive_pid(22, DRIVE_SPEED, true); 
  chassis.wait_drive();
  pros::delay(600);
  chassis.set_drive_pid(-3, 90, true);
  chassis.wait_until(-2);
  chassis.set_drive_pid(3, 60, true);
  chassis.wait_until(2); //adjusts for the scrapper
  pros::delay(1000);
  chassis.set_drive_pid(-30, DRIVE_SPEED, true); 
  chassis.wait_until(-28);
  intake1.move_voltage(12000);
  pros::delay(300);
  intake1.move_voltage(-12000);
  intake2.move_voltage(12000);
  pros::delay(2000); //scores the 6 blocks
  intake2.move_voltage(0);
  chassis.set_drive_pid(15, DRIVE_SPEED, true); 
  chassis.wait_until(13);
  scraper.set_value(false);
  chassis.set_turn_pid(-330, TURN_SPEED);
  chassis.wait_until(28); //turns for park
  chassis.set_drive_pid(40, DRIVE_SPEED, true); 
  chassis.wait_until(38);
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  intake2.move_voltage(12000);
  chassis.set_drive_pid(30, DRIVE_SPEED, true); 
  chassis.wait_drive();
  }


///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .