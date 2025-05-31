//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution. 
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
//
//*****************************************************************************


//*****************************************************************************
//
// Application Name     -   SSL Demo
// Application Overview -   This is a sample application demonstrating the
//                          use of secure sockets on a CC3200 device.The
//                          application connects to an AP and
//                          tries to establish a secure connection to the
//                          Google server.
// Application Details  -
// docs\examples\CC32xx_SSL_Demo_Application.pdf
// or
// http://processors.wiki.ti.com/index.php/CC32xx_SSL_Demo_Application
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup ssl
//! @{
//
//*****************************************************************************


//      EEC 172 FINAL PROJECT
// Asad Melibaev and George Jenov


// Standard includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "uart.h"
#include "gpio.h"
#include "spi.h"

// Common interface includes
#include "uart_if.h"
#include "i2c_if.h"

// OLED
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "glcdfont.h"
#include "oled_test.h"



#include <stdio.h>

// Simplelink includes
#include "simplelink.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "uart.h"

//Common interface includes
#include "pinmux.h"
#include "gpio_if.h"
#include "common.h"
#include "uart_if.h"

// Custom includes
#include "utils/network_utils.h"




// Standard includes
#include <stdlib.h>
#include <string.h>

// Driverlib includes
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_types.h"
#include "hw_timer.h"
#include "uart.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "timer.h"
#include "interrupt.h"

// Common interface includes
#include "systick_if.h"
#include "uart_if.h"




//NEED TO UPDATE THIS FOR IT TO WORK!
#define DATE                30    /* Current Date */
#define MONTH               5     /* Month 1-12 */
#define YEAR                2025  /* Current year */
#define HOUR                20    /* Time - hours */
#define MINUTE              21    /* Time - minutes */
#define SECOND              0     /* Time - seconds */

#define APPLICATION_VERSION     "1.4.0"
#define APP_NAME             "Interrupt Reference"
#define SYSCLK               80000000
#define UART_PRINT           Report
#define APPLICATION_NAME      "SSL"
#define SERVER_NAME           "a11iiid5mknk2s-ats.iot.us-east-2.amazonaws.com" // CHANGE ME
#define GOOGLE_DST_PORT       8443

#define APPLICATION_VERSION     "1.4.0"
//#define APP_NAME                "I2C Demo"
#define UART_PRINT              Report
#define FOREVER                 1
#define CONSOLE                 UARTA0_BASE
#define FAILURE                 -1
#define SUCCESS                 0
#define RETERR_IF_TRUE(condition) {if(condition) return FAILURE;}
#define RET_IF_ERR(Func)          {int iRetVal = (Func); \
                                   if (SUCCESS != iRetVal) \
                                     return  iRetVal;}

#define SPI_IF_BIT_RATE  10000000
#define TR_BUFF_SIZE     100


#define POSTHEADER "POST /things/George_CC3200/shadow HTTP/1.1\r\n"             // CHANGE ME
#define HOSTHEADER "Host: a11iiid5mknk2s-ats.iot.us-east-2.amazonaws.com\r\n"  // CHANGE ME
#define CHEADER "Connection: Keep-Alive\r\n"
#define CTHEADER "Content-Type: application/json; charset=utf-8\r\n"
#define CLHEADER1 "Content-Length: "
#define CLHEADER2 "\r\n\r\n"

char DATA1[512];

#define SLOW_TIMER_DELAY_uS 2000
#define LOW_PRIORITY  0xFF
#define HIGH_PRIORITY 0x00
#define MIDDLE_PRIORITY 0x80

#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"
#include "gpio.h"

// Common interface includes
#include "uart_if.h"

//for int and str
#include <string.h>
#include <stdint.h>
#include <stdio.h>

// OLED
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "glcdfont.h"
#include "oled_test.h"



#define MASTER_MODE      0
// PIN_04 (DC)
#define OLED_DC_BASE     GPIOA1_BASE
#define OLED_DC_PIN      0x20
// PIN_06 (Reset)
#define OLED_RST_BASE    GPIOA1_BASE
#define OLED_RST_PIN     0x80
// PIN_03 (OLEDCS)
#define OLED_CS_BASE     GPIOA1_BASE
#define OLED_CS_PIN      0x10



//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************

// Globals used to track calls to the test interrupt handlers.
static volatile unsigned long g_ulA0IntCount;
static volatile unsigned long g_ulA1IntCount;
static volatile unsigned long g_ulA2IntCount;
static volatile tBoolean g_bA1CountChanged;
static volatile tBoolean g_bA2CountChanged;

// Globals used to save and restore interrupt settings.
static unsigned long g_ulTimer0APriority;
static unsigned long g_ulTimer1APriority;
static unsigned long g_lPriorityGrouping;

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

//*****************************************************************************
//                 GLOBAL VARIABLES -- End: df
//*****************************************************************************


//****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//****************************************************************************
static int set_time();
static void BoardInit(void);
static int http_post(int);

//*****************************************************************************
//
//! \TimerA0IntHandler
//!
//! Handles interrupts for Timer A0,
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
int
DisplayBuffer(unsigned char *pucDataBuf, unsigned char ucLen)
{
    unsigned char ucBufIndx = 0;
    int buffer;
    while(ucBufIndx < ucLen)
    {
        buffer = (int) pucDataBuf[ucBufIndx];

        if(buffer & 0x80){
            buffer = buffer | 0xffffff00;
        }
        ucBufIndx++;
    }
    return buffer;
}

int
ProcessReadCommand(char *pcInpString)
{
    unsigned char ucDevAddr, ucLen;
    unsigned char aucDataBuf[256];
    char *pcErrPtr;
    int iRetVal;

    //
    // Get the device address
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucDevAddr = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);
    //
    // Get the length of data to be read
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucLen = (unsigned char)strtoul(pcInpString, &pcErrPtr, 10);
    //RETERR_IF_TRUE(ucLen > sizeof(aucDataBuf));

    //
    // Read the specified length of data
    //
    iRetVal = I2C_IF_Read(ucDevAddr, aucDataBuf, ucLen);

    if(iRetVal == SUCCESS)
    {
        UART_PRINT("I2C Read complete\n\r");

        //
        // Display the buffer over UART on successful write
        //
        DisplayBuffer(aucDataBuf, ucLen);
    }
    else
    {
        UART_PRINT("I2C Read failed\n\r");
        return FAILURE;
    }

    return SUCCESS;
}

