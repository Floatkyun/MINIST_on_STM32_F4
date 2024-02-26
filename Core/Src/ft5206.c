/**
 ****************************************************************************************************
 * @file        ft5206.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       7寸电容触摸屏-FT5206/FT5426 驱动代码
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
 * 兼容7寸 CST340触摸屏
 ****************************************************************************************************
 */

#include "string.h"
#include "lcd.h"
#include "touch.h"
#include "ctiic.h"
#include "ft5206.h"
#include "usart.h"
#include "delay.h"


/**
 * @brief       向FT5206写入一次数据
 * @param       reg : 起始寄存器地址
 * @param       buf : 数据缓缓存区
 * @param       len : 写数据长度
 * @retval      0, 成功; 1, 失败;
 */
uint8_t ft5206_wr_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    uint8_t ret = 0;
    
    ct_iic_start();
    ct_iic_send_byte(FT5206_CMD_WR);    /* 发送写命令 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg & 0XFF);       /* 发送低8位地址 */
    ct_iic_wait_ack();

    for (i = 0; i < len; i++)
    {
        ct_iic_send_byte(buf[i]);       /* 发数据 */
        ret = ct_iic_wait_ack();

        if (ret)break;
    }

    ct_iic_stop();  /* 产生一个停止条件 */
    return ret;
}

/**
 * @brief       从FT5206读出一次数据
 * @param       reg : 起始寄存器地址
 * @param       buf : 数据缓缓存区
 * @param       len : 读数据长度
 * @retval      无
 */
void ft5206_rd_reg(uint16_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    
    ct_iic_start();
    ct_iic_send_byte(FT5206_CMD_WR);    /* 发送写命令 */
    ct_iic_wait_ack();
    ct_iic_send_byte(reg & 0XFF);       /* 发送低8位地址 */
    ct_iic_wait_ack();
    ct_iic_start();
    ct_iic_send_byte(FT5206_CMD_RD);    /* 发送读命令 */
    ct_iic_wait_ack();

    for (i = 0; i < len; i++)
    {
        buf[i] = ct_iic_read_byte(i == (len - 1) ? 0 : 1);  /* 读取数据 */
    }

    ct_iic_stop();  /* 产生一个停止条件 */
}

/**
 * @brief       初始化FT5206触摸屏
 * @param       无
 * @retval      0, 初始化成功; 1, 初始化失败;
 */
uint8_t ft5206_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    uint8_t temp[2];

    FT5206_RST_GPIO_CLK_ENABLE();   /* RST引脚时钟使能 */
    FT5206_INT_GPIO_CLK_ENABLE();   /* INT引脚时钟使能 */

    gpio_init_struct.Pin = FT5206_RST_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 高速 */
    HAL_GPIO_Init(FT5206_RST_GPIO_PORT, &gpio_init_struct); /* 初始化RST引脚 */

    gpio_init_struct.Pin = FT5206_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 高速 */
    HAL_GPIO_Init(FT5206_INT_GPIO_PORT, &gpio_init_struct); /* 初始化INT引脚 */

    ct_iic_init();      /* 初始化电容屏的I2C总线 */
    FT5206_RST(0);      /* 复位 */
    delay_ms(20);
    FT5206_RST(1);      /* 释放复位 */
    delay_ms(50);
    temp[0] = 0;
    ft5206_wr_reg(FT5206_DEVIDE_MODE, temp, 1); /* 进入正常操作模式 */
    ft5206_wr_reg(FT5206_ID_G_MODE, temp, 1);   /* 查询模式 */
    temp[0] = 22;                               /* 触摸有效值，22，越小越灵敏 */
    ft5206_wr_reg(FT5206_ID_G_THGROUP, temp, 1);/* 设置触摸有效值 */
    temp[0] = 12;                               /* 激活周期，不能小于12，最大14 */
    ft5206_wr_reg(FT5206_ID_G_PERIODACTIVE, temp, 1);
    
    /* 读取版本号，参考值：0x3003 */
    ft5206_rd_reg(FT5206_ID_G_LIB_VERSION, &temp[0], 2);
    
    if ((temp[0] == 0X30 && temp[1] == 0X03) || temp[1] == 0X01 || temp[1] == 0X02 || (temp[0] == 0x0 && temp[1] == 0X0))   /* 版本:0X3003/0X0001/0X0002/CST340 */
    {
        printf("CTP ID:%x\r\n", ((uint16_t)temp[0] << 8) + temp[1]);
        return 0;
    }

    return 1;
}

