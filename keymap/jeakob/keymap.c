/* jeakob — GMMK Pro Rev1 ISO (UK) keymap for QMK mainline.
   Derived from gourdo1's keymap (GPL-2.0-or-later, Copyright 2021 Jonavin Eng, 2022-2023 gourdo1).
   Full key reference: KEYMAP.md in https://github.com/jeakob/gmmkpro-media */

#include QMK_KEYBOARD_H

enum layers { _BASE, _FN1, _RGBFINE };

enum custom_keycodes {
    ENCFUNC = SAFE_RANGE, // knob press: play/pause or mute
    KNOB_SLP,             // FN + knob press: sleep / lock screen
    DELHOME,              // sidebar Delete (Home when swapped)
    PRNCONF,              // type out current settings
    TG_CAPS, TG_ESC, TG_DEL, TG_TDCAP, TG_ENC, TG_INS, TG_ENGCAP,
    RGB_TOD, RGB_TOI,     // idle timeout down / up
    RGB_NITE,             // night mode
    CAD,                  // Ctrl+Alt+Del
    TERM,                 // Ctrl+` (Win/Linux) / Ctrl+\ (macOS)
    TILE_TL, TILE_BL, TILE_TR, TILE_BR, // macOS quarter tiling
    FINE_HUD, FINE_HUI, FINE_SAD, FINE_SAI, FINE_VAD, FINE_VAI,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          ENCFUNC,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           DELHOME,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN1] = LAYOUT(
        EE_CLR,  KC_BRID, KC_BRIU, S(KC_F3),C(S(KC_D)),KC_LPAD,_______,KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______,          KNOB_SLP,
        PRNCONF, TG_CAPS, _______, TG_ESC,  TG_DEL,  TG_TDCAP,TG_ENC,  TG_INS,  _______, AC_TOGG, TG_ENGCAP,RGB_TOD,RGB_TOI, QK_BOOT,          TILE_TL,
        _______, RM_SATD, RM_VALU, RM_SATU, DM_REC1, _______, _______, _______, _______, _______, DM_PLY1, _______, _______,                   TILE_BL,
        _______, RM_HUED, RM_VALD, RM_HUEU, TERM,    _______, _______, _______, _______, _______, _______, _______, _______, MO(_RGBFINE),     TILE_TR,
        _______, _______, RGB_NITE,_______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, CAD,              _______, RM_NEXT, TILE_BR,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),
    // Hold FN + Enter: Q/W/E/A/S/D step saturation/brightness/hue by 1 instead of the default step
    [_RGBFINE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, FINE_SAD,FINE_VAI,FINE_SAI,_______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, FINE_HUD,FINE_VAD,FINE_HUI,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};
// clang-format on

// ---------------------------------------------------------------- user config (EEPROM)

typedef union {
    uint32_t raw;
    struct {
        bool    caps_hilite : 1;     // [FN]1
        bool    esc_dbl_base : 1;    // [FN]3
        bool    del_home : 1;        // [FN]4
        bool    lsft_dbl_caps : 1;   // [FN]5
        bool    enc_play : 1;        // [FN]6 play/pause (1) or mute (0)
        bool    ins_shift_bspc : 1;  // [FN]7
        bool    caps_extended : 1;   // [FN]0
        uint8_t timeout_idx : 4;     // index into TIMEOUT_MIN
    };
} user_config_t;

static user_config_t cfg;

static const uint8_t TIMEOUT_MIN[] = {0, 1, 2, 3, 5, 10, 15, 20, 30, 60};
#define TIMEOUT_DEFAULT_IDX 6

void eeconfig_init_user(void) {
    cfg.raw           = 0;
    cfg.caps_hilite   = true;
    cfg.esc_dbl_base  = true;
    cfg.enc_play      = true;
    cfg.timeout_idx   = TIMEOUT_DEFAULT_IDX;
    eeconfig_update_user(cfg.raw);
}

