/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC12F1572
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "PIC12_HEFlash.h"
#include "Softdelay.h"


#define LIGHT LATAbits.LATA1

//#define ON 1
//#define OFF 0
//#define LIGHT_ADDR 0x0780


#define LDR_THRESHOLD 750

static uint32_t time_EEPROM_WRITE_Period = 0;
uint16_t time_EEPROM_WRITE_count = 10; 
   

void LIGHT_Trigger(unsigned char Status );
static unsigned char last_saved_status = 0xFF;  // Declare here at function scope


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    LED_SetDigitalOutput();
    
    uint16_t ldr1 = 0;
    uint16_t ldr2 = 0;
    bool V_LightStatus;
    uint32_t myTimer = 0;

    V_LightStatus =old_light_status();
    while (1)
{
    ldr1 = ADC1_GetConversion(channel_AN0);
    __delay_ms(5);
    ldr2 = ADC1_GetConversion(channel_AN2);
    __delay_ms(5);

//    static unsigned char last_saved_status = 0xFF;

    if (ldr1 > LDR_THRESHOLD && ldr2 > LDR_THRESHOLD)
    {
        if (V_LightStatus == OFF)
        {   
//            printf("First OFF\r\n");
            LED_SetHigh();
            V_LightStatus = ON;
//            printf("Second ON\r\n");
            SoftDelay_Start(&myTimer);  

            // Save ON status
            if (V_LightStatus != last_saved_status)
            {
                ReadWrite_HEFlash(1, V_LightStatus, LIGHT_ADDR);
                last_saved_status = V_LightStatus;
            }
        }

        if (SoftDelay_IsOneMinuteOver(&myTimer))
        {
            LED_SetLow();
            V_LightStatus = OFF;

            // Save OFF status
            if (V_LightStatus != last_saved_status)
            {
                ReadWrite_HEFlash(1, V_LightStatus, LIGHT_ADDR);
                last_saved_status = V_LightStatus;
            }
        }
    }
    else
    {
        if (V_LightStatus == ON)
        {
            LED_SetLow();
            V_LightStatus = OFF;

            // Save OFF status
            if (V_LightStatus != last_saved_status)
            {
                ReadWrite_HEFlash(1, V_LightStatus, LIGHT_ADDR);
                last_saved_status = V_LightStatus;
            }
        }
    }

    __delay_ms(100);
}
}
