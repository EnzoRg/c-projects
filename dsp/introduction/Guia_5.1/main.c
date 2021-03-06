/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    ConfigureOscillator();
    InitApp();
    bool valor;
    int32_t i;
    
    
    while(1)
    {
       //Ej 1.1
       //  valor = PORTBbits.RB7;
       // LATBbits.LATB2 = valor;
        
       //Ej 1.2
        for(i=0; i<155000;i=i+1)
            LATBbits.LATB2 = ~LATBbits.LATB2;
        
        
    }
}
