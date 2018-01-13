// NEONATAL ANIMATRONIC NEWBORN OFFSPRING
//=======================================================================//
//====================--- I N N E R B R E E D F X ---====================//
// Project; NANO Baby (Base Code)                                        //
//  Description: http://www.innerbreed.co.uk                             //
//   Version: V1.0                                                       //
//    Start Date: 24/12/2017                                             //
//     Last Edit Date: 11/01/2018                                        //
//      Developer/s: Jonny Poole (aka Innerbreed)                        // 
//                                                                       //
// FEATURES: Servo Easing applied for joint compliance.                  //
//=======================================================================//
//=======================================================================//

// Engineer / Developers notes:
// ServoEaser library for Arduino
// ==============================
// 2011, TeamPneumo, Tod E. Kurt, http://todbot.com/blog/
// ServoEaser is an Arduino library makes doing animation-style movements with
// servos easier.

// Features:
// - Supports directly telling a servo to ease to a position over a duration
// - Supports playing of previously-defined "move lists"
// - User-specified easing functions (defaults to easeInOutCubic), see Easing lib
// - User-specified "servo arrived" function for async callback when movement done
// - Supports both integer angle movement and a "microseconds" mode for fine-grained control with float-ing point angles

// License
// Copyright © 2018 by Jonny Poole. All right reserved. 

//----------------
// HEADER FILES
#include <Servo.h>
#include "ServoEaser.h"

//----------------
// SERVO NAMES (Defined)              (15 Servos in total)
   Servo Blink;                     // Right and Left run together 2x(hs65hb)
   Servo Jaw;                       // 1x(hs65hb)
   Servo Lip;                       // 1x(hs65hb)
   Servo Neck_Tilt_Left;            // Combines with (Neck_Tilt_Right) to lift head 1x(hs65mg)
   Servo Neck_Tilt_Right;           // Combines with (Neck_Tilt_Left) to lift head 1x(hs65mg)
   Servo Head_Rotate;               // 1x(hs645mg)
   Servo Left_Elbow_ShoulderRoll;   // 1x(hs311) and 1x(hs65hb)
   Servo Right_Elbow_ShoulderRoll;  // 1x(hs311) and 1x(hs65hb)
   Servo Right_ShoulderUp;          // 1x(hs65hb)
   Servo Left_ShoulderUp;           // 1x(hs65hb)
   Servo Legs;                      // Right and left run together 2x(hs311)

//----------------
// SERVO EASER (Defined)
ServoEaser BlinkEaser;         // Set up ServoEaser for each servo
ServoEaser JawEaser;
ServoEaser LipEaser;
ServoEaser Neck_Tilt_LeftEaser;
ServoEaser Neck_Tilt_RightEaser;
ServoEaser Head_RotateEaser;
ServoEaser Left_Elbow_ShoulderRollEaser;
ServoEaser Right_Elbow_ShoulderRollEaser;
ServoEaser Right_ShoulderUpEaser;
ServoEaser Left_ShoulderUpEaser;
ServoEaser LegsEaser;

//----------------
// INTERNAL CLOCK
int servoFrameMillis = 10;     // Minimum time in m/s between servo updates
unsigned long lastMillis; 

//---------------------------------------------------------------
// INITIAL SET UP
void setup(){
       // Initialize digital pin LED_BUILTIN as an output.
       pinMode(LED_BUILTIN, OUTPUT);
     
// ATTACHED SERVOS ServoName.attach(Pin);
     Blink.attach(2);                   
     Jaw.attach(3); 
     Lip.attach(4); 
     Neck_Tilt_Left.attach(5); 
     Neck_Tilt_Right.attach(6); 
     Head_Rotate.attach(7); 
     Left_Elbow_ShoulderRoll.attach(8); 
     Right_Elbow_ShoulderRoll.attach(9);
     Right_ShoulderUp.attach(10); 
     Left_ShoulderUp.attach(11); 
     Legs.attach(12);

     // Initiate blink upon power-up to show that the mech is active
     // Active LED for engineers attention
     Blink.write(115);                   // Closed
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
        delay(120);  
     Blink.write(80);                    // Opened
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
        delay(750);
     Blink.write(115);                   // Closed
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
        delay(120);
     Blink.write(80);                    // Opened
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
        delay(500);
     Blink.write(115);                   // Closed
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
        
//----------------     
// CALL EASING PARAMETERS
  BlinkEaser.begin( Blink, servoFrameMillis);   // Begin servo moves
  JawEaser.begin( Jaw, servoFrameMillis);
  LipEaser.begin( Lip, servoFrameMillis);
  Neck_Tilt_LeftEaser.begin( Neck_Tilt_Left, servoFrameMillis);
  Neck_Tilt_RightEaser.begin( Neck_Tilt_Right, servoFrameMillis);
  Head_RotateEaser.begin( Head_Rotate, servoFrameMillis);
  Left_Elbow_ShoulderRollEaser.begin( Left_Elbow_ShoulderRoll, servoFrameMillis);
  Right_Elbow_ShoulderRollEaser.begin( Right_Elbow_ShoulderRoll, servoFrameMillis);
  Right_ShoulderUpEaser.begin( Right_ShoulderUp, servoFrameMillis); 
  Left_ShoulderUpEaser.begin( Left_ShoulderUp, servoFrameMillis);
  LegsEaser.begin( Legs, servoFrameMillis);
  
  BlinkEaser.useMicroseconds( true );           // Start timer
  JawEaser.useMicroseconds( true ); 
  LipEaser.useMicroseconds( true ); 
  Neck_Tilt_LeftEaser.useMicroseconds( true );  
  Neck_Tilt_RightEaser.useMicroseconds( true );
  Head_RotateEaser.useMicroseconds( true );  
  Left_Elbow_ShoulderRollEaser.useMicroseconds( true ); 
  Right_Elbow_ShoulderRollEaser.useMicroseconds( true );
  Right_ShoulderUpEaser.useMicroseconds( true ); 
  Left_ShoulderUpEaser.useMicroseconds( true );
  LegsEaser.useMicroseconds( true );  
  
  BlinkEaser.easeTo( 90, 5000);                 // Eases to given random angle and speed
  JawEaser.easeTo( 90, 5000);
  LipEaser.easeTo( 90, 5000);
  Neck_Tilt_LeftEaser.easeTo( 90, 5000);
  Neck_Tilt_RightEaser.easeTo( 90, 5000);
  Head_RotateEaser.easeTo( 90, 5000);
  Left_Elbow_ShoulderRollEaser.easeTo( 90, 5000);
  Right_Elbow_ShoulderRollEaser.easeTo( 90, 5000);
  Right_ShoulderUpEaser.easeTo( 90, 5000);
  Left_ShoulderUpEaser.easeTo( 90, 5000);
  LegsEaser.easeTo( 90, 5000);
}

