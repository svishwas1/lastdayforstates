#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor leftF = motor(PORT1, ratio6_1, true);
motor leftM = motor(PORT19, ratio6_1, true); // changed to port 16 from port 4
motor leftR = motor(PORT6, ratio6_1, true);
motor_group left = motor_group(leftF, leftM, leftR);

motor rightF = motor(PORT10, ratio6_1, false);
motor rightM = motor(PORT16, ratio6_1, false);
motor rightR = motor(PORT4, ratio6_1, false);
motor_group right = motor_group(rightF, rightM, rightR);

motor hook = motor(PORT11, ratio6_1, true);
motor intake = motor(PORT8, ratio6_1, true);

inertial iner = inertial(PORT13);
digital_out pneums = digital_out(Brain.ThreeWirePort.H);
digital_out pneums2 = digital_out(Brain.ThreeWirePort.F);
digital_out sweepPneum = digital_out(Brain.ThreeWirePort.E);
controller Controller1 = controller(primary);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void)
{
  // nothing to initialize
}