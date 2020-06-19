
/***************************/
#include <string.h>
#include <stdio.h>


#include "main.h"
#include "sys.h"
#include "Lcd.h"
/***************************/
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

static RTC_DateTypeDef sdatestructureget;
static RTC_TimeTypeDef stimestructureget;
/***************************/

volatile uint8_t Flag_Usr_SW1,Flag_Usr_SW2,Flag_Usr_SW3;
volatile uint8_t Rx_Flag;
volatile uint8_t Rx_Data[1];


int All_Test_Case_Counter=0;

char Lcd_Buff[16];
/***************************/
void Sys_Init(void){
Max_Wait_Cnt=5000000;
Wait_Cnt = Max_Wait_Cnt+1;
Sys_Ptr = State_Test_Case_LCD;		
	//	Sys_Ptr = State_Test_Case_I2C_EEPROM;
Flag_Usr_SW1 = Flag_Usr_SW2 = Flag_Usr_SW3 = 0;
for(int i=0; i<4; i++){
	HAL_GPIO_TogglePin(GPIOB,Buzzer_Pin);
	HAL_Delay(100);
	}
}
/***************************/




/***************************/
void Sys_Loop(void){
	All_Test_Case_Counter=0;
if(++Wait_Cnt >= Max_Wait_Cnt){
	Wait_Cnt=0;
	Sys_Func[Sys_Ptr]();
	}
}
/***************************/



/***************************/



/***************************/
void Test_Case_LCD(void){
RM_LCD_Init();
RM_LCD_Write_Str(1,0,"WELCOME TO KM");
Sys_Ptr = State_Test_Case_USR_SW1;
	All_Test_Case_Counter++;
}
/***************************/	


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
if(GPIO_Pin == GPIO_PIN_9){
	Flag_Usr_SW1=1;
	return;
	}
if(GPIO_Pin == GPIO_PIN_8){
	Flag_Usr_SW2=1;
	return;
	}
if(GPIO_Pin == GPIO_PIN_0){
	Flag_Usr_SW3=1;
	return;
	}
}


/***************************/
void Test_Case_USR_SW1(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"SWITCH TEST CASE");	
	RM_LCD_Write_Str(0,1,"PRESS USR_SW1:  ");
	Bit=1;
	return;
	}
if(Flag_Usr_SW1 == 1){
	Flag_Usr_SW1=0;
	RM_LCD_Write_Str(0,1,"PRESS USR_SW1:OK");
	Sys_Ptr = State_Test_Case_USR_SW2;
		All_Test_Case_Counter++;
	Bit=0;
	Buzzer_ON();
	}
}
/***************************/



/***************************/
void Test_Case_USR_SW2(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"SWITCH TEST CASE");	
	RM_LCD_Write_Str(0,1,"PRESS USR_SW2:  ");
	Bit=1;
	return;
	}
if(Flag_Usr_SW2 == 1){
	Flag_Usr_SW2=0;
	RM_LCD_Write_Str(0,1,"PRESS USR_SW2:OK");
	Sys_Ptr = State_Test_Case_USR_SW3;
		All_Test_Case_Counter++;
	Bit=0;
	Buzzer_ON();
	}
}
/***************************/


/***************************/
void Test_Case_USR_SW3(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"SWITCH TEST CASE");	
	RM_LCD_Write_Str(0,1,"PRESS WAKE_UP:  ");
	Bit=1;
	return;
	}
if(Flag_Usr_SW3 == 1){
	Flag_Usr_SW3=0;
	RM_LCD_Write_Str(0,1,"PRESS WAKE_UP:OK");
	Sys_Ptr = State_Test_Case_Buzzer;
		All_Test_Case_Counter++;
	Bit=0;
	Buzzer_ON();
	}
}
/***************************/







/***************************/
void Test_Case_Buzzer(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"BUZZER TEST CASE");	
	RM_LCD_Write_Str(0,1,"PRESS WAKEUP KEY");	
	Bit=1;
	return;
	}
if(Flag_Usr_SW3 == 1){
	Flag_Usr_SW3=0;
	RM_LCD_Write_Str(0,1,"  BUZZER IS OK  ");
	Sys_Ptr = State_Test_Case_LM35;
	Bit=0;
	Buzzer_OFF();
		All_Test_Case_Counter++;
	return;
	}
