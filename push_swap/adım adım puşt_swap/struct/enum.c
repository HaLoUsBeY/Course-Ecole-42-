#include "tlist.h"
#include <stdio.h>

int main (void)
{
    t_layout order;

    enum e_layout morde;
    order = ASCENDING;
    morde = DESCENDING;

    if (order == ASCENDING)
        printf("Artan sıralama seçildi.\n");
    else
        printf("Azalan sıralama seçildi.\n");

    if (morde == ASCENDING)
        printf("Artan sıralama seçildi.\n");
    else
        printf("Azalan sıralama seçildi.\n");


    return (0);
}