static bool is_mac(void) {
    os_variant_t os = detected_host_os();
    return os == OS_MACOS || os == OS_IOS;
}

// macOS: swap left Alt/GUI so Cmd sits next to Space. Right Alt stays AltGr (Polish characters).
bool process_detected_host_os_user(os_variant_t os) {
    keymap_config.swap_lalt_lgui = (os == OS_MACOS || os == OS_IOS);
    keymap_config.swap_ralt_rgui = false;
    return true;
}

// Mods as the physical keys are labelled (undo the macOS Alt/GUI swap)
static uint8_t physical_mods(void) {
    uint8_t m = get_mods();
    if (is_mac()) {
        bool lalt = m & MOD_BIT_LALT, lgui = m & MOD_BIT_LGUI;
        m &= ~(MOD_BIT_LALT | MOD_BIT_LGUI);
        if (lalt) m |= MOD_BIT_LGUI;
        if (lgui) m |= MOD_BIT_LALT;
    }
    return m;
}

// Tap a key with exactly `mods` held, restoring the real mods afterwards
static void tap_with_mods(uint8_t mods, uint16_t kc) {
    uint8_t saved = get_mods();
    set_mods(mods);
    tap_code(kc);
    set_mods(saved);
}

// ---------------------------------------------------------------- RGB state

static bool rgb_night;   // night mode: all LEDs off except indicators
static bool idle_off;    // LEDs turned off by idle timeout / FN+knob
static bool dm_recording;
static bool caps_on;     // tracked locally: macOS often doesn't report Caps Lock back
static bool host_caps_last;

static void leds_wake(void) {
    if (idle_off) {
        idle_off = false;
        rgb_matrix_enable_noeeprom();
    }
}

static void leds_sleep(void) {
    idle_off = true;
    rgb_matrix_disable_noeeprom();
}

void housekeeping_task_user(void) {
    uint8_t minutes = rgb_night ? 1 : TIMEOUT_MIN[cfg.timeout_idx];
    if (!idle_off && minutes && last_input_activity_elapsed() > (uint32_t)minutes * 60000) leds_sleep();
}

bool led_update_user(led_t led_state) {
    // Only follow the host when its report actually changes, so a stale "off" can't cancel a physical toggle
    if (led_state.caps_lock != host_caps_last) {
        host_caps_last = led_state.caps_lock;
        caps_on        = led_state.caps_lock;
    }
    return true;
}

bool dynamic_macro_record_start_user(int8_t direction) {
    dm_recording = true;
    return true;
}

bool dynamic_macro_record_end_user(int8_t direction) {
    dm_recording = false;
    return true;
}

// ---------------------------------------------------------------- keys

static void toggle(uint16_t keycode) {
    switch (keycode) {
        case TG_CAPS:   cfg.caps_hilite ^= 1; break;
        case TG_ESC:    cfg.esc_dbl_base ^= 1; break;
        case TG_DEL:    cfg.del_home ^= 1; break;
        case TG_TDCAP:  cfg.lsft_dbl_caps ^= 1; break;
        case TG_ENC:    cfg.enc_play ^= 1; break;
        case TG_INS:    cfg.ins_shift_bspc ^= 1; break;
        case TG_ENGCAP: cfg.caps_extended ^= 1; break;
        case RGB_TOD:   if (cfg.timeout_idx > 0) cfg.timeout_idx--; break;
        case RGB_TOI:   if (cfg.timeout_idx < ARRAY_SIZE(TIMEOUT_MIN) - 1) cfg.timeout_idx++; break;
    }
    eeconfig_update_user(cfg.raw);
}