Wait_Cnt = (Max_Wait_Cnt-500000);
//	Wait_Cnt = 4500000;
HAL_GPIO_TogglePin(GPIOB,Buzzer_Pin);
}
/***************************/


/***************************/
void Test_Case_LM35(void){
static char Bit=0,Temp_Value[10];
	static int temp1,i=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0," ADC1 TEST CASE ");	
	RM_LCD_Write_Str(0,1,"ADC VALUE:");	
	Bit=1;
	Flag_Usr_SW3=0;
	/************************/
	for(i=0;i<10;i++){
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1,10);
		temp1=HAL_ADC_GetValue(&hadc1);
		//temp1=(temp1*350.00);
		//temp1=(temp1/4096);
		temp1=(temp1/12);
		sprintf(Temp_Value, "%d", temp1);
		RM_LCD_Goto(11,1);
		//RM_LCD_PutStr("TEMP: ");
		RM_LCD_PutStr(Temp_Value);
		RM_LCD_Put_Char(0xDF);
		RM_LCD_Put_Char('C');
		HAL_Delay(300);
		HAL_Delay(1000);
	}
	  //RM_LCD_Clear();
	
	
	/************************/
	return;
	}
if(Flag_Usr_SW3 == 1){
	Flag_Usr_SW3=0;
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0," ADC1 TEST: OK  ");
	Sys_Ptr = State_Test_Case_Led;
	All_Test_Case_Counter++;
	Bit=0;
	return;
	}
}
/***************************/




/***************************/
void Test_Case_Led(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"  LED BLINKING  ");	
	RM_LCD_Write_Str(0,1,"PRESS WAKEUP KEY");	
	Bit=1;
	HAL_GPIO_WritePin(USER_LED_1_GPIO_Port, USER_LED_1_Pin, GPIO_PIN_RESET);
	return;
	}	
if(Flag_Usr_SW3 == 1){
	Flag_Usr_SW3=0;
	RM_LCD_Write_Str(0,0," LED TEST IS OK ");
	Sys_Ptr = State_Test_Case_UART1;
		All_Test_Case_Counter++;
	Bit=0;
	HAL_GPIO_WritePin(USER_LED_1_GPIO_Port, USER_LED_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(USER_LED_2_GPIO_Port, USER_LED_2_Pin, GPIO_PIN_SET);
	return;
	}
Wait_Cnt = (Max_Wait_Cnt-500000);
HAL_GPIO_TogglePin(USER_LED_1_GPIO_Port,USER_LED_1_Pin);
HAL_GPIO_TogglePin(USER_LED_2_GPIO_Port,USER_LED_2_Pin);
}
/***************************/


/***************************/
void Test_Case_Error(void){
}
/***************************/


/***************************/
void Dummy_Wait(void){
	
}
/***************************/


/***************************/
void All_Test_Passed(void){
static char Bit=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	if(State_All_Test_Passed==11)
	{
	RM_LCD_Write_Str(0,0," ALL TEST CASES ");	
	RM_LCD_Write_Str(0,1,"   * PASSED *   ");	
	}
	Bit=1;
	return;
	}		
}
/***************************/


/***************************/
void Test_Case_USB(void){
}
/***************************/


/***************************/
void Test_Case_UART6(void){
	static char Bit=0;
char Tx_Data[1];
Tx_Data[0]	=0x43;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"UART-6 TEST CASE");	
	RM_LCD_Write_Str(0,1,"SHORT Tx AND Rx: ");	
	Bit=1;
	Rx_Flag=0;
	HAL_UART_Receive_IT(&huart6,(uint8_t *)Rx_Data,1);
	__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
	return;
	}
if(Rx_Flag){
	Rx_Flag=0;
	RM_LCD_Write_Str(0,1,"RECEIVED DATA: C");	
	Sys_Ptr = State_Test_Case_Internal_RTC;
		All_Test_Case_Counter++;
	Buzzer_ON();
	return;
	}
 __HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);
 HAL_UART_Transmit(&huart6,(uint8_t *)Tx_Data,1,1000);
}
/***************************/


