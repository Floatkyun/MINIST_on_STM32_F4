/**
 ****************************************************************************************************
 * @file        touch.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       触摸屏 驱动代码
 *   @note      支持电阻/电容式触摸屏
 *              触摸屏驱动（支持ADS7843/7846/UH7843/7846/XPT2046/TSC2046/GT9147/GT9271/FT5206/GT1151等）代码
 *
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
 * V1.0 20211025
 * 第一次发布
 * V1.1 20230529
 * 1，新增对ST7796 3.5寸屏 GT1151的支持
 * 2，新增对ILI9806 4.3寸屏 GT1151的支持
 ****************************************************************************************************
 */

#ifndef __TOUCH_H__
#define __TOUCH_H__

//#include "./SYSTEM/sys/sys.h"
#include "gt9xxx.h"
#include "ft5206.h"


/******************************************************************************************/
/* 电阻触摸屏驱动IC T_PEN/T_CS/T_MISO/T_MOSI/T_SCK 引脚 定义 */

#define T_PEN_GPIO_PORT                 GPIOB
#define T_PEN_GPIO_PIN                  GPIO_PIN_1
#define T_PEN_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define T_CS_GPIO_PORT                  GPIOC
#define T_CS_GPIO_PIN                   GPIO_PIN_13
#define T_CS_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define T_MISO_GPIO_PORT                GPIOB
#define T_MISO_GPIO_PIN                 GPIO_PIN_2
#define T_MISO_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define T_MOSI_GPIO_PORT                GPIOF
#define T_MOSI_GPIO_PIN                 GPIO_PIN_11
#define T_MOSI_GPIO_CLK_ENABLE()        do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

#define T_CLK_GPIO_PORT                 GPIOB
#define T_CLK_GPIO_PIN                  GPIO_PIN_0
#define T_CLK_GPIO_CLK_ENABLE()         do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 所在IO口时钟使能 */

/******************************************************************************************/

/* 电阻触摸屏控制引脚 */
#define T_PEN           HAL_GPIO_ReadPin(T_PEN_GPIO_PORT, T_PEN_GPIO_PIN)             /* T_PEN */
#define T_MISO          HAL_GPIO_ReadPin(T_MISO_GPIO_PORT, T_MISO_GPIO_PIN)           /* T_MISO */

#define T_MOSI(x)     do{ x ? \
                          HAL_GPIO_WritePin(T_MOSI_GPIO_PORT, T_MOSI_GPIO_PIN, GPIO_PIN_SET) : \
                          HAL_GPIO_WritePin(T_MOSI_GPIO_PORT, T_MOSI_GPIO_PIN, GPIO_PIN_RESET); \
                      }while(0)     /* T_MOSI */

#define T_CLK(x)      do{ x ? \
                          HAL_GPIO_WritePin(T_CLK_GPIO_PORT, T_CLK_GPIO_PIN, GPIO_PIN_SET) : \
                          HAL_GPIO_WritePin(T_CLK_GPIO_PORT, T_CLK_GPIO_PIN, GPIO_PIN_RESET); \
                      }while(0)     /* T_CLK */

#define T_CS(x)       do{ x ? \
                          HAL_GPIO_WritePin(T_CS_GPIO_PORT, T_CS_GPIO_PIN, GPIO_PIN_SET) : \
                          HAL_GPIO_WritePin(T_CS_GPIO_PORT, T_CS_GPIO_PIN, GPIO_PIN_RESET); \
                      }while(0)     /* T_CS */


#define TP_PRES_DOWN    0x8000  /* 触屏被按下 */
#define TP_CATH_PRES    0x4000  /* 有按键按下了 */
#define CT_MAX_TOUCH    10      /* 电容屏支持的点数,固定为5点 */

/* 触摸屏控制器 */
typedef struct
{
    uint8_t (*init)(void);      /* 初始化触摸屏控制器 */
    uint8_t (*scan)(uint8_t);   /* 扫描触摸屏.0,屏幕扫描;1,物理坐标; */
    void (*adjust)(void);       /* 触摸屏校准 */
    uint16_t x[CT_MAX_TOUCH];   /* 当前坐标 */
    uint16_t y[CT_MAX_TOUCH];   /* 电容屏有最多10组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
                                 * x[9],y[9]存储第一次按下时的坐标.
                                 */

    uint16_t sta;               /* 笔的状态
                                 * b15:按下1/松开0;
                                 * b14:0,没有按键按下;1,有按键按下.
                                 * b13~b10:保留
                                 * b9~b0:电容触摸屏按下的点数(0,表示未按下,1表示按下)
                                 */

    /* 5点校准触摸屏校准参数(电容屏不需要校准) */
    float xfac;                 /* 5点校准法x方向比例因子 */
    float yfac;                 /* 5点校准法y方向比例因子 */
    short xc;                   /* 中心X坐标物理值(AD值) */
    short yc;                   /* 中心Y坐标物理值(AD值) */

    /* 新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
     * b0:0, 竖屏(适合左右为X坐标,上下为Y坐标的TP)
     *    1, 横屏(适合左右为Y坐标,上下为X坐标的TP)
     * b1~6: 保留.
     * b7:0, 电阻屏
     *    1, 电容屏
     */
    uint8_t touchtype;
} _m_tp_dev;

extern _m_tp_dev tp_dev;        /* 触屏控制器在touch.c里面定义 */


/* 电阻屏函数 */

static void tp_write_byte(uint8_t data);                /* 向控制芯片写入一个数据 */
static uint16_t tp_read_ad(uint8_t cmd);                /* 读取AD转换值 */
static uint16_t tp_read_xoy(uint8_t cmd);               /* 带滤波的坐标读取(X/Y) */
static void tp_read_xy(uint16_t *x, uint16_t *y);       /* 双方向读取(X+Y) */
static uint8_t tp_read_xy2(uint16_t *x, uint16_t *y);   /* 带加强滤波的双方向坐标读取 */
static void tp_draw_touch_point(uint16_t x, uint16_t y, uint16_t color);    /* 画一个坐标校准点 */
static void tp_adjust_info_show(uint16_t xy[5][2], double px, double py);   /* 显示校准信息 */

uint8_t tp_init(void);                 /* 初始化 */
static uint8_t tp_scan(uint8_t mode);  /* 扫描 */
void tp_adjust(void);                  /* 触摸屏校准 */
void tp_save_adjust_data(void);        /* 保存校准参数 */
uint8_t tp_get_adjust_data(void);      /* 读取校准参数 */
void tp_draw_big_point(uint16_t x, uint16_t y, uint16_t color); /* 画一个大点 */

#endif

















