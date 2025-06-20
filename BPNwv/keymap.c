#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#include "features/achordion.h"

void matrix_scan_user(void) {
  achordion_task();
}
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
        case KC_SPACE:
            return 250;  // trying to fix mistyping m when i want -
    }
  return 0;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
    bool shifted = (mods & MOD_MASK_SHIFT);  // Was Shift held?
    if ((mods & MOD_MASK_CTRL)) {  // Was Ctrl held?
        switch (keycode) {
            case KC_C: return C(KC_V); // Ctrl+C repeats as Ctrl+V
            case KC_V: return C(KC_C); // Ctrl+V repeats as Ctrl+C
            case KC_Z: return C(KC_Y); // Ctrl+Z (Undo) repeats as Ctrl+Y (Redo)
            case KC_Y: return C(KC_Z); // Ctrl+Y (Redo) repeats as Ctrl+Z (Undo)
            case KC_LEFT: return C(KC_LEFT); // Ctrl+Left repeats as Ctrl+Left (word left)
            case KC_RIGHT: return C(KC_RIGHT); // Ctrl+Right repeats as Ctrl+Right (word right)
            case KC_BSPC: return C(KC_BSPC);   // Ctrl+Backspace repeats as Ctrl+Backspace (delete word back)
            case KC_DEL: return C(KC_DEL);     // Ctrl+Delete repeats as Ctrl+Delete (delete word forward)
        }
    }
    switch (keycode) {
        case KC_COMM: return shifted ? S(KC_DOT) : KC_COMM; // < repeats as >, comma repeats as comma
        case KC_DOT:  return shifted ? S(KC_COMM) : KC_DOT;  // > repeats as <, period repeats as period
        case KC_LEFT:  return C(KC_LEFT);   // Left Arrow repeats as Word Left
        case KC_RIGHT: return C(KC_RIGHT);  // Right Arrow repeats as Word Right
        case KC_UP:    return KC_PGUP;      // Up Arrow repeats as Page Up
        case KC_DOWN:  return KC_PGDN;      // Down Arrow repeats as Page Down
        case KC_BSPC:  return C(KC_BSPC);   // Backspace repeats as Ctrl+Backspace (delete word back)
        case KC_DEL:   return C(KC_DEL);    // Delete repeats as Ctrl+Delete (delete word forward)
        case KC_LPRN: return KC_RPRN;      // ( repeats as )
        case KC_RPRN: return KC_LPRN;      // ) repeats as (
        case KC_LBRC: return KC_RBRC;      // [ repeats as ]
        case KC_RBRC: return KC_LBRC;      // ] repeats as [
        case KC_LCBR: return KC_RCBR;      // { repeats as }
        case KC_RCBR: return KC_LCBR;      // } repeats as {
        case KC_MINS: // Minus or Underscore
            return shifted ? KC_MINS : S(KC_EQL); // _ (S(KC_MINS)) repeats as -, - repeats as + (S(KC_EQL))
        case KC_EQL:  // Equal or Plus
            return shifted ? KC_MINS : KC_EQL;  // + (S(KC_EQL)) repeats as -, = repeats as =
        case KC_TAB:  return S(KC_TAB);    // Tab repeats as Shift+Tab
    }

    return KC_TRNS;  // Defer to default definitions.
}

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
  ST_MACRO_4,
  ST_MACRO_5,
  ST_MACRO_6,
  ST_MACRO_7,
  ST_MACRO_8,
  ST_MACRO_9,
  ST_MACRO_10,
  ST_MACRO_11,
  ST_MACRO_12,
  ST_MACRO_13,
  ST_MACRO_14,
  ST_MACRO_15,
  ST_MACRO_16,
  ST_MACRO_17,
  ST_MACRO_18,
  ST_MACRO_19,
  ST_MACRO_20,
  ST_MACRO_21,
  ST_MACRO_22,
  ST_MACRO_23,
  ST_MACRO_24,
  ST_MACRO_25,
  ST_MACRO_26,
  ST_MACRO_27,
  ST_MACRO_28,
  ST_MACRO_29,
  ST_MACRO_30,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes {
  DANCE_0,
  DANCE_10,
  DANCE_11,
  DANCE_12,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
  DANCE_5,
  DANCE_6,
  DANCE_7,
  DANCE_8,
  DANCE_9,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox_pretty(
    KC_AUDIO_MUTE,  TD(DANCE_0),    TD(DANCE_1),    TD(DANCE_2),    TD(DANCE_3),    TD(DANCE_4),    KC_TRANSPARENT,                                 KC_TRANSPARENT, TD(DANCE_5),    TD(DANCE_6),    TD(DANCE_7),    TD(DANCE_8),    TD(DANCE_9),    KC_TRANSPARENT,
    CW_TOGG,        KC_Q,           KC_W,           LT(3,KC_E),     KC_R,           KC_T,           KC_F8,                                          KC_TRANSPARENT, KC_Y,           KC_U,           LT(3,KC_I),     KC_O,           KC_P,           LT(4,KC_DELETE),
    MT(MOD_LSFT | MOD_LCTL, KC_TAB),MT(MOD_LGUI, KC_A),MT(MOD_LALT, KC_S),MT(MOD_LCTL, KC_D),MT(MOD_LSFT, KC_F),KC_G,                                                                           KC_H,           MT(MOD_RSFT, KC_J),MT(MOD_RCTL, KC_K),MT(MOD_RALT, KC_L),MT(MOD_RGUI, KC_SCLN), QK_REP,
    OSM(MOD_HYPR),  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_F9,                                          KC_TRANSPARENT, KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OSM(MOD_MEH),
    KC_MS_LEFT,     KC_MS_UP,       KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_BTN1,                                                                                                     LT(6,KC_ESCAPE),KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,
                                                                                                    KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
                                                                                                                    KC_TRANSPARENT, KC_MEDIA_STOP,
                                                                                    LT(2,KC_SPACE), LT(1,KC_BSPC),  KC_TRANSPARENT, KC_PAUSE,       KC_TRANSPARENT, LT(5,KC_ENTER)
  ),
  [1] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_UP,    KC_MS_WH_DOWN,  KC_MS_WH_RIGHT, TD(DANCE_10),   KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PC_PASTE,    KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_WH_RIGHT, KC_TRANSPARENT,
    KC_TRANSPARENT, MT(MOD_LGUI, KC_LEFT),MT(MOD_LALT, KC_UP),MT(MOD_LCTL, KC_DOWN),MT(MOD_LSFT, KC_RIGHT),TD(DANCE_11),                                                                   KC_PC_COPY,     MT(MOD_RSFT, KC_LEFT),MT(MOD_RCTL, KC_DOWN),MT(MOD_RALT, KC_UP),MT(MOD_RGUI, KC_RIGHT),KC_TRANSPARENT,
    KC_MS_BTN2,     KC_MS_LEFT,     KC_MS_UP,       KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_BTN1,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,    KC_MS_BTN3,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_ACCEL0,   KC_MS_ACCEL2,
                                                                                                                    KC_TRANSPARENT, KC_MS_ACCEL1,
                                                                                    KC_TRANSPARENT, KC_MS_BTN1,     KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN2,     KC_MS_BTN1
  ),
  [2] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_PIPE,        KC_LCBR,        KC_RCBR,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_TILD,        KC_DQUO,        KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_HASH,        KC_DLR,         KC_EQUAL,       KC_LPRN,        KC_RPRN,                                                                        KC_NO,          KC_UNDS,        KC_QUOTE,       KC_PLUS,        KC_ASTR,        QK_AREP,
    KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_AMPR,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_MINUS,       KC_GRAVE,       KC_TRANSPARENT, KC_BSLS,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_0,     ST_MACRO_1,     ST_MACRO_2,     ST_MACRO_3,     KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_4,     ST_MACRO_5,     ST_MACRO_6,     ST_MACRO_7,     ST_MACRO_8,                                                                     ST_MACRO_9,     ST_MACRO_10,    ST_MACRO_11,    ST_MACRO_12,    TD(DANCE_12),   KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_ergodox_pretty(
    KC_INSERT,      KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          QK_BOOT,
    KC_CAPS,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, TOGGLE_LAYER_COLOR,RGB_VAD,        RGB_VAI,        KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_TRANSPARENT,
    KC_NUM,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,                                                                         KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT, TO(0),
    KC_SCRL,        KC_F11,         KC_F12,         KC_F13,         KC_F14,         KC_F15,         KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MEDIA_STOP,  KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_PAUSE,       KC_PSCR,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [5] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_NO,          KC_NO,          ST_MACRO_13,    KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_14,    ST_MACRO_15,    ST_MACRO_16,    ST_MACRO_17,    KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, ST_MACRO_25,    ST_MACRO_26,    ST_MACRO_27,    KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_18,    ST_MACRO_19,    ST_MACRO_20,    ST_MACRO_21,    KC_NO,                                                                          ST_MACRO_28,    ST_MACRO_29,    ST_MACRO_30,    KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, ST_MACRO_22,    ST_MACRO_23,    ST_MACRO_24,    KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [6] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_0,           KC_1,           KC_2,           KC_3,           KC_4,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, MT(MOD_LGUI, KC_0),MT(MOD_LALT, KC_1),MT(MOD_LCTL, KC_2),MT(MOD_LSFT, KC_3),KC_NO,                                                                          KC_NO,          MT(MOD_RSFT, KC_6),MT(MOD_RCTL, KC_7),MT(MOD_RALT, KC_8),MT(MOD_RGUI, KC_9),KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_4,           KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_5,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 TO(0),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};




extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [2] = { {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223}, {139,243,223} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,227,205}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 2:
      set_layer_color(2);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_achordion(keycode, record)) { return false; }
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCLN)) SS_DELAY(100) SS_RSFT(SS_TAP(X_Q)) SS_DELAY(100) SS_LSFT(SS_TAP(X_1))  SS_DELAY(100) SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_RSFT(SS_TAP(X_ESCAPE)) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCLN)) SS_DELAY(100) SS_TAP(X_W)  SS_DELAY(100) SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_TAP(X_SPACE) SS_DELAY(100) SS_TAP(X_T) SS_DELAY(100) SS_TAP(X_1));
    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(100) SS_TAP(X_1));
    }
    break;
    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_TAP(X_Y) SS_DELAY(100) SS_TAP(X_P));
    }
    break;
    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_P)));
    }
    break;
    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_QUOTE)) SS_DELAY(100) SS_TAP(X_A) SS_DELAY(100) SS_TAP(X_Y) SS_DELAY(100) SS_TAP(X_Y));
    }
    break;
    case ST_MACRO_7:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(100) SS_TAP(X_5));
    }
    break;
    case ST_MACRO_8:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_RSFT(SS_TAP(X_SCLN)) SS_DELAY(100) SS_LSFT(SS_TAP(X_5)) SS_DELAY(100) SS_TAP(X_S) SS_DELAY(100) SS_TAP(X_SLASH));
    }
    break;
    case ST_MACRO_9:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_COMMA)) SS_DELAY(100) SS_LSFT(SS_TAP(X_COMMA)));
    }
    break;
    case ST_MACRO_10:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_MINUS)));
    }
    break;
    case ST_MACRO_11:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_4)));
    }
    break;
    case ST_MACRO_12:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_ESCAPE) SS_DELAY(100) SS_LSFT(SS_TAP(X_DOT)) SS_DELAY(100) SS_LSFT(SS_TAP(X_DOT)));
    }
    break;
    case ST_MACRO_13:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_DOT) SS_DELAY(100) SS_LSFT(SS_TAP(X_E)));
    }
    break;
    case ST_MACRO_14:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_LSFT(SS_TAP(X_A)));
    }
    break;
    case ST_MACRO_15:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_LSFT(SS_TAP(X_S)));
    }
    break;
    case ST_MACRO_16:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_DOT) SS_DELAY(100) SS_TAP(X_E));
    }
    break;
    case ST_MACRO_17:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_TAP(X_E));
    }
    break;
    case ST_MACRO_18:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_TAP(X_A));
    }
    break;
    case ST_MACRO_19:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_TAP(X_S));
    }
    break;
    case ST_MACRO_20:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_LSFT(SS_TAP(X_C)));
    }
    break;
    case ST_MACRO_21:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_LSFT(SS_TAP(X_E)));
    }
    break;
    case ST_MACRO_22:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_TAP(X_Z));
    }
    break;
    case ST_MACRO_23:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_LSFT(SS_TAP(X_Z)));
    }
    break;
    case ST_MACRO_24:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_V) SS_DELAY(100) SS_TAP(X_C));
    }
    break;
    case ST_MACRO_25:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_TAP(X_U));
    }
    break;
    case ST_MACRO_26:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_MINUS) SS_DELAY(100) SS_TAP(X_U));
    }
    break;
    case ST_MACRO_27:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_TAP(X_I));
    }
    break;
    case ST_MACRO_28:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_LSFT(SS_TAP(X_U)));
    }
    break;
    case ST_MACRO_29:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_MINUS) SS_DELAY(100) SS_RSFT(SS_TAP(X_U)));
    }
    break;
    case ST_MACRO_30:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_COMMA) SS_DELAY(100) SS_LSFT(SS_TAP(X_I)));
    }
    break;

    case TD(DANCE_0):
    case TD(DANCE_10):
    case TD(DANCE_11):
    case TD(DANCE_12):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

