#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h> // for sleep
#include <sys/types.h> // for testing sharing
#include <sys/ipc.h> // for testing sharing
#include <sys/shm.h> // for testing sharing
//For Bot
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.c"
#include <math.h>		//Remove this if program doesn't run. 
#define THRESHOLD 20
//THRESHOLD : ADC Value decided as threshold for sensing black line. Value above threshold corresponds to a black line. Threshold may change for track and lighting