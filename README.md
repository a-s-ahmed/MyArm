# Emulate Arm Motion On Robotic Arm: HACKED 2020 
# Best Hardware Project Winner and 2nd Overall!

Group Members: Dawood Ali, Amro Amanuddein, and Portia Rayner

Create a lasercut robotic arm which can remotely emulate your own within 24 hours

The physical arm itself is actually the MeArm (https://www.instructables.com/id/Pocket-Sized-Robot-Arm-meArm-V04/) which we lasercut and assembled for the competition. Massive shout out to Dejan author of the article "Arduino and MPU6050 Accelerometer and Gyroscope Tutorial" (https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/) which showcases a way to use the accelerometer to create a gimbal with the mpu6050. After researching further, this project may have some similarities with gesture controlled robotic arms, but our implementation with multiple accelerometers allows for true motion control. The difference is explained more within running instructions.  We based this code off of the tutorial in Dejan's article as well as this article about how to use the mpu6050 (https://playground.arduino.cc/Main/MPU-6050/#short). 


# Components:

For Initial Design:
      
      1 x V1 folder
      
      1 x MPU6050 (accelerometer and gyroscope)

      1 x 330 Ohm Resistor

      1 x Green LED

     
For Final Design:
      
      1 x V2 folder.
      
      2 x MPU6050 (accelerometer and gyroscope)
      
      1 x Arduino Uno
      
      
For both:

      1 x Glove

      1 x arduino Mega2560

      1 x One square foot of acrylic (And access to a lasercutter)

      1 x Grove Touch Sensor (and its respective cord)

      TOBEFILLED IN x male-to-male wires

      TOBEFILLED IN x female to male wires

# Wiring Instructions

To be filled in.

# Running Instructions V1:
*This build is completely wired.*

Connect the arduino to your computer via usb and upload winning_project.ino. Rotate your arm (about the axis from your wrist to your elbow) to rotate the base, this could be considered roll. Raise/drop your arm about the perpendicular axis or raise/drop your wrist to control the main arm. Rotate your wrist up/down for 4-5 seconds to change modes (The LED should light up) and now you can control the smaller part of the arm for finer vertical motion. Touch the your index finger to the touch sensor on your thumb to close the claw. Pictures and/or videos coming soon!

# Running Instructions V2:
*This build allows for wireless motion emulation*

This is the wireless version where we overhauled the motion-sensing and no longer require two modes. We didnt have access to a touch sensor so minor modification is necessary to implement that. Control the main arm by moving your whole arm. For example, rotate your arm to rotate the base. Control the secondary joint with your wrist.
 
