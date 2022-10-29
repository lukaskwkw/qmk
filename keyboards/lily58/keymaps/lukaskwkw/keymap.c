#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_MINS, KC_LSFT, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, RSFT_T(KC_QUOT), KC_LCTL, KC_X, KC_C, KC_D, KC_V, KC_Z, KC_MPRV, KC_MNXT, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_EQL), MO(2), KC_LGUI, LALT_T(KC_ESC), KC_SPC, KC_ENT, KC_BSPC, RGUI_T(KC_DEL), MO(1)),
                                                              [1] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_PSCR, KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MSTP, KC_PIPE, KC_GRV, KC_PLUS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_UP, KC_PGDN, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_NUM, KC_PLUS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, DF(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_TRNS, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MPRV, KC_MNXT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, DF(0), KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS)};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {              // Encoder on Master side
        if (IS_LAYER_ON(_LOWER)) { //  On _RAISE layer
            if (clockwise) {
                tap_code(KC_WH_R); // Move wheel right
            } else {
                tap_code(KC_WH_L); // Move wheel left
            }
        } else if (IS_LAYER_ON(_RAISE)) { //  On _RAISE layer
            if (clockwise) {
                tap_code(KC_MS_R); // Move cursor right
            } else {
                tap_code(KC_MS_L); // Move cursor left
            }
        } else { // On other layers
            if (clockwise) {
                tap_code(KC_VOLU); // Volume Up
            } else {
                tap_code(KC_VOLD); // Volume Down
            }
        }
    } else if (index == 1) {       // Encoder on Slave Side
        if (IS_LAYER_ON(_RAISE)) { // On _LOWER layer
            if (clockwise) {
                tap_code(KC_BRIU); // Brightness up
            } else {
                tap_code(KC_BRID); // Brightness down
            }
        } else if (IS_LAYER_ON(_LOWER)) { //  On _RAISE layer
            if (clockwise) {
                tap_code(KC_MS_D); // Move cursor down
            } else {
                tap_code(KC_MS_U); // Move cursor up
            }
        } else { // On other layers
            if (clockwise) {
                tap_code(KC_WH_D); // Move wheel down
            } else {
                tap_code(KC_WH_U); // Move wheel up
            }
        }
    }
    return true;
}

// SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        // oled_write_ln(read_host_led_state(), false);
        // oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }
    return true;
}
