#include "headersC.h"
#include "globalMembers.h"
#include "initValues.h"
#include "testPrintValues.h" // used only for debugging
#include "shareFunctions.h"
#include "algoFunctions.h"
#include "botFunctions.h"

int completePathA(char driver, char str[]) {
	int temp;
	startBot(driver);
	while (pathLenA > 0) {
		pathLenA--;
		while (botA[pathLenA].subPathCount > 0) {
			botA[pathLenA].subPathCount--;
			// if (botAstat.ready == 0) {
			// 	stopBot("Obstacle", driver);
			// 	botBstat.ready = 0;
			// 	while (botAstat.ready == 0);
			// 	return 0;
			// }
			if (obstacleDetect()) {
				setObstacle(botAstat.node, botA[pathLenA].subPath[ botA[pathLenA].subPathCount ]);
				botBstat.ready = 0;
				while (botAstat.ready == 1);
				updatePaths("test");
				return 0;
			}
			temp = botAstat.node;
			// printf("Status: Bot A %d Bot B %d\n", botA[pathLenA].subPath[ botA[pathLenA].subPathCount ], botBstat.node);
			if (botA[pathLenA].subPath[ botA[pathLenA].subPathCount ] == botBstat.node) {
				stopBot("Collision", driver);
				while (botA[pathLenA].subPath[ botA[pathLenA].subPathCount ] == botBstat.node) {
					// if (botAstat.ready == 0) {
					// 	stopBot("Obstacle", driver);
					// 	botBstat.ready = 0;
					// 	while (botAstat.ready == 0);
					// 	return 0;
					// }
					updateShareA(str);
				}
				startBot(driver);
			}
			botAstat.node = botA[pathLenA].subPath[ botA[pathLenA].subPathCount ];
			updateShareA(str);
			goFromTo(temp, botAstat.node, driver);
		}
		while (botA[pathLenA].note != notes[noteCount-1]) {
			// if (botAstat.ready == 0) {
			// 	stopBot("Obstacle", driver);
			// 	botBstat.ready = 0;
			// 	while (botAstat.ready == 0);
			// 	return 0;
			// }
			updateShareA(str);
		}
		printf("A played %d\n", notes[noteCount-1]);
		noteCount--;
		playNote(driver);
		str[2]++;
	}
	botAstat.ready = 2;
	stopBot("Completed", driver);
	return 1;
}

int completePathB(char driver, char str[]) {
	int temp;
	startBot(driver);
	while (pathLenB > 0) {
		pathLenB--;
		while (botB[pathLenB].subPathCount > 0) {
			updateShareB(str);
			botB[pathLenB].subPathCount--;
			// if (botBstat.ready == 0) {
			// 	stopBot("Obstacle", driver);
			// 	botBstat.ready = 0;
			// 	while (botBstat.ready == 0);
			// 	return 0;
			// }
			if (obstacleDetect()) {
				setObstacle(botBstat.node, botB[pathLenB].subPath[ botB[pathLenB].subPathCount ]);
				botBstat.ready = 0;
				while (botBstat.ready == 1);
				updatePaths("test");
				return 0;
			}
			temp = botBstat.node;
			// printf("Status: Bot A %d Bot B %d\n", botAstat.node, botB[pathLenB].subPath[ botB[pathLenB].subPathCount ]);
			if (botB[pathLenB].subPath[ botB[pathLenB].subPathCount ] == botAstat.node) {
				stopBot("Collision", driver);
				while (botB[pathLenB].subPath[ botB[pathLenB].subPathCount ] == botBstat.node) {
					// if (botBstat.ready == 0) {
					// 	stopBot("Obstacle", driver);
					// 	botBstat.ready = 0;
					// 	while (botBstat.ready == 0);
					// 	return 0;
					// }
					updateShareB(str);
				}
				startBot(driver);
			}
			botBstat.node = botB[pathLenB].subPath[ botB[pathLenB].subPathCount ];
			updateShareB(str);
			goFromTo(temp, botBstat.node, driver);
		}
		while (botB[pathLenB].note != notes[noteCount-1]) {
			// if (botBstat.ready == 0) {
			// 	stopBot("Obstacle", driver);
			// 	botBstat.ready = 0;
			// 	while (botBstat.ready == 0);
			// 	return 0;
			// }
			updateShareB(str);
		}
		printf("B played %d\n", notes[noteCount-1]);
		noteCount--;
		playNote(driver);
		str[6]++;
	}
	botBstat.ready = 2;
	stopBot("Completed", driver);
	return 1;
}

