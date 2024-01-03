#ifndef STATUS_TYPE_H__
#define STATUS_TYPE_H__

typedef enum {
    ST_NONE,
    ST_LOAD_DONE,
    ST_LOAD_FAILED,
    ST_IMAGE_NOT_LOADED,
    ST_SELECT_CUSTOM_DONE,
    ST_SELECT_CUSTOM_FAILED,
    ST_SELECT_ALL_DONE,
    ST_ROTATE_DONE,
    ST_ROTATE_SELECTION_INVALID,
    ST_ROTATE_ANGLE_INVALID,
    ST_EQUALIZE_DONE,
    ST_EQUALIZE_FORMAT_INVALID,
    ST_CROP_DONE,
    ST_APPLY_DONE,
    ST_APPLY_GRAYSCALE_IMAGE,
    ST_APPLY_PARAMETER_INVALID,
    ST_HISTOGRAM_GRAYSCALE_INVALID,
    ST_HISTOGRAM_DONE,
    ST_EXIT,
    ST_COMMAND_ERROR,

} status_type_t;

#endif // STATUS_TYPE_H__