#include <stdio.h>

#include <app_manager.h>

int main(void)
{
    while (!app_manager_tick());

    return 0;
}