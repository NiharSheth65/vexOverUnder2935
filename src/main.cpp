/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// intake               motor         9               
// rightFront           motor         4               
// rightBack            motor         10              
// leftFront            motor         18              
// leftBack             motor         20              
// flywheelRight        motor         6               
// flywheelLeft         motor         16              
// wing                 motor         13              
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


float wheelCircumfrence = 4 * 3.14;
float turnRatio = 295/ 90;
int motorSpeed = 90;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void moveCommand(float distance, int speed) {
  float motorDegrees = (distance / wheelCircumfrence) * 360;

  rightFront.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  rightBack.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                       speed, velocityUnits::pct);
  leftFront.startRotateFor(directionType::fwd, motorDegrees, rotationUnits::deg,
                         speed, velocityUnits::pct);
  leftBack.rotateFor(directionType::fwd, motorDegrees, rotationUnits::deg, speed,
                    velocityUnits::pct);
}


int rightMultiplier; 
int leftMultiplier; 

void turnCommand(float angle, int speed) {
  float motorDegrees = turnRatio * angle; 

  if(motorDegrees > 0){
    leftMultiplier = 1; 
    rightMultiplier = -1; 
  }

  else if(motorDegrees < 0){
    leftMultiplier = 1; 
    rightMultiplier = -1; 
  }

  else{
    leftMultiplier = 0; 
    rightMultiplier = 0; 
  }


  rightFront.startRotateFor(directionType::fwd, rightMultiplier * motorDegrees, rotationUnits::deg,
                        speed, velocityUnits::pct);
  rightBack.startRotateFor(directionType::fwd, rightMultiplier * motorDegrees, rotationUnits::deg,
                       speed, velocityUnits::pct);
  leftFront.startRotateFor(directionType::fwd, leftMultiplier * motorDegrees, rotationUnits::deg,
                         speed, velocityUnits::pct);
  leftBack.rotateFor(directionType::fwd, leftMultiplier * motorDegrees, rotationUnits::deg, speed,
                    velocityUnits::pct);
}


void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  turnCommand(-90, 50); 
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
  leftFront.spin(vex::directionType::fwd, Controller1.Axis2.position() - Controller1.Axis1.position(), vex::velocityUnits::pct); 
  leftBack.spin(vex::directionType::fwd, Controller1.Axis2.position() - Controller1.Axis1.position(), vex::velocityUnits::pct); 
  rightFront.spin(vex::directionType::fwd, Controller1.Axis2.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
  rightBack.spin(vex::directionType::fwd, Controller1.Axis2.position() + Controller1.Axis1.position(), vex::velocityUnits::pct); 
}

void intakeCommand(int speed){
  intake.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct); 
}

void flyWheelCommand(int speed){
  flywheelRight.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  flywheelLeft.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}

void wingCommand(int speed){
  wing.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}





int intakeSpeed  = 0; 
int flywheelSpeed = 0; 
int wingSpeed = 0; 

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

    if(Controller1.ButtonL1.pressing()){
      intakeSpeed = 100;       
    }

    else if(Controller1.ButtonR1.pressing() ){
      intakeSpeed = -100;       
    }

    // ussing intakes for flaps 
    else{
      intakeSpeed = 0; 
    }

    if(Controller1.ButtonA.pressing()){
      flywheelSpeed = 100; 
    }

    else if(Controller1.ButtonB.pressing()){
      flywheelSpeed = -100; 
    }

    else{
      flywheelSpeed = 0; 
    }

    if(Controller1.ButtonR2.pressing()){
      wingSpeed = 100; 
    }

    else if(Controller1.ButtonL2.pressing()){
      wingSpeed = -100; 
    }

    
    else{
      wingSpeed = 0; 
    }

    intakeCommand(intakeSpeed); 
    driveCommand(); 
    flyWheelCommand(flywheelSpeed); 
    wingCommand(wingSpeed); 
    
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