static void print_settings(void) {
    send_string("\n--- jeakob GMMK Pro settings (FN + number to toggle) ---\n");
    send_string(cfg.caps_hilite ? "1. CapsLock RGB highlight: ON\n" : "1. CapsLock RGB highlight: OFF\n");
    send_string(cfg.esc_dbl_base ? "3. ESC double tap to base layer: ON\n" : "3. ESC double tap to base layer: OFF\n");
    send_string(cfg.del_home ? "4. Sidebar DEL sends: HOME\n" : "4. Sidebar DEL sends: DEL\n");
    send_string(cfg.lsft_dbl_caps ? "5. LShift double tap for CapsLock: ON\n" : "5. LShift double tap for CapsLock: OFF\n");
    send_string(cfg.enc_play ? "6. Knob press: PLAY/PAUSE\n" : "6. Knob press: MUTE\n");
    send_string(cfg.ins_shift_bspc ? "7. Shift+Backspace = Insert: ON\n" : "7. Shift+Backspace = Insert: OFF\n");
    send_string(autocorrect_is_enabled() ? "9. AutoCorrect: ON\n" : "9. AutoCorrect: OFF\n");
    send_string(cfg.caps_extended ? "0. CapsLock highlights #: ON\n" : "0. CapsLock highlights #: OFF\n");
    send_string("RGB idle timeout (min): ");
    send_string(get_u8_str(TIMEOUT_MIN[cfg.timeout_idx], ' '));
    send_string("\n");
}

static uint8_t clamp_step(uint8_t v, int8_t d) {
    int16_t r = v + d;
    return r < 0 ? 0 : r > 255 ? 255 : r;
}