int
ProcessReadRegCommand(char *pcInpString)
{
    unsigned char ucDevAddr, ucRegOffset, ucRdLen;
    unsigned char aucRdDataBuf[256];
    char *pcErrPtr;

    //
    // Get the device address
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucDevAddr = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);
    //
    // Get the register offset address
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucRegOffset = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);

    //
    // Get the length of data to be read
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucRdLen = (unsigned char)strtoul(pcInpString, &pcErrPtr, 10);
    //RETERR_IF_TRUE(ucLen > sizeof(aucDataBuf));

    //
    // Write the register address to be read from.
    // Stop bit implicitly assumed to be 0.
    //
    RET_IF_ERR(I2C_IF_Write(ucDevAddr,&ucRegOffset,1,0)); //breaks here

    //
    // Read the specified length of data
    //
    RET_IF_ERR(I2C_IF_Read(ucDevAddr, &aucRdDataBuf[0], ucRdLen));

    //UART_PRINT("I2C Read From address complete\n\r");

    //
    // Display the buffer over UART on successful readreg
    //
    //



    return DisplayBuffer(aucRdDataBuf, ucRdLen);
}
int
ProcessWriteRegCommand(char *pcInpString)
{
    unsigned char ucDevAddr, ucRegOffset, ucWrLen;
    unsigned char aucDataBuf[256];
    char *pcErrPtr;
    int iLoopCnt = 0;

    //
    // Get the device address
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucDevAddr = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);

    //
    // Get the register offset to be written
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucRegOffset = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);
    aucDataBuf[iLoopCnt] = ucRegOffset;
    iLoopCnt++;

    //
    // Get the length of data to be written
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucWrLen = (unsigned char)strtoul(pcInpString, &pcErrPtr, 10);
    //RETERR_IF_TRUE(ucWrLen > sizeof(aucDataBuf));

    //
    // Get the bytes to be written
    //
    for(; iLoopCnt < ucWrLen + 1; iLoopCnt++)
    {
        //
        // Store the data to be written
        //
        pcInpString = strtok(NULL, " ");
        RETERR_IF_TRUE(pcInpString == NULL);
        aucDataBuf[iLoopCnt] =
                (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);
    }
    //
    // Write the data values.
    //
    RET_IF_ERR(I2C_IF_Write(ucDevAddr,&aucDataBuf[0],ucWrLen+1,1));

    UART_PRINT("I2C Write To address complete\n\r");

    return SUCCESS;
}

//****************************************************************************
//
//! Parses the write command parameters and invokes the I2C APIs
//!
//! \param pcInpString pointer to the write command parameters
//!
//! This function
//!    1. Parses the write command parameters.
//!    2. Invokes the corresponding I2C APIs
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************
int
ProcessWriteCommand(char *pcInpString)
{
    unsigned char ucDevAddr, ucStopBit, ucLen;
    unsigned char aucDataBuf[256];
    char *pcErrPtr;
    int iRetVal, iLoopCnt;

    //
    // Get the device address
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucDevAddr = (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);

    //
    // Get the length of data to be written
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucLen = (unsigned char)strtoul(pcInpString, &pcErrPtr, 10);
    //RETERR_IF_TRUE(ucLen > sizeof(aucDataBuf));

    for(iLoopCnt = 0; iLoopCnt < ucLen; iLoopCnt++)
    {
        //
        // Store the data to be written
        //
        pcInpString = strtok(NULL, " ");
        RETERR_IF_TRUE(pcInpString == NULL);
        aucDataBuf[iLoopCnt] =
                (unsigned char)strtoul(pcInpString+2, &pcErrPtr, 16);
    }

    //
    // Get the stop bit
    //
    pcInpString = strtok(NULL, " ");
    RETERR_IF_TRUE(pcInpString == NULL);
    ucStopBit = (unsigned char)strtoul(pcInpString, &pcErrPtr, 10);

    //
    // Write the data to the specified address
    //
    iRetVal = I2C_IF_Write(ucDevAddr, aucDataBuf, ucLen, ucStopBit);
    if(iRetVal == SUCCESS)
    {
        UART_PRINT("I2C Write complete\n\r");
    }
    else
    {
        UART_PRINT("I2C Write failed\n\r");
        return FAILURE;
    }

    return SUCCESS;
}

//****************************************************************************
//
//! Parses the user input command and invokes the I2C APIs
//!
//! \param pcCmdBuffer pointer to the user command
//!
//! This function
//!    1. Parses the user command.
//!    2. Invokes the corresponding I2C APIs
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************
int
ParseNProcessCmd(char *pcCmdBuffer)
{
    char *pcInpString;
    int iRetVal;

    pcInpString = strtok(pcCmdBuffer, " \n\r");
    if(pcInpString != NULL)

    {

        if(!strcmp(pcInpString, "read"))
        {
            //
            // Invoke the read command handler
            //
            iRetVal = ProcessReadCommand(pcInpString);
        }
        else if(!strcmp(pcInpString, "readreg"))
        {
            //
            // Invoke the readreg command handler
            //
            iRetVal = ProcessReadRegCommand(pcInpString);
        }
        else if(!strcmp(pcInpString, "writereg"))
        {
            //
            // Invoke the writereg command handler
            //
            iRetVal = ProcessWriteRegCommand(pcInpString);
        }
        else if(!strcmp(pcInpString, "write"))
        {
            //
            // Invoke the write command handler
            //
            iRetVal = ProcessWriteCommand(pcInpString);
        }
        else
        {
            UART_PRINT("Unsupported command\n\r");
            return FAILURE;
        }
    }

    return iRetVal;
}





