/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "pic.h"
#include "stdio.h"
#include "network.h"//调用网络推理所需的各种函数
#include "network_data.h"//包含网络权重参数
#include "ai_platform.h"//包含各种定义和宏
#include "touch.h"
#include "delay.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int fps=0,FPS=0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


ai_handle network=AI_HANDLE_NULL;
static float aiInData[AI_NETWORK_IN_1_SIZE]={0};
static float aiOutData[AI_NETWORK_OUT_1_SIZE];
ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];

ai_buffer * ai_input;
ai_buffer * ai_output;

uint16_t lastpos[10][2]; 


static void AI_Init(void)
{
  ai_error err;

  /* Create a local array with the addresses of the activations buffers */
  const ai_handle act_addr[] = { activations };
  /* Create an instance of the model */
  err = ai_network_create_and_init(&network, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    printf("ai_network_create error - type=%d code=%d\r\n", err.type, err.code);
    Error_Handler();
  }
	else 
	{
		printf("AI init success!\r\n");
	}
  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);
}

static void AI_Run(float *pIn, float *pOut)
{
	char logStr[100];
	int count = 0;
	float max = 0;
  ai_i32 batch;
  ai_error err;

  /* Update IO handlers with the data payload */
  ai_input[0].data = AI_HANDLE_PTR(pIn);
  ai_output[0].data = AI_HANDLE_PTR(pOut);

  batch = ai_network_run(network, ai_input, ai_output);
  if (batch != 1) {
    err = ai_network_get_error(network);
    printf("AI ai_network_run error - type=%d code=%d\r\n", err.type, err.code);
    Error_Handler();
  }
  for (uint32_t i = 0; i < AI_NETWORK_OUT_1_SIZE; i++) {

	  sprintf(logStr,"%d  %8.6f\r\n",i,aiOutData[i]);
		
		
	  //printf("%s",logStr);
		
		lcd_show_string(72, 336+72+i*32,336, 32,32, logStr,BLACK);
	  if(max<aiOutData[i])
	  {
		  count = i;
		  max= aiOutData[i];
	  }
  }
	if(aiOutData[count]>0.5)
	{
  sprintf(logStr,"current number is %d   \r\n",count);
	}
	else 
	{
		sprintf(logStr,"current number is none");
	}
  //printf("%s",logStr);
	lcd_show_string(72,336+ 72+10*32,400, 32,32, logStr,BLACK);
}



void load_draw_dialog(void)
{
    lcd_clear(WHITE);                                                /* 清屏 */
    lcd_show_string(lcddev.width - 24, 0, 200, 16, 16, "RST", BLUE); /* 显示清屏区域 */
	lcd_draw_rectangle(72, 72, 336+72-1,336+72-1,  BLUE);
	for (int i=0;i<AI_NETWORK_IN_1_SIZE;i++)
	{
		aiInData[i]=0;
	}
}

void process_data(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1;      /* 计算坐标增量 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0)
    {
        incx = 1;       /* 设置单步方向 */
    }
    else if (delta_x == 0)
    {
        incx = 0;       /* 垂直线 */
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0;       /* 水平线 */
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y)
    {
        distance = delta_x;  /* 选取基本增量坐标轴 */
    }
    else
    {
        distance = delta_y;
    }

    for (t = 0; t <= distance + 1; t++)     /* 画线输出 */
    {
        //lcd_draw_point((row-30)/12, (col-30)/12);    /* 画点 */
			aiInData[((col-72)/12)*28+(row-72)/12 ]=1;
			lcd_draw_point((row-72)/12, (col-72)/12,BLACK);
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/* 10个触控点的颜色(电容触摸屏用) */
const uint16_t POINT_COLOR_TBL[10] = {RED, GREEN, BLUE, BROWN, YELLOW, MAGENTA, CYAN, LIGHTBLUE, BRRED, GRAY};

/**
 * @brief       电容触摸屏测试函数
 * @param       无
 * @retval      无
 */
void ctp_test(void)
{
    uint8_t t = 0;
    uint8_t i = 0;
       /* 最后一次的数据 */
    uint8_t maxp = 5;

        tp_dev.scan(0);

        for (t = 0; t < maxp; t++)
        {
            if ((tp_dev.sta) & (1 << t))
            {
                if (tp_dev.x[t] > 72 &&tp_dev.x[t] < 336+72-1 && tp_dev.y[t] > 72&& tp_dev.y[t] < 336+72-1)  /* 坐标在屏幕范围内 */
                {
                    if (lastpos[t][0] == 0xFFFF)
                    {
                        lastpos[t][0] = tp_dev.x[t];
                        lastpos[t][1] = tp_dev.y[t];
                    }

                    lcd_draw_bline(lastpos[t][0], lastpos[t][1], tp_dev.x[t], tp_dev.y[t], 10, POINT_COLOR_TBL[t]); /* 画线 */
										process_data(lastpos[t][0],  lastpos[t][1],tp_dev.x[t],tp_dev.y[t]);
                    lastpos[t][0] = tp_dev.x[t];
                    lastpos[t][1] = tp_dev.y[t];
										


                }                    
								if (tp_dev.x[t] > (lcddev.width - 24) && tp_dev.y[t] < 20)
                    {
                        load_draw_dialog();/* 清除 */
                    }
            }
            else 
            {
                lastpos[t][0] = 0xFFFF;
            }
        }

    
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
    if(htim->Instance==TIM2){
					//printf("LCD FPS:%d\r\n",fps);
			//FPS=fps;
					//fps=0;
		 ctp_test();
    }
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_FSMC_Init();
  MX_TIM2_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
   lcd_init();  
	 tp_dev.init(); 
	 HAL_TIM_Base_Start_IT(&htim2);
	 AI_Init();
	 printf("LCD ID:%x\r\n", lcddev.id);
	load_draw_dialog();


	// AI_Run(test_img, aiOutData);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//		unsigned char *ch=NULL;
//		sprintf(ch,"LCD ID:%d\r\n", 111);
//		HAL_UART_Transmit(&huart1,ch,sizeof(ch),1000);
//  switch (x)
//        {
//        case 0:
//            lcd_clear(WHITE);
//            break;

//        case 1:
//            lcd_clear(BLACK);
//            break;

//        case 2:
//            lcd_clear(BLUE);
//            break;

//        case 3:
//            lcd_clear(RED);
//            break;

//        case 4:
//            lcd_clear(MAGENTA);
//            break;

//        case 5:
//            lcd_clear(GREEN);
//            break;

//        case 6:
//            lcd_clear(CYAN);
//            break;

//        case 7:
//            lcd_clear(YELLOW);
//            break;

//        case 8:
//            lcd_clear(BRRED);
//            break;

//        case 9:
//            lcd_clear(GRAY);
//            break;

//        case 10:
//            lcd_clear(LGRAY);
//            break;

//        case 11:
//            lcd_clear(BROWN);
//            break;
//        }
AI_Run(aiInData, aiOutData);




//        x++;

//        if (x == 12)
//            x = 0;

		//lcd_show_move_pic(0, 0, 240-1, 400-1	, gImage_catmiao240_400);

//	char*ch=NULL;
	//	sprintf(ch,"FPS=%d",FPS);
		//lcd_show_pic(0, 0, 480-1, 700-1	, gImage_emxq);
	//	lcd_show_string(0, 0,16*4-1,32, 32 , "FPS=", BLACK);
	//	lcd_show_num(16*4-1,0,FPS,3,32,BLACK);

	
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