int main() {
	int shmid;
	pid_t pid,pid2;
	int n;
	char *str;
	initBotDevices();
	if((shmid = shmget(IPC_PRIVATE,10 * sizeof(char),0666))<0){
		printf("error in creating shmid\n");
		return 0;
	}
	str = shmat(shmid, NULL, 0);
	int p = fork();
	if (p) {
		initValues();
		initShare(str);
		updatePaths(str);
		changeReadyA(str, 1);
		changeReadyB(str, 1);
		while (botAstat.ready != 2 || botBstat.ready != 2) {
			while (botAstat.ready != 1 && botBstat.ready != 2);
			while (!completePathA('A', str));
		}
		return 0;
	} else {
		initValues();
		botBstat.node = 12;
		do {
			updateShareB(str);
		} while (botBstat.ready == 0);
		while (botAstat.ready != 2 || botBstat.ready != 2) {
			while (botBstat.ready != 1 && botAstat.ready != 2);
			while (!completePathB('B', str));
		}
		return 0;
	}
}

// int printNsetDJ(void)
// {
// 	int djFlag=0,Sharp;
// /****djFlag is an important variable. It holds the information for line following
// 	 djFlag=10 when the bot is exactly on the black line
// 	 djFlag=100 when the bot is tilted towards the right
// 	 djFlag=1 when the bot is tilted toward the left
// 	 It takes other values depending on number of sensors is in and out of the line
// */
// /* 	 Sharp holds the Sharp sensor adc value*/
// 	Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
// 	Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
// 	Right_white_line = ADC_Conversion(1);   //Getting data of Right WL Sensor
// 	Sharp=ADC_Conversion(11);
// 	djFlag = 0;
// 	distance_Sharp=Sharp_dist(Sharp); 		//Converting Voltage value to distance in mm
// 	if (Left_white_line>THRESHOLD) djFlag = 100;
// 	if (Center_white_line>THRESHOLD) djFlag += 10;
// 	if (Right_white_line>THRESHOLD) djFlag +=1;
// 	lcd_print(1,13,djFlag,3);
// 	//Setting the djFlag
// 	//lcd_print (2,13,distance_Sharp,3);
// 	return djFlag;
// }

// /*
// * Function Name:	printLCD1
// * Input:			a,b,c -Integets
// * Output:			Prints a,b,c, on the LCD Screen 
// * Logic:			Debugger function used to check sensor and other values by printing them on Row 1 of LCD
// * Example Call:		printNsetDJ()
// */

// void printLCD1(int a,int b,int c) {
// 	lcd_print(1,1,a,2);
// 	lcd_print(1,4,b,2);
// 	if (c>=0) lcd_print(1,7,c,3);		//Checking Negative Value
// 	else lcd_print(1,7,-c,3);
// }

// /*
// * Function Name:	printLCD2
// * Input:			a,b,c -Integets
// * Output:			Prints a,b,c, on the LCD Screen 
// * Logic:			Debugger function used to check sensor and other values by printing them on Row 2 of LCD
// * Example Call:		printNsetDJ()
// */

// void printLCD2(int a,int b,int c) {
// 	lcd_print(2,1,a,3);
// 	if (b>=0) lcd_print(2,5,b,3);	//Checking Negative Value
// 	else lcd_print(2,5,-b,3);
// 	if (c>=0) lcd_print(2,9,c,3);
// 	else lcd_print(2,9,-c,3);
// }

// /*
// * Function Name:	beep()
// * Input:			None
// * Output:			Rings buzzer for 500 ms followed by silence of 500ms 
// * Logic:			Sets the buzzer pin to high for 500ms and low for 500ms
// * Example Call:		beep()
// */

