#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);
motor LeftFront = motor(PORT5, ratio6_1, true);
motor LeftMid = motor(PORT6, ratio6_1, true);
motor LeftBack = motor(PORT7, ratio6_1, true);
motor RightFront = motor(PORT8, ratio6_1, false);
motor RightMid = motor(PORT9, ratio6_1, false);
motor RightBack = motor(PORT10, ratio6_1, false);
motor Intake = motor(PORT20, ratio6_1, false);
motor Lever = motor(PORT1, ratio6_1, true);
digital_out Frame = digital_out(Brain.ThreeWirePort.A);
digital_out Tounge = digital_out(Brain.ThreeWirePort.B);
digital_out Wing = digital_out(Brain.ThreeWirePort.D);
digital_out Hood = digital_out(Brain.ThreeWirePort.C);
controller Controller1 = controller(primary);


//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}