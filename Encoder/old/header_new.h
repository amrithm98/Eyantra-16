




/*
* Function Name:	linear_distance_mm
* Input:			DistanceInMM(Integer storing the Distance in mm)
* Output:			Initialize the required registers
* Logic :			For moving robot by specified distance using encoders. When the shaftCount varibles reach the threshold, the motion is stopped
* Example Call:		linear_distance_mm(100)
*/

void linear_distance_mm(unsigned int DistanceInMM)
{
 float ReqdShaftCount = 0;
 unsigned long int ReqdShaftCountInt = 0;
 ReqdShaftCount =(float) DistanceInMM / 5.338; // division by resolution to get shaft count
 ReqdShaftCountInt = (unsigned long int) ReqdShaftCount;
 ShaftCountLeft = ShaftCountRight = 0;
 while(1)
 {
  //lcd_print(2,1,ShaftCountLeft,2);
  //lcd_print(2,1,ShaftCountRight,5);
  //lcd_print(2,7,ReqdShaftCountInt,5);
  if((ShaftCountLeft > ReqdShaftCountInt) | (ShaftCountRight > ReqdShaftCountInt))
  {
  	break;
  }
 } 
 stop(); //Stop robot
}

/*
* Function Name:	forward_mm
* Input:			DistanceInMM(Integer storing the Distance in mm)
* Output:			Initialize the required registers
* Logic:			Function for moving the robot forward by specified distance. Robot starts moving forward and the linear_distance_mm function is called. Motion is terminated once the terminating condition is reached in the function when the encoder wheel makes the requried number of cuts for the distance to be covered
* Example Call:		forward_mm(100)
*/

void forward_mm(unsigned int DistanceInMM)
{
 forward();
 linear_distance_mm(DistanceInMM);
}

/*
* Function Name:	back_mm
* Input:			DistanceInMM(Integer storing the Distance in mm)
* Output:			Initialize the required registers
* Logic:			Function for moving the robot backward by specified distance. Robot starts moving backward and the linear_distance_mm function is called. Motion is terminated once the terminating condition is reached in the function when the encoder wheel makes the requried number of cuts for the distance to be covered
* Example Call:		back_mm(100)
*/

void back_mm(unsigned int DistanceInMM)
{
 back();
 linear_distance_mm(DistanceInMM);
}