// void beep(void)
// {
// 		buzzer_on();
// 		_delay_ms(500);
// 		buzzer_off();
// 		_delay_ms(500);
// }

// /*
// * Function Name:	main()
// * Input:			None
// * Output:			Robot Motion according to input path 
// * Logic:			Implented Line tracking code and calls the shortest path algorithm which returns the
// 					shortest path array. Using this array and conditions obtained on trial and error basis
// 					the robot follows the path.
// 					This function controls the entire bot funtioning.
// 					Detailed description will be provided at required places.
// * Example Call:		Automatically called by the microcontroller
// */

// int main(void)
// {
// 	int djFlag,compass = 0, rotA, arr[10] = {1,7,29,26,18,24,13,30,16,20},ii,last = 1, shFlag = 0, i, reqd;
// 	//arr : Input String is stored in this array . Number 1 is added to every string 
// 	//Compass : Current angle of robot w.r.t. X Axis
// 	//last:	Holds the position of current node if an obstacle is detected on the path to next node
// 	//shFlag: Used to check whether obstacle is detected or not
// 	//***** Robot is maintained at actual angle with the help of compass which stores tha angle it has turned****
// 	init_devices();
// 	init_graph();
// 	lcd_set_4bit();
// 	lcd_init();
// 	beep();//Beep
// 	for (ii = 1; ii < 10; ii++) {
// 		//if There's an obstacle, this function is called again to get the new shortest path
// 		//Find Shortest path between MNP 1 and the first MNP in the number string in the first iteratoin
// 		//Later on , shortest path between current and the next number in the number string
// 		mainFun(last,arr[ii],compass);		//Calls the algorithm written in graph.h file. Shortest path stored in Array 'path'
// 		printLCD1(last,arr[ii],compass);
// 		velocity(MAX_VEL,MAX_VEL);    					// Set the speed to max velocity
// 		/* path ARRAY
// 		Sample Input : 1 29
// 		Sample Output: 1 -82 20 2 15 19 3 67 23 28 0 22 29 0 45 34 
// 		1st Element : MNP
// 		2nd Element : Angle to be rotated
// 		3rd Element	: Distance to be moved
// 		This pattern follows
// 		*/
// 		for (i = 0; i < pathLen - 1; i+=3) {			//Access every third element in array i.e. MNP
// 			stop();
// 			_delay_ms(1500);
// 			printLCD2(path[i],path[i+1],compass);

// 			//You're at node, rotate an angle

// 			lcd_print(2,13,1,1);
// 			reqd = 8;									//Setting Threshold for encoder
// 			shFlag = 0; 
// 			forward();			
// 			//forward_mm(40);
// 			if (path[i+1] == 0) forward_mm(40);			//Angle 0 degree.. go 4cm forward
// 			else if (path[i+1] <= 20) forward_mm(20);	//Angle <=20 degree go 2cm forward
// 			else {										//Otherwise Do not turn much
// 				ShaftCountLeft = ShaftCountRight = 0;
// 				while (1) {
// 					if ( (ShaftCountLeft > reqd) | (ShaftCountRight > reqd) )
// 						break;
// 					djFlag = printNsetDJ();
// 					switch (djFlag) {					//Line follower Logic
// 						case 11:	
// 						case 1:
// 							velocity(AVG_VEL,0);		//Right Sensor on black line -> Left Wheel Forward
// 							break;
// 						case 110:
// 						case 100:
// 							velocity(0,AVG_VEL);		//LEft Sensor on black line -> Right Wheel Forward
// 							break;
// 						case 111:
// 						case 0:
// 						case 10:
// 							velocity(MAX_VEL,MAX_VEL);	//Center Sensor on black line and others on white-> Both Wheels Forward
// 					}
// 				}
// 			}
// 			velocity(MAX_VEL,MAX_VEL);
// 			stop();

// 			//ANGLE DEPENDS ON BATTERY CHARGE & LIGHT CONDITIONS

// 			//path[i+1] denotes angle to be turned