/***************************/
void Test_Case_UART2(void){
static char Bit=0;
char Tx_Data[1];
Tx_Data[0]	=0x42;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"UART-2 TEST CASE");	
	RM_LCD_Write_Str(0,1,"SHORT Tx AND Rx: ");	
	Bit=1;
	Rx_Flag=0;
	HAL_UART_Receive_IT(&huart2,(uint8_t *)Rx_Data,1);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	return;
	}
if(Rx_Flag){
	Rx_Flag=0;
	RM_LCD_Write_Str(0,1,"RECEIVED DATA: B");	
	Sys_Ptr = State_Test_Case_UART6;
	All_Test_Case_Counter++;
	Buzzer_ON();
	return;
	}
__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
HAL_UART_Transmit(&huart2,(uint8_t *)Tx_Data,1,1000);
}
/***************************/







/***************************/
void Test_Case_UART1(void){
static char Bit=0;
char Tx_Data[1];
Tx_Data[0]	=0x41;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"UART-1 TEST CASE");	
  RM_LCD_Write_Str(0,1,"SHORT Tx AND Rx: ");	
	Bit=1;
	Rx_Flag=0;
	HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx_Data,1);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	return;
	}
if(Rx_Flag){
	Rx_Flag=0;
	RM_LCD_Write_Str(0,1,"RECEIVED DATA: A");	
	Sys_Ptr = State_Test_Case_UART2;
	All_Test_Case_Counter++;
	Buzzer_ON();
	return;
	}
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  HAL_UART_Transmit(&huart1,(uint8_t *)Tx_Data,1,1000);
}
/***************************/


/***************************/
void Test_Case_I2C_DS1307(void){
}
/***************************/




/***************************/
void Test_Case_I2C_EEPROM(void){
static char Bit=0;
static char Flag=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"  I2C TEST CASE ");	
	Bit=1;
	return;
	}		
if(Flag==0){
	
	
		 int i;
	   char I2c_Number_Buf[10];
	   for(i=0;i<128;i++)
     if((HAL_I2C_IsDeviceReady(&hi2c1,(i<<1),1,10))==HAL_OK){
      RM_LCD_Clear();
	    sprintf(I2c_Number_Buf,"%d",i);
			if(i==0x68){
	    RM_LCD_Write_Str(0 ,1,"DS1307 Found:");
	    RM_LCD_Write_Str(13 ,1,I2c_Number_Buf);
	    HAL_Delay(1000);
			  HAL_Delay(1000);
			 }
			 	else if(i==0x50){
			     RM_LCD_Write_Str(0 ,1,"EEPROM Found:");
	    RM_LCD_Write_Str(13 ,1,I2c_Number_Buf);
					 HAL_Delay(1000);
	    HAL_Delay(1000);
			 	//Flag=1;
				}
				else
				{					
					 RM_LCD_Write_Str(0 ,1,"Device Found:");
					 RM_LCD_Write_Str(13 ,1,I2c_Number_Buf);
					 HAL_Delay(1000);
			     HAL_Delay(500);
      }
		 //Flag=1;
			Sys_Ptr = State_Test_Case_LCD;
				//All_Test_Case_Counter++;
		 }
 }
}
/***************************/


/***************************/
void Test_Case_Internal_RTC(void){
static char Bit=0;
static char Flag=0;
if(!Bit){
	Buzzer_OFF();
	RM_LCD_Init();
	RM_LCD_Write_Str(0,0,"  INTERNAL RTC  ");	
	Bit=1;
	return;
	}		
if(Flag_Usr_SW3 == 1){
	Flag_Usr_SW3=0;
	RM_LCD_Write_Str(0,0,"INTERNAL RTC: OK");	
	Sys_Ptr = State_Test_Case_I2C_EEPROM;
	Buzzer_ON();
	Bit=0;
	return;
	}
HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BCD);
HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BCD);
if(Flag==0){
	sprintf(Lcd_Buff, "TIME: %02x:%02x:%02x",stimestructureget.Hours,stimestructureget.Minutes,stimestructureget.Seconds); 
	RM_LCD_Write_Str(0,1,Lcd_Buff); 
	RM_LCD_Write_Str(14,1,"  ");
	Flag=1;
	return;
	}
sprintf(Lcd_Buff, "DATE: %02x-%02x-20%02x",sdatestructureget.Date,sdatestructureget.Month,sdatestructureget.Year); 
RM_LCD_Write_Str(0,1,Lcd_Buff); 
Flag=0;

}
/***************************/



