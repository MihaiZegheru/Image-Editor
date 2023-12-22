#include <stdio.h>

#include <image_loader.h>

int main(void)
{
    printf("Hello world");

    image_t *image = image_loader_load("src/a.ppm");
    printf("%d\n", image->image_data.max_pixel_value);
    color_t color = image_at(0, 0, image);
    printf("%d %d %d", color.r, color.g, color.b);

    return 0;
}