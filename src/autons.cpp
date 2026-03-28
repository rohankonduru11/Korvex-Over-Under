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

void safewp(){
  intake();
  scraper.set_value(true);
  chassis.set_drive_pid(-32, 110, true);
  chassis.wait_until(-30);
  //comes back for the scrapper
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(11.5, 75, true);
  chassis.wait_drive();
  pros::delay(100); //adjusts 300 beforepro
  chassis.set_drive_pid(-28, 70, true);
  chassis.wait_until(-23); //comes back to score
  scraper.set_value(false);
  pros::delay(1300); //1300
  chassis.set_drive_pid(14, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(42, TURN_SPEED);
  chassis.wait_drive();
  //turns for the 3 blocks
  chassis.set_drive_pid(31, DRIVE_SPEED, true);
  chassis.wait_until(29);
  pros::delay(200);
  //intakes the 3 blocks
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_until(2);
  chassis.set_drive_pid(45, 90, true);
  chassis.wait_until(43);
  //intakes the other 3 blocks
  chassis.set_turn_pid(-49, TURN_SPEED);
  chassis.wait_until(-41);
  chassis.set_drive_pid(-16, DRIVE_SPEED, true);
  chassis.wait_until(-11);
  //middle goal macro add here
  pros::delay(850);
  //MIDDLE GOAL MACRO HERE
  scraper.set_value(true);
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(54.5, DRIVE_SPEED, true);
  chassis.wait_until(52.5);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_until(88);
  chassis.set_drive_pid(10.7, 45, true);
  chassis.wait_until(8.7);
  pros::delay(50);
  chassis.set_drive_pid(-28, DRIVE_SPEED, true);
  chassis.wait_until(-23);
  pros::delay(500);
  pros::delay(100);
}
void BottomAndLong(){
  intake();
  //goes to the bot and picks up ball and pushes the bot
  scraper.set_value(true);
  chassis.set_drive_pid(-32, DRIVE_SPEED, true);
  chassis.wait_until(-30);
  //comes back for the scrapper
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(11.5, 80, true);
  chassis.wait_drive();
  pros::delay(50); //adjusts
  chassis.set_drive_pid(-28, 70, true);
  chassis.wait_until(-26); //comes back to score
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
  chassis.set_drive_pid(18, DRIVE_SPEED, true);
  chassis.wait_until(15);
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(100);
  chassis.set_drive_pid(35, 60, true);
  chassis.wait_until(33);
  pros::delay(600);  
  chassis.set_drive_pid(18, 60, true);
  chassis.wait_until(16);
  pros::delay(1000);
  chassis.set_drive_pid(-5, 40, true);
  chassis.wait_until(-3);
  pros::delay(200);
  chassis.set_drive_pid(-31, DRIVE_SPEED, true);
  chassis.wait_until(-29);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_until(88);
  chassis.set_drive_pid(23, 50, true);
  chassis.wait_until(21);
  chassis.set_turn_pid(30, 40);
  chassis.wait_drive();
}
void sevenball(){
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_until(8);
  intake();
  chassis.set_turn_pid(30, TURN_SPEED);
  //turns for the 3 blokcs near middle goal
  chassis.wait_drive();
  chassis.set_drive_pid(15, 80, true); 
  chassis.wait_until(10);
  scraper.set_value(true);
  pros::delay(200); 
  //gets the 3 blocks from mid
  chassis.set_turn_pid(120, 70);
  chassis.wait_drive();
  chassis.set_drive_pid(36, DRIVE_SPEED, true);  
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-16, DRIVE_SPEED, true);  
  chassis.wait_until(-14);
  pros::delay(1200);
  //scores on long goal
  chassis.set_drive_pid(28, 55, true);  
  chassis.wait_drive();
  pros::delay(230); //adjusts
  chassis.set_drive_pid(-30, 80, true);  
  chassis.wait_until(-25);
  pros::delay(2000);
  scraper.set_value(false);
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-11, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED); //turn for the 3 blocks and get control
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 45, true);
  chassis.wait_until(-25);
  }
