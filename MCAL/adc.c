#include "adc.h"

void (*ADC_CallBackPtr)(void) = 0;

void ADC_Init(ADC_Mode Mode, ADC_Prescaler PresCaler, ADC_Voltage_Refrance VREF)
{
    ADMUX = ((VREF<<6)&0xC0);
    switch(Mode)
    {
        case Single_Conversion:
            ADCSRA = (0x80| (PresCaler&0x07));
            break;
        case Auto_Triggering:
            ADCSRA = (0xA0| (PresCaler&0x07));
            break;
        case Free_Running:
            ADCSRA = (0xA0| (PresCaler&0x07));
            SFIOR &= 0x0F;
            break;
    }
    
}

void ADC_Set_Channel(Channel_MUX MUX)
{
    ADMUX |= (MUX&0x1F);
}
void ADC_Start_Conversion(void)
{
    ADCSRA |= (1<<ADSC);
}
void ADC_Select_Trigger(Trigger_Source Source)
{
    SFIOR |= ((Source<<5)&0xE0); 
}

uint16_t ADC_Get_Value(void)
{
    uint16_t ret;
    while(!(ADCSRA&0x10));
    ADCSRA |= (1<<ADIF);
    ret = ADCL;
    ret += (ADCH * 256);
    return ret;
}
uint8_t ADC_Get_INT_Flag(void)
{
    uint8_t ret;
    if(ADCSRA & 0x10)
    {
        ret = 1;
        ADCSRA |= (1<<ADIF);
    }
    else
    {
        ret = 0;
    }
    return ret;
}
    
void ADC_Enable_Interrupt(void)
{
    ADCSRA |= (1<<ADIE);
}
void ADC_Disable_Interrupt(void)
{
    ADCSRA &= ~(1<<ADIE);
}

void ADC_INT_Callback(void (*funcPtr)(void))
{
    ADC_CallBackPtr = funcPtr;
}

ISR (ADC_vect)
{
    if(ADC_CallBackPtr != 0)
        ADC_CallBackPtr();
}
