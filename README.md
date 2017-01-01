# Box-Joint-Jig-Control
**The software for a Box Joint jig controlled by an Arduino Due**

This software is used in a screw advance box joint jig as it s shown on the youtube video https://youtu.be/NJFSuEncSqo?list=PLBW3QMLH63V2iZNUMlxDlf6X9UJRqANAe

**Always read the License, especially the extra part on safety and the application of this software. Always read and follow the safety instructions.**   

The project as provided here needs some extra setup work to compile, since it is dependend on other libraries. The process to compile is described in the BUILD.md file in the same directory. The process is not really complicated. Also the programming of the controller is simple and possible without deep knowledge in electronics.


#Note: 
This software is not a product. By compiling this software and bringing it to a concrete micro controller and operating some hardware based on this it may be used within a product. You have full responsibility over the complete product when You set up such a system. Read the license for details.


##Step by step investment 

The process to take everything into operation is not simple. But it is also not rocket science. 

If You have some knowledge in electronics and are able to solder some cables for electronics and You know how to use a normal PC, than You have a fair chance to get erverything right. 

If You are unsure if You can do this then go step by step: 

1.  Do not buy anything. Simply follow the details in BUILD.md file till point 8. If You succeed in this, than it is only a little step to program the micro controller board and You are ready to order the Arduino Due board, the adapter and the TFT. 
2.  Once You have received the board, then You can program the board and take the software into operation. This is the most critical point: If the display shows up and You have the user interaction working, than it is relativly easy to connect the stepper motor. If You have problems with the display and also Step 10 in Build.md does not help, it is really a problem and nobody can help You with this without physical access to the setup. Till here You might have spend some 35€. This is a clear risk if You have no real in depth knowledge in electronics and computer science.  
3.  Then it is time to order a stepper motor and a driver and all the other surrounding hardware, like a power supply, etc. and to build the actual jig.       

 

#Contributions:
This software reqires some other open source software packages. Without the contribution of these packages the project could not have been realised. 
 
1. UTFT (Author:  Henning Karlsen under Creative Commons (CC BY-NC-SA 3.0)): for the control of the TFT display
2. URTouch  (Autor:  Henning Karlsen under Creative Commons (CC BY-NC-SA 3.0)): used for the evaluation of the touch display
3. TFT_Extension (Autor: Andrew Mascolo Jr under MIT License): for the buttons on the display 
4. DueTimer (Autor: Ivan Seidel under MIT License): For the generation of the signal to the Stepper motor driver by timer interrupts
5. DueFlashStorage (Autor: Sebastian Nilsson under MIT License): To store the entered data persisitent. 
6. EFC Flash Treiber (Autor: Atmel Corporation under ASF License): For the HW access of the DueFlashStorage module to the concrete Flash Hardware
7. LinkedList (Autor: Ivan Seidel under MIT License): for the internal handling of the entered data and the calculated positions for the cuts.






