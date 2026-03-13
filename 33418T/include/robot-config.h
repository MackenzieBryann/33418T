using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:
extern motor LeftFront;
extern motor LeftMid;
extern motor LeftBack;
extern motor RightFront;
extern motor RightMid;
extern motor RightBack;
extern motor Intake;
extern motor Lever;
extern controller Controller1;
extern digital_out Frame;
extern digital_out Tounge;
extern digital_out Wing;
extern digital_out Hood;

void  vexcodeInit( void );