static void fine_hsv(int8_t dh, int8_t ds, int8_t dv) {
    hsv_t hsv = rgb_matrix_get_hsv();
    rgb_matrix_sethsv(hsv.h + dh, clamp_step(hsv.s, ds), clamp_step(hsv.v, dv)); // hue wraps around
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool    pressed = record->event.pressed;
    uint8_t mods    = get_mods();

    if (pressed && keycode != KNOB_SLP) leds_wake();

    // FN + ESC always resets EEPROM and reboots, even if VIA has remapped that key
    if (pressed && layer_state_is(_FN1) && record->event.key.row == 1 && record->event.key.col == 3) {
        eeconfig_init();
        soft_reset_keyboard();
        return false;
    }

    // ESC double tap: back to base layer
    static uint16_t esc_timer;
    static bool     esc_tapped;
    if (keycode == KC_ESC && pressed && cfg.esc_dbl_base) {
        if (esc_tapped && timer_elapsed(esc_timer) < TAPPING_TERM) layer_clear();
        esc_tapped = true;
        esc_timer  = timer_read();
    } else if (pressed && keycode != KC_ESC) {
        esc_tapped = false;
    }

    // Left Shift double tap: Caps Lock
    static uint16_t lsft_timer;
    static bool     lsft_tapped;
    if (keycode == KC_LSFT && pressed && cfg.lsft_dbl_caps) {
        if (lsft_tapped && timer_elapsed(lsft_timer) < TAPPING_TERM) {
            tap_code(KC_CAPS);
            caps_on     = !caps_on;
            lsft_tapped = false;
        } else {
            lsft_tapped = true;
            lsft_timer  = timer_read();
        }
    } else if (pressed && keycode != KC_LSFT) {
        lsft_tapped = false;
    }

    switch (keycode) {
        case KC_CAPS:
            if (pressed) caps_on = !caps_on;
            return true;

        case TG_CAPS: case TG_ESC: case TG_DEL: case TG_TDCAP: case TG_ENC: case TG_INS: case TG_ENGCAP:
        case RGB_TOD: case RGB_TOI:
            if (pressed) toggle(keycode);
            return false;

        case PRNCONF:
            if (pressed) print_settings();
            return false;

        case RGB_NITE:
            if (pressed) rgb_night = !rgb_night;
            return false;

        case ENCFUNC:
            if (pressed) tap_code(cfg.enc_play ? KC_MPLY : KC_MUTE);
            return false;

        case KNOB_SLP:
            if (pressed) {
                leds_sleep(); // LEDs off before the host reacts
                if (is_mac()) {
                    tap_with_mods(MOD_BIT_LCTRL | MOD_BIT_LGUI, KC_Q); // Lock Screen; HID sleep is ignored on macOS 13+
                } else {
                    tap_code(KC_SLEP);
                }
            }
            return false;

        case CAD: // register directly so the macOS Alt/GUI swap doesn't touch it (RDP)
            if (pressed) tap_with_mods(MOD_BIT_LCTRL | MOD_BIT_LALT, KC_DEL);
            return false;

        case TERM:
            if (pressed) tap_with_mods(MOD_BIT_LCTRL, is_mac() ? KC_NUBS : KC_GRV);
            return false;

        case TILE_TL: case TILE_BL: case TILE_TR: case TILE_BR:
            if (pressed && is_mac()) {
                static const uint16_t tile_keys[] = {KC_LBRC, KC_SCLN, KC_RBRC, KC_QUOT};
                tap_with_mods(MOD_BIT_LCTRL | MOD_BIT_LALT | MOD_BIT_LGUI, tile_keys[keycode - TILE_TL]);
            }
            return false;

        case FINE_HUD: if (pressed) fine_hsv(-1, 0, 0); return false;
        case FINE_HUI: if (pressed) fine_hsv(1, 0, 0); return false;
        case FINE_SAD: if (pressed) fine_hsv(0, -1, 0); return false;
        case FINE_SAI: if (pressed) fine_hsv(0, 1, 0); return false;
        case FINE_VAD: if (pressed) fine_hsv(0, 0, -1); return false;
        case FINE_VAI: if (pressed) fine_hsv(0, 0, 1); return false;

        // Sidebar Delete: plain Delete (so Shift+Delete stays Shift+Delete), or Home when swapped
        case DELHOME: {
            static uint16_t sent;
            if (pressed) {
                sent = cfg.del_home ? KC_HOME : KC_DEL;
                register_code(sent);
            } else if (sent) {
                unregister_code(sent);
                sent = 0;
            }
            return false;
        }

        case KC_BSPC: {
            static uint16_t sent;
            if (pressed) {
                if (cfg.ins_shift_bspc && (mods & MOD_MASK_SHIFT)) {
                    // Shift+Backspace = Insert
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_INS);
                    set_mods(mods);
                    sent = KC_INS;
                    return false;
                }
                if (is_mac() && (mods & MOD_MASK_CTRL)) {
                    // Ctrl+Backspace deletes a word: macOS uses Option+Backspace
                    set_mods((mods & ~MOD_MASK_CTRL) | MOD_BIT_LALT);
                    register_code(KC_BSPC);
                    set_mods(mods);
                    sent = KC_BSPC;
                    return false;
                }
            } else if (sent) {
                unregister_code(sent);
                sent = 0;
                return false;
            }
            return true;
        }

        // Ctrl+Shift+\ (ISO key, code IntlBackslash): send the ANSI Backslash key instead so browsers
        // report code "Backslash" — Termix's Split Right matches on that. All other \ | typing is untouched.
        case KC_NUBS: {
            static bool sent;
            if (pressed) {
                if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_SHIFT) && !(mods & (MOD_MASK_ALT | MOD_MASK_GUI))) {
                    register_code(KC_BSLS);
                    sent = true;
                    return false;
                }
            } else if (sent) {
                unregister_code(KC_BSLS);
                sent = false;
                return false;
            }
            return true;
        }
    }
    return true;
}

// ---------------------------------------------------------------- encoder

