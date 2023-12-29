#include <input_handler.h>

#include <stdio.h>
#include <string.h>

command_type_t input_handler_read_command()
{
    const uint8_t MAX_BUFFER = 25;
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

void input_handler_read_string(char *str)
{
    scanf("%s", str);
}

void input_handler_read_vector2(vector2_t *coords)
{
    scanf("%u%u", &coords->x, &coords->y);
}

void input_handler_read_int64(int64_t *int64)
{
    scanf("%"SCNd64, int64);
}

void input_handler_read_size(size_t *size)
{
    scanf("%d", size);
}
