/* ************************************************************************
> File Name:     primes.c
> Author:        Hongtao Wang
> mail:          1196354180@qq.com
> Created Time:  Fri 12 Jul 2024 03:50:18 PM CST
> Description:   
 ************************************************************************/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RD 0
#define WR 1

const uint INT_LEN = sizeof(int);

int read_lpipe(int lpipe[2], int *dst){
    if(read(lpipe[RD], dst, sizeof(int)) == sizeof(int)){
        fprintf(1, "prime %d\n", *dst);
        return 0;
    }
    return -1;
}

void transmit_data(int lpipe[2], int rpipe[2], int dst){
    int data;
    while(read(lpipe[RD], &data, sizeof(int)) == sizeof(int)){
        if(data % dst){
            write(rpipe[WR], &data, sizeof(int));
        }
    }
    close(lpipe[RD]);
    close(rpipe[WR]);

}

void primes(int lpipe[2]){
    close(lpipe[WR]);
    int first;
    if(read_lpipe(lpipe, &first) == 0){
        int p[2];
        pipe(p);
        transmit_data(lpipe, p, first);

        if(fork() == 0){
            primes(p);
        }else{
            close(p[RD]);
            wait(0);
        }
    }
}

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    for(int i = 2; i <= 35; ++i){
        write(p[WR], &i, INT_LEN);
    }

    if(fork() == 0){
        primes(p);
    }else{
        close(p[WR]);
        close(p[RD]);
        wait(0);
    }
    exit(0);

}