static void encoder_volume(bool clockwise) {
    static uint16_t timer;
    static bool     last_cw;
    static uint8_t  streak;
    if (timer_elapsed(timer) > 600 || clockwise != last_cw) streak = 0;
    timer   = timer_read();
    last_cw = clockwise;

    // Accelerate within a streak: up 1, 2, 4, 8 / down 1, 3, 9
    uint8_t taps = 1;
    for (uint8_t i = 0; i < streak; i++) taps *= clockwise ? 2 : 3;
    if (streak < (clockwise ? 3 : 2)) streak++;
    for (uint8_t i = 0; i < taps; i++) tap_code(clockwise ? KC_VOLU : KC_VOLD);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    leds_wake();
    uint8_t m = physical_mods();
    if (layer_state_is(_FN1)) {
        toggle(clockwise ? RGB_TOI : RGB_TOD);
    } else if (m & MOD_BIT_RSHIFT) {
        tap_with_mods(0, clockwise ? KC_PGUP : KC_PGDN);
    } else if (m & MOD_BIT_LCTRL) {
        tap_code(clockwise ? KC_RGHT : KC_LEFT); // Ctrl already held: word right / left
    } else if (m & MOD_BIT_RCTRL) {
        if (clockwise) rgb_matrix_increase_hue(); else rgb_matrix_decrease_hue();
    } else if (m & MOD_BIT_LALT) {
        // Undo / redo, OS-aware
        if (is_mac()) {
            tap_with_mods(clockwise ? (MOD_BIT_LGUI | MOD_BIT_LSHIFT) : MOD_BIT_LGUI, KC_Z);
        } else {
            tap_with_mods(MOD_BIT_LCTRL, clockwise ? KC_Y : KC_Z);
        }
    } else if (m & (MOD_BIT_LGUI | MOD_BIT_RGUI)) {
        tap_with_mods(0, clockwise ? KC_MNXT : KC_MPRV);
    } else if (m & MOD_BIT_LSHIFT) {
        tap_with_mods(0, clockwise ? KC_BRIU : KC_BRID);
    } else {
        encoder_volume(clockwise);
    }
    return false;
}

// ---------------------------------------------------------------- RGB indicators

// LED indices (ISO)
enum {
    L_ESC = 0, L_F1 = 6, L_F2 = 12, L_F3 = 18, L_F4 = 23, L_F5 = 28, L_F7 = 39, L_F8 = 44, L_F9 = 50, L_F10 = 56, L_F11 = 61, L_F12 = 66,
    L_1 = 7, L_3 = 19, L_4 = 24, L_5 = 29, L_6 = 35, L_7 = 40, L_9 = 51, L_0 = 57, L_MINS = 62, L_EQL = 79, L_BSPC = 86,
    L_Q = 8, L_W = 14, L_E = 20, L_A = 9, L_S = 15, L_D = 21, L_F = 26, L_Z = 10, L_B = 32, L_N = 38, L_SLSH = 60, L_HASH = 95,
    L_PGUP = 73, L_PGDN = 76, L_DEL = 87, L_END = 83, L_UP = 94, L_DOWN = 98, L_LEFT = 96, L_RIGHT = 80,
    L_SIDE1 = 68, L_SIDE2 = 71, L_SIDE3 = 74,
};

static const uint8_t LED_LETTERS[] = {8, 14, 20, 25, 30, 36, 41, 46, 52, 58, 9, 15, 21, 26, 31, 37, 42, 47, 53, 10, 16, 22, 27, 32, 38, 43};
static const uint8_t LED_FROW[]    = {L_F1, L_F2, L_F3, L_F4, L_F5, 34, L_F7, L_F8, L_F9, L_F10, L_F11, L_F12};

#define SET(i, c) RGB_MATRIX_INDICATOR_SET_COLOR(i, c)
#define RGB_DIMRED 0x40, 0x00, 0x00
#define RGB_ORANGERED 0xFF, 0x28, 0x00
#define RGB_PURPLEBLUE 0x50, 0x00, 0xFF

