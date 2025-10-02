#ifndef TMP36_H_
#define TMP36_H_

#include <avr/io.h>
#include "avr_adc.h"
#include "avr_usart.h"
#include <util/delay.h>

uint16_t ADC_RawData = 0x0000;
float voltage = 0.0f;
float TMP36_Temp = 0.0f;
int LDR_Value = 0;


	/* ADC Configuration and Init */
void initAdc()
{
    ADC_ConfigData ADC_Data;
    ADC_Data.Prescaler = ADC_PRESCALER_128;
    ADC_Data.VoltageReference = ADC_VOLTAGE_REFERENCE_AVCC;
    ADC_Init(ADC_Data);
}


/* USART Configuration and Init */
void initUsart()
{
    USART_ConfigData USART_Data;
    USART_Data.BaudRate = 9600;
    USART_Data.DataBit = USART_DATA_BIT_EIGHT;
    USART_Data.ParityBit = USART_PARITY_BIT_NO;
    USART_Data.StopBit = USART_STOP_BIT_ONE;
    USART_Data.UsartMode = USART_MODE_ASYNCHRONOUS;
    USART_Init(USART_Data);
}


void readTmp36()
{
    /* Read ADC Value at Pin PC0 (A0/ADC0) */
    ADC_RawData = ADC_ReadPin(ADC0);
    
    /* Convert the raw ADC value to voltage */
    voltage = ((float)( ADC_RawData * 5 ) / 1023);
    
    /* Convert to Degrees Celsius */
    TMP36_Temp = (voltage - 0.5) * 100.0;
    
}


void readLDR() {
    /* Read ADC Value at Pin PC1 (A1/ADC1) */
    ADC_RawData = ADC_ReadPin(ADC1);
    LDR_Value = ADC_RawData;
}



void printTmp36()
{
    /* Print the data in terminal */
    USART_TransmitString("\nTMP36 Temperature Degree C = ");
    USART_WaitTillTransmitFree();
    USART_TransmitFloat(TMP36_Temp,3);


}

void printLDR()
{
    /* Print the data in terminal */
    USART_TransmitString("\nLDR Value = ");
    USART_WaitTillTransmitFree();
    USART_TransmitInt(LDR_Value);
}


#endif /* TMP36_H_ */

