/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftFront            motor         1               
// leftBack             motor         2               
// rightFront           motor         11              
// rightBack            motor         12              
// intake               motor         5               
// flyWheelLeft         motor         8               
// flyWheelRight        motor         9               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int wheelCircumfrence = 4 * 3.14; 
float turnRatio = 570 / 90;

void autoDriveCommand(float driveDistance, int speed){
  float numberOfRotations = driveDistance / wheelCircumfrence; 
  int motorDegrees = numberOfRotations * 360; 

  leftFront.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  leftBack.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                       speed, velocityUnits::pct);
  rightFront.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  rightBack.rotateFor(directionType::fwd, motorDegrees, rotationUnits::deg, speed,
                  velocityUnits::pct);
}

void autoTurnCommand(int angle, int speed){

  int numberOfDegrees = turnRatio * angle; 
  leftFront.startRotateFor(directionType::fwd, numberOfDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  leftBack.startRotateFor(directionType::fwd, numberOfDegrees, rotationUnits::deg,
                       speed, velocityUnits::pct);
  rightFront.startRotateFor(directionType::fwd, -numberOfDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  rightBack.rotateFor(directionType::fwd, -numberOfDegrees, rotationUnits::deg, speed,
                  velocityUnits::pct);
}

void autoOuttakeCommand(int durration, int outtakeSpeed){
  intake.rotateFor(directionType::fwd, durration, timeUnits::sec,
                         outtakeSpeed, velocityUnits::pct);
}


void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void driveCommand(void){
  leftFront.spin(vex::directionType::fwd, Controller1.Axis3.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
  leftBack.spin(vex::directionType::fwd, Controller1.Axis1.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
  rightFront.spin(vex::directionType::fwd, Controller1.Axis1.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
  rightBack.spin(vex::directionType::fwd, Controller1.Axis1.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
}

void intakeCommand(int speed){
  intake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct); 
}

void flyWheelCommand(int speed){
  flyWheelRight.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}


int intakeSpeed  = 0; 
int flywheelSpeed = 0; 

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    // spinning the intake fast 
    if(Controller1.ButtonL1.pressing()){
      intakeSpeed = 100;       
    }

    else if(Controller1.ButtonL1.pressing() ){
      intakeSpeed = -100;       
    }

    // ussing intakes for flaps 
    if(Controller1.ButtonR1.pressing()){
      intakeSpeed = 50; 
    }

    else if(Controller1.ButtonR2.pressing()){
      intakeSpeed = -50;
    }

    else{
      intakeSpeed = 0; 
    }

    if(Controller1.ButtonA.pressing()){
      flywheelSpeed = 100; 
    }

    else{
      flywheelSpeed = 0; 
    }

    intakeCommand(intakeSpeed); 
    driveCommand(); 
    flyWheelCommand(flywheelSpeed); 

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
