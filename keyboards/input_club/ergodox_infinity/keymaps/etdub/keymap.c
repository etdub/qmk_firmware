#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "process_tap_dance.h"

#define L0 0 // default layer
#define L1 1
#define L2 2

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)

// Right-hand home row mods
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
} td_state_t;

enum {
  TD_LAYER_TG,
  TD_CTL,
};

// Create a global instance of the tapdance state type
// static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
      if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
      else return TD_DOUBLE_HOLD;
    }

    if (state->count == 3) {
      return TD_TRIPLE_TAP;
    }

    return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L0] = LAYOUT_ergodox(  // layer 0 : default
/*
 * left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |   =   |  0  |  2  |  3  |  4  |  5  | ESC |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |   \   |  Q  |  W  |  E  |  R  |  T  |     |
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |  TAB  |  A  |  S  |  D  |  F  |  G  +-----+
 *    +-------+-----+-----+-----+-----+-----+L1/L2|
 *    | LSHIFT|  Z  |  X  |  C  |  V  |  B  |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |LGUI |  `  |  \  |LEFT |RIGHT|
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |LCTRL| LALT|
 *                                  +-----+-----+-----+
 *                                  |     |     | HOME|
 *                                  |BKSPC| DEL +-----+
 *                                  |     |     | END |
 *                                  +-----+-----+-----+
 */
        KC_EQL,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5, KC_ESC,
        KC_BSLS, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T, KC_TRNS,
        KC_TAB,  HOME_A, HOME_S,  HOME_D,  HOME_F,  KC_G,
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, TD(TD_LAYER_TG),
        KC_LGUI, KC_GRV, KC_BSLS, KC_LEFT, KC_RGHT,
                                                      TD(TD_CTL), KC_LALT,
                                                               KC_HOME,
                                             KC_BSPC, KC_DEL,  KC_END,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |  6  |  7  |  8  |  9  |  0  |   -   |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |  [  |  Y  |  U  |  I  |  O  |  P  |   ]   |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+  H  |  J  |  K  |  L  |  ;  |   '   |
 *        |L1/L2+-----+-----+-----+-----+-----+-------+
 *        |     |  N  |  M  |  ,  |  .  |  /  | RSHIFT|
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |LEFT |DOWN | UP  |RIGHT| RGUI|
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    | RALT|RCTRL|
 *    +-----+-----+-----+==========================================================================
 *    | PGUP|     |     |
 *    +-----+ ENT | SPC |
 *    | PGDN|     |     |
 *    +-----+-----+-----+
 */
             KC_TRNS,  KC_6,   KC_7,    KC_8,    KC_9,   KC_0,     KC_MINS,
             KC_LBRC, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,     KC_RBRC,
                      KC_H,  HOME_J,  HOME_K,  HOME_L, HOME_SCLN,  KC_QUOT,
             TD(TD_LAYER_TG),  KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                              KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_RGUI,
             KC_RALT, TD(TD_CTL),
             KC_PGUP,
             KC_PGDN, KC_ENT, KC_SPC
    ),

[L1] = LAYOUT_ergodox( // layer 1 : function layers
/* left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       | f1  | f2  | f3  | f4  | f5  | f11 |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       |     |     |     |     |     |
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |MSLT |MSDN |MSUP |MSRT |     +-----+
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |     |     |
 *                                  +-----+-----+-----+
 *                                  |     |     |     |
 *                                  |     |     +-----+
 *                                  |     |     |     |
 *                                  +-----+-----+-----+
 */
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                      KC_TRNS, KC_TRNS,
                                                               KC_TRNS,
                                             KC_TRNS, KC_TRNS, KC_TRNS,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        | f12 | f6  | f7  | f8  | f9  | f10 |       |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |MSBT1|MSBT3|MSBT2|     |     |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+ MWLT|MWDN |MWUP |MWRT |     |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        |     |     |     |     |     |     |       |
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |     |     |     |     |     |
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    |     |     |
 *    +-----+-----+-----+
 *    |     |     |     |
 *    +-----+     |     |
 *    |     |     |     |
 *    +-----+-----+-----+
 */
       KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[L2] = LAYOUT_ergodox(
/* Left hand
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    | FLASH |     |     |     |     |     | RST |
 *    +-------+-----+-----+-----+-----+-----+-----+
 *    |       |     |     |     |     |     |     |
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     +-----+
 *    +-------+-----+-----+-----+-----+-----+     |
 *    |       |     |     |     |     |     |     |
 *    +-+-----+-----+-----+-----+-----+-----+-----+
 *      |     |     |     |     |     |
 *      +-----+-----+-----+-----+-----+   +-----+-----+
 *                                        |     |     |
 *                                  +-----+-----+-----+
 *                                  |     |     |     |
 *                                  |     |     +-----+
 *                                  |     |     |     |
 *                                  +-----+-----+-----+
 */
       QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_RBT,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
/* right hand
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        | RST |     |NMLCK| P/  | P*  | P-  | FLASH |
 *        +-----+-----+-----+-----+-----+-----+-------+
 *        |     |     | P7  | P8  | P9  | P+  |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        +-----+     | P4  | P5  | P6  | P+  |       |
 *        |     +-----+-----+-----+-----+-----+-------+
 *        |     |     | P1  | P2  | P3  |PENT |       |
 *        +-----+-----+-----+-----+-----+-----+-----+-+
 *                    |     |     | P.  |PENT |     |
 *    +-----+-----+   +-----+-----+-----+-----+-----+
 *    |     |     |
 *    +-----+-----+-----+
 *    |     |     |     |
 *    +-----+     | P0  |
 *    |     |     |     |
 *    +-----+-----+-----+
 */
       QK_RBT,  KC_TRNS, KC_NUM,     KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, QK_BOOT,
       KC_TRNS,  KC_TRNS, KC_KP_7,    KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  KC_TRNS,
                 KC_TRNS, KC_KP_4,    KC_KP_5,     KC_KP_6,        KC_KP_PLUS,  KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_KP_1,    KC_KP_2,     KC_KP_3,        KC_KP_ENTER, KC_TRNS,
                          KC_TRNS,    KC_TRNS,     KC_KP_DOT,      KC_KP_ENTER, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_KP_0
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};


// https://thomasbaart.nl/2018/12/13/qmk-basics-tap-dance/
void td_toggle_layers(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case (TD_SINGLE_TAP):
           layer_invert(L1);
           break;
        case (TD_DOUBLE_TAP):
           layer_invert(L2);
           break;
        case (TD_TRIPLE_TAP):
           layer_off(L1);
           layer_off(L2);
        default:
            break;
    }
} 

void td_ctl_finished(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case (TD_SINGLE_TAP):
        case (TD_SINGLE_HOLD):
           register_code(KC_LCTL);
           break;
        case (TD_DOUBLE_TAP):
        case (TD_DOUBLE_HOLD):
           register_code(KC_LGUI);
           break;
        default:
            break;
    }
}

void td_ctl_reset(tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case (TD_SINGLE_TAP):
        case (TD_SINGLE_HOLD):
           unregister_code(KC_LCTL);
           break;
        case (TD_DOUBLE_TAP):
        case (TD_DOUBLE_HOLD):
           unregister_code(KC_LGUI);
           break;
        default:
            break;
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for L1, tap twice for L2
    [TD_LAYER_TG] = ACTION_TAP_DANCE_FN(td_toggle_layers),
    [TD_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ctl_finished, td_ctl_reset),
};