static void set_toggle(uint8_t led, bool on, uint8_t led_min, uint8_t led_max) {
    if (on) {
        SET(led, RGB_GREEN);
    } else {
        SET(led, RGB_PURPLE);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_night) {
        for (uint8_t i = led_min; i < led_max; i++) rgb_matrix_set_color(i, RGB_OFF);
    }

    led_t host = host_keyboard_led_state();
    bool  fn   = layer_state_is(_FN1);

    // Left underglow: 1 = Scroll Lock (blinks while recording a macro), 2 = night mode (FN held), 3 = Caps Lock
    if (dm_recording ? (timer_read() / 250) & 1 : host.scroll_lock) SET(L_SIDE1, RGB_RED);
    if (rgb_night && fn) SET(L_SIDE2, RGB_PURPLE);
    if (caps_on) {
        SET(L_SIDE3, RGB_GREEN);
        if (cfg.caps_hilite) {
            for (uint8_t i = 0; i < ARRAY_SIZE(LED_LETTERS); i++) SET(LED_LETTERS[i], RGB_GREEN);
            if (cfg.caps_extended) SET(L_HASH, RGB_GREEN);
        }
    }

    if (fn) {
        SET(L_ESC, RGB_DIMRED);
        SET(L_BSPC, RGB_RED);
        SET(L_B, RGB_RED);
        SET(L_N, RGB_YELLOW);
        SET(L_SLSH, RGB_ORANGERED);
        SET(L_F, RGB_WHITE);
        SET(L_F1, RGB_WHITE);
        SET(L_F2, RGB_WHITE);
        SET(L_F3, RGB_GREEN);
        SET(L_F4, RGB_GREEN);
        SET(L_F5, RGB_GREEN);
        SET(L_F7, RGB_BLUE);
        SET(L_F8, RGB_BLUE);
        SET(L_F9, RGB_BLUE);
        SET(L_F10, RGB_BLUE);
        SET(L_F11, RGB_BLUE);
        SET(L_F12, RGB_BLUE);
        SET(L_PGUP, RGB_ORANGE);
        SET(L_PGDN, RGB_ORANGE);
        SET(L_DEL, RGB_ORANGE);
        SET(L_END, RGB_ORANGE);
        SET(L_Q, RGB_CYAN);
        SET(L_W, RGB_CYAN);
        SET(L_E, RGB_CYAN);
        SET(L_A, RGB_CYAN);
        SET(L_S, RGB_CYAN);
        SET(L_D, RGB_CYAN);
        SET(L_Z, RGB_PURPLE);
        SET(L_UP, RGB_PURPLEBLUE);
        SET(L_DOWN, RGB_PURPLEBLUE);
        SET(L_LEFT, RGB_PURPLEBLUE);
        SET(L_RIGHT, RGB_PURPLEBLUE);
        SET(L_MINS, RGB_YELLOW);
        SET(L_EQL, RGB_YELLOW);

        set_toggle(L_1, cfg.caps_hilite, led_min, led_max);
        set_toggle(L_3, cfg.esc_dbl_base, led_min, led_max);
        set_toggle(L_4, cfg.del_home, led_min, led_max);
        set_toggle(L_5, cfg.lsft_dbl_caps, led_min, led_max);
        set_toggle(L_6, cfg.enc_play, led_min, led_max);
        set_toggle(L_7, cfg.ins_shift_bspc, led_min, led_max);
        set_toggle(L_9, autocorrect_is_enabled(), led_min, led_max);
        set_toggle(L_0, cfg.caps_extended, led_min, led_max);

        // Idle timeout level: F1..F(N) bright cyan
        for (uint8_t i = 0; i < cfg.timeout_idx && i < ARRAY_SIZE(LED_FROW); i++) SET(LED_FROW[i], RGB_CYAN);
    }
    return false;
}

void keyboard_post_init_user(void) {
    cfg.raw = eeconfig_read_user();
    if (cfg.timeout_idx >= ARRAY_SIZE(TIMEOUT_MIN)) cfg.timeout_idx = TIMEOUT_DEFAULT_IDX;
}
