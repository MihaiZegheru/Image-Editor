#include <input_handler.h>

#include <stdio.h>
#include <string.h>

#include <utils.h>

command_data_t input_handler_read_command_data()
{
    command_type_t command_type = input_handler_read_command();
    command_data_t command_data;
    command_data.base.command_type = CT_NONE;

    switch (command_type) {
        case CT_LOAD:
            return input_handler_read_load();
            break;
        case CT_SELECT:
            return input_handler_read_select();
            break;
        case CT_HISTOGRAM:
            return input_handler_read_histogram();
            break;
        case CT_EQUALIZE:
            return input_handler_read_equalize();
            break;
        case CT_ROTATE:
            return input_handler_read_rotate();
            break;
        case CT_CROP:
            return input_handler_read_crop();
            break;
        case CT_APPLY:
            return input_handler_read_apply();
            break;
        case CT_SAVE:
            return input_handler_read_save();
            break;
        case CT_EXIT:
            return input_handler_read_exit();
            break;
        default:
            return command_data;
            break;
    }
}

command_type_t input_handler_read_command()
{
    const size_t MAX_BUFFER = 255;
    char command_text[MAX_BUFFER];
    scanf("%s", command_text);
    char c;
    scanf("%c", &c);

    command_type_t command_type;
    if (!strcmp(command_text, "LOAD")) {
        command_type = CT_LOAD;
    } else if (!strcmp(command_text, "SELECT")) {
        command_type = CT_SELECT;
    } else if (!strcmp(command_text, "HISTOGRAM")) {
        command_type = CT_HISTOGRAM;
    } else if (!strcmp(command_text, "EQUALIZE")) {
        command_type = CT_EQUALIZE;
    } else if (!strcmp(command_text, "ROTATE")) {
        command_type = CT_ROTATE;
    } else if (!strcmp(command_text, "CROP")) {
        command_type = CT_CROP;
    } else if (!strcmp(command_text, "APPLY")) {
        command_type = CT_APPLY;
    } else if (!strcmp(command_text, "SAVE")) {
        command_type = CT_SAVE;
    } else if (!strcmp(command_text, "EXIT")) {
        command_type = CT_EXIT;
    } else {
        command_type = CT_NONE;
    }

    return command_type;
}

command_data_t input_handler_read_load()
{
    command_data_t command_data;
    command_data.load.command_type = CT_LOAD;
    input_handler_read_string(command_data.load.file_path);

    return command_data;
}

command_data_t input_handler_read_select()
{
    command_data_t command_data;

    char input[100];
    input_handler_read_string(input);

    if (!strcmp(input, "ALL")) {
        command_data.select_all.command_type = CT_SELECT_ALL;
    } else {
        command_data.select.command_type = CT_SELECT;
        size_t x1, y1, x2, y2; 
        y1 = utils_string_to_int64(input);
        input_handler_read_size(&x1);
        input_handler_read_size(&y2);
        input_handler_read_size(&x2);
        
        command_data.select.point_a.x = x1;
        command_data.select.point_a.y = y1;
        command_data.select.point_b.x = x2;
        command_data.select.point_b.y = y2;
    }

    return command_data;
}

command_data_t input_handler_read_histogram()
{
    command_data_t command_data;
    command_data.histogram.command_type = CT_HISTOGRAM;
    input_handler_read_vector2(&command_data.histogram.resolution);

    return command_data;
}

command_data_t input_handler_read_equalize()
{
    command_data_t command_data;
    command_data.equalize.command_type = CT_EQUALIZE;
    
    return command_data;
}

command_data_t input_handler_read_rotate()
{
    command_data_t command_data;
    command_data.rotate.command_type = CT_ROTATE;
    input_handler_read_int64((int64_t *)&command_data.rotate.angle);

    return command_data;
}

command_data_t input_handler_read_crop()
{
    command_data_t command_data;
    command_data.crop.command_type = CT_CROP;

    return command_data;
}

command_data_t input_handler_read_apply()
{
    command_data_t command_data;
    command_data.apply.command_type = CT_APPLY;
    
    char input[25];
    input_handler_read_string(input);
    
    if (!strcmp(input, "EDGE")) {
        command_data.apply.image_kernel_type = IKT_EDGE;
    } else if (!strcmp(input, "SHARPEN")) {
        command_data.apply.image_kernel_type = IKT_SHARPEN;
    } else if (!strcmp(input, "BLUR")) {
        command_data.apply.image_kernel_type = IKT_BOX_BLUR;
    } else if (!strcmp(input, "GAUSSIAN_BLUR")) {
        command_data.apply.image_kernel_type = IKT_GAUSSIAN_BLUR;
    } else {
        command_data.apply.image_kernel_type = IKT_NONE;
    }

    return command_data;
}

command_data_t input_handler_read_save()
{
    command_data_t command_data;
    command_data.save.command_type = CT_SAVE;
    input_handler_read_string(command_data.save.file_path);
    printf("%s\n", command_data.save.file_path);

    char input[25];
    input_handler_read_string(input);
    if (!strcmp(input, "ascii")) {
        command_data.save.save_as_ascii = 1;
        printf("AA");
    } else {
        command_data.save.save_as_ascii = 0;
        printf("BB");
    }

    return command_data;
}

command_data_t input_handler_read_exit()
{
    command_data_t command_data;
    command_data.exit.command_type = CT_EXIT;

    return command_data;
}

void input_handler_read_string(char *str)
{
    scanf("%s[ \n]", str);
}

void input_handler_read_vector2(vector2_t *coords)
{
    scanf("%zu%zu", &coords->x, &coords->y);
}

void input_handler_read_int64(int64_t *int64)
{
    scanf("%"SCNd64, int64);
}

void input_handler_read_size(size_t *size)
{
    scanf("%zu", size);
}