static void
TimerA0IntHandler(void)
{
    unsigned long ulStatus;
    unsigned long ulCountOnEntry;

    //
    // Clear all interrupts for Timer unit 0.
    //
    ulStatus = MAP_TimerIntStatus(TIMERA0_BASE, true);
    MAP_TimerIntClear(TIMERA0_BASE, ulStatus);

    //
    // Take a snapshot of the other interrupt's counter.
    //
    ulCountOnEntry = g_ulA1IntCount;
    MAP_TimerEnable(TIMERA1_BASE, TIMER_A);

    //
    // We wait 2mS to give the A1 interrupt a chance to fire.
    //
    UTUtilsDelay(SLOW_TIMER_DELAY_uS);

    //
    // Determine whether the Timer A1 interrupt handler was processed during our
    // delay and set the global flag accordingly.
    //
    if(ulCountOnEntry == g_ulA1IntCount)
    {
        g_bA1CountChanged = false;
    }
    else
    {
        g_bA1CountChanged = true;
    }

    //
    // Increment our interrupt counter.
    //
    g_ulA0IntCount++;

    //
    // Alert to the user
    //
    UART_PRINT("Completed TimerA0 Interrupt Handler \n\r");
}

//*****************************************************************************
//
//! \TimerA1IntHandler
//!
//! Handles interrupts for Timer A1.
//! This interrupt handler clears the source of the interrupt, calls Timer A2,
//! increments a counter and returns.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static void
TimerA1IntHandler(void)
{
    unsigned long ulStatus;
    unsigned long ulCountOnEntry;

    //
    // Clear all interrupts for Timer.
    //
    ulStatus = MAP_TimerIntStatus(TIMERA1_BASE, true);
    MAP_TimerIntClear(TIMERA1_BASE, ulStatus);

    ulCountOnEntry=g_ulA2IntCount;
    MAP_TimerEnable(TIMERA2_BASE, TIMER_A);

    //
    // We wait 2mS to give Timer A2 interrupt a chance to fire
    //
    UTUtilsDelay(SLOW_TIMER_DELAY_uS);

    //
    // Determine whether the fast interrupt handler was processed during our
    // delay and set the global flag accordingly.
    //
    if(ulCountOnEntry==g_ulA2IntCount)
    {
      g_bA2CountChanged=false;

    }
    else
    {
      g_bA2CountChanged=true;
    }

    //
    // Increment our global interrupt counter.
    //
    g_ulA1IntCount++;
    //
    // Alert to the User
    //
    UART_PRINT("Completed TimerA1 Interrupt Handler \n\r");
}

//*****************************************************************************
//
//! \TimerA2IntHandler
//!
//! Handles interrupts for Timer A2.
//! This interrupt handler clears the source of the interrupt and
//! increments a counter and returns.
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
static void
TimerA2IntHandler(void)
{
    unsigned long ulStatus;

    //
    // Clear all interrupts for Timer.
    //
    ulStatus = MAP_TimerIntStatus(TIMERA2_BASE, true);
    MAP_TimerIntClear(TIMERA2_BASE, ulStatus);

    //
    // Increment our global interrupt counter.
    //
    g_ulA2IntCount++;

    //
    // Alert to the User
    //
    UART_PRINT("Completed TimerA2 Interrupt Handler \n\r");
}

