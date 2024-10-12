/*
Copyright (C) 2024 Lishaocheng <https://shaocheng.li>

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3 as published by the Free Software Foundation.
*/

#ifndef __LIBUARTDEV_H__
#define __LIBUARTDEV_H__

#define pr_error(fmt, ...) printf("Error : " fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...) printf("Info : " fmt, ##__VA_ARGS__)
/* 定义 __DEBUG__ 时，打印调试信息 */
#ifdef __DEBUG__
#define pr_debug(fmt, ...) printf("[%s:%04d]%s() : " fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...)
#endif

#include <stdint.h>

typedef struct _uartdev_t
{
    /* Device descriptor, the return value of open the serial port */
    int fd;
    /* Uart Port: or "/dev/tty.USA19*" on Mac OS X. */
    char *port;
    /* Bauds: 9600, 19200, 57600, 115200, etc */
    int baud;
    /* Data bit : 5, 6, 7, 8 */
    uint8_t data_bit;
    /* Parity: 'N'/'n', 'O'/'o', 'E'/'e' */
    char parity;
    /* Stop bit: 1, 2 */
    uint8_t stop_bit;

} uartdev_t;

uartdev_t *uartdev_new(const char *port, int baud, int data_bit, char parity, int stop_bit);

int uartdev_setup(uartdev_t *dev);

int uartdev_del(uartdev_t *dev);

int uartdev_send(uartdev_t *dev, const char *buf, int len);

int uartdev_recv(uartdev_t *dev, char *buf, int len);

int uartdev_flush(uartdev_t *dev);

#endif