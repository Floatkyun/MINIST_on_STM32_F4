#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f4xx_hal.h"


void delay_init(void);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);



#endif
//u16 Get_adc(u16 times)
//{
//	int i;
//	u16 temp;
//	for(i=0;i<times;i++)
//	{
//		HAL_ADC_Start(&hadc1);
//		temp += HAL_ADC_GetValue(&hadc1);
//		delay_ms(5);
//	} 
//	return temp/times;
//}
//void Show_adc(void)
//{
//	float temp = Get_adc(10) * 3.3f/4480;
//	if (temp<0.01f){temp = 0;}
//	else{temp += 0.02;}
//	LCD_ShowFloatNum1(0,120,temp,3,BLACK,WHITE,32);
//}
//int main(void)
//{
//  /* USER CODE BEGIN 1 */

//  /* USER CODE END 1 */

//  /* MCU Configuration--------------------------------------------------------*/

//  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();

//  /* USER CODE BEGIN Init */

//  /* USER CODE END Init */

//  /* Configure the system clock */
//  SystemClock_Config();

//  /* USER CODE BEGIN SysInit */

//  /* USER CODE END SysInit */

//  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_TIM12_Init();
//  MX_SPI5_Init();
//  MX_ADC1_Init();

//	delay_init();
//	LCD_Init();
//	LCD_Fill(0,0,240,240,RED);
//	LCD_ShowChar(0, 0, 'a', BLACK, WHITE, 32, 1);
//	LCD_Fill(0,0,240,240,WHITE);
//  while (1)
//  {
//		Show_adc();
//		delay_ms(500);
//  }
//}


//delay_init();
//	LCD_Init();
//	LCD_Fill(0,0,240,240,WHITE);
//	HAL_TIM_Base_Start(&htim3);
//	u16 aADCxConvertedData[120];
//  HAL_ADC_Start_DMA(&hadc3,(uint32_t *)aADCxConvertedData,120);
//	
//	float temp;
//	u16 lcd_x = 0;
//	u16 lcd_y = 0;

//  while (1)
//  {
//		while(!dma_status){}dma_status=0;
//		for(int i=0;i<120;i++)
//		{
//			temp = aADCxConvertedData[i] * 3.3f/4480;
//			if (temp<0.01f){temp = 0;}
//			else{temp += 0.02;}
//			if(temp>3.3f){temp = 3.3f;}
//			lcd_x = i;
////			temp=3.3*sin(i/120.0f*3.14);
//			lcd_y = 240-temp/3.3f*240; 
//			lcd_y = lcd_y<0?0:lcd_y;
//			lcd_y = lcd_y>240?240:lcd_y;
//			LCD_DrawLine(lcd_x, 0, lcd_x,240,WHITE);
//			LCD_DrawPoint(lcd_x,lcd_y,BLACK);
//		}
//		delay_ms(500);
//		LCD_Fill(0,0,240,240,WHITE);
//		delay_ms(500);
//  }





























