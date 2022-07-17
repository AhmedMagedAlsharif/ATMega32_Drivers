/* 
 * File:   encoder.h
 * Author: ENG-Ahmed Maged
 *
 * Created on May 18, 2022, 2:38 PM
 */

#ifndef ENCODER_H
#define	ENCODER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "gpio.h"
    
void Encoder_Init(void);
void Encoder_Update(void);
int16_t Encoder_Get_Value(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ENCODER_H */