//*****************************************************************************
//
//! \PerformIntTest
//!
//! Performs the repeated steps in running each test scenario.
//!
//! \param ucPriorityA0 is the interrupt priority to be used for Timer A0
//! \param ucPriorityA1 is the interrupt priority to be used for Timer A1
//! \param ucPriorityA2 is the interrupt priority to be used for Timer A2
//!
//! This function performs all the steps which are common to each test scenario
//! inside function InterruptTest.
//!
//! \return None.
//
//*****************************************************************************
tBoolean
PerformIntTest(unsigned long ulPriBits, unsigned char ucPriorityA0,
       unsigned char ucPriorityA1,unsigned char ucPriorityA2)
{
    tBoolean bRetcode;
    unsigned long ulStatus;

    //
    // Set the appropriate interrupt priorities.
    //
    MAP_IntPriorityGroupingSet(ulPriBits);
    MAP_IntPrioritySet(INT_TIMERA0A, ucPriorityA0);
    MAP_IntPrioritySet(INT_TIMERA1A, ucPriorityA1);
    MAP_IntPrioritySet(INT_TIMERA2A, ucPriorityA2);

    //
    // Clear any pending timer interrupts
    //
    ulStatus = MAP_TimerIntStatus(TIMERA0_BASE, false);
    MAP_TimerIntClear(TIMERA0_BASE, ulStatus);
    ulStatus = MAP_TimerIntStatus(TIMERA1_BASE, false);
    MAP_TimerIntClear(TIMERA1_BASE, ulStatus);
    ulStatus = MAP_TimerIntStatus(TIMERA2_BASE, false);
    MAP_TimerIntClear(TIMERA2_BASE, ulStatus);

    //
    // Clear all the counters and flags used by the interrupt handlers.
    //
    g_ulA0IntCount = 0;
    g_ulA1IntCount = 0;
    g_ulA2IntCount=0;
    g_bA1CountChanged = false;

    //
    // Enable three timer interrupts
    //
    MAP_TimerIntEnable(TIMERA0_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntEnable(TIMERA1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntEnable(TIMERA2_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable Timer A0
    //
    MAP_TimerEnable(TIMERA0_BASE, TIMER_A);

    //
    // Wait for Timer 0/A to fire.
    //
    bRetcode = UTUtilsWaitForCount(&g_ulA0IntCount, 1,
                                       ((SLOW_TIMER_DELAY_uS*3)/1000));


    //
    // Stop All timers and disable their interrupts
    //
    MAP_TimerDisable(TIMERA2_BASE, TIMER_A);
    MAP_TimerDisable(TIMERA1_BASE, TIMER_A);
    MAP_TimerDisable(TIMERA0_BASE, TIMER_A);
    MAP_TimerIntDisable(TIMERA2_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntDisable(TIMERA1_BASE, TIMER_TIMA_TIMEOUT);
    MAP_TimerIntDisable(TIMERA0_BASE, TIMER_TIMA_TIMEOUT);

    return(bRetcode);
}

//*****************************************************************************
//
//! Main test implementation function
//!
//! It uses 3 different timers to test that interrupts can be enabled
//! and disabled successfully and that preemption occurs as expected when
//! different priority levels are assigned.
//
//! \return Returns 1 on Success.
//
//*****************************************************************************

//*****************************************************************************
//
//! Application startup display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
static void
DisplayBanner(char * AppName)
{
    Report("\n\n\n\r");
    Report("\t\t *************************************************\n\r");
    Report("\t\t    CC3200 %s Application       \n\r", AppName);
    Report("\t\t *************************************************\n\r");
    Report("\n\n\n\r");
}


//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void BoardInit(void) {
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


#include "timer_if.h"
#include "gpio.h"
#include <stdbool.h>

#define PULSE_MONITOR_PORT GPIOA3_BASE

// address for pin 1
#define PULSE_MONITOR_PIN 0x10

// Important vars to keep track of time
static volatile unsigned long  int g_timerTicks = 0;
static volatile unsigned long  int g_pulseStartTime = 0;
static volatile unsigned long  int g_pulseWidth = 0;
static volatile bool g_pulseDetected = false;
static volatile bool StartPulse = false;
static volatile char TvCode = 0;
static volatile unsigned long g_clockBase = TIMERA0_BASE;


static volatile unsigned long  int g_lastEdgeTime = 0;
static volatile unsigned long  int g_lowPulseDuration = 0;
static volatile unsigned long  int g_highPulseDuration = 0;

static volatile unsigned long  int startTimeWatch = 0;
static volatile bool BackSpaced = false;

static volatile unsigned long int bits;

static volatile char UserMessage[128];

static volatile char result;


void ClockHandler(){
    Timer_IF_InterruptClear(g_clockBase);
    g_timerTicks++;
}

void GPIOHandler(){
    MAP_GPIOIntClear(PULSE_MONITOR_PORT, PULSE_MONITOR_PIN);
    bool pinInput = GPIOPinRead(PULSE_MONITOR_PORT, PULSE_MONITOR_PIN);
    long unsigned int currentTime = g_timerTicks;
    long unsigned duration = 0;

    if(bits >= 23){
        duration = 0;
        currentTime = 0;
        //g_timerTicks = 0;
        g_lastEdgeTime = 0;
        g_lowPulseDuration = 0;
        g_highPulseDuration = 0;
    }

    duration = currentTime - g_lastEdgeTime;
    g_lastEdgeTime = currentTime;

    // Rising edge
    if (pinInput){
        g_lowPulseDuration = duration;
    }
    // Falling edge
    else{
        g_highPulseDuration = duration;

        g_pulseWidth = g_highPulseDuration;
        g_pulseDetected = true;
    }
    //g_pulseStartTime = g_pulseWidth;
}

void ClockInit(){
    // Initializing the timer
    Timer_IF_Init(PRCM_TIMERA0, g_clockBase, TIMER_CFG_PERIODIC, TIMER_A, 0);
    // Setting up the timer interrupt
    Timer_IF_IntSetup(g_clockBase, TIMER_A, ClockHandler);
    // Start timer to interrupt every microsecond 1ms
    Timer_IF_Start(g_clockBase, TIMER_A, 1);
}

// Enable pin 1 as an interrupt
void PinInit(){
    //MAP_GPIOPinTypeGPIOInput(PULSE_MONITOR_PORT, PULSE_MONITOR_PIN);
    MAP_GPIOIntTypeSet(PULSE_MONITOR_PORT, PULSE_MONITOR_PIN, GPIO_BOTH_EDGES);
    MAP_GPIOIntRegister(PULSE_MONITOR_PORT, GPIOHandler);
    MAP_GPIOIntEnable(PULSE_MONITOR_PORT, PULSE_MONITOR_PIN);
}

static char remoteCodes[255][5];

void prepareArray(){
    int i = 0;
    int j = 0;

    for (i = 0; i < 255; i++){
        for (j = 0; j < 255; j++){
            remoteCodes[i][j] = '\0';
        }
    }
}

int BinaryToInt(char TvCode){
    // Buffer to store binary string (8 bits + null terminator)
    char binaryStr[9];
    // Convert char to binary string
    int i;
    for (i = 7; i >= 0; --i) {
        binaryStr[7 - i] = (TvCode & (1 << i)) ? '1' : '0';
    }
    binaryStr[8] = '\0'; // Null-terminate the string
    // Print binary string to UART

   return strtol(binaryStr, NULL, 2);
}

bool convertToInt(char TvCode){
    int intValue = BinaryToInt(TvCode);

    if(intValue == 2  || intValue == 11 || intValue == 8 || intValue == 34 || intValue == 38 ||
       intValue == 35 || intValue == 32|| intValue == 130|| intValue == 138||
      intValue == 134 || intValue == 44|| intValue == 0){
        return true;
    }

    return false;
}

void PrintBinaryToUART(char TvCode) {
    int intValue = BinaryToInt(TvCode);
    //testing 1
    /*
    UART_PRINT("Obtained binary data is: %s \n\r", binaryStr);
    UART_PRINT("Int value of the data is: %d \n\r", intValue);
    UART_PRINT("%s \n\r",remoteCodes[intValue]);
    */

    /*testing 2
    UART_PRINT("Int value of the data is: %d \n\r", intValue);
    UART_PRINT("%s \n\r",remoteCodes[intValue]);
    */

    //UART_PRINT("%s ",remoteCodes[intValue]);
}

char* convertToString(char TvCode) {
    return remoteCodes[(unsigned char)TvCode];
}

static volatile int count = 0;
static volatile int previousCharacterNum;
static volatile int count1 = 0;

static char letterArray1[140][2];
static char letterArray2[140][2];
static char letterArray3[140][2];
static char letterArray4[140][2];

void setArray(){
    // Keys
    strcpy(remoteCodes[2], "1");
    strcpy(remoteCodes[11], "2");
    strcpy(remoteCodes[8], "3");
    strcpy(remoteCodes[34], "4");
    strcpy(remoteCodes[38], "5");
    strcpy(remoteCodes[35], "6");
    strcpy(remoteCodes[32], "7");
    strcpy(remoteCodes[130], "8");
    strcpy(remoteCodes[138], "9");
    strcpy(remoteCodes[0], "0");

    strcpy(remoteCodes[134], "Mute");
    strcpy(remoteCodes[44], "Last");

}

void setArray1(){
    strcpy(letterArray1[11], "A");
    strcpy(letterArray1[8], "D");
    strcpy(letterArray1[34], "G");
    strcpy(letterArray1[38], "J");
    strcpy(letterArray1[35], "M");
    strcpy(letterArray1[32], "P");
    strcpy(letterArray1[130], "T");
    strcpy(letterArray1[138], "W");
}

void setArray2(){
    strcpy(letterArray2[11], "B");
    strcpy(letterArray2[8], "E");
    strcpy(letterArray2[34], "H");
    strcpy(letterArray2[38], "K");
    strcpy(letterArray2[35], "N");
    strcpy(letterArray2[32], "Q");
    strcpy(letterArray2[130], "U");
    strcpy(letterArray2[138], "X");
}

void setArray3(){
    strcpy(letterArray3[11], "C");
    strcpy(letterArray3[8], "F");
    strcpy(letterArray3[34], "I");
    strcpy(letterArray3[38], "L");
    strcpy(letterArray3[35], "O");
    strcpy(letterArray3[32], "R");
    strcpy(letterArray3[130], "V");
    strcpy(letterArray3[138], "Y");
}

void setArray4(){
    strcpy(letterArray4[32], "S");
    strcpy(letterArray4[138], "Z");
}

//handling multiple inputs on one key
int previousintValue;
char* letterConversion(char TvCode){

    int intValue = BinaryToInt(TvCode);

    UART_PRINT("String: %d \n\r", intValue);
    //previousCharacterNum;

    //temporary fix to address the 0 int error:
    if(intValue == 0 || intValue == 2){
        if(count1 == 0){
            count1 = 1;
        }
        else{
            count1 = count1;
        }
        intValue = previousintValue;
    }
    else{
        //count1 = 0;
       count1 = count1 + 1;
    }

    if(count1 == 1){
        result = letterArray1[intValue][0];
        previousintValue = intValue;
        return letterArray1[intValue];
    }
    else if(count1 == 2){
        result = letterArray2[intValue][0];
        previousintValue = intValue;
        return letterArray2[intValue];
    }
    else if(count1 == 3){
        result = letterArray3[intValue][0];
        previousintValue = intValue;
        return letterArray3[intValue];
    }
    else if(count1 >= 4){
        /*
         * Check if the value matches the white list, else reset the count to 0
         */
        if(intValue == 32 || intValue == 138){
            count1 = 0;
            previousCharacterNum = 888;
            result = letterArray4[intValue][0];
            previousintValue = intValue;
            return letterArray4[intValue];
        }
        else{
            count1 = 0;
            previousCharacterNum = 888;
            result = letterArray1[intValue][0];
            previousintValue = intValue;
            return letterArray1[intValue];
        }
    }


    return "error";
}

static void delay(unsigned long ulCount){
    int i;

  do{
    ulCount--;
        for (i=0; i< 65535; i++) ;
    }while(ulCount);
}

void drawBitmap1(int16_t x, int16_t y, const uint8_t *bitmap, int16_t width, int16_t height,
                uint16_t color, uint16_t bg_color, bool draw_bg) {
    int16_t byteWidth = (width + 7) / 8; // Bytes per row
    uint8_t byte = 0;
    int16_t j;
    int16_t i;
    for ( j = 0; j < height; j++) {
        for ( i = 0; i < width; i++) {
            if (i & 7) {
                byte >>= 1;
            } else {
                byte = bitmap[j * byteWidth + i / 8];
            }

            // If bit is set in the bitmap, draw the foreground pixel
            if (byte & 0x01) {
                drawPixel(x + i, y + j, color);
            }
            // If drawing background is enabled and bit is not set, draw background
            else if (draw_bg) {
                drawPixel(x + i, y + j, bg_color);
            }
        }
    }
}

/*
 * TODO
 * Enable UART -> UART with both boards and then add function to clear the message that was sent
 */

/*
 * RX on Pin 45
 * TX on pin 16
 */

void InitUART1(void)
{
    // 1. Enable the UART1 peripheral
    MAP_PRCMPeripheralClkEnable(PRCM_UARTA1, PRCM_RUN_MODE_CLK);

    // 3. Configure UART1 with same settings as console UART
    MAP_UARTConfigSetExpClk(UARTA1_BASE,
                           MAP_PRCMPeripheralClockGet(PRCM_UARTA1),
                           115200,
                           (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    // 4. Enable UART1
    MAP_UARTEnable(UARTA1_BASE);
}

// Function to send a string over UART
void UARTSendString(unsigned long ulBase, const char *pucBuffer)
{
    // Calculate the actual string length instead of using sizeof
    unsigned long ulLength = 0;
    while(pucBuffer[ulLength] != '\0') {
        ulLength++;
    }

    // Send each character
    unsigned long i;
    for(i = 0; i < ulLength; i++)
    {
        // Wait until space is available
        while(MAP_UARTSpaceAvail(ulBase) == false);

        // Send the character
        MAP_UARTCharPut(ulBase, pucBuffer[i]);
    }
}

// Function to receive a string from UART
void UARTReceiveString(unsigned long ulBase, char *pucBuffer, unsigned long ulMaxLen)
{
    unsigned long ulCount = 0;

    // Make sure we leave space for null terminator
    ulMaxLen--;

    // Clear our buffer first
    memset(pucBuffer, 0, ulMaxLen + 1);

    // Read available characters up to max length
    while(ulCount < ulMaxLen && MAP_UARTCharsAvail(ulBase))
    {
        pucBuffer[ulCount++] = MAP_UARTCharGet(ulBase);
    }

    // Ensure null termination
    pucBuffer[ulCount] = '\0';
}
//*****************************************************************************
//
//! This function updates the date and time of CC3200.
//!
//! \param None
//!
//! \return
//!     0 for success, negative otherwise
//!
//*****************************************************************************

static int set_time() {
    long retVal;

    g_time.tm_day = DATE;
    g_time.tm_mon = MONTH;
    g_time.tm_year = YEAR;
    g_time.tm_sec = HOUR;
    g_time.tm_hour = MINUTE;
    g_time.tm_min = SECOND;

    retVal = sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,
                          SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
                          sizeof(SlDateTime),(unsigned char *)(&g_time));

    ASSERT_ON_ERROR(retVal);
    return SUCCESS;
}

//*****************************************************************************
//
//! Main 
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************

//black
static unsigned char body[] = {
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0xf0, 0x0f, 0xd8, 0x1b, 0x08, 0x10,
   0x10, 0x08, 0x20, 0x04, 0xe0, 0x07, 0xcc, 0x33, 0xf8, 0x1f, 0xe0, 0x07,
   0xe0, 0x07, 0xc0, 0x03, 0x40, 0x02, 0x60, 0x06 };

//white
static unsigned char mask[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0xf0, 0x0f,
   0xe0, 0x07, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//green
static unsigned char armor[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0xc8, 0x13, 0xc0, 0x03,
   0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04 };

static unsigned char clown_1[] = {
   0xc3, 0x7e, 0x24, 0x42, 0x42, 0x4a, 0x24, 0x18 };
//orange
static unsigned char clown_2[] = {
   0x3c, 0x00, 0x18, 0x3c, 0x3c, 0x34, 0x18, 0x00 };



#define MAX_PROJECTILES 5

typedef struct {
    int x, y;
    int active;
    int speed;
    uint16_t color;
} Projectile;

Projectile projectiles[MAX_PROJECTILES];



void main() {
    int x = 8;
    int y = 63;
    int newSignal = 0;
    int screenidx = 0;
    int MessageIndex = 0;
    long lRetVal = -1;
    //
    // Initialize board configuration
    //
    BoardInit();

    PinMuxConfig();
    I2C_IF_Open(I2C_MASTER_MODE_FST);

    MAP_SPIReset(GSPI_BASE);

        MAP_SPIFIFOEnable(GSPI_BASE, SPI_TX_FIFO || SPI_RX_FIFO);
        //
        // Configure SPI interface
        //
        MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                         SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                         (SPI_SW_CTRL_CS |
                         SPI_4PIN_MODE |
                         SPI_TURBO_OFF |
                         SPI_CS_ACTIVELOW |
                         SPI_WL_8));

    MAP_SPIEnable(GSPI_BASE);

    Adafruit_Init();

    InitUART1();

    ClockInit();

    PinInit();

    prepareArray();

    setArray();
    setArray1();
    setArray2();
    setArray3();
    setArray4();

    fillScreen(BLACK);
    setCursor(8,0);
    Outstr("Sent: ");
    setCursor(8,40);
    Outstr("Received: ");




    while(1){
            // Check Uart
            if(MAP_UARTCharsAvail(UARTA1_BASE)){
                fillRoundRect(0, 16, 128, 16, 0, BLACK);
                setCursor(0,16);

                //store in buffer
                char ReceivedMessage[128];
                UARTReceiveString(UARTA1_BASE, ReceivedMessage, sizeof(ReceivedMessage));

                Outstr(ReceivedMessage);
            }
            if(g_pulseDetected){
                MAP_IntMasterDisable();
                g_pulseDetected = false;
                MAP_IntMasterEnable();
                if(!StartPulse && g_pulseWidth > 50000){
                    StartPulse = true;
                    bits = 0;
                    TvCode = 0;
                    continue;
                }
                if(g_timerTicks - startTimeWatch > 1000000 && (newSignal == 1)){
                    newSignal = 0;
                    startTimeWatch = g_timerTicks;
                    x += 8;
                    screenidx += 1;
                    setCursor(x,y);


                    UserMessage[MessageIndex] = result;
                    MessageIndex++;
                }

                if(StartPulse && bits < 23){
                    if(((g_highPulseDuration > 400 && g_highPulseDuration < 450))){
                        TvCode = (TvCode << 1) | 0;
                        bits++;
                        TvCode = (TvCode << 1) | 0;
                        bits++;
                    }
                    else if ((g_lowPulseDuration > 450 && g_lowPulseDuration < 480)){
                        TvCode = (TvCode << 1) | 1;
                        bits++;
                        TvCode = (TvCode << 1) | 0;
                        bits++;
                    }
                    else if ((g_highPulseDuration > 480 && g_highPulseDuration < 1000)){
                        TvCode = (TvCode << 1) | 0;
                        bits++;
                        TvCode = (TvCode << 1) | 1;
                        bits++;
                    }
                    else if ((g_lowPulseDuration > 480 && g_lowPulseDuration < 1000)){
                        TvCode = (TvCode << 1) | 1;
                        bits++;
                        TvCode = (TvCode << 1) | 1;
                        bits++;
                    }
                }


                if(bits >= 23 && convertToInt(TvCode)){
                    // If we're waiting more than a second move on to the next chunk


                    PrintBinaryToUART(TvCode);


                    if(screenidx > 13){
                        y += 8;
                        x = 8;
                        screenidx = 0;
                    }

                    setCursor(x,y);
                    fillRoundRect(x - 2, y - 2, 10, 10, 0, BLACK);
                    Outstr(letterConversion(TvCode));
                    //new signal, reset timer
                    newSignal = 1;
                    startTimeWatch = g_timerTicks;


                    //send "MUTE"
                    if(BinaryToInt(TvCode) == 134){
                        //UART_PRINT("Mute \n\r");
                        fillRoundRect(0, 120, 128, 16, 0, BLACK);
                        setCursor(0,120);

                        //UART_PRINT("String: %s \n\r", (char*)UserMessage);
                        UserMessage[MessageIndex + 1] = '\0';

                        //UARTSendString(UARTA1_BASE, (const char*)UserMessage);

                        Outstr((char*)UserMessage);

                        break;
                        //clear usermessage
                        int i;
                        for(i = 0; i < 128; i++){
                            UserMessage[i] = '\0';
                        }
                        MessageIndex = 0;

                    }


                    //Backspace "LAST"
                    else if(BinaryToInt(TvCode) == 44){
                        //UART_PRINT("LAST");
                        x -= 8;
                        setCursor(x,y);
                        fillRoundRect(x - 2, y - 2, 10, 10, 0, BLACK);
                        //BackSpaced = true;

                        screenidx -= 1;
                        if(x < 0){
                          x = 8;
                        }
                        if(screenidx < 0){
                           screenidx = 0;
                        }



                        if(MessageIndex != 0){
                            MessageIndex--;
                            UserMessage[MessageIndex] = '\0';
                        }


                    }

                    // Clear the top text by pressing 1 on the remote
                    else if(BinaryToInt(TvCode) == 2){
                        //UART_PRINT("1");

                        fillRoundRect(0, 16, 128, 16, 0, BLACK);
                    }


                    StartPulse = false;
                    bits = 0;
                    g_highPulseDuration = 0;
                    g_lowPulseDuration = 0;
                    TvCode = 0;

                    g_pulseDetected = false;


                    //BackSpaced = false;
                }
                else if(bits >= 24){
                    StartPulse = false;
                    bits = 0;
                    g_highPulseDuration = 0;
                    g_lowPulseDuration = 0;
                    TvCode = 0;
                    g_pulseDetected = false;
                }

                MAP_IntMasterDisable();
                g_pulseDetected = false;
                MAP_IntMasterEnable();
            }
        }

   MAP_IntMasterDisable();
   g_pulseDetected = false;


    int i = 0;
    for (i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].active = 0;
    }
    fillScreen(BLUE);

    signed char x_acc, y_acc;
    int current_x, current_y;
    current_x = 63;
    current_y = 63;
    unsigned int current_color = WHITE;

    int enemy_x = rand() % 120;
    int enemy_y = rand() % 120;


    static const uint16_t colors[] = {
        WHITE
    };
    static const uint16_t fish_colors[] = {
        ORANGE,CYAN,RED,GREEN
    };
    //int color_idx = rand() % 1;
    unsigned int enemy_color = WHITE;
    drawCircle(enemy_y,enemy_x, 4, enemy_color);
    int counter = 0;
    char conv_buf[12];
    int game_speed = 160000;
    int timer_speed = 100;
    int TTL = 10;
    int TTL_counter = 0;
    fillRect(100, 100, 12, 10, BLACK);
    setCursor(100,100);
    sprintf(conv_buf, "%d", TTL);
    Outstr(conv_buf);
    int drawCheck = 0;

    int last_x = current_x;
    int last_y = current_y;


    while(FOREVER)
    {

        if(drawCheck > 5){
            drawCircle(enemy_y,enemy_x, 4, BLUE);
            drawCircle(enemy_y,enemy_x, 4, enemy_color);
            drawCheck = 0;
            fillRect(10, 10, 20, 10, BLUE);
            setCursor(10,10);
            sprintf(conv_buf, "%d", counter);
            Outstr(conv_buf);
            fillRect(100, 100, 12, 10, BLUE);
            setCursor(100,100);
            sprintf(conv_buf, "%d", TTL);
            Outstr(conv_buf);
        }
        drawCheck++;
        //projectiles



        for (i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) {
                projectiles[i].x = 0;
                projectiles[i].y = rand() % 120;
                projectiles[i].active = 1;
                projectiles[i].speed = (rand() % 1) + 2;
                int random_color = rand() % 4;
                projectiles[i].color = fish_colors[random_color];
                break;  // Only spawn one per cycle
            }
        }

        for (i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i].active) {


                fillRect(projectiles[i].y, projectiles[i].x, 8, 8, BLUE);
                //drawCircle(projectiles[i].y, projectiles[i].x, 2, BLUE);
                //fillCircle(projectiles[i].y, projectiles[i].x, 2, BLUE);  // Ensure fill too

                // Move down
                projectiles[i].x += projectiles[i].speed;

                // Check collision with player (doomGuy: 16x16)
                if(abs((current_x + 8) - projectiles[i].x) <= 12 && abs((current_y+8) - projectiles[i].y) <= 12){


                    TTL -= 1;
                    drawPixel(current_y + 6, current_x + 6, RED);
                    drawPixel(current_y - 6, current_x - 6, RED);
                    drawPixel(current_y - 6, current_x + 6, RED);
                    drawPixel(current_y + 6, current_x - 6, RED);
                    drawPixel(current_y + 6, current_x + 12, RED);
                    drawPixel(current_y - 5, current_x - 6, RED);
                    drawPixel(current_y - 2, current_x + 3, RED);
                    drawPixel(current_y + 12, current_x - 10, RED);
                    if (TTL < 0) TTL = 0;

                    fillRect(100, 100, 12, 10, BLUE);
                    setCursor(100, 100);
                    sprintf(conv_buf, "%d", TTL);
                    Outstr(conv_buf);

                    projectiles[i].active = 0;
                    continue;
                }

                // Deactivate if out of screen
                if (projectiles[i].x - 2 > 128) {
                    projectiles[i].active = 0;
                } else {
                    // Draw red circle
                    // Erase previous circle

                    drawBitmap(projectiles[i].y, projectiles[i].x, clown_1, 8, 8, BLACK, BLUE, 0);
                    drawBitmap(projectiles[i].y, projectiles[i].x, clown_2, 8, 8, projectiles[i].color, BLUE, 0);//orange 0xFD20
                    //drawBitmap(projectiles[i].y, projectiles[i].x, clown_3, 8, 8, WHITE, BLUE, 0);
                }
            }
        }





        char x_command[256] = "readreg 0x18 0x3 1";
        char y_command[256] = "readreg 0x18 0x5 1";
        x_acc = ProcessReadRegCommand(strtok(x_command, " \n\r"));
        y_acc = ProcessReadRegCommand(strtok(y_command, " \n\r"));
       // x = ParseNProcessCmd(x_command);
       // y = ParseNProcessCmd(y_command);

        x_acc = x_acc / 5;
        y_acc = y_acc / 5;
//drawCircle(current_y,current_x, 4, BLUE);
        //void drawBitmap(int x, int y, const unsigned char *bitmap, int width, int height, int color, int bg_color, int draw_bg) {

        //clear
        //setCursor(current_y, current_x);
        fillRect(current_y, current_x, 16, 16, BLUE);

        current_x = current_x + x_acc;
        current_y = current_y + y_acc;

        if (current_x > 124){
            current_x = 124;

        }
        if (current_y > 124){
            current_y = 124;

        }
        if (current_x < 2){
            current_x = 2;

        }
        if (current_y < 2){
            current_y = 2;

        }

      //  printf("x = %d\n", current_x);
      //  printf("y = %d\n", current_y);

        if(abs((current_x + 8) - enemy_x) <= 12 && abs((current_y+8) - enemy_y) <= 12){
            TTL = TTL + 1;
            fillRect(100, 100, 12, 10, BLUE);
            setCursor(100,100);
            sprintf(conv_buf, "%d", TTL);
            Outstr(conv_buf);
            counter++;
            if(counter % 10 == 0 && game_speed >= 80000){
                game_speed = game_speed - 10000;
                timer_speed = timer_speed - 10;
            }
            fillRect(10, 10, 20, 10, BLUE);
            setCursor(10,10);
            sprintf(conv_buf, "%d", counter);
            Outstr(conv_buf);

            drawCircle(enemy_y,enemy_x, 4, BLUE);

            drawPixel(enemy_y + 6, enemy_x + 6, enemy_color);
            drawPixel(enemy_y - 6, enemy_x - 6, enemy_color);
            drawPixel(enemy_y - 6, enemy_x + 6, enemy_color);
            drawPixel(enemy_y + 6, enemy_x - 6, enemy_color);
            drawPixel(enemy_y + 6, enemy_x + 12, enemy_color);
            drawPixel(enemy_y - 5, enemy_x - 6, enemy_color);
            drawPixel(enemy_y - 2, enemy_x + 3, enemy_color);
            drawPixel(enemy_y + 12, enemy_x - 10, enemy_color);
            enemy_x = rand() % 110;
            enemy_y = rand() % 110;
            current_color = enemy_color;
            //color_idx = rand() % 7;
            enemy_color = WHITE;


            drawCircle(enemy_y,enemy_x, 4, enemy_color);
        }

        //drawBitmap(int x, int y, const unsigned char *bitmap, int width, int height, int color, int bg_color, int draw_bg);
        //drawBitmap(current_y, current_x, doomGuy, 16, 16, BLUE, BLUE, 0);
        drawBitmap(current_y, current_x, body, 16, 16, BLACK, BLUE, 0);
        drawBitmap(current_y, current_x, mask, 16, 16, CYAN, BLUE, 0);
        drawBitmap(current_y, current_x, armor, 16, 16, 0xFFF0, BLUE, 0);
        //drawCircle(current_y,current_x, 4, current_color);
        MAP_UtilsDelay(game_speed);
        TTL_counter++;
        if(TTL_counter >= timer_speed){
            TTL_counter = 0;
            TTL = TTL - 1;
            fillRect(100, 100, 12, 10, BLUE);
            setCursor(100,100);
            sprintf(conv_buf, "%d", TTL);
            Outstr(conv_buf);
            if(TTL < 1){
                fillRect(30, 61, 60, 12, RED);
                setCursor(32,63);
                Outstr("GAME OVER");
                setCursor(37,78);
                Outstr("SCORE: ");
                setCursor(72,78);
                sprintf(conv_buf, "%d", counter);
                Outstr(conv_buf);
                break;
            }
        }

    }
    MAP_IntMasterEnable();
    fillScreen(BLUE);

   InitTerm();
   ClearTerm();
   UART_PRINT("My terminal works!\n\r");

    // initialize global default app configuration
    g_app_config.host = SERVER_NAME;
    g_app_config.port = GOOGLE_DST_PORT;

    //do IR HERE

    char* dynamicMessage = (char*)UserMessage;
    strcpy(DATA1, "{\"state\":{\"desired\":{\"var\":\"");
    strcat(DATA1, dynamicMessage);
    strcat(DATA1, "\"}}}");


    //Connect the CC3200 to the local access point
    lRetVal = connectToAccessPoint();
    //Set time so that encryption can be used
    lRetVal = set_time();
    fillScreen(BLACK);
    if(lRetVal < 0) {
        fillScreen(RED);
        UART_PRINT("Unable to set time in the device");
        LOOP_FOREVER();
    }
    //Connect to the website with TLS encryption
    fillScreen(GREEN);
    lRetVal = tls_connect();
    if(lRetVal < 0) {
        ERR_PRINT(lRetVal);
    }
    http_post(lRetVal);

    sl_Stop(SL_STOP_TIMEOUT);
    LOOP_FOREVER();
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

static int http_post(int iTLSSockID){
    char acSendBuff[512];
    char acRecvbuff[1460];
    char cCLLength[200];
    char* pcBufHeaders;
    int lRetVal = 0;

    pcBufHeaders = acSendBuff;
    strcpy(pcBufHeaders, POSTHEADER);
    pcBufHeaders += strlen(POSTHEADER);
    strcpy(pcBufHeaders, HOSTHEADER);
    pcBufHeaders += strlen(HOSTHEADER);
    strcpy(pcBufHeaders, CHEADER);
    pcBufHeaders += strlen(CHEADER);
    strcpy(pcBufHeaders, "\r\n\r\n");

    int dataLength = strlen(DATA1);

    strcpy(pcBufHeaders, CTHEADER);
    pcBufHeaders += strlen(CTHEADER);
    strcpy(pcBufHeaders, CLHEADER1);

    pcBufHeaders += strlen(CLHEADER1);
    sprintf(cCLLength, "%d", dataLength);

    strcpy(pcBufHeaders, cCLLength);
    pcBufHeaders += strlen(cCLLength);
    strcpy(pcBufHeaders, CLHEADER2);
    pcBufHeaders += strlen(CLHEADER2);

    strcpy(pcBufHeaders, DATA1);
    pcBufHeaders += strlen(DATA1);

    int testDataLength = strlen(pcBufHeaders);

    UART_PRINT(acSendBuff);


    //
    // Send the packet to the server */
    //
    lRetVal = sl_Send(iTLSSockID, acSendBuff, strlen(acSendBuff), 0);
    if(lRetVal < 0) {
        UART_PRINT("POST failed. Error Number: %i\n\r",lRetVal);
        sl_Close(iTLSSockID);
        //GPIO_IF_LedOn(MCU_RED_LED_GPIO);
        return lRetVal;
    }
    lRetVal = sl_Recv(iTLSSockID, &acRecvbuff[0], sizeof(acRecvbuff), 0);
    if(lRetVal < 0) {
        UART_PRINT("Received failed. Error Number: %i\n\r",lRetVal);
        //sl_Close(iSSLSockID);
        //GPIO_IF_LedOn(MCU_RED_LED_GPIO);
           return lRetVal;
    }
    else {
        acRecvbuff[lRetVal+1] = '\0';
        UART_PRINT(acRecvbuff);
        UART_PRINT("\n\r\n\r");
    }

    return 0;
}
