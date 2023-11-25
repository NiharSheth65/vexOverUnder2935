#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor intake = motor(PORT9, ratio18_1, false);
motor rightFront = motor(PORT4, ratio18_1, true);
motor rightBack = motor(PORT10, ratio18_1, true);
motor leftFront = motor(PORT18, ratio18_1, false);
motor leftBack = motor(PORT20, ratio18_1, false);
motor flywheelRight = motor(PORT6, ratio6_1, true);
motor flywheelLeft = motor(PORT16, ratio6_1, false);
motor wing = motor(PORT13, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}