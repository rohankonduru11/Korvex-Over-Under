#include "main.h"
#include <fstream>

using namespace std;

void wait(int sec) {
  pros::delay(sec);
}

void intake() {
  bottomstage.move_voltage(-12000);
  middlestage.move_voltage(12000);
  topstage.move_voltage(12000);
}

void outtake() {
  bottomstage.move_voltage(12000);
  middlestage.move_voltage(-12000);
  topstage.move_voltage(-12000);
}

void stopIntake() {
  bottomstage.move_voltage(0);
  middlestage.move_voltage(0);
  topstage.move_voltage(0);
}
void middlegoal(){
  bottomstage.move_voltage(-12000);
  middlestage.move_voltage(12000);
  topstage.move_voltage(-12000);
}