// 			if (path[i+1] <= 90 && path[i+1] >= -90) rotA = path[i+1]*2/5;	//Angle for turning based on trial and error. Turn less if angle>90 ot <-90(angle*2/5). 
// 			else rotA = path[i+1]*2/3;										//Else turn greater (angle*2/3)
// 			//_delay_ms(500);
// 			if (path[i+1]>20) right_degrees(rotA);
// 			else if (path[i+1]<-20) left_degrees(-rotA);
// 			//_delay_ms(1000);
// 			do {
// 				djFlag = printNsetDJ();
// 				if (path[i+1]>20) right_degrees(5);
// 				else if (path[i+1]<-20) left_degrees(5);
// 				else break;
// 			} while ( ((djFlag/10)%10) !=1 );					//Function for aligning robot to line by turning 5 degress until center on white line 
// 			velocity(MAX_VEL,MAX_VEL);

// 			//Update compass

// 			lcd_print(2,13,2,1);
// 			compass += path[i+1];								//Updates compass with current angle bot makes w.r.t X axis
// 			if (compass > 180) compass -= 360;
// 			if (compass < -180) compass += 360;
// 			printLCD2(path[i],path[i+1],compass);

// 			//Check for obstacle

// 			lcd_print(2,13,3,1);
// 			//printLCD2(distance_Sharp,path[i+2],0);

// 			/* Finding an Obstacle 
// 				In our path array , we have the distance between two adjacent nodes. If the distance between the
// 				Sharp sensor and obstacle is less than that distance, then it knows that there is an obstacle along
// 				that edge when it in the current node. So it doesn't follow the current path. Instead It finds the
// 				shortest path neglecting that edge from the current node to the destination node.
// 			*/

// 			if (distance_Sharp < path[i+2]*8 ) {
// 				stop();
// 				_delay_ms(1000);
// 				printLCD2(path[i],path[i+1],compass);
// 				addObstacle(path[i],path[i+3]);
// 				last = path[i];
// 				ii--;
// 				shFlag = 1;
// 				//lcd_print(2,13,1,1);
// 				break;
// 			}

// 			//Get out of the node
			
// 			lcd_print(2,13,4,1);
// 			distanceShaft = 0;
// 			forward();
// 			reqd = 12;
// 			ShaftCountLeft = ShaftCountRight = 0;
// 			while (1) {
// 				if ( (ShaftCountLeft > reqd) | (ShaftCountRight > reqd) )
// 					break;
// 				djFlag = printNsetDJ();
// 				switch (djFlag) {
// 					case 11:
// 					case 1:
// 						velocity(AVG_VEL,0);
// 						break;
// 					case 110:
// 					case 100:
// 						velocity(0,AVG_VEL);
// 						break;
// 					case 111:
// 					case 0:
// 					case 10:
// 						velocity(MAX_VEL,MAX_VEL);
// 				}
// 			}

// 			//Follow the line, if you reach a node, break

// 			lcd_print(2,13,5,1);
// 			while (1) {
// 				djFlag = printNsetDJ();
// 				if (djFlag == 11 || djFlag == 110 || djFlag==111) break;	//Node Reached Condition
// 				switch(djFlag) {
// 					case 1:
// 													//Go right
// 						velocity(AVG_VEL,0);    	 
// 						break;

// 					case 10:
// 					case 0:
// 						//Go straight
// 						velocity(MAX_VEL,MAX_VEL); 
// 						forward();     				// Run robot at max velocity 
// 						break;

// 					case 100:
// 						//Go left
// 						velocity(0,AVG_VEL);   		 
// 						break;
// 				}
// 			}
// 			velocity(MAX_VEL,MAX_VEL);
// 			if (shFlag == 1) break;					//Node Reached and there is obstacle in the next node
// 		}
// 		//If shFlag is 1, then obstacle is detected
// 		if (shFlag == 1) continue;
// 		last = path[i];								//Stores current position
// 		stop();
// 		//Node Detected 500 milli seconds beep
// 		if (ii != 9) beep();
// 		else {										//Last Node Reached
// 			buzzer_on();
// 			_delay_ms(6000);
// 			buzzer_off();
// 			_delay_ms(6000);
// 		}
// 	}
// }