/* FT5206 5个触摸点 对应的寄存器表 */
const uint16_t FT5206_TPX_TBL[5] = {FT5206_TP1_REG, FT5206_TP2_REG, FT5206_TP3_REG, FT5206_TP4_REG, FT5206_TP5_REG};

/**
 * @brief       扫描触摸屏(采用查询方式)
 * @param       mode : 电容屏未用到次参数, 为了兼容电阻屏
 * @retval      当前触屏状态
 *   @arg       0, 触屏无触摸; 
 *   @arg       1, 触屏有触摸;
 */
uint8_t ft5206_scan(uint8_t mode)
{
    uint8_t sta = 0;
    uint8_t buf[4];
    uint8_t i = 0;
    uint8_t res = 0;
    uint16_t temp;
    static uint8_t t = 0;   /* 控制查询间隔,从而降低CPU占用率 */
    
    t++;
    
    if ((t % 10) == 0 || t < 10)   /* 空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率 */
    {
        ft5206_rd_reg(FT5206_REG_NUM_FINGER, &sta, 1);  /* 读取触摸点的状态 */

        if ((sta & 0XF) && ((sta & 0XF) < 6))
        {
            temp = 0XFFFF << (sta & 0XF);           /* 将点的个数转换为1的位数,匹配tp_dev.sta定义 */
            tp_dev.sta = (~temp) | TP_PRES_DOWN | TP_CATH_PRES;
            delay_ms(4);    /* 必要的延时，否则老是认为有按键按下 */
            
            for (i = 0; i < 5; i++)
            {
                if (tp_dev.sta & (1 << i))          /* 触摸有效? */
                {
                    ft5206_rd_reg(FT5206_TPX_TBL[i], buf, 4);   /* 读取XY坐标值 */

                    if (tp_dev.touchtype & 0X01)    /* 横屏 */
                    {
                        tp_dev.y[i] = ((uint16_t)(buf[0] & 0X0F) << 8) + buf[1];
                        tp_dev.x[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }
                    else
                    {
                        tp_dev.x[i] = lcddev.width - (((uint16_t)(buf[0] & 0X0F) << 8) + buf[1]);
                        tp_dev.y[i] = ((uint16_t)(buf[2] & 0X0F) << 8) + buf[3];
                    }

                    if ((buf[0] & 0XF0) != 0X80)tp_dev.x[i] = tp_dev.y[i] = 0;      /* 必须是contact事件，才认为有效 */

                    //printf("x[%d]:%d,y[%d]:%d\r\n", i, tp_dev.x[i], i, tp_dev.y[i]);
                }
            }

            res = 1;

            if (tp_dev.x[0] == 0 && tp_dev.y[0] == 0)sta = 0;   /* 读到的数据都是0,则忽略此次数据 */

            t = 0;  /* 触发一次,则会最少连续监测10次,从而提高命中率 */
        }
    }

    if ((sta & 0X1F) == 0)  /* 无触摸点按下 */
    {
        if (tp_dev.sta & TP_PRES_DOWN)      /* 之前是被按下的 */
        {
            tp_dev.sta &= ~TP_PRES_DOWN;    /* 标记按键松开 */
        }
        else    /* 之前就没有被按下 */
        {
            tp_dev.x[0] = 0xffff;
            tp_dev.y[0] = 0xffff;
            tp_dev.sta &= 0XE000;           /* 清除点有效标记 */
        }
    }

    if (t > 240)t = 10; /* 重新从10开始计数 */

    return res;
}




