uint8_t layer_state_set_user(uint8_t state) {
    uint8_t layer = biton(state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case 5:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case 6:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case 7:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
  return state;
};

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[9];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_1);
        tap_code16(KC_1);
        tap_code16(KC_1);
    }
    if(state->count > 3) {
        tap_code16(KC_1);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_1); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_1)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_1))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_1); register_code16(KC_1);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_1); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_1)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_1))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_1); break;
    }
    dance_state[0].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_2);
        tap_code16(KC_2);
        tap_code16(KC_2);
    }
    if(state->count > 3) {
        tap_code16(KC_2);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_2); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_2)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_2))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_2); register_code16(KC_2);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_2); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_2)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_2))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_2); break;
    }
    dance_state[1].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_3)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_3))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_3)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_3))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    dance_state[2].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_4);
        tap_code16(KC_4);
        tap_code16(KC_4);
    }
    if(state->count > 3) {
        tap_code16(KC_4);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_4); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_4)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_4))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_4); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_4)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_4))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;
    }
    dance_state[3].step = 0;
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_5);
        tap_code16(KC_5);
        tap_code16(KC_5);
    }
    if(state->count > 3) {
        tap_code16(KC_5);
    }
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(KC_5); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_5)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_5))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_5); register_code16(KC_5);
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_5); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_5)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_5))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_5); break;
    }
    dance_state[4].step = 0;
}
void on_dance_6(tap_dance_state_t *state, void *user_data);
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void on_dance_6(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_6);
        tap_code16(KC_6);
        tap_code16(KC_6);
    }
    if(state->count > 3) {
        tap_code16(KC_6);
    }
}

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP: register_code16(KC_6); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_6)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_6))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_6); register_code16(KC_6);
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP: unregister_code16(KC_6); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_6)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_6))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_6); break;
    }
    dance_state[5].step = 0;
}
void on_dance_7(tap_dance_state_t *state, void *user_data);
void dance_7_finished(tap_dance_state_t *state, void *user_data);
void dance_7_reset(tap_dance_state_t *state, void *user_data);