//---------------------------------------------------------------
// MAIN CODE
void loop()
{
// UPDATE SERVO POSITION
   BlinkEaser.update();                        
   JawEaser.update();  
   LipEaser.update();
   Neck_Tilt_LeftEaser.update();
   Neck_Tilt_RightEaser.update();
   Head_RotateEaser.update();
   Left_Elbow_ShoulderRollEaser.update();
   Right_Elbow_ShoulderRollEaser.update();
   Right_ShoulderUpEaser.update();
   Left_ShoulderUpEaser.update();
   LegsEaser.update();

ALIVE();
  }

//---------------- 
void ALIVE() // ITS MAGIC TIME  
{

  if( BlinkEaser.hasArrived() ) {                    // BLINK EYES
    lastMillis = millis();                            // Timer count
    int angle    = random(80,120);                     // Servo operating angle: 0 - 180
    int duration = random(100,2000);                    // Speed of rotation min/max 
    BlinkEaser.easeTo( angle, duration );                // Eases to given random angle and speed
  }     
  if( JawEaser.hasArrived() ) {                      // JAW
    lastMillis = millis();
    int angle    = random(50,110);
    int duration = random(200,3000);
    JawEaser.easeTo( angle, duration );
  }
    if( LipEaser.hasArrived() ) {                    // LIP
    lastMillis = millis();
    int angle    = random(60,90);
    int duration = random(200,1000);
    LipEaser.easeTo( angle, duration );
  }
    if( Neck_Tilt_LeftEaser.hasArrived() ) {         // NECK TILT LEFT
    lastMillis = millis();
    int angle    = random(60,90);
    int duration = random(200,1500);
    Neck_Tilt_LeftEaser.easeTo( angle, duration );
  }
    if( Neck_Tilt_RightEaser.hasArrived() ) {        // NECK TILT RIGHT
    lastMillis = millis();
    int angle    = random(90,110);
    int duration = random(200,1500);
    Neck_Tilt_RightEaser.easeTo( angle, duration );
  }
    if( Head_RotateEaser.hasArrived() ) {            // HEAD ROTATE
    lastMillis = millis();
    int angle    = random(30, 150);
    int duration = random(800,3500);
    Head_RotateEaser.easeTo( angle, duration );
  }
   if( Left_Elbow_ShoulderRollEaser.hasArrived() ) { // SHOULDER ROLL and ELBOW LEFT
    lastMillis = millis();
    int angle    = random(70, 90);
    int duration = random(200,2000);
    Left_Elbow_ShoulderRollEaser.easeTo( angle, duration );
  }
    if( Right_Elbow_ShoulderRollEaser.hasArrived() ) {// SHOULDER ROLL and ELBOW RIGHT
    lastMillis = millis();
    int angle    = random(80, 105);
    int duration = random(200,2000);
    Right_Elbow_ShoulderRollEaser.easeTo( angle, duration );
  }
    if( Right_ShoulderUpEaser.hasArrived() ) {       // SHOULDER UP RIGHT
    lastMillis = millis();
    int angle    = random(80, 140);
    int duration = random(200,1500);
    Right_ShoulderUpEaser.easeTo( angle, duration );
  }
    if( Left_ShoulderUpEaser.hasArrived() ) {        // SHOULDER UP LEFT
    lastMillis = millis();
    int angle    = random(40, 110);
    int duration = random(200,1500);
    Left_ShoulderUpEaser.easeTo( angle, duration );
  }
    if( LegsEaser.hasArrived() ) {                   // LEGS
    lastMillis = millis();
    int angle    = random(180);
    int duration = random(200,5000);
    LegsEaser.easeTo( angle, duration );
  }
}

// License
// Copyright © 2018 by Jonny Poole. All right reserved. 

