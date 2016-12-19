/*
* Team Id: 1320
* Author List: Daniel James, Amrith M
* Filename: encoder.c
* Theme: Bothoven
* Functions: printNsetDJ,printLCD1,printLCD2,beep,main
* Global Variables: None
*/
#include "header.h"
#include "graph.h"

int printNsetDJ(void)
{
	int djFlag=0,Sharp;
	Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
	Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
	Right_white_line = ADC_Conversion(1); //Getting data of Right WL Sensor
	Sharp=ADC_Conversion(11);
	djFlag = 0;
	distance_Sharp=Sharp_dist(Sharp); 
	if (Left_white_line>THRESHOLD) djFlag = 100;
	if (Center_white_line>THRESHOLD) djFlag += 10;
	if (Right_white_line>THRESHOLD) djFlag +=1;
	lcd_print(1,13,djFlag,3);
	//lcd_print (2,13,distance_Sharp,3);
	return djFlag;
}

void printLCD1(int a,int b,int c) {
	lcd_print(1,1,a,2);
	lcd_print(1,4,b,2);
	if (c>=0) lcd_print(1,7,c,3);
	else lcd_print(1,7,-c,3);
}

void printLCD2(int a,int b,int c) {
	lcd_print(2,1,a,3);
	if (b>=0) lcd_print(2,5,b,3);
	else lcd_print(2,5,-b,3);
	if (c>=0) lcd_print(2,9,c,3);
	else lcd_print(2,9,-c,3);
}
void beep(void)
{
		buzzer_on();
		_delay_ms(500);
		buzzer_off();
		_delay_ms(500);
}
int main(void)
{
	int djFlag,compass = 0, rotA, arr[10] = {1,7,29,26,18,24,13,30,16,20},ii,last = 1, shFlag = 0, i, reqd;
	init_devices();
	init_graph();
	lcd_set_4bit();
	lcd_init();
	beep();//Beep
	for (ii = 1; ii < 10; ii++) {
		mainFun(last,arr[ii],compass);
		printLCD1(last,arr[ii],compass);
		velocity(MAX_VEL,MAX_VEL);    // Set the speed to max velocity
		for (i = 0; i < pathLen - 1; i+=3) {
			stop();
			_delay_ms(1500);
			printLCD2(path[i],path[i+1],compass);

			//You're at node, rotate an angle


			lcd_print(2,13,1,1);
			reqd = 8;
			shFlag = 0; 
			forward();
			//forward_mm(40);
			if (path[i+1] == 0) forward_mm(40);
			else if (path[i+1] <= 20) forward_mm(20);
			else {
				ShaftCountLeft = ShaftCountRight = 0;
				while (1) {
					if ( (ShaftCountLeft > reqd) | (ShaftCountRight > reqd) )
						break;
					djFlag = printNsetDJ();
					switch (djFlag) {
						case 11:
						case 1:
							velocity(AVG_VEL,0);
							break;
						case 110:
						case 100:
							velocity(0,AVG_VEL);
							break;
						case 111:
						case 0:
						case 10:
							velocity(MAX_VEL,MAX_VEL);
					}
				}
			}
			velocity(MAX_VEL,MAX_VEL);
			stop();
			//Angle depends on battery charge & light conditions
			if (path[i+1] <= 90 && path[i+1] >= -90) rotA = path[i+1]*2/5;
			else rotA = path[i+1]*2/3;
			//_delay_ms(500);
			if (path[i+1]>20) right_degrees(rotA);
			else if (path[i+1]<-20) left_degrees(-rotA);
			//_delay_ms(1000);
			do {
				djFlag = printNsetDJ();
				if (path[i+1]>20) right_degrees(5);
				else if (path[i+1]<-20) left_degrees(5);
				else break;
			} while ( ((djFlag/10)%10) !=1 );
			velocity(MAX_VEL,MAX_VEL);

			//Update compass

			lcd_print(2,13,2,1);
			compass += path[i+1];
			if (compass > 180) compass -= 360;
			if (compass < -180) compass += 360;
			printLCD2(path[i],path[i+1],compass);

			//Check for obstacle

			lcd_print(2,13,3,1);
			//printLCD2(distance_Sharp,path[i+2],0);
			if (distance_Sharp < path[i+2]*8 ) {
				stop();
				_delay_ms(1000);
				printLCD2(path[i],path[i+1],compass);
				addObstacle(path[i],path[i+3]);
				last = path[i];
				ii--;
				shFlag = 1;
				//lcd_print(2,13,1,1);
				break;
			}

			//Get out of the node
			
			lcd_print(2,13,4,1);
			distanceShaft = 0;
			forward();
			reqd = 12;
			ShaftCountLeft = ShaftCountRight = 0;
			while (1) {
				if ( (ShaftCountLeft > reqd) | (ShaftCountRight > reqd) )
					break;
				djFlag = printNsetDJ();
				switch (djFlag) {
					case 11:
					case 1:
						velocity(AVG_VEL,0);
						break;
					case 110:
					case 100:
						velocity(0,AVG_VEL);
						break;
					case 111:
					case 0:
					case 10:
						velocity(MAX_VEL,MAX_VEL);
				}
			}

			//Follow the line, if you reach a node, break

			lcd_print(2,13,5,1);
			while (1) {
				djFlag = printNsetDJ();
				if (djFlag == 11 || djFlag == 110 || djFlag==111) break;
				switch(djFlag) {
					case 1:
						//Go right
						velocity(AVG_VEL,0);    // Run robot right wheel at max velocity and left wheel 
						break;

					case 10:
					case 0:
						//Go straight
						velocity(MAX_VEL,MAX_VEL); 
						forward();     // Run robot at max velocity 
						break;

					case 100:
						//Go left
						velocity(0,AVG_VEL);   // Run robot left wheel at max velocity and right wheel 
						break;
				}
			}
			velocity(MAX_VEL,MAX_VEL);
			if (shFlag == 1) break;
		}
		if (shFlag == 1) continue;
		last = path[i];
		stop();
		//500 milli seconds beep
		if (ii != 9) beep();
		else {
			buzzer_on();
			_delay_ms(6000);
			buzzer_off();
			_delay_ms(6000);
		}
	}
}
