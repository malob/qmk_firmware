// Includes and externs ------------------------------------------------------------------------ {{{

#include QMK_KEYBOARD_H

// Userspace includes
#include "malob.h"
#include "leader.h" // custom leader implementation
#include "vim.h"    // Vim mode implementation

extern keymap_config_t keymap_config;
LEAD_EXTERNS(); // needed for custom leader implementation
VIM_EXTERNS();  // needed for vim mode
// }}}

enum layer_names {
  _BASE,
  _RAISE,
  _LOWER,
};
enum custom_keycodes {
  LEAD = SAFE_RANGE,
};
#define KC_LEAD  LEAD
#define KC_SPLWR LT(_LOWER, KC_SPC)
#define KC_BSRSE LT(_RAISE, KC_BSPC)

// Note that `CRKBD_LAYOUT` macro prepends `KC_` to everything. Layout macro and some custom
// keycodes are defined in `malob.h` in from userspace.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = CRKBD_LAYOUT(
//┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓              ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓
    TAB , Q   , W   , F   , P   , G   ,                J   , L   , U   , Y   , SCLN, MINS,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    ESC , A   , R   , S   , T   , D   ,                H   , N   , E   , I   , O   , QUOT,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    LEAD, Z   , X   , C   , V   , B   ,                K   , M   , COMM, DOT , QUES, ENT ,
//┗━━━━━┷━━━━━┷━━━━━┷━━━━━╅─────┼─────╄━━━━━┓  ┏━━━━━╃─────┼─────╆━━━━━┷━━━━━┷━━━━━┷━━━━━┛
                            CMD ,SPLWR, OPT ,    CTRL,BSRSE, SHFT
//                        ┗━━━━━┷━━━━━┷━━━━━┛  ┗━━━━━┷━━━━━┷━━━━━┛
  ),

  [_RAISE] = CRKBD_LAYOUT(
//┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓              ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓
    GRV , EXLM, AT  , HASH, DLR , PERC,                CIRC, AMPR, ASTR, PIPE, COLN, UNDS,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    TILD, LT  , LCBR, LBRC, LPRN, SLSH,                BSLS, RPRN, RBRC, RCBR, GT  , DQUO,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    EQL , 1   , 2   , 3   , 4   , 5   ,                6   , 7   , 8   , 9   , 0   , PLUS,
//┗━━━━━┷━━━━━┷━━━━━┷━━━━━╅─────┼─────╄━━━━━┓  ┏━━━━━╃─────┼─────╆━━━━━┷━━━━━┷━━━━━┷━━━━━┛
                           _____,_____,_____,   _____,_____,_____
//                        ┗━━━━━┷━━━━━┷━━━━━┛  ┗━━━━━┷━━━━━┷━━━━━┛
  ),

  [_LOWER] = CRKBD_LAYOUT(
//┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓              ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓
   RESET,_____,_____,_____,BDOWN, BUP ,                DOWN, RGHT,VDOWN, VUP ,VMUTE, LCK ,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    F1  , F2  , F3  , F4  , F5  , F6  ,                LEFT,_____,PRTRK, PLAY,NXTRK,POWER,
//┠─────┼─────┼─────┼─────┼─────┼─────┨              ┠─────┼─────┼─────┼─────┼─────┼─────┨
    F7  , F8  , F9  , F10 , F11 , F12 ,                UP  ,_____,_____,_____,_____,_____,
//┗━━━━━┷━━━━━┷━━━━━┷━━━━━╅─────┼─────╄━━━━━┓  ┏━━━━━╃─────┼─────╆━━━━━┷━━━━━┷━━━━━┷━━━━━┛
                           _____,_____,_____,   _____, DEL ,_____
//                        ┗━━━━━┷━━━━━┷━━━━━┛  ┗━━━━━┷━━━━━┷━━━━━┛
  ),
};

// OLED screens {{{
// Uses QMK's OLED code rather than code in project

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void print_status(void) {
  // Print current layer
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("Base\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("Raise\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("Lower\n"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undefined"), false);
  }

  oled_write_ln_P(PSTR(""), false);

  if (leading) {
    oled_write_ln_P(PSTR("LEADING"), false);
  }
  else if (vim_mode != INSERT) {
    switch (vim_mode) {
      case NORMAL: oled_write_ln_P(PSTR("NORMAL"), false); break;
      case REPLACE: oled_write_ln_P(PSTR("REPLACE"), false); break;
    }
  }
  else {
    oled_write_ln_P(PSTR(""), false);
  }
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    print_status();
  } else {
    render_logo();
  }
}
// }}}

// Leader {{{
// Custom leader definitions, see users/malob/leader.md for documentation.

uint16_t leader_keycode = LEAD;

#define WM_MOD1(kc) A(S(kc))
#define WM_MOD2(kc) C(A(S(kc)))

bool check_leaders(void) {
  // Spaces
  LEAD2_TAP(KC_T, KC_H, C(KC_LEFT))  // Move one space to the left
  LEAD2_TAP(KC_T, KC_L, C(KC_RIGHT)) // Move one space to the right

  // Window
  LEAD2_TAP(KC_W, KC_W, C(A(G(KC_GRAVE)))) // Display Hammerspoon window hints

  // Amethyst window manager
  // Docs: https://github.com/ianyh/Amethyst
  LEAD2_TAP(KC_P, KC_M,   WM_MOD1(KC_SPACE)) // Cycle layout
  LEAD2_TAP(KC_P, KC_H,   WM_MOD1(KC_H))     // Shrink main pane
  LEAD2_TAP(KC_P, KC_L,   WM_MOD1(KC_L))     // Expand main pane
  LEAD2_TAP(KC_W, KC_F,   WM_MOD1(KC_T))     // Toggle float of current window
  LEAD2_TAP(KC_W, KC_ESC, WM_MOD1(KC_Z))     // Force windows to be reevaluated

  LEAD2_TAP(KC_W, KC_M,   WM_MOD2(KC_L))     // Swap window to clockwise screen
  LEAD2_TAP(KC_W, KC_J,   WM_MOD2(KC_J))     // Swap window clockwise
  LEAD2_TAP(KC_W, KC_K,   WM_MOD2(KC_K))     // Swap window counter clockwise
  LEAD2_TAP(KC_W, KC_S,   WM_MOD1(KC_ENTER)) // Swap window w/ main window

  LEAD2_TAP(KC_W, KC_H,   WM_MOD2(KC_LEFT))  // Move to space to the left
  LEAD2_TAP(KC_W, KC_L,   WM_MOD2(KC_RIGHT)) // Move to space to the right

  // Move tab to next Safari window
  LEAD4(KC_A, KC_S, KC_T, KC_N) {
    tap_code16(G(KC_L));
    tap_code16(G(KC_C));
    tap_code16(G(KC_W));
    tap_code16(G(KC_GRAVE));
    wait_ms(500);
    tap_code16(G(KC_T));
    tap_code16(G(KC_V));
    tap_code16(KC_ENTER);
    return false;
  }

  // Turn on Vim mode
  LEAD1(LEAD) {
    vim_mode = NORMAL;
    return false;
  }

  return true;
}
// }}}

// Keycode processing {{{

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_leader(keycode, record)) { return false; } // custom leader implementation
  if (!process_record_vim(keycode, record)) { return false; }
  return true;
}
// }}}
// vim: foldmethod=marker