void on_dance_7(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_7);
        tap_code16(KC_7);
        tap_code16(KC_7);
    }
    if(state->count > 3) {
        tap_code16(KC_7);
    }
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP: register_code16(KC_7); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_7)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_7))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_7); register_code16(KC_7);
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP: unregister_code16(KC_7); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_7)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_7))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_7); break;
    }
    dance_state[6].step = 0;
}
void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

void on_dance_8(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_8);
        tap_code16(KC_8);
        tap_code16(KC_8);
    }
    if(state->count > 3) {
        tap_code16(KC_8);
    }
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_8); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_8)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_8))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_8); register_code16(KC_8);
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_8); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_8)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_8))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_8); break;
    }
    dance_state[7].step = 0;
}
void on_dance_9(tap_dance_state_t *state, void *user_data);
void dance_9_finished(tap_dance_state_t *state, void *user_data);
void dance_9_reset(tap_dance_state_t *state, void *user_data);

void on_dance_9(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_9);
        tap_code16(KC_9);
        tap_code16(KC_9);
    }
    if(state->count > 3) {
        tap_code16(KC_9);
    }
}

void dance_9_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[8].step = dance_step(state);
    switch (dance_state[8].step) {
        case SINGLE_TAP: register_code16(KC_9); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_9)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_9))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_9); register_code16(KC_9);
    }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[8].step) {
        case SINGLE_TAP: unregister_code16(KC_9); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_9)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_9))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_9); break;
    }
    dance_state[8].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_TAP_HOLD(KC_0, LGUI(KC_SPACE)),
        [DANCE_10] = ACTION_TAP_DANCE_TAP_HOLD(KC_HOME, KC_PAGE_UP),
        [DANCE_11] = ACTION_TAP_DANCE_TAP_HOLD(KC_END, KC_PGDN),
        [DANCE_12] = ACTION_TAP_DANCE_TAP_HOLD(KC_RIGHT, KC_END),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
        [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_9, dance_9_finished, dance_9_reset),
};

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand
  switch (tap_hold_keycode) {
    case KC_D:
      return true;
    case KC_A:
      return true;
    case KC_SPACE:
      return true;
    case KC_L:
      return true;
    case KC_BSPC:
      return true;
    // case HOME_S:  // S + H and S + G.
      // if (other_keycode == HOME_H || other_keycode == KC_G) { return true; }
      // break;
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }

  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
}
