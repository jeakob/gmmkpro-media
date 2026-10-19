// jeakob — GMMK Pro Rev1 ISO (UK). Based on gourdo1's keymap, rebuilt on QMK mainline.
#pragma once

// Emulated EEPROM size (gourdo1's values; QMK default 1024 is too small for VIA + user config)
#define WEAR_LEVELING_LOGICAL_SIZE 1280
#define WEAR_LEVELING_BACKING_SIZE 2560

#define FORCE_NKRO
#define DEBOUNCE 8
#define TAPPING_TERM 300

// Caps Word: both Shifts toggle it, Shift while active types lowercase
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT
#define CAPS_WORD_IDLE_TIMEOUT 10000

#define DYNAMIC_MACRO_NO_NESTING

#ifdef RGB_MATRIX_ENABLE
// Render black and hold LEDs off while the host is suspended (without this the suspend gate is a no-op)
#    define RGB_MATRIX_SLEEP
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180 // protect the AW20216S driver, limit USB current
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define RGB_MATRIX_DEFAULT_HUE 0
#    define RGB_MATRIX_DEFAULT_SAT 70
#    define RGB_MATRIX_DEFAULT_VAL 180
#    define RGB_MATRIX_DEFAULT_SPD 10
#endif
