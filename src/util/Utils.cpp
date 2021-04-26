//
// Created by vince on 08.04.21.
//

#include "Utils.h"
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <ctype.h>


/* Function to reverse bits of num */
unsigned char Utils::reverse_bits(unsigned char num) {
    unsigned int NO_OF_BITS = 8;
    unsigned int reverse_num = 0, i, temp;

    for (i = 0; i < NO_OF_BITS; i++) {
        temp = (num & (1 << i));
        if (temp)
            reverse_num |= (1 << ((NO_OF_BITS - 1) - i));
    }

    return reverse_num;
}

void Utils::printChars(unsigned char *ptr, int size)
{
    unsigned char *p = ptr;
    int i;
    bool chars = false;
    for (i=0; i<size; i++) {
        if (isalnum(p[i])){
            chars=true;
            printf("%c", p[i]);
        } else{
            if (chars){
                printf("%s", " ");
            }
            printf("%02hhX ", p[i]);
            chars=false;
        }
    }
    printf("\n");
}


void Utils::printBytes(void *ptr, int size)
{
    unsigned char *p = (unsigned char *)ptr;
    int i;
    for (i=0; i<size; i++) {
        printf("%02hhX ", p[i]);
    }
    printf("\n");
}

void Utils::printBits(unsigned char val) {
    std::bitset<8> bits(val);
    std::cout << bits << '\n';
}

unsigned Utils::createBitMask(unsigned a, unsigned b)
{
    unsigned r = 0;
    for (unsigned i=a; i<=b; i++)
        r |= 1 << i;

    return r;
}


void Utils::extractSubArray(unsigned char *srcArray, unsigned char *subArray, int n)
{
    for (int i = 0; i < n; i++)
    {
        subArray[i] = srcArray[i];
    }
}