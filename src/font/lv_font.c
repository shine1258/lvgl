/**
 * @file lv_font.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "lv_font.h"
#include "../misc/lv_text_private.h"
#include "../misc/lv_utils.h"
#include "../misc/lv_log.h"
#include "../misc/lv_assert.h"
#include "../stdlib/lv_string.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

const void * lv_font_get_glyph_bitmap(lv_font_glyph_dsc_t * g_dsc, lv_draw_buf_t * draw_buf)
{
    const lv_font_t * font_p = g_dsc->resolved_font;
    LV_ASSERT_NULL(font_p);
    return font_p->get_glyph_bitmap(g_dsc, draw_buf);
}

void lv_font_glyph_release_draw_data(lv_font_glyph_dsc_t * g_dsc)
{
    const lv_font_t * font = g_dsc->resolved_font;

    if(font != NULL && font->release_glyph) {
        font->release_glyph(font, g_dsc);
    }
}

bool lv_font_get_glyph_dsc(const lv_font_t * font_p, lv_font_glyph_dsc_t * dsc_out, uint32_t letter,
                           uint32_t letter_next)
{

    LV_ASSERT_NULL(font_p);
    LV_ASSERT_NULL(dsc_out);

#if LV_USE_FONT_PLACEHOLDER
    const lv_font_t * placeholder_font = NULL;
#endif

    const lv_font_t * f = font_p;

    dsc_out->resolved_font = NULL;
    dsc_out->req_raw_bitmap = 0;

    while(f) {
        bool found = f->get_glyph_dsc(f, dsc_out, letter, f->kerning == LV_FONT_KERNING_NONE ? 0 : letter_next);
        if(found) {
            if(!dsc_out->is_placeholder) {
                dsc_out->resolved_font = f;
                return true;
            }
#if LV_USE_FONT_PLACEHOLDER
            else if(placeholder_font == NULL) {
                placeholder_font = f;
            }
#endif
        }
        f = f->fallback;
    }

#if LV_USE_FONT_PLACEHOLDER
    if(placeholder_font != NULL) {
        placeholder_font->get_glyph_dsc(placeholder_font, dsc_out, letter,
                                        placeholder_font->kerning == LV_FONT_KERNING_NONE ? 0 : letter_next);
        dsc_out->resolved_font = placeholder_font;
        return true;
    }
#endif

#if LV_USE_FONT_PLACEHOLDER
    dsc_out->box_w = font_p->line_height / 2;
    dsc_out->adv_w = dsc_out->box_w + 2;
#else
    dsc_out->box_w = 0;
    dsc_out->adv_w = 0;
#endif

    dsc_out->resolved_font = NULL;
    dsc_out->box_h = font_p->line_height;
    dsc_out->ofs_x = 0;
    dsc_out->ofs_y = 0;
    dsc_out->format = LV_FONT_GLYPH_FORMAT_A1;
    dsc_out->is_placeholder = true;

    return false;
}

uint16_t lv_font_get_glyph_width(const lv_font_t * font, uint32_t letter, uint32_t letter_next)
{
    LV_ASSERT_NULL(font);
    lv_font_glyph_dsc_t g;

    /*Return zero if letter is marker*/
    if(lv_text_is_marker(letter)) return 0;

    lv_font_get_glyph_dsc(font, &g, letter, letter_next);
    return g.adv_w;
}

void lv_font_set_kerning(lv_font_t * font, lv_font_kerning_t kerning)
{
    LV_ASSERT_NULL(font);
    font->kerning = kerning;
}

int32_t lv_font_get_line_height(const lv_font_t * font)
{
    return font->line_height;
}

const lv_font_t * lv_font_default(void)
{
    return LV_FONT_DEFAULT;
}

const lv_font_t* lv_font_get(uint8_t size)
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


/**********************
 *   STATIC FUNCTIONS
 **********************/
