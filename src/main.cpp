#include "main.h"
//#include "pros/misc.h"
//#include "pros/rtos.hpp"
using namespace std;



/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negati	cve port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-1, -2, -11}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{10, 8, 20}	

  // IMU Port
  ,6

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.333

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

enum class autonStates { // the possible auton selections
	off,
	solowp,
  sevenball,
  Redrush,
  midandlong,
  Bluerush,
	Skills,
	test
};


autonStates autonSelection = autonStates::off;

static lv_res_t SoloWpAction(lv_obj_t *btn) {
    autonSelection = autonStates::solowp;
    std::cout << pros::millis() << "Solowp" << std::endl;
    return LV_RES_OK;
}

static lv_res_t SevenBallAction(lv_obj_t *btn) {
	autonSelection = autonStates::sevenball;
	std::cout << pros::millis() << "sevenball" << std::endl;
	return LV_RES_OK;
}

static lv_res_t RedRushAction(lv_obj_t *btn) {
	autonSelection = autonStates::Redrush;
	std::cout << pros::millis() << "Redrush" << std::endl;
	return LV_RES_OK;
}

static lv_res_t MidAndLongAction(lv_obj_t *btn) {
	autonSelection = autonStates::midandlong;
	std::cout << pros::millis() << "midandlong" << std::endl;
	return LV_RES_OK;
}
static lv_res_t BlueRushAction(lv_obj_t *btn) {
	autonSelection = autonStates::Bluerush;
	std::cout << pros::millis() << "Bluerush" << std::endl;
	return LV_RES_OK;
}
static lv_res_t SkillsBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::Skills;
	std::cout << pros::millis() << "Skills" << std::endl;
	return LV_RES_OK;
}

static lv_res_t ResetBtnAction(lv_obj_t *btn) {
	imu.reset();

	leftMotors.tare_position();
	rightMotors.tare_position();

	while (imu.is_calibrating() and pros::millis() < 5000)
	{
		pros::delay(10);
	}
	if (pros::millis() < 5000) std::cout << pros::millis() << ": finished calibrating!" << std::endl;
	return LV_RES_OK;
}

