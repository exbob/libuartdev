/*
Copyright (C) 2024 Lishaocheng <https://shaocheng.li>

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3 as published by the Free Software Foundation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include "libuartdev.h"

/* 定义全局变量 */
char _port[20] = "/dev/ttyS0";
int _baud = 115200;
int _data_bit = 8;
char _parity = 'N';
int _stop_bit = 1;
int _verbose = 0;

int _int_sig = 0;

/*
输出帮助信息
*/
void help()
{
    printf("Usage:\n");
    printf("  uartecho  [option] \n");
    printf("Option:  \n");
    printf("  -d   serial port , default /dev/ttyS0\n");
    printf("  -b   baud rate , default 115200 \n");
    printf("  -p   parity , O,E or N ,default N \n");
    printf("  -x   data bit , 7 or 8 ,defalut 8 \n");
    printf("  -z   stop bit , 1 or 2 ,default 1 \n");
    printf("  -v   output more infomation\n");
    printf("  -h   help \n");
}

/*
获取命令行参数，设置相关变量。
返回值：
    -h 选项显示 help 信息，并返回 1
    设置成功返回 0
    参数错误返回负数，并设置 errno
*/
int get_arg(int arg_c, char *arg_v[])
{
    int opt = 0;
    char optstring[] = ":d:b:p:x:z:vh";

    while ((opt = getopt(arg_c, arg_v, optstring)) != -1)
    {
        switch (opt)
        {
        case 'd':
            strcpy(_port, optarg);
            break;
        case 'b':
            _baud = atoi(optarg);
            break;
        case 'p':
            _parity = optarg[0];
            break;
        case 'x':
            _data_bit = atoi(optarg);
            break;
        case 'z':
            _stop_bit = atoi(optarg);
            break;

        case 'v':
            _verbose = 1;
            break;
        case 'h':
            help();
            return 1;

        case ':':
            pr_error("need a value\n");
            errno = EINVAL;
            return -EINVAL;

        case '?':
            pr_error("unknow option : %c\n", optopt);
            errno = EINVAL;
            return -EINVAL;
        }
    }
    return 0;
}

/*
处理 SIGINT 信号的函数
*/
void int_handler(int sig)
{
    _int_sig = 1;
}

int main(int argc, char *argv[])
{
    uartdev_t *dev;
    char *buf;
    int buf_size = 1000;
    int nread = 0;
    int ret = 0;

    fd_set rset;
    FD_ZERO(&rset);

    struct timeval timeout;

    /* 接收 SIGINT 信号退出程序*/
    struct sigaction act;
    act.sa_handler = int_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    /* 接收参数 */
    ret = get_arg(argc, argv);
    if (ret < 0)
    {
        pr_error("%s\n", strerror(errno));
        return -1;
    }
    else if (ret > 0)
    {
        return 0;
    }

    dev = uartdev_new(_port, _baud, _data_bit, _parity, _stop_bit);
    if (dev == NULL)
    {
        pr_error("%s\n", strerror(errno));
        return -1;
    }

    /* 设置 */
    ret = uartdev_setup(dev);
    if (ret)
    {
        pr_error("%s\n", strerror(errno));
        uartdev_del(dev);
        return -1;
    }

    pr_info("Open %s, %d, %d%C%d\n", _port, _baud, _data_bit, _parity, _stop_bit);

    buf = malloc(buf_size);
    memset(buf, 0, buf_size);

    uartdev_flush(dev);

    while (!_int_sig)
    {
        FD_ZERO(&rset);
        FD_SET(dev->fd, &rset);
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        ret = select(dev->fd + 1, &rset, NULL, NULL, &timeout);
        pr_debug("select return %d\n", ret);

        switch (ret)
        {
        case 0:
            pr_info("Timeout ...\n");
            break;
        case -1:
            pr_error("%s\n", strerror(errno));
            _int_sig = 1;
            break;
        default:
            if (FD_ISSET(dev->fd, &rset))
            {
                ioctl(dev->fd, FIONREAD, &nread);
                if (nread == 0)
                {
                    break;
                }

                ret = uartdev_recv(dev, buf, (nread < buf_size) ? nread : buf_size - 1);
                if (ret > 0)
                {
                    *(buf + ret) = '\0';
                    pr_info("Received %d Bytes: %s\n", ret, buf);
                    uartdev_send(dev, buf, ret);
                }
                else
                {
                    pr_error("return %d, %s\n", ret, strerror(errno));
                }
                break;
            }
            break;
        }
    }

    /* Exit */
    free(buf);
    ret = uartdev_del(dev);
    if (ret)
    {
        pr_error("%s\n", strerror(errno));
        return -1;
    }

    pr_info("Stop.\n");

    return 0;
}
