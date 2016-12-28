# Box-Joint-Jig-Control
**The software for a Box Joint jig controlled by an Arduino Due**

This software is used in a screw advance box joint jig as it s shown on the youtube video https://youtu.be/NJFSuEncSqo?list=PLBW3QMLH63V2iZNUMlxDlf6X9UJRqANAe

The project as provided here needs some extra setup work to compile, since it is dependend on other libraries. The process to compile is described in the BUILD.md file in the same directory. The process is not really complicated. Also the programming of the controller is simple and possible without deep knowledge in electronics.  

**Note:** 
This software is not a product. By compiling this software and bringing it to a concrete micro controller and operating some hardware based on this it may be used within a product. You have full responsibility over the complete product when You set up such a system. Read the license for details. 

##Contributions:
This software reqires some other open source software packages. Without the contribution of these packages the project could not have been realised. 
 
1. UTFT (Author:  Henning Karlsen under Creative Commons (CC BY-NC-SA 3.0)): for the control of the TFT display
2. URTouch  (Autor:  Henning Karlsen under Creative Commons (CC BY-NC-SA 3.0)): used for the evaluation of the touch display
3. TFT_Extension (Autor: Andrew Mascolo Jr unter MIT Lizenz): for the buttons on the display 
4. DueTimer (Autor: Ivan Seidel unter MIT Lizenz): For the generation of the signal to the Stepper motor driver by timer interrupts
5. DueFlashStorage (Autor: Sebastian Nilsson unter MIT Lizenz): To store the entered data persisitent. 
6. EFC Flash Treiber (Autor: Atmel Corporation unter ASF Lizenz): For the HW access of the DueFlashStorage module to the concrete Flash Hardware
7. LinkedList (Autor: Ivan Seidel unter MIT Lizenz): for the internal handling of the entered data and the calculated positions for the cuts.






