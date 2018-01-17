/*

* Author: Texas Instruments

* Editted by: Parin Chheda
          ERTS Lab, CSE Department, IIT Bombay

* Description: This code structure will assist you in completing Lab 1
* Filename: lab-1.c

* Functions: setup(), config(), main()


*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include <time.h>

char status,colour=0x02;
int flag=0,sw1Status=1,j,sw2Status=0;
/*

* Function Name: setup()

* Input: none

* Output: none

* Description: Set crystal frequency,enable GPIO Peripherals and unlock Port F pin 0 (PF0)

* Example Call: setup();

*/
void setup(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01 ;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= 0 ;
	//unlock PF0 based on requirement

}
void key_debounce(void)
{
    status=GPIOPinRead(GPIO_PORTF_BASE,0xFF);
    SysCtlDelay(1000000);
    if( GPIOPinRead(GPIO_PORTF_BASE,0xFF) == status)
        flag=1;

}
/*

* Function Name: pin_config()

* Input: none

* Output: none

* Description: Set Port F Pin 1, Pin 2, Pin 3 as output. On this pin Red, Blue and Green LEDs are connected.
			   Set Port F Pin 0 and 4 as input, enable pull up on both these pins.

* Example Call: pin_config();

*/

void pin_config(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
}

void Delay()
{
    for(j=1;j<=sw1Status;j++)
        SysCtlDelay(6700000);
}
int main(void)
{
    

    setup();
    pin_config();

    while(1)
    {
        key_debounce();

        /*// problem statement-1 to switch between colours on switch 1 press
        if((status&0x10)==0x00&&flag==1) //switch 1
         {
                flag=0;
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,colour);
                SysCtlDelay(1000000);
                colour+=colour;
                if(colour==0x10)
                      colour=0x02;

          }
        */


        /*// Second problem statement to count the number of times Switch 2 is pressed
        if((status&0x01)==0x00&&flag==1) // switch 2
          {
             flag=0;
             sw2Status+=1;

          }

       /*
         // third problem statement of using Switch1 and Switch 2
        if((status&0x10)==0x00&&flag==1) //switch 1
        {
            flag=0;
            if(sw1Status<4)
                sw1Status+=sw1Status;
            else
                sw1Status=1;

        }

        if((status&0x01)==0x00&&flag==1) // switch 2
         {
             flag=0;
             GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,colour);
             Delay();
             GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,(colour^colour));
             colour+=colour;
             if(colour==0x10)
                 colour=0x02;
         }
       */
        
    }
}
