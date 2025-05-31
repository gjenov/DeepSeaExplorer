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
// Application Name     - I2C 
// Application Overview - The objective of this application is act as an I2C 
//                        diagnostic tool. The demo application is a generic 
//                        implementation that allows the user to communicate 
//                        with any I2C device over the lines. 
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup i2c_demo
//! @{
//
//*****************************************************************************

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

#include "pin_mux_config.h"

// OLED
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "glcdfont.h"
#include "oled_test.h"

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
//                      MACRO DEFINITIONS
//*****************************************************************************
#define APPLICATION_VERSION     "1.4.0"
#define APP_NAME                "I2C Demo"
#define UART_PRINT              Report
#define FOREVER                 1
#define CONSOLE                 UARTA0_BASE
#define FAILURE                 -1
#define SUCCESS                 0
#define RETERR_IF_TRUE(condition) {if(condition) return FAILURE;}
#define RET_IF_ERR(Func)          {int iRetVal = (Func); \
                                   if (SUCCESS != iRetVal) \
                                     return  iRetVal;}

#define SPI_IF_BIT_RATE  1000000
#define TR_BUFF_SIZE     100

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************


//****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS                          
//****************************************************************************

//*****************************************************************************


//*****************************************************************************
//
//! Display the buffer contents over I2C
//!
//! \param  pucDataBuf is the pointer to the data store to be displayed
//! \param  ucLen is the length of the data to be displayed
//!
//! \return none
//! 
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


//****************************************************************************
//
//! Parses the read command parameters and invokes the I2C APIs
//!
//! \param pcInpString pointer to the user command parameters
//! 
//! This function  
//!    1. Parses the read command parameters.
//!    2. Invokes the corresponding I2C APIs
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************
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

//****************************************************************************
//
//! Parses the readreg command parameters and invokes the I2C APIs
//! i2c readreg 0x<dev_addr> 0x<reg_offset> <rdlen>
//!
//! \param pcInpString pointer to the readreg command parameters
//! 
//! This function  
//!    1. Parses the readreg command parameters.
//!    2. Invokes the corresponding I2C APIs
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************
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

//****************************************************************************
//
//! Parses the writereg command parameters and invokes the I2C APIs
//! i2c writereg 0x<dev_addr> 0x<reg_offset> <wrlen> <0x<byte0> [0x<byte1> ...]>
//!
//! \param pcInpString pointer to the readreg command parameters
//! 
//! This function  
//!    1. Parses the writereg command parameters.
//!    2. Invokes the corresponding I2C APIs
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************
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


//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
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

//*****************************************************************************
//
//! Main function handling the I2C example
//!
//! \param  None
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

//FISH 1 CLOWN FISH
/*
//black
static unsigned char clown_1[] = {
   0xc0, 0x03, 0x40, 0x02, 0x20, 0x04, 0xd0, 0x0b, 0x10, 0x08, 0xe8, 0x17,
   0x08, 0x10, 0xfc, 0x3f, 0x02, 0x40, 0xfe, 0x7f, 0x04, 0x20, 0x88, 0x10,
   0xd0, 0x08, 0x10, 0x08, 0x20, 0x04, 0xc0, 0x03 };
//orange
static unsigned char clown_2[] = {
   0x00, 0x00, 0x80, 0x01, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08,
   0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0x30, 0x0f,
   0x20, 0x07, 0xe0, 0x07, 0xc0, 0x03, 0x00, 0x00 };
//white
static unsigned char clown_3[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0xe0, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
*/
//black
static unsigned char clown_1[] = {
   0xc3, 0x7e, 0x24, 0x42, 0x42, 0x4a, 0x24, 0x18 };
//orange
static unsigned char clown_2[] = {
   0x3c, 0x00, 0x18, 0x3c, 0x3c, 0x34, 0x18, 0x00 };



#define MAX_PROJECTILES 5

typedef struct {
    int x, y;
    int active;
} Projectile;

Projectile projectiles[MAX_PROJECTILES];

void main()
{

    //int8_t acc_x;
   // int iRetVal;
   // char acCmdStore[512];
    
    //
    // Initialize board configurations
    //
    BoardInit();
    
    //
    // Configure the pinmux settings for the peripherals exercised
    //
    PinMuxConfig();
    
    
    //
    I2C_IF_Open(I2C_MASTER_MODE_FST);
    
    //initialize SPI here


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

        //initialize projectiles

        int i = 0;
        for (i = 0; i < MAX_PROJECTILES; i++) {
            projectiles[i].active = 0;
        }

//        printAllFonts();
//        MAP_UtilsDelay(16000000);
        fillScreen(BLUE);

    signed char x, y;
    int current_x, current_y;
    current_x = 63;
    current_y = 63;
    unsigned int current_color = WHITE;

    int enemy_x = rand() % 120;
    int enemy_y = rand() % 120;



    static const uint16_t colors[] = {
        WHITE
    };
    //int color_idx = rand() % 1;
    unsigned int enemy_color = WHITE;
    drawCircle(enemy_y,enemy_x, 4, enemy_color);
    int counter = 0;
    char conv_buf[12];
    int game_speed = 16000;
    int timer_speed = 100;
    int TTL = 10;
    int TTL_counter = 0;
    fillRect(100, 100, 12, 10, BLACK);
    setCursor(100,100);
    sprintf(conv_buf, "%d", TTL);
    Outstr(conv_buf);
    while(FOREVER)
    {
        //projectiles

        for (i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) {
                projectiles[i].x = 0;
                projectiles[i].y = rand() % 120;
                projectiles[i].active = 1;
                break;  // Only spawn one per cycle
            }
        }
        for (i = 0; i < MAX_PROJECTILES; i++) {
            if (projectiles[i].active) {


                fillRect(projectiles[i].y, projectiles[i].x, 8, 8, BLUE);
                //drawCircle(projectiles[i].y, projectiles[i].x, 2, BLUE);
                //fillCircle(projectiles[i].y, projectiles[i].x, 2, BLUE);  // Ensure fill too

                // Move down
                projectiles[i].x += 2;

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
                    drawBitmap(projectiles[i].y, projectiles[i].x, clown_2, 8, 8, ORANGE, BLUE, 0);//orange 0xFD20
                    //drawBitmap(projectiles[i].y, projectiles[i].x, clown_3, 8, 8, WHITE, BLUE, 0);
                }
            }
        }




        char x_command[256] = "readreg 0x18 0x3 1";
        char y_command[256] = "readreg 0x18 0x5 1";
        x = ProcessReadRegCommand(strtok(x_command, " \n\r"));
        y = ProcessReadRegCommand(strtok(y_command, " \n\r"));
       // x = ParseNProcessCmd(x_command);
       // y = ParseNProcessCmd(y_command);

        x = x / 5;
        y = y / 5;
//drawCircle(current_y,current_x, 4, BLUE);
        //void drawBitmap(int x, int y, const unsigned char *bitmap, int width, int height, int color, int bg_color, int draw_bg) {

        //clear
        //setCursor(current_y, current_x);
        fillRect(current_y, current_x, 16, 16, BLUE);

        current_x = current_x + x;
        current_y = current_y + y;

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
                return;
            }
        }

    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @
//
//*****************************************************************************

