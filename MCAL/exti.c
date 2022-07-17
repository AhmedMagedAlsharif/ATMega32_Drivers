#include "exti.h"

void (*EXTI0_CallBackPtr)(void) = 0;
void (*EXTI1_CallBackPtr)(void) = 0;
void (*EXTI2_CallBackPtr)(void) = 0;

void EXTI0_Init(Interrupt_Sense_Control Control)
{
    MCUCR |= (Control&0x03);
}
void EXTI0_Enable_Interrupt(void)
{
    GICR |= (1<<INT0);
}
void EXTI0_Disable_Interrupt(void)
{
    GICR &= ~(1<<INT0);
}

void EXTI0_INT_CallBack(void (*funcPtr)(void))
{
    EXTI0_CallBackPtr = funcPtr;
}

ISR (INT0_vect)
{
    if(EXTI0_CallBackPtr != 0)
        EXTI0_CallBackPtr();
}

void EXTI1_Init(Interrupt_Sense_Control Control)
{
    MCUCR |= ((Control<<2)&0x0C);
}
void EXTI1_Enable_Interrupt(void)
{
    GICR |= (1<<INT1);
}
void EXTI1_Disable_Interrupt(void)
{
    GICR &= ~(1<<INT1);
}

void EXTI1_INT_CallBack(void (*funcPtr)(void))
{
   EXTI1_CallBackPtr =  funcPtr;
}

ISR (INT1_vect)
{
    if(EXTI1_CallBackPtr != 0)
        EXTI1_CallBackPtr();
}

void EXTI2_Init(Interrupt_Sense_Control Control)
{
    if(Control == EXTI_Rissing_Edge)
    {
        MCUCSR |= (1<<ISC2);
    }
    else
    {
        MCUCSR &= ~(1<<ISC2);
    }
}
void EXTI2_Enable_Interrupt(void)
{
    GICR |= (1<<INT2);
}
void EXTI2_Disable_Interrupt(void)
{
    GICR &= ~(1<<INT2);
}

void EXTI2_INT_CallBack(void (*funcPtr)(void))
{
    EXTI2_CallBackPtr = funcPtr;
}

ISR (INT2_vect)
{
    if(EXTI2_CallBackPtr != 0)
        EXTI2_CallBackPtr();
}
