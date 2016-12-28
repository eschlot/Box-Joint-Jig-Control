#The build process


To build the project the following steps have to be taken (Windows 10): 

1. Install Arduino Software Version 1.8.0 from [https://www.arduino.cc/en/Main/Software]
2. Start the Arduino software and go to Tools->Board->Board Manager
	*   Search for "Due" in the Board Manager
	*   install version 1.6.10 of "Arduino SAM Boards (32-bits ARM Cortex-M3) by Arduino"
	*   Close the window
3. Go to this GitHub page. 
	*   Go to the main page of this project: [https://github.com/eschlot/Box-Joint-Jig-Control]
	*   Click on "Clone or Download"
	*   Click on Download ZIP
	*   Move the zip file to C:\Users\<Your user>\OneDrive\Dokumente\Arduino and extract it. You should get something like C:\Users\<Your user>\OneDrive\Dokumente\Arduino\Box-Joint-Jig-Control-master\PositionControl\PositionControl as a result. **Note:** Earlier versions of windows use c:\Users\<your user>\Documents\Arduino or similar as a base.   
4. Go to [http://www.rinkydinkelectronics.com/library.php?id=51] 
	* Download UTFT library version 2.82
	* Save the UTFT.zip in Your download folder. 
5. Go to [http://www.rinkydinkelectronics.com/library.php?id=92]
	* Download URTouch library version 2.01
	* Save the URTouch.zip in Your download folder.
6. Go to [https://github.com/eschlot/TFT_Extension/tree/URTouch-update] **Note:** I hope this is a temporary solution as it is a branch of the original implementation of Andrew Mascolo.
	*   Click on "Clone or Download"
	*   Click on Download ZIP		
7. Go back to the Arduino Software and 
	*  open the File C:\Users\<Your user>\OneDrive\Dokumente\Arduino\Box-Joint-Jig-Control-master\PositionControl\PositionControl\PositionControl.ino
	*  Go to Tools->Board and select "Arduino Due (Programming Port)" as Your board.
	*  Go to Sketch->Include Library->Manage Libraries
		* Type "duetimer" into the search field and install version 1.4.7	
		* Type "dueflashstorage" into the search field and install version 1.0.0
	* Go to Sketch->Include Library->Add .ZIP Library
		* select the **UTFT.zip** downloaded before
	* Go to Sketch->Include Library->Add .ZIP Library
		* select the **URTouch.zip** downloaded before
	* Go to Sketch->Include Library->Add .ZIP Library
		* select the **TFT_Extension-URTouch-update.zip** downloaded before
8. Compile:
	* Click Sketch->Verify/Compile: If You get the message "Sketch uses 97392 bytes (18%) of program storage space. Maximum is 524288 bytes." or similar, then the complete compilation process went fine and You are ready to program Your Arduino Due Board.
9. Program the Board:
	* Connect Your Board by USB: Use the Port at the Due Board named "Programming Port"
	* Go to Tools->Port and select the right COM-Port
	* Go to Sketch->Upload. If that succeeds, the Controller is ready to go. 
		
10. If the TFT only lights up, but does not show anything, then You have most probably a different TFT driver chip on Your display. As a consequence comment line 99 in the file PositionControl.ino and uncomment line 98. Go to step 8 and repeat the process. Good luck. 
	* If all this fails, than You are in trouble. The sources of errors for the display are numerous and it might be a contact problem or the wrong driver, or ... The only thing You can do is to search the internet for a solution and to debug the display driver.  
	
 

