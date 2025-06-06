//*****************************************************************************
// timer_if.h
//
// timer interface header file: Prototypes and Macros for timer APIs
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

#ifndef __TIMER_IF_H__
#define __TIMER_IF_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************/
/*								MACROS										*/
/****************************************************************************/

// Adjusted the timer macro to make it microseconds to ticks

#define SYS_CLK				    80000000
#define MILLISECONDS_TO_TICKS(ms)   ((SYS_CLK/1000000) * (ms))
#define PERIODIC_TEST_LOOPS     5

extern void Timer_IF_Init( unsigned long ePeripheralc, unsigned long ulBase,
    unsigned long ulConfig, unsigned long ulTimer, unsigned long ulValue);
extern void Timer_IF_IntSetup(unsigned long ulBase, unsigned long ulTimer, 
                   void (*TimerBaseIntHandler)(void));
extern void Timer_IF_InterruptClear(unsigned long ulBase);
extern void Timer_IF_Start(unsigned long ulBase, unsigned long ulTimer, 
                unsigned long ulValue);
extern void Timer_IF_Stop(unsigned long ulBase, unsigned long ulTimer);
extern void Timer_IF_ReLoad(unsigned long ulBase, unsigned long ulTimer, 
                unsigned long ulValue);
extern unsigned int Timer_IF_GetCount(unsigned long ulBase, unsigned long ulTimer);
void Timer_IF_DeInit(unsigned long ulBase,unsigned long ulTimer);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif
#endif //  __TIMER_IF_H__
