/*
******************************************************************************
File:     utilities.h

Provide some utilities functions to be used in code

******************************************************************************
*/

void delay(int millisec){
	// Convert millisecond in factor assuming that mcu is running with 168 MHz
	int factor = (int)(168000*millisec);
	for( int i = 0; i < factor; i++ );
}
