/* 
 * File:   adc.h
 * Author: ENG-Ahmed Maged
 *
 * Created on 19 ??????, 2021, 05:49 ?
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <avr/interrupt.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum
    {
        AREF,           /*Analog Reference Pin*/
        AVCC,           
        Reserved,
        Internal_HalfVolt
    }ADC_Voltage_Refrance;
    
    typedef enum
    {
        ADC_No_Prescaler,
        ADC_Prescaler_2,
        ADC_Prescaler_4,
        ADC_Prescaler_8,
        ADC_Prescaler_16,
        ADC_Prescaler_32,
        ADC_Prescaler_64,
        ADC_Prescaler_128
    }ADC_Prescaler;
    
    typedef enum
    {
        Single_Conversion,
        Auto_Triggering,
        Free_Running
    }ADC_Mode;
    
    typedef enum
    {
        ADC0 = 0x0,
        ADC1,
        ADC2,
        ADC3,
        ADC4,
        ADC5,
        ADC6,
        ADC7
    }Channel_MUX;
    
    typedef enum
    {
        Free_Running_Mode,
        Analog_Comparator,
        EXTI0,
        Timer0_CompareMatch,
        Timer0_OverFlow,
        Timer1_CompareMatchB,
        Timer1_OverFlow,
        Timer1_CaptureEvent
    }Trigger_Source;
    
    void ADC_Init(ADC_Mode, ADC_Prescaler, ADC_Voltage_Refrance);
    void ADC_Set_Channel(Channel_MUX);
    void ADC_Start_Conversion(void);
    void ADC_Select_Trigger(Trigger_Source);
    uint16_t ADC_Get_Value(void);
    uint8_t ADC_Get_INT_Flag(void);
    
    void ADC_Enable_Interrupt(void);
    void ADC_Disable_Interrupt(void);
    
    void ADC_INT_Callback(void (*funcPtr)(void));

#endif	/* ADC_H */

