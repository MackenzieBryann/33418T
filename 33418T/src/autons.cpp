#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(270);
  chassis.right_swing_to_angle(90);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    //task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

void parking(){
Tounge.set(false);
Frame.set(false);
Intake.setVelocity(100, percent);
chassis.drive_distance(-10);
chassis.drive_distance(30);
chassis.drive_distance(5);
chassis.drive_distance(-5);
chassis.drive_distance(10);
chassis.drive_distance(-6);
Intake.spin(reverse);
wait(1, sec);
Intake.stop(coast);
}

void comp_auton_rightside(){
  //setup
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  Intake.setVelocity(100, percent);
  chassis.set_swing_exit_conditions(.5, 200, 1000);
  Lever.setVelocity(100, percent);
  double leverpos = Lever.position(rev);
  //grab right three
  chassis.drive_distance(9);
  chassis.left_swing_to_angle(50);
  Intake.spin(reverse);
  chassis.drive_distance(6);
  chassis.drive_distance(6, 45, 3, 3);
  //dispense into bottom goal
  chassis.drive_distance(4);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(11);
  Intake.setVelocity(70, percent);
  Intake.spin(forward);
  wait(1700, msec);
  //go to right loader
  Intake.setVelocity(100, percent);
  chassis.drive_distance(-43);
  chassis.turn_to_angle(181);
  chassis.drive_distance(-5);
  Tounge.set(true);
  wait(300, msec);
  Intake.spin(reverse);
  chassis.drive_distance(13.5, 181);
  wait(100, msec);
  Frame.set(false);
  chassis.set_turn_exit_conditions(0.1, 200, 1000);
  chassis.turn_to_angle(183);
  //go to long goal
  chassis.drive_distance(-30, 180);
  Hood.set(true);
  Lever.spin(reverse);
  wait(1000, msec);
  Lever.spinToPosition(.85, rev);


}

void comp_auton_leftside(){

}

//lever position at top = -1.75 rev
//lever position at bottom = .7 rev

void comp_auton_skills(){
  //setup
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  Intake.setVelocity(100, percent);
  chassis.set_swing_exit_conditions(.1, 200, 1500);
  Lever.setVelocity(100, percent);
  double leverpos = Lever.position(rev);
  //close right loader
  chassis.drive_distance(37.35);
  Tounge.set(true);
  chassis.turn_to_angle(90);
  Intake.spin(reverse);
  chassis.drive_distance(10);
 wait(200, msec);
  chassis.drive_distance(-3);
  chassis.drive_distance(6);
  wait(200, msec);
  chassis.drive_distance(-4);
  chassis.drive_distance(6.1);
  wait(1.1, sec);
  chassis.drive_distance(-10);
  Tounge.set(false);
  Frame.set(false);
  wait(500, msec);
  chassis.right_swing_to_angle(267.3);
  Intake.stop();
  // drive to far side long goal
  chassis.drive_distance(90, 267.2);
  chassis.set_swing_exit_conditions(1, 300, 3000);
  chassis.right_swing_to_angle(350);
  chassis.drive_distance(1);
  chassis.set_swing_exit_conditions(1, 300, 1500);
  chassis.left_swing_to_angle(268);
  Hood.set(true);
  chassis.drive_distance(-15);
  // dispense into far side long goal
  Intake.spin(reverse);
  wait(200, msec);
  chassis.drive_distance(-1);
  Lever.spin(reverse);
  wait(1000, msec);
  if (leverpos >  -1.3){
    Intake.spin(forward);
    wait(400, msec);
    Intake.spin(reverse);
  }
  wait(1000, msec);
  Lever.spin(forward);
  wait(250, msec);
  Lever.spin(reverse);
  Tounge.set(true);
  wait(1000, msec);
  Lever.spinToPosition(.85, rev);
  // far right loader
  Frame.set(true);
  Hood.set(false);
  chassis.drive_distance(27, 267, 6, 6);
  wait(200, msec);
  chassis.drive_distance(-3);
  chassis.drive_distance(6);
  wait(200, msec);
  chassis.drive_distance(-4);
  chassis.drive_distance(6.2);
  wait(1.1, sec);
  // go to far side long goal
  Intake.stop();
  chassis.drive_distance(-20, 270);
  Frame.set(false);
  Hood.set(true);
  wait(400, msec);
  chassis.drive_distance(-10, 270);
  // dispense into far side long goal
  Intake.spin(reverse);
  wait(200, msec);
  chassis.drive_distance(-1);
  Lever.spin(reverse);
  wait(1000, msec);
  if (leverpos >  -1.3){
    Intake.spin(forward);
    wait(400, msec);
    Intake.spin(reverse);
  }
  wait(1000, msec);
  Lever.spin(forward);
  wait(200, msec);
  Lever.spin(reverse);
  Tounge.set(true);
  wait(1000, msec);
  Lever.spinTo(.85, rev);
  //clear parking zone
  Tounge.set(false);
  Intake.spin(forward);
  chassis.drive_distance(7);
  chassis.drive_distance(28, 230);
  chassis.set_swing_exit_conditions(1, 200, 900);
  chassis.right_swing_to_angle(160);
  chassis.drive_distance(-12, 169);
  chassis.turn_to_angle(180);
  chassis.drive_distance(79, 183.5, 12, 12);
  chassis.drive_distance(-10);
  //far left loader
  chassis.right_swing_to_angle(140);
  chassis.drive_distance(32, 140);
  Tounge.set(true);
  chassis.turn_to_angle(270);
  Intake.spin(reverse);
  wait(200, msec);
  chassis.drive_distance(33);
  wait(500, msec);
  chassis.drive_distance(-3);
  chassis.drive_distance(6);
  wait(400, msec);
  chassis.drive_distance(-4);
  chassis.drive_distance(6);
  wait(400, sec);
  chassis.drive_distance(-4);
  chassis.drive_distance(6);
  wait(400, sec);
  chassis.drive_distance(-12);
  Tounge.set(false);
  Intake.spin(forward);
  // go to parking space
  chassis.left_swing_to_angle(84);
  chassis.drive_distance(80, 87);
  chassis.set_swing_exit_conditions(1.5, 100, 1000);
  chassis.right_swing_to_angle(0);
  chassis.drive_distance(-15, 10);
  chassis.turn_to_angle(0);
  chassis.drive_distance(40, 1, 12, 12);
  chassis.drive_distance(5);
  chassis.drive_distance(-5);
  chassis.drive_distance(10);
  chassis.drive_distance(-6);

}
