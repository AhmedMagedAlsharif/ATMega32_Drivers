#include "i2c.h"

static uint16_t time_out = 0;
static unsigned char I2C_buf[ I2C_BUFFER_SIZE ]; 
static uint8_t I2C_msgSize = 0;
static uint8_t I2C_state = I2C_NO_STATE;
static uint8_t lastTransOK = 0;

void I2C_Init(I2C_Freq_Mode_t freq_mode, I2C_PullUp i2c_pullup)
{
    if(i2c_pullup == I2C_PULLUP_ON)
    {
    GPIO_Init(I2C_PORT, I2C_SCL_PIN|I2C_SDA_PIN, GPIO_Mode_IN_PU);
    }
    else if(i2c_pullup == I2C_PULLUP_OFF)
    {
        
    }
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
	TWBR = ((F_CPU / freq_mode) - 16) / 2;
	TWDR = 0xFF;
	TWCR = (1 << TWEN)|(0 << TWIE)|(0 << TWINT)|(0 << TWEA)|(0 << TWSTA)|(0 << TWSTO)|(0 << TWWC);                                
}        

uint8_t I2C_Transceiver_Busy(void)
{       
  time_out++;
  if (time_out > 1000)
  {
	  time_out = 0;
	  return 0;
  }	  
  return (TWCR & (1 << TWIE));
}

uint8_t I2C_Get_State_Info(void)
{
  time_out = 0;
  while (I2C_Transceiver_Busy()); 
  return (I2C_state);
}

uint8_t I2C_Get_Receive_Flag(void)
{
    uint8_t ret;
    if(lastTransOK != 0)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

void I2C_Start_Transceiver_With_Data(unsigned char *msg, uint8_t msgSize)
{
  uint8_t temp;
  
  time_out = 0;
  while (I2C_Transceiver_Busy());
  I2C_msgSize = msgSize;
  I2C_buf[0]  = msg[0];
  if (!(msg[0] & (TRUE << I2C_READ_BIT)))
  {
    for (temp = 1; temp < msgSize; temp++)
    {
        I2C_buf[ temp ] = msg[ temp ];
    }
  }
  lastTransOK = 0;      
  I2C_state = I2C_NO_STATE;
  TWCR = (1 << TWEN)|(1 << TWIE)|(1 << TWINT)|(0 << TWEA)|(1 << TWSTA)|(0 << TWSTO)|(0 << TWWC);                             
}

void I2C_Start_Transceiver(void)
{  	
  time_out = 0;
  while (I2C_Transceiver_Busy()); 
  lastTransOK = 0;      
  I2C_state = I2C_NO_STATE ;
  TWCR = (1 << TWEN)|(1 << TWIE)|(1 << TWINT)|(0 << TWEA)|(1 << TWSTA)|(0 << TWSTO)|(0 << TWWC);                             
}

uint8_t I2C_Get_Data_From_Transceiver(unsigned char *msg, uint8_t msgSize)
{
  uint8_t i;
  
  time_out = 0;
  while (I2C_Transceiver_Busy());

  if(I2C_Get_Receive_Flag())       
  {                                             
    for (i = 0; i < msgSize; i++)
    {
      msg[i] = I2C_buf[i + 1];
    }
  }
  return(I2C_Get_Receive_Flag());                                   
}


ISR(TWI_vect)
{	
  static uint8_t I2C_bufPtr;    
  
  switch (TWSR)
  {
    case I2C_START:
    case I2C_REP_START:
      I2C_bufPtr = 0;  
	case I2C_MTX_ADR_ACK:
    case I2C_MTX_DATA_ACK:
      if (I2C_bufPtr < I2C_msgSize){
        TWDR = I2C_buf[I2C_bufPtr++];
        TWCR = (1 << TWEN)|
               (1 << TWIE)|(1 << TWINT)|
               (0 << TWEA)|(0 << TWSTA)|(0 << TWSTO)|         
               (0 << TWWC);                                   
   }
    else
   {
        lastTransOK = TRUE;
        TWCR = (1 << TWEN)|
               (0 << TWIE)|(1 << TWINT)|
               (0 << TWEA)|(0 << TWSTA)|(1 << TWSTO)|
               (0 << TWWC);                               
   }
    break;
    case I2C_MRX_DATA_ACK:
      I2C_buf[I2C_bufPtr++] = TWDR;
    case I2C_MRX_ADR_ACK:
      if (I2C_bufPtr < (I2C_msgSize-1))
      {
        TWCR = (1 << TWEN)|
               (1 << TWIE)|(1 << TWINT)|
               (1 << TWEA)|(0 << TWSTA)|(0 << TWSTO)|
               (0 << TWWC);                                   
      }else 
      {
        TWCR = (1 << TWEN)|
               (1 << TWIE)|(1 << TWINT)|
               (0 << TWEA)|(0 << TWSTA)|(0 << TWSTO)|
               (0 << TWWC);                                  
      }    
      break; 
    case I2C_MRX_DATA_NACK:
      I2C_buf[I2C_bufPtr] = TWDR;
      lastTransOK = TRUE;
      TWCR = (1 << TWEN)|
             (0 << TWIE)|(1 << TWINT)|
             (0 << TWEA)|(0 << TWSTA)|(1 << TWSTO)|
             (0 << TWWC);                              
      break;      
    case I2C_ARB_LOST:
      TWCR = (1 << TWEN)|
             (1 << TWIE)|(1 << TWINT)|
             (0 << TWEA)|(1 << TWSTA)|(0 << TWSTO)|
             (0 << TWWC);                                 
      break;
    case I2C_MTX_ADR_NACK:
    case I2C_MRX_ADR_NACK:
    case I2C_MTX_DATA_NACK:
    case I2C_BUS_ERROR:
    default:     
      I2C_state = TWSR;         
	  TWCR = (1 << TWEN)|
	  	     (0 << TWIE)|(1 << TWINT)|
	  	     (0 << TWEA)|(0 << TWSTA)|(1 << TWSTO)|
	  	     (0 << TWWC);
	  	  
	  TWCR = (1 << TWEN)|
             (0 << TWIE)|(0 << TWINT)|
             (0 << TWEA)|(0 << TWSTA)|(0 << TWSTO)|
             (0 << TWWC);                               	  
  }
}
