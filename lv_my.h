#ifndef LV_MY_H
#define LV_MY_H

#include "lvgl.h"

void lv_my_init(const char * fb_path);
void lv_my_loop(void);

const lv_font_t* lv_my_font_get(uint8_t size);
int32_t lv_my_size_to_content();

#endif /*LV_MY_EXT_H*/