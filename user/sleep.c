/* ************************************************************************
> File Name:     sleep.c
> Author:        Hongtao Wang
> mail:          1196354180@qq.com
> Created Time:  Thu 11 Jul 2024 05:05:15 PM CST
> Description:   
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2, "Usage:sleep <time>\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}