#ifndef COMMAND_TYPE_H__
#define COMMAND_TYPE_H__

typedef enum {
    CT_NONE,
    CT_LOAD,
    CT_SELECT,
    CT_SELECT_ALL,
    CT_HISTOGRAM, 
    CT_EQUALIZE,
    CT_ROTATE,
    CT_CROP,
    CT_APPLY,
    CT_SAVE,
    CT_EXIT,
} command_type_t;

#endif // COMMAND_TYPE_H__