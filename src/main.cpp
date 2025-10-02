#include <util/delay.h>
#include "sensors.h"


int main(void)
{
    
  initAdc();
  initUsart();

    while (1) 
    {
    readTmp36();
    readLDR();
    printSensorValue();
  
    /* Wait for 10s */
		_delay_ms(10000);
	
    }
    
}