static lv_res_t noAutonBtnAction(lv_obj_t *btn) {
	autonSelection = autonStates::off;
	std::cout << pros::millis() << "None" << std::endl;
	return LV_RES_OK;
}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    rotation_sensor.reset_position();


	
  // Print our branding over your terminal :D
  
	pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  	imu.reset();	
	pros::delay(500); // Stop the user from doing anything while legacy ports configure.
  	imu.reset();	
	lv_theme_t *th = lv_theme_alien_init(360, NULL); //Set a HUE value and keep font default RED
	lv_theme_set_current(th);

	// create a tab view object
	std::cout << pros::millis() << ": creating gui..." << std::endl;
	lv_obj_t *tabview = lv_tabview_create(lv_scr_act(), NULL);

	//button layout
	lv_obj_t *LeftTab = lv_tabview_add_tab(tabview, "Left");
	lv_obj_t *RightTab = lv_tabview_add_tab(tabview, "Right");
	lv_obj_t *SkillsTab = lv_tabview_add_tab(tabview, "Skills");
	lv_obj_t *OffTab = lv_tabview_add_tab(tabview, "Turn Off");
	

	// Red tab
	lv_obj_t *SoloWpBtn = lv_btn_create(RightTab, NULL);
	lv_obj_t *labelSoloWp = lv_label_create(SoloWpBtn, NULL);

	lv_obj_t *SevenBallBtn = lv_btn_create(RightTab, NULL);
	lv_obj_t *labelSevenBall = lv_label_create(SevenBallBtn, NULL);

	lv_obj_t *RedRushBtn = lv_btn_create(RightTab, NULL);
	lv_obj_t *labelRedRush = lv_label_create(RedRushBtn, NULL);


	

	// Blue tab
	lv_obj_t *MidAndLongBtn = lv_btn_create(LeftTab, NULL);
	lv_obj_t *labelMidAndLong = lv_label_create(MidAndLongBtn, NULL);

	lv_obj_t *BlueRushBtn = lv_btn_create(LeftTab, NULL);
	lv_obj_t *labelBlueRush = lv_label_create(BlueRushBtn, NULL);

	lv_label_set_text(labelSoloWp, "solowp");
  lv_btn_set_action(SoloWpBtn, LV_BTN_ACTION_CLICK, SoloWpAction);
  lv_obj_set_size(SoloWpBtn, 150, 50);
  lv_btnm_set_toggle(SoloWpBtn, true, 1);
  lv_obj_set_pos(SoloWpBtn, 0, 0);
  lv_obj_align(SoloWpBtn, NULL, LV_ALIGN_CENTER, -150, 0);

	lv_label_set_text(labelSevenBall, "Sevenball");
	lv_btn_set_action(SevenBallBtn, LV_BTN_ACTION_CLICK, SevenBallAction);
	lv_obj_set_size(SevenBallBtn, 150, 50);
	lv_btnm_set_toggle(SevenBallBtn, true, 1);
	lv_obj_set_pos(SevenBallBtn, 0, 0);
	lv_obj_align(SevenBallBtn, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_label_set_text(labelRedRush, "Redrush");
	lv_btn_set_action(RedRushBtn, LV_BTN_ACTION_CLICK, RedRushAction);
	lv_obj_set_size(RedRushBtn, 150, 50);
	lv_btnm_set_toggle(RedRushBtn, true, 1);
	lv_obj_set_pos(RedRushBtn, 0, 0);
	lv_obj_align(RedRushBtn, NULL, LV_ALIGN_CENTER, -150, 0);
  
  lv_label_set_text(labelMidAndLong, "midandlong");
  lv_btn_set_action(MidAndLongBtn, LV_BTN_ACTION_CLICK, MidAndLongAction);
  lv_obj_set_size(MidAndLongBtn, 150, 50);
  lv_btnm_set_toggle(MidAndLongBtn, true, 1);
  lv_obj_set_pos(MidAndLongBtn, 0, 0);
  lv_obj_align(MidAndLongBtn, NULL, LV_ALIGN_CENTER, 0, 0);

  lv_label_set_text(labelBlueRush, "bluerush");
  lv_btn_set_action(BlueRushBtn, LV_BTN_ACTION_CLICK, BlueRushAction);
  lv_obj_set_size(BlueRushBtn, 150, 50);
  lv_btnm_set_toggle(BlueRushBtn, true, 1);
  lv_obj_set_pos(BlueRushBtn, 0, 0);
  lv_obj_align(BlueRushBtn, NULL, LV_ALIGN_CENTER, 150, 0);

	

	//DiagonalDouble tab
	lv_obj_t *OffBtn = lv_btn_create(OffTab, NULL);
	lv_obj_t *Offlabel = lv_label_create(OffBtn, NULL);
	lv_label_set_text(Offlabel, "Turn Off");
	lv_btn_set_action(OffBtn, LV_BTN_ACTION_CLICK, noAutonBtnAction);
	lv_obj_set_size(OffBtn, 450, 50);
	lv_btnm_set_toggle(OffBtn, true, 1);
	lv_obj_set_pos(OffBtn, 0, 100);
	lv_obj_align(OffBtn, NULL, LV_ALIGN_CENTER, 0, 0);


	// skills tab
	lv_obj_t *SkillsBtn = lv_btn_create(SkillsTab, NULL);
	lv_obj_t *skillslabel = lv_label_create(SkillsBtn, NULL);

	lv_label_set_text(skillslabel, "Skills");
	lv_btn_set_action(SkillsBtn, LV_BTN_ACTION_CLICK, SkillsBtnAction);
	lv_obj_set_size(SkillsBtn, 450, 50);
	lv_btnm_set_toggle(SkillsBtn, true, 1);
	lv_obj_set_pos(SkillsBtn, 0, 100);
	lv_obj_align(SkillsBtn, NULL, LV_ALIGN_CENTER, 0, 0);

	//reset btn
	lv_obj_t *ResetBtn = lv_btn_create(tabview, NULL);
	lv_obj_t *ResetLabel = lv_label_create(ResetBtn, NULL);

	lv_label_set_text(ResetLabel, "Reset");
	lv_btn_set_action(ResetBtn, LV_BTN_ACTION_CLICK, ResetBtnAction);
	lv_obj_set_size(ResetBtn, 250, 50);
	lv_btnm_set_toggle(ResetBtn, true, 1);
	lv_obj_set_pos(ResetBtn, 0, 100);
	lv_obj_align(ResetBtn, NULL, LV_ALIGN_CENTER, 0, 50);

	chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.


  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  

  // Initialize chassis and auton selector
  chassis.initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */


void disabled() {
}
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.

  if(autonSelection == autonStates::off) {
		autonSelection = autonStates::test;
	}	

	switch(autonSelection) {
		case autonStates::test:
			test();
			break;
		default:
			break;
	}
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
bool clamp1 = false;
bool clamp2 = false;
bool clamp3 = false;

void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  wallstake.set_brake_mode(MOTOR_BRAKE_HOLD);
  pros::Motor wallstake(-9);
  pros::Rotation rotation_sensor(10);
  pros::IMU imu(8);
  pros::ADIDigitalOut middlegoal('H', false);
  pros::ADIDigitalOut descore('F', false);
  pros::ADIDigitalOut scraper('B', false);
  pros::Motor intake1(3);
  pros::Motor intake2(14);
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  
  while (true) {
  
  


    chassis.tank(); // Tank control
     //chassis.arcade_standard(ez::SPLIT); // Standard split arcade
     //chassis.arcade_standard(ez::SINGLE); // Standard single arcade
     //chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
     //chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .
    // intake code
    if(master.get_digital(DIGITAL_L1)){
        intake1.move_voltage(-12000);
  }  
    
    else if(master.get_digital(DIGITAL_L2)){
        intake1.move_voltage(12000);
    }
    else{
        intake1.move_voltage(0);
    }

    if(master.get_digital(DIGITAL_R1)){
        intake2.move_voltage(12000);
  }  
    
    else if(master.get_digital(DIGITAL_R2)){
        intake2.move_voltage(-12000);
    }
    else{
        intake2.move_voltage(0);
    }



     
	if(master.get_digital_new_press(DIGITAL_X)){
      if(clamp1 == false) {
          middlegoal.set_value(true);
		  clamp1 = true;
      }	
	  else if(clamp1 == true) {
          middlegoal.set_value(false);
		  clamp1 = false;
      }
	}


  if(master.get_digital_new_press(DIGITAL_B)) {
    if(clamp2 == false) {
        descore.set_value(true);
        clamp2 = true;
      }
    else if(clamp2 == true) {
        descore.set_value(false);
        clamp2 = false;
      }
  }


  if(master.get_digital_new_press(DIGITAL_DOWN)) {
    if(clamp3 == false) {
        scraper.set_value(true);
        clamp3 = true;
      }
    else if(clamp3 == true) {
        scraper.set_value(false);
        clamp3 = false;
      }
}
  }
}