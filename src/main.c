#include <stdio.h>

#include <app_manager.h>

#include <stddef.h>
#include <inttypes.h>

int main(void)
{
    // size_t a = 100;
    // int64_t b = a;
    // printf("%d", b);
    // return 0;
    app_manager_main_loop();

    return 0;
}