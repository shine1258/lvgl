#include "lv_my.h"
#include <unistd.h>

void lv_my_init(const char* fb_path)
{
    lv_init();

    lv_disp_t* disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, fb_path);
    lv_libinput_create(LV_INDEV_TYPE_POINTER, lv_libinput_find_dev(LV_LIBINPUT_CAPABILITY_TOUCH, true));
}

void lv_my_loop(void)
{
    while (1) {
        usleep(lv_timer_handler() * 1000);
    }
}

const lv_font_t* lv_my_font_get(uint8_t size)
{
    switch (size) {
    case 12:
        return &lv_font_montserrat_12;
    case 14:
        return &lv_font_montserrat_14;
    case 16:
        return &lv_font_montserrat_16;
    case 18:
        return &lv_font_montserrat_18;
    case 20:
        return &lv_font_montserrat_20;
    case 22:
        return &lv_font_montserrat_22;
    case 24:
        return &lv_font_montserrat_24;
    case 26:
        return &lv_font_montserrat_26;
    case 28:
        return &lv_font_montserrat_28;
    case 30:
        return &lv_font_montserrat_30;
    case 32:
        return &lv_font_montserrat_32;
    case 34:
        return &lv_font_montserrat_34;
    case 36:
        return &lv_font_montserrat_36;
    case 38:
        return &lv_font_montserrat_38;
    case 40:
        return &lv_font_montserrat_40;
    case 42:
        return &lv_font_montserrat_42;
    case 44:
        return &lv_font_montserrat_44;
    case 46:
        return &lv_font_montserrat_46;
    case 48:
        return &lv_font_montserrat_48;
    default:
        return NULL;
    }
}

int32_t lv_my_size_to_content()
{
    return LV_SIZE_CONTENT;
}