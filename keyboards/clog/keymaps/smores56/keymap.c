// Copyright 2026 Sam Mohr <sam@sammohr.dev>
// SPDX-License-Identifier: GPL-2.0+

// Ported from the ZMK layout in smores56/zmk-config (config/34-key.keymap).
// Board family: Clog, Clog V3, Steel Toe, Sephirette (upstream keyboards/clog).

#include QMK_KEYBOARD_H

enum layers {
    _MAIN = 0,
    _SYM,
    _NAV,
    _FN,
};

enum combos {
    FM_Z,
    MP_Q,
    MV_J,
    CL_ESCAPE,
    LD_TAB,
};

const uint16_t PROGMEM z_combo[]      = {LT(_FN, KC_F), KC_M, COMBO_END};
const uint16_t PROGMEM q_combo[]      = {KC_M, KC_P, COMBO_END};
const uint16_t PROGMEM j_combo[]      = {KC_M, KC_V, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM tab_combo[]    = {KC_L, LT(_SYM, KC_D), COMBO_END};

combo_t key_combos[] = {
    [FM_Z]      = COMBO(z_combo, KC_Z),
    [MP_Q]      = COMBO(q_combo, KC_Q),
    [MV_J]      = COMBO(j_combo, KC_J),
    [CL_ESCAPE] = COMBO(escape_combo, KC_ESC),
    [LD_TAB]    = COMBO(tab_combo, KC_TAB),
};

// ZMK mod-morphs (dot_excl, comma_pipe) as QMK key overrides.
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_1));
const key_override_t comma_pipe_override       = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, S(KC_BSLS));

const key_override_t *key_overrides[] = {
    &exclamation_mark_override,
    &comma_pipe_override,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT_split_3x5_2(
        KC_W,         LT(_FN, KC_F),   KC_M,          KC_P,          KC_V,           KC_SCLN,  KC_DOT,         KC_SLSH,         LT(_FN, KC_BSLS), KC_QUOT,
        SFT_T(KC_R),  ALT_T(KC_S),     CTL_T(KC_N),   GUI_T(KC_T),   KC_G,           KC_COMM,  GUI_T(KC_A),    CTL_T(KC_E),     ALT_T(KC_I),      SFT_T(KC_H),
        KC_X,         KC_C,            KC_L,          LT(_SYM, KC_D), KC_B,          KC_MINS,  LT(_SYM, KC_U), KC_O,            KC_Y,             KC_K,
                                                     KC_ENT,        LT(_NAV, KC_SPC), OSM(MOD_RSFT), KC_BSPC
    ),

    [_SYM] = LAYOUT_split_3x5_2(
        S(KC_6),  KC_7, KC_8, KC_9, S(KC_8),        S(KC_GRV),  S(KC_LBRC), S(KC_RBRC), S(KC_3),  KC_GRV,
        KC_DOT,   KC_1, KC_2, KC_3, KC_EQL,         S(KC_COMM), S(KC_9),    S(KC_0),    S(KC_DOT), S(KC_7),
        KC_COMM,  KC_4, KC_5, KC_6, S(KC_EQL),      S(KC_4),    KC_LBRC,    KC_RBRC,    S(KC_2),  S(KC_5),
                                    S(KC_SCLN),     KC_0,       KC_TRNS,    KC_TRNS
    ),

    [_NAV] = LAYOUT_split_3x5_2(
        KC_MPLY, KC_VOLD, KC_VOLU, KC_MPRV,  KC_MNXT,        KC_F10,  KC_F7,  KC_F8, KC_F9, KC_BRIU,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  C(KC_TAB),      KC_F11,  KC_F1,  KC_F2, KC_F3, KC_BRID,
        KC_HOME, KC_PGDN, KC_PGUP, KC_END,   C(S(KC_TAB)),   KC_F12,  KC_F4,  KC_F5, KC_F6, KC_PSCR,
                                  KC_NO,     KC_NO,          KC_TRNS, KC_DEL
    ),

    // ZMK's FN layer was Bluetooth (BT_SEL/BT_CLR), which has no wired Proton C
    // equivalent. Reset/boot loader occupy the same positions; F-keys fill the rest.
    [_FN] = LAYOUT_split_3x5_2(
        KC_NO, KC_NO, KC_NO, QK_RBT, QK_BOOT,        QK_BOOT, QK_RBT, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_F3, KC_F2, KC_F1,  KC_F6,          KC_F6,   KC_F1,              KC_F2,                KC_F3, KC_NO,
        KC_NO, KC_NO, KC_F5, KC_F4,  KC_NO,          KC_NO,   KC_F4,              KC_F5,                KC_NO, KC_NO,
                              KC_NO, KC_NO,           KC_TRNS, KC_NO
    ),
};
