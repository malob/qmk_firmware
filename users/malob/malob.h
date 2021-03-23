// `KC_` prefixed layout macros ------------------------------------------------------------------ {{{

// Layout macros for keyboards that prefix `KC_` to each entry for cleaner looking layouts.

// Dactyl Manuform 4x6 layout
#define DACMAN_LAYOUT(                                                               \
    L00, L01, L02, L03, L04, L05,                      R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                      R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                      R20, R21, R22, R23, R24, R25, \
              L32, L33,                                          R32, R33,           \
                        L34, L35, L44, L45,  R40, R41, R30, R31,                     \
                                  L42, L43,  R42, R43                                \
  ) \
  { \
    { KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05 }, \
    { KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15 }, \
    { KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25 }, \
    { KC_NO,    KC_NO,    KC_##L32, KC_##L33, KC_##L34, KC_##L35 }, \
    { KC_NO,    KC_NO,    KC_##L42, KC_##L43, KC_##L44, KC_##L45 }, \
                                                                    \
    { KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05 }, \
    { KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15 }, \
    { KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25 }, \
    { KC_##R30, KC_##R31, KC_##R32, KC_##R33, KC_NO,    KC_NO    }, \
    { KC_##R40, KC_##R41, KC_##R42, KC_##R43, KC_NO,    KC_NO    }  \
  }

// Crone 3x6 layout
#define CRKBD_LAYOUT(                                                   \
  L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
  L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
  L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
                      L30, L31, L32, R30, R31, R32                      \
  ) \
  { \
    { KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05 }, \
    { KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15 }, \
    { KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##L30, KC_##L31, KC_##L32 }, \
    { KC_##R05, KC_##R04, KC_##R03, KC_##R02, KC_##R01, KC_##R00 }, \
    { KC_##R15, KC_##R14, KC_##R13, KC_##R12, KC_##R11, KC_##R10 }, \
    { KC_##R25, KC_##R24, KC_##R23, KC_##R22, KC_##R21, KC_##R20 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##R32, KC_##R31, KC_##R30 }  \
  }
// }}}

// Keycode macros -------------------------------------------------------------------------------{{{

// Keycode docs: https://docs.qmk.fm/#/keycodes

// Macros needed when using `KC_` prefixed layout marcros above.
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_RESET RESET

// One shot modifier macros
// Docs: https://docs.qmk.fm/#/one_shot_keys
#define KC_CMD  OSM(MOD_LGUI)
#define KC_CTRL OSM(MOD_RCTL)
#define KC_OPT  OSM(MOD_LALT)
#define KC_SHFT OSM(MOD_RSFT)

// Misc macros mostly defined for esthetic reasons.

#define KC_BDOWN KC_BRMD     // brightness down on macOS
#define KC_BUP   KC_BRMU     // brightness up on macOS
#define KC_LCK   G(C(KC_Q))  // lock on macOS
#define KC_NXTRK KC_MFFD     // next track on macOS
#define KC_PLAY  KC_MPLY     // play/pause
#define KC_PRTRK KC_MRWD     // previous track on macOS
#define KC_VDOWN KC__VOLDOWN // volume down on macOS
#define KC_VMUTE KC__MUTE    // mute on macOS
#define KC_VUP   KC__VOLUP   // volume up on macOS

// vim: foldmethod=marker
