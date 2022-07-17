/* 
 * File:   exti.h
 * Author: ENG-Ahmed Maged
 *
 * Created on April 26, 2022, 2:11 AM
 */

#ifndef EXTI_H
#define	EXTI_H

#include <xc.h>
#include <avr/interrupt.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
    EXTI_Low_Level,
    EXTI_Logic_Change,
    EXTI_Falling_Edge,
    EXTI_Rissing_Edge
}Interrupt_Sense_Control;

void EXTI0_Init(Interrupt_Sense_Control);
void EXTI0_Enable_Interrupt(void);
void EXTI0_Disable_Interrupt(void);

void EXTI0_INT_CallBack(void (*funcPtr)(void));

void EXTI1_Init(Interrupt_Sense_Control);
void EXTI1_Enable_Interrupt(void);
void EXTI1_Disable_Interrupt(void);

void EXTI1_INT_CallBack(void (*funcPtr)(void));

void EXTI2_Init(Interrupt_Sense_Control);
void EXTI2_Enable_Interrupt(void);
void EXTI2_Disable_Interrupt(void);

void EXTI2_INT_CallBack(void (*funcPtr)(void));


#ifdef	__cplusplus
}
#endif

#endif	/* EXTI_H */

