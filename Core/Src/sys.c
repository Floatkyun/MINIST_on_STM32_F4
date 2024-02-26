/**
 ****************************************************************************************************
 * @file        sys.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       系统初始化代码(包括时钟配置/中断管理/GPIO设置等)
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20211014
 * 第一次发布
 ****************************************************************************************************
 */

#include "sys.h"


/**
 * @brief       设置中断向量表偏移地址
 * @param       baseaddr: 基址
 * @param       offset: 偏移量
 * @retval      无
 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{
    /* 设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留 */
    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

/**
 * @brief       执行: WFI指令(执行完该指令进入低功耗状态, 等待中断唤醒)
 * @param       无
 * @retval      无
 */
void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

/**
 * @brief       关闭所有中断(但是不包括fault和NMI中断)
 * @param       无
 * @retval      无
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       开启所有中断
 * @param       无
 * @retval      无
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

/**
 * @brief       设置栈顶地址
 * @note        左侧若出现红X, 属于MDK误报, 实际是没问题的
 * @param       addr: 栈顶地址
 * @retval      无
 */
void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);    /* 设置栈顶地址 */
}

/**
 * @brief       进入待机模式
 * @param       无
 * @retval      无
 */
void sys_standby(void)
{
    __HAL_RCC_PWR_CLK_ENABLE();    /* 使能电源时钟 */
    SET_BIT(PWR->CR, PWR_CR_PDDS); /* 进入待机模式 */
}

/**
 * @brief       系统软复位
 * @param       无
 * @retval      无
 */
void sys_soft_reset(void)
{
    NVIC_SystemReset();
}

/**
 * @brief       时钟设置函数
 * @param       plln: 主PLL倍频系数(PLL倍频), 取值范围: 64~432.
 * @param       pllm: 主PLL和音频PLL预分频系数(进PLL之前的分频), 取值范围: 2~63.
 * @param       pllp: 主PLL的p分频系数(PLL之后的分频), 分频后作为系统时钟, 取值范围: 2, 4, 6, 8.(仅限这4个值)
 * @param       pllq: 主PLL的q分频系数(PLL之后的分频), 取值范围: 2~15.
 * @note
 *
 *              Fvco: VCO频率
 *              Fsys: 系统时钟频率, 也是主PLL的p分频输出时钟频率
 *              Fq:   主PLL的q分频输出时钟频率
 *              Fs:   主PLL输入时钟频率, 可以是HSI, HSE等.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              外部晶振为 8M的时候, 推荐值: plln = 336, pllm = 8, pllp = 2, pllq = 7.
 *              得到:Fvco = 8 * (336 / 8) = 336Mhz
 *                   Fsys = pll_p_ck = 336 / 2 = 168Mhz
 *                   Fq   = pll_q_ck = 336 / 7 = 48Mhz
 *
 *              F407默认需要配置的频率如下:
 *              CPU频率(HCLK) = pll_p_ck = 168Mhz
 *              AHB1/2/3(rcc_hclk1/2/3) = 168Mhz
 *              APB1(rcc_pclk1) = pll_p_ck / 4 = 42Mhz
 *              APB1(rcc_pclk2) = pll_p_ck / 2 = 84Mhz
 *
 * @retval      错误代码: 0, 成功; 1, 错误;
 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef rcc_osc_init = {0};
    RCC_ClkInitTypeDef rcc_clk_init = {0};

    __HAL_RCC_PWR_CLK_ENABLE();                                         /* 使能PWR时钟 */

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);      /* 设置调压器输出电压级别，以便在器件未以最大频率工作 */

    /* 使能HSE，并选择HSE作为PLL时钟源，配置PLL1，开启USB时钟 */
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;        /* 时钟源为HSE */
    rcc_osc_init.HSEState = RCC_HSE_ON;                          /* 打开HSE */
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;                      /* 打开PLL */
    rcc_osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;              /* PLL时钟源选择HSE */
    rcc_osc_init.PLL.PLLN = plln;
    rcc_osc_init.PLL.PLLM = pllm;
    rcc_osc_init.PLL.PLLP = pllp;
    rcc_osc_init.PLL.PLLQ = pllq;
    ret = HAL_RCC_OscConfig(&rcc_osc_init);                      /* 初始化RCC */
    if(ret != HAL_OK)
    {
        return 1;                                                /* 时钟初始化失败，可以在这里加入自己的处理 */
    }

    /* 选中PLL作为系统时钟源并且配置HCLK,PCLK1和PCLK2 */
    rcc_clk_init.ClockType = ( RCC_CLOCKTYPE_SYSCLK \
                                    | RCC_CLOCKTYPE_HCLK \
                                    | RCC_CLOCKTYPE_PCLK1 \
                                    | RCC_CLOCKTYPE_PCLK2);

    rcc_clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;         /* 设置系统时钟时钟源为PLL */
    rcc_clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;                /* AHB分频系数为1 */
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV4;                 /* APB1分频系数为4 */
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV2;                 /* APB2分频系数为2 */
    ret = HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);   /* 同时设置FLASH延时周期为5WS，也就是6个CPU周期 */
    if(ret != HAL_OK)
    {
        return 1;                                                /* 时钟初始化失败 */
    }
    
    /* STM32F405x/407x/415x/417x Z版本的器件支持预取功能 */
    if (HAL_GetREVID() == 0x1001)
    {
        __HAL_FLASH_PREFETCH_BUFFER_ENABLE();                    /* 使能flash预取 */
    }
    return 0;
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief       当编译提示出错的时候此函数用来报告错误的文件和所在行
 * @param       file：指向源文件
 *              line：指向在文件中的行数
 * @retval      无
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    while (1)
    {
    }
}
#endif




