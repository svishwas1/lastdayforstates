#include "vex.h"
#include <string>
using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

    // Specify your drive setup below. There are seven options:
    // ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
    // For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
    ZERO_TRACKER_NO_ODOM,

    // Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
    // You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

    // Left Motors:
    motor_group(leftF, leftM, leftR),

    // Right Motors:
    motor_group(rightF, rightM, rightR),

    // Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
    PORT13,

    // Input your wheel diameter. (4" omnis are actually closer to 4.125"):
    3.25,

    // External ratio, must be in decimal, in the format of input teeth/output teeth.
    // If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
    // If the motor drives the wheel directly, this value is 1:
    0.75,

    // Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
    // For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
    360,

    /*---------------------------------------------------------------------------*/
    /*                                  PAUSE!                                   */
    /*                                                                           */
    /*  The rest of the drive constructor is for robots using POSITION TRACKING. */
    /*  If you are not using position tracking, leave the rest of the values as  */
    /*  they are.                                                                */
    /*---------------------------------------------------------------------------*/

    // If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

    // FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
    // LF:      //RF:
    PORT1, -PORT2,

    // LB:      //RB:
    PORT3, -PORT4,

    // If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
    // If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
    // If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
    3,

    // Input the Forward Tracker diameter (reverse it to make the direction switch):
    2.75,

    // Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
    // For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
    // This distance is in inches:
    -2,

    // Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
    1,

    // Sideways tracker diameter (reverse to make the direction switch):
    -2.75,

    // Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
    5.5

);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while (auto_started == false)
  {                             // Changing the names below will only change their names on the
    Brain.Screen.clearScreen(); // brain screen for auton selection.
    switch (current_auton_selection)
    { // Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "Skills Auton");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Right Auton");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Left Auton");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Match Auton");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Match Auton2" );
        break;
      /*case 4:
        Brain.Screen.printAt(50, 50, "Full Test");
        break;
      case 5:
        Brain.Screen.printAt(50, 50, "Odom Test");
        break;
      case 6:
        Brain.Screen.printAt(50, 50, "Tank Odom Test");
        break;
      case 7:
        Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
        break;*/
    }
    if (Brain.Screen.pressing())
    {
      while (Brain.Screen.pressing())
      {
      }
      current_auton_selection++;
    }
    else if (current_auton_selection == 8)
    {
      current_auton_selection = 0;
    }
    wait(10, msec);
  }
}

void autonomous(void)
{
  auto_started = true;
  switch (current_auton_selection)
  {
  case 0:
    matchauton_red_left_four();
    break;
  case 1:
    skills_462B();
    break;
  case 2:
    right_auton_462B();
    break;
  case 3: 
    left_auton_462B();
    break;
  case 4:
    matchauton_blue_right_four();
    break;
  }
}

std::string detectColor(void) {
   
    int red = ColorSensor.rgb() >> 16 & 0xFF;  // Extract Red value (0-255)
    int green = ColorSensor.rgb() >> 8 & 0xFF; // Extract Green value (0-255)
    int blue = ColorSensor.rgb() & 0xFF;       // Extract Blue value (0-255)
    int brightness = ColorSensor.brightness() * 100; // Convert to percentage (0-100)

    // Display detected values on the Brain screen
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("R: %d G: %d B: %d Brightness: %d", red, green, blue, brightness);

    // Determine the dominant color using RGB values
    if (red > green && red > blue && brightness > 20) {
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print("Detected: RED");
        return "RED";
    } 
    else if (blue > red && blue > green && brightness > 20) {
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print("Detected: BLUE");
        return "BLUE";
    }
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

void usercontrol(void)
{
  bool pneumButtonPress = false;
  bool pneumButtonPress2 = false;
  bool pneumButtonPress3 = false;
  //float a, d;
  // User control code here, inside the loop
  while (1)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // Chassis:
    // if (Controller1.ButtonB.pressing() && !pneumButtonPress2)
    // {
    //   pneumButtonPress2 = true;
    //   pneums2.set(!pneums2.value());
    // }
    // else if (!Controller1.ButtonB.pressing())
    // {
    //   pneumButtonPress2 = false;
    // }

    //both spin
      
    if (Controller1.ButtonR2.pressing())
    {
      hook.spin(fwd, 100, percent);
      intake.spin(reverse, 100, percent);
       if (detectColor() == "RED") {
        hook.stop();
      

      }
    }
    else if (Controller1.ButtonR1.pressing())
    {
      hook.spin(reverse, 100, percent);
      intake.spin(fwd, 100, percent);
    }
    else
    {
      hook.stop(hold);
      intake.stop(hold);
    }

    //individual spin
    // if (Controller1.ButtonL2.pressing())
    // {
    //   hook.spin(fwd, 100, percent);
    // }
    // else if (Controller1.ButtonL1.pressing())
    // {
    //   intake.spin(reverse, 100, percent);
    // }
    // else
    // {
    //   hook.stop(hold);
    //   intake.stop(hold);
    // }

    // Pneumatics:
    if (Controller1.ButtonA.pressing() && !pneumButtonPress)
    {
      pneumButtonPress = true;
      pneums.set(!pneums.value());
    }
    else if (!Controller1.ButtonA.pressing())
    {
      pneumButtonPress = false;
    }

    // sweeeeeeeep
    if (Controller1.ButtonX.pressing() && !pneumButtonPress3)
    {
      pneumButtonPress3 = true;
      sweepPneum.set(!sweepPneum.value());
    }
    else if (!Controller1.ButtonX.pressing())
    {
      pneumButtonPress3 = false;
    }

    // Replace this line with chassis.control_tank(); for tank drive
    // or chassis.control_holonomic(); for holo drive.
    chassis.control_tank();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
   // Run the pre-autonomous function.
  pre_auton();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(50, msec);
  }
}
