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

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* This is not all available configuration bits for all dsPIC devices.        */
/* Refer to the dsPIC device specific .h file in the compiler                 */
/* support\dsPIC33F\h directory for complete options specific to the device   */
/* selected.  For additional information about what hardware configurations   */
/* mean in terms of device operation, refer to the device datasheet           */
/* 'Special Features' chapter.                                                */
/*                                                                            */
/* A feature of MPLAB X is the 'Generate Source Code to Output' utility in    */
/* the Configuration Bits window.  Under Window > PIC Memory Views >          */
/* Configuration Bits, a user controllable configuration bits window is       */
/* available to Generate Configuration Bits source code which the user can    */
/* paste into this project.                                                   */
/******************************************************************************/

/* TODO Fill in your configuration bits from the config bits generator here.  */

/* Ejercicio 2.2 PLL */
_FOSCSEL(FNOSC_FRC & IESO_OFF); // Internal FRC start-up without PLL,
// no Two Speed Start-up
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT); // Clock switch enabled,
// Primarly Oscillator XT
_FWDT(FWDTEN_OFF); // Watchdog Timer disabled
//_FPOR(PPWRT_PWR128); // Power-up Timer enabled 128 ms
_FICD(JTAGEN_OFF); // Disable JTAG

