#include "header.h"
#include "graph.h"

int printNsetDJ(void)
{
/*

*/
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
	//lcd_print(1,13,djFlag,3);
	//lcd_print (2,13,distance_Sharp,3);
	return djFlag;
}

/*void moveSetX(int x)
{
	lcd_print(2,9,1,1);
	int djFlag=printNsetDJ(), reqd = 10;//20mm
	forward();
	if (x == 0) forward_mm(40);
	else {
		ShaftCountLeft = ShaftCountRight = 0;
		while (1) {
			if ( (ShaftCountLeft > reqd) | (ShaftCountRight > reqd) )
				break;
			lcd_print(2,9,2,1);
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
	lcd_print(2,9,3,1);
	stop();
	_delay_ms(500);
	//forward();
	if (x>5) right_degrees(x);
	else if (x<-5) left_degrees(-x);
	do {
		djFlag = printNsetDJ();
		if (x>5) right_degrees(5);
		else if (x<-5) left_degrees(5);
		else {
			lcd_print(2,9,4,1);
			forward();
			velocity(MAX_VEL,MAX_VEL);
			switch (djFlag) {
			case 11:
			case 1:
				velocity(AVG_VEL,0);
				break;
			case 110:
			case 100:
				velocity(0,AVG_VEL);
				break;
			}
			lcd_print(2,9,5,1);
			if (djFlag != 0) stop();
		}
	} while ( ((djFlag/10)%10) !=1 );
	velocity(MAX_VEL,MAX_VEL);
	back();
	while ( 1 ) {
		djFlag = printNsetDJ();
		if (djFlag == 11 || djFlag == 110 || djFlag == 111) break;
		switch(djFlag) {
			case 1:
				velocity(0,AVG_VEL);
				break;
			case 100:
				velocity(AVG_VEL,0);
				break;
			case 10:
				velocity(MAX_VEL,MAX_VEL);
				break;
		}
	}
	//stop();
	//_delay_ms(3000);
	forward();
	while (1) {
		djFlag = printNsetDJ();
		if (djFlag != 11 && djFlag != 110 && djFlag != 111) break;
		switch (djFlag) {
			case 11:
				velocity(AVG_VEL,0);
				break;
			case 110:
				velocity(0,AVG_VEL);
				break;
			case 111:
				velocity(MAX_VEL,MAX_VEL);
		}
	}
	stop();
	_delay_ms(3000);
	lcd_print(2,9,6,1);
}*/

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
	lcd_print(2,9,c,2);
	lcd_print(2,12,0,1);
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
	int djFlag,curDis,compass = 0, arr[10] = {1,7,29,26,18,24,13,30,16,20},ii,last = 41, shFlag, i, reqd;
	init_devices();
	init_graph();
	lcd_set_4bit();
	lcd_init();
	beep();//Beep
	for (ii = 6; ii < 10; ii++) {
		mainFun(last,arr[ii],compass);
		printLCD1(last,arr[ii],compass);
		shFlag = 0;
		velocity(MAX_VEL,MAX_VEL);    // Set the speed to max velocity
		for (i = 0; i < pathLen - 1; i+=3) {
			stop();
			_delay_ms(1500);
			//printLCD2(path[i],path[i+1],0);

			//You're at node, rotate an angle path[i+1]/3

			reqd = 8;
			forward();
			//forward_mm(40);
			if (path[i+1] == 0) forward_mm(40);
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
			_delay_ms(500);
			if (path[i+1]>5) right_degrees(path[i+1]/3);
			else if (path[i+1]<-5) left_degrees(-path[i+1]/3);
			_delay_ms(1000);
			do {
				djFlag = printNsetDJ();
				if (path[i+1]>15) right_degrees(5);
				else if (path[i+1]<-15) left_degrees(5);
				/*else {
					forward();
					velocity(MAX_VEL,MAX_VEL);
					switch (djFlag) {
						case 11:
						case 1:
							velocity(AVG_VEL,0);
							break;
						case 110:
						case 100:
							velocity(0,AVG_VEL);
							break;
					}
					//lcd_print(2,9,5,1);
					if (djFlag != 0) stop();
				}*/
			} while ( ((djFlag/10)%10) !=1 );
			velocity(MAX_VEL,MAX_VEL);

			//Update compass

			compass += path[i+1];
			if (compass > 180) compass -= 360;
			if (compass < -180) compass += 360;
			printLCD1(last,arr[ii],compass);

			//Check for obstacle

			printLCD2(distance_Sharp,path[i+2],0);
			if (distance_Sharp < path[i+2]*10) {
				stop();
				addObstacle(path[i],path[i+3]);
				last = path[i];
				ii--;
				shFlag = 1;
				lcd_print(2,13,1,1);
				break;
			}

			//Get out of the node
			
			distanceShaft = 0;
			forward();
			reqd = 20;
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
			//printLCD2(path[i],path[i+1],distanceShaft + 8);
			//_delay_ms(2000);

			//curDis = distanceShaft;
			/*if ( i == pathLen-1 ) {
				last = path[i];
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
				break;
			}*/
			//if (compass>=0) lcd_print(1,7,compass,3);
			//else lcd_print(1,7,-compass,3);
			//if (compass>=0) lcd_print(2,1,compass,3);
			//else lcd_print(2,1,-compass,3);
			//if (i-1>0) lcd_print(1,13,path[i-1],3);
			//lcd_print(1,13,sqrt(1),3);
			//forward();
			/*while(1)
			{	
				//lcd_print(2,13,distanceShaft-curDis,3);
				if (i > 1 && distanceShaft - curDis >= path[i-1]*4) {
					if (distanceShaft - curDis - path[i-1]*4 >= 10) {
						stop();
						back();
						while ( 1 ) {
							djFlag = printNsetDJ();
							if (djFlag == 11 || djFlag == 110 || djFlag == 111) break;
							switch(djFlag) {
								case 1:
									velocity(0,AVG_VEL);
									break;
								case 100:
									velocity(AVG_VEL,0);
									break;
								case 10:
									velocity(MAX_VEL,MAX_VEL);
									break;
							}
						}
						stop();
					}
				}
				//lcd_print(2,9,1,1);
				djFlag = printNsetDJ();
				switch(djFlag) {
					case 11:
					case 110:
					case 111:
						stop();
						_delay_ms(500);
						moveSetX(path[i+1]/3);
						forward();
						curDis = distanceShaft;
						while (distanceShaft - curDis < path[i+2]) {
									djFlag = printNsetDJ();
									switch(djFlag) {
										case 1:
										case 11:
											velocity(AVG_VEL,0);
											break;
										case 100:
										case 110:
											velocity(0,AVG_VEL);
											break;
										case 10:
										case 111:
											velocity(MAX_VEL,MAX_VEL);
											break;
									}
						}
						stop();
						djFlag = 11;
						if (0 && distance_Sharp < path[i+2]) {
							stop();
							addObstacle(path[i],path[i+3]);
							last = path[i];
							ii--;
							shFlag = 1;
							break;
						}
						break;

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
				if (shFlag == 1) break;
				//lcd_print(2,9,7,1);
				if (djFlag==11 || djFlag==110 || djFlag==111) {
					//lcd_print(2,9,8,1);
					forward();
					break;
				}
				//lcd_print(2,9,9,1);
			}*/
			if (shFlag == 1) break;
		}
		last = path[i];
		if (shFlag == 1) continue;
		stop();
		//500 milli seconds beep
		beep();
	}
}
