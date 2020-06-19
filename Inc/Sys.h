#ifndef _SYS_H_
#define _SYS_H_
/***********************************************************/

#include "main.h"
/****************************/
void Sys_Init(void);
void Sys_Loop(void);


#define Buzzer_ON()   HAL_GPIO_WritePin(GPIOB,Buzzer_Pin, GPIO_PIN_SET);
#define Buzzer_OFF()   HAL_GPIO_WritePin(GPIOB,Buzzer_Pin, GPIO_PIN_RESET);
/****************************/
static uint8_t Sys_Ptr;
static unsigned long Wait_Cnt,Max_Wait_Cnt;

/****************************/
enum{
State_Test_Case_LCD=0,
State_Test_Case_USR_SW1,
State_Test_Case_USR_SW2,
State_Test_Case_USR_SW3,
State_Test_Case_Led,
State_Test_Case_Buzzer,
State_Test_Case_LM35,
State_Test_Case_Internal_RTC,
State_Test_Case_I2C_EEPROM,
State_Test_Case_I2C_DS1307,
State_Test_Case_UART1,
State_Test_Case_UART2,
State_Test_Case_UART6,
State_Test_Case_USB,
State_Dummy_Wait,
State_Test_Case_Error,
State_All_Test_Passed
};
/****************************/



/****************************/
void Test_Case_LCD(void);
void Test_Case_USR_SW1(void);
void Test_Case_USR_SW2(void);
void Test_Case_USR_SW3(void);
void Test_Case_Buzzer(void);
void Test_Case_LM35(void);
void Test_Case_Led(void);
void Test_Case_Error(void);
void Dummy_Wait(void);
void All_Test_Passed(void);
void Test_Case_USB(void);
void Test_Case_UART6(void);
void Test_Case_UART2(void);
void Test_Case_UART1(void);
void Test_Case_I2C_DS1307(void);
void Test_Case_I2C_EEPROM(void);
void Test_Case_Internal_RTC(void);
/****************************/


/****************************/
static void (*Sys_Func[])(void)={
	Test_Case_LCD,
	Test_Case_USR_SW1,
	Test_Case_USR_SW2,
	Test_Case_USR_SW3,
	Test_Case_Led,
	Test_Case_Buzzer,
	Test_Case_LM35,
	Test_Case_Internal_RTC,
	Test_Case_I2C_EEPROM,
	Test_Case_I2C_DS1307,
	Test_Case_UART1,
	Test_Case_UART2,
	Test_Case_UART6,
	Test_Case_USB,
	Dummy_Wait,
	Test_Case_Error,
	All_Test_Passed,
};
/***********************************************************/
#endif
/***********************************************************/


