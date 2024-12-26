#include <gbdk/platform.h>
#include <gb/drawing.h>
#include <stdint.h>

#include "images.h"

#define CGB_BKG_PAL_0 0u
#define CGB_ONE_PAL   1u
const palette_color_t cgb_pal_black[] = {RGB_BLACK, RGB_BLACK, RGB_BLACK, RGB_BLACK};

uint8_t buttons, buttons_prev;
#define UPDATE_BUTTONS()            (buttons_prev = buttons, buttons = joypad())
#define BUTTON_TOGGLED(BUTTON_MASK) ((buttons & (~buttons_prev)) & (BUTTON_MASK))
#define BUTTON_PRESSED(BUTTON_MASK) (buttons & (BUTTON_MASK))
int16_t current_image = 0;

void main(void)
{
    if (_cpu == CGB_TYPE) {
        set_bkg_palette(BKGF_CGB_PAL0, CGB_ONE_PAL, cgb_pal_black);
    } else {
        BGP_REG = DMG_PALETTE(DMG_BLACK, DMG_BLACK, DMG_BLACK, DMG_BLACK);
    }
    draw_image(images[current_image]);
    SHOW_BKG;

    vsync();
    if (_cpu == CGB_TYPE) {
        set_bkg_palette(BKGF_CGB_PAL0, CGB_ONE_PAL, palettes[current_image]);
    } else {
        BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    }
    while(1) {
        UPDATE_BUTTONS();
        if (BUTTON_TOGGLED(J_A | J_B)){
            current_image = (current_image + 1) % NUM_IMAGES;
            draw_image(images[current_image]);
            if (_cpu == CGB_TYPE) {
                set_bkg_palette(BKGF_CGB_PAL0, CGB_ONE_PAL, palettes[current_image]);
            }
        }
        vsync();
    }
}
