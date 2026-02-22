#The build process


To build the project the following steps have to be taken (Windows 10): 

1. Install VSCode
2. Install the Platform IO Plugin. (PlatformIO IDE)
3. Go to this GitHub page. 
	*   Go to the main page of this project: [https://github.com/eschlot/Box-Joint-Jig-Control]
	*   Click on "Clone or Download"
	*   Click on Download ZIP
	*   Extract the zip file 
4. Use the option "Project Open" to open the directory in which the platformio.ini file is located.
5. Build the project.
6. Program the Board:
	* Connect Your Board by USB: Use the Port at the Due Board named "Programming Port"
	* Go to "Upload". If that succeeds, the Controller is ready to go. 
		
7. If the TFT only lights up, but does not show anything, then You have most probably a different TFT driver chip on Your display. As a consequence comment line 99 in the file PositionControl.ino and uncomment line 98. Go to step 5 and repeat the process. Good luck. 
	* **If all this fails, than You are in trouble. The sources of errors for the display are numerous and it might be a contact problem or the wrong driver, or ... The only thing You can do is to search the internet for a solution and to debug the display driver.**  
	
 

