/**
 ****************************************************************************************************
 * @file        24cxx.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-23
 * @brief       24CXX 驱动代码
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
 * V1.0 20211023
 * 第一次发布
 *
 ****************************************************************************************************
 */
#ifndef __24CXX_H
#define __24CXX_H

#include "main.h"


#define AT24C01     127
#define AT24C02     255
#define AT24C04     511
#define AT24C08     1023
#define AT24C16     2047
#define AT24C32     4095
#define AT24C64     8191
#define AT24C128    16383
#define AT24C256    32767

/* 开发板使用的是24c02，所以定义EE_TYPE为AT24C02 */

#define EE_TYPE     AT24C02

void at24cxx_init(void);        /* 初始化IIC */
uint8_t at24cxx_check(void);    /* 检查器件 */
uint8_t at24cxx_read_one_byte(uint16_t addr);                       /* 指定地址读取一个字节 */
void at24cxx_write_one_byte(uint16_t addr,uint8_t data);            /* 指定地址写入一个字节 */
void at24cxx_write(uint16_t addr, uint8_t *pbuf, uint16_t datalen); /* 从指定地址开始写入指定长度的数据 */
void at24cxx_read(uint16_t addr, uint8_t *pbuf, uint16_t datalen);  /* 从指定地址开始读出指定长度的数据 */

#endif