void midandlong(){
  intake();
  scraper.set_value(true);
  chassis.set_drive_pid(-32, DRIVE_SPEED, true);
  chassis.wait_drive();
  //comes back for the scrapper
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(11.5, 80, true);
  chassis.wait_drive();
  pros::delay(80); //adjusts
  chassis.set_drive_pid(-30, 64, true);
  chassis.wait_until(-28); //comes back to score
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
  chassis.set_drive_pid(19, DRIVE_SPEED, true);
  chassis.wait_until(17);
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  //turns for the 3 blocks
  chassis.set_drive_pid(10, 90, true);
  chassis.wait_until(8);
  scraper.set_value(true);
  chassis.set_drive_pid(23, 90, true);
  chassis.wait_until(21);
  pros::delay(350);
  chassis.set_turn_pid(138, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-23, 60, true);
  chassis.wait_until(-21);
  pros::delay(1700);
  //MIDDLE GOAL MACRO HERE
  chassis.set_drive_pid(35, DRIVE_SPEED, true);
  chassis.wait_drive();
  scraper.set_value(false);
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-23, 45, true);
  chassis.wait_until(-21);
  }


void RedRush(){
  intake();
  //goes to the bot and picks up ball and pushes the bot
  chassis.set_drive_pid(-32, DRIVE_SPEED, true);
  chassis.wait_drive();
  //comes back for the scrapper
  scraper.set_value(true);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(11.5, 45, true);
  chassis.wait_drive();
  pros::delay(220); //adjusts
  chassis.set_drive_pid(-28, 64, true);
  chassis.wait_until(-26); //comes back to score
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
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
  intake();
  scraper.set_value(true);
  chassis.set_drive_pid(-32, DRIVE_SPEED, true);
  chassis.wait_drive();
  //comes back for the scrapper
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //turns to face the goal
  chassis.set_drive_pid(9.5, 45, true);
  chassis.wait_drive();
  pros::delay(220); //adjusts
  chassis.set_drive_pid(-30, 64, true);
  chassis.wait_until(-28); //comes back to score
  scraper.set_value(false); //pulls scraper up
  pros::delay(1500);
  chassis.set_drive_pid(9, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(12.3, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED); //turn for the 3 blocks and get control
  chassis.wait_drive();
  chassis.set_drive_pid(-30, 45, true);
  chassis.wait_until(-28);
  }

void Skills(){
  scraper.set_value(true);
  intake();
  chassis.set_drive_pid(31, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED); //turns for the scraper
  chassis.wait_drive();
  chassis.set_drive_pid(13, 35, true); 
  chassis.wait_drive();
  pros::delay(700);
  chassis.set_drive_pid(-15, 64, true);
  chassis.wait_until(-13);
  scraper.set_value(false); //pulls scraper up
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(9, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(75, DRIVE_SPEED, true); 
  chassis.wait_until(73); // goes for the other side
  pros::delay(300);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_until(-178);
  chassis.set_drive_pid(12, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 60, true); 
  chassis.wait_drive();
  scraper.set_value(true);
  pros::delay(1500); //intakes on the right side all 6 blocks
  pros::delay(200);
  pros::delay(1500);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //intake2.move_voltage(0);
  chassis.set_drive_pid(32, 35, true); 
  chassis.wait_drive(); //adjusts for the scprapper
  pros::delay(700);
  chassis.set_drive_pid(-31, 60, true); 
  chassis.wait_until(-29);
  pros::delay(1500); //intakes on the right side all 6 blocks
  pros::delay(200);
  pros::delay(1500);
  chassis.set_drive_pid(15, DRIVE_SPEED, true); 
  chassis.wait_until(13);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(97, DRIVE_SPEED, true); 
  chassis.wait_drive(); //goes for the other side
  pros::delay(300);
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(20, 35, true); 
  chassis.wait_drive(); //adjust for the scrapper
  pros::delay(700);
  chassis.set_drive_pid(-15, 64, true);
  chassis.wait_until(-13);
  scraper.set_value(false); //pulls scraper up
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive(); //turns for the other side
  chassis.set_drive_pid(5, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -270, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(76, DRIVE_SPEED, true); 
  chassis.wait_until(74); // goes for the other side
  pros::delay(300);
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-14, 60, true); 
  chassis.wait_drive();
  scraper.set_value(true);
  pros::delay(1500); //intakes on the right side all 6 blocks
  pros::delay(200);
  pros::delay(1500);
  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(37, 35, true); 
  chassis.wait_drive();
  pros::delay(700);
  chassis.set_drive_pid(-32, 60, true); 
  chassis.wait_until(-30);
  pros::delay(1500); //intakes on the right side all 6 blocks
  pros::delay(200);
  pros::delay(1500);
  chassis.set_drive_pid(16.5, DRIVE_SPEED, true); 
  chassis.wait_until(14.5);
  scraper.set_value(false);
  chassis.set_turn_pid(-120, TURN_SPEED);
  chassis.wait_drive(); //turns for park
  chassis.set_drive_pid(-21, DRIVE_SPEED, true); 
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -180, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-54, DRIVE_SPEED, true); 
  chassis.wait_drive();
  }
void test(){
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