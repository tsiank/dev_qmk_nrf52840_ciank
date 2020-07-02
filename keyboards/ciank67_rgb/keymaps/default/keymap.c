#include QMK_KEYBOARD_H
#include "app_ble_func.h"

int RGB_current_mode;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix.h"
#include "i2c.h"
extern rgb_config_t rgb_matrix_config;
#endif

const uint8_t is_master = IS_LEFT_HAND;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ciank67_layers {
    _DVORAKR,
    _SIGN,
    _FN,
    _QWERTY,
    _RGBST,
    _MOUSE
};

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    REBOOT,
    RGBRST,
   RM_TOG
};

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAKR] = LAYOUT(
        GRAVE_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_J,  KC_L,  KC_M,    KC_F,    KC_P,    KC_SLSH,    KC_LBRC,        KC_RBRC,   KC_BSPC,
        KC_TAB,   KC_5,    KC_6,    KC_Q,    KC_DOT,  KC_O,  KC_R,  KC_S,    KC_U,    KC_Y,    KC_B,          KC_SCLN,        KC_EQL,  KC_BSLS,
        KC_CAPS,   KC_7,    KC_8,    KC_Z,    KC_A,             KC_E,    KC_H,    KC_T,    KC_D,    KC_C,    KC_K,          KC_MINS,           KC_ENT,
        KC_LSFT,      KC_9,    KC_0,    KC_X,     KC_COMM,     KC_I,    KC_N,    KC_W,    KC_V, KC_G,      KC_QUOT,   KC_GRAVE, KC_UP,   TG(_QWERTY),
        KC_LCTL,    KC_LALT, KC_LWIN,  MO(_SIGN),              RSFT_T(KC_SPC), MO(_FN),  KC_MENU, KC_RALT,                   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
                        ),
    [_SIGN]   = LAYOUT(
        _______,  KC_F1,  KC_F2,  KC_F3,  KC_TAB,  KC_EXCLAIM,    KC_AT,    KC_HASH,   KC_LBRC,   KC_RBRC  , KC_SLSH, _______,    _______,   _______,
        _______,  KC_F4,  KC_F5,  KC_F6,    KC_LCBR,  KC_DOLLAR, KC_PERCENT,   KC_CIRCUMFLEX,    KC_COLON,  KC_EQL,    KC_PIPE,    _______,   _______,   _______,
        _______,    KC_F7,  KC_F8,  KC_F9,    KC_RCBR ,   KC_AMPERSAND,   KC_ASTERISK,     KC_LEFT_PAREN,   KC_MINS,    KC_PLUS,    KC_TILDE,   _______,  _______,
        ENT_DFU,       KC_F10,  KC_F11,   KC_F12,   KC_BSLS,         KC_RIGHT_PAREN,    KC_QUOT,    KC_DOUBLE_QUOTE,   KC_UNDERSCORE,    _______,   _______, _______,_______, _______,
        _______,    _______, _______, KC_TRNS,              RSFT_T(KC_SPC),       KC_TRNS,  _______, _______, _______,    _______, _______, _______
                      ),
    [_FN]   = LAYOUT(
       REBOOT,  ENT_SLP,   _______, _______,    _______, _______,  _______, BLE_DIS, KC_PSCREEN, KC_SCROLLLOCK, KC_PAUSE, _______,_______, ENT_DFU,
        RM_TOG,  USB_EN, USB_DIS,  DELBNDS,   _______ ,_______,   _______, _______, KC_INSERT, KC_HOME, KC_PGUP, _______,_______, _______, 
        RGBM_TOG,  RGBM_MOD,RGBM_RMOD,  RGBM_M_P,  RGBM_M_B, RGBM_M_R, RGBM_M_SW, _______, _______, _______, KC_DELETE, KC_END,KC_PGDOWN,
        RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, ADV_ID0,ADV_ID1, AD_WO_L,BLE_EN,  _______, 
        RGB_TOG, RGBRST, RGB_MOD,  RGB_RMOD, KC_SPC, KC_TRNS,BATT_LV, _______, _______, _______, TO(_RGBST), TO(_MOUSE)
                      ),
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRAVE,  KC_UP,  TG(_QWERTY),
        KC_LCTL,    KC_LALT, KC_LWIN,  MO(_SIGN),              RSFT_T(KC_SPC), MO(_FN),  KC_MENU, KC_RALT,                   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
                       ),
    [_RGBST] = LAYOUT(
        _______, RGBM_HUI, RGBM_HUD, RGBM_SAI, RGBM_SAD, RGBM_VAI, RGBM_VAD, RGBM_SPI, RGBM_SPD, _______, _______,_______, _______,_______, 
        _______, _______,_______,_______, _______,_______,  _______, _______,_______,_______, _______,_______,_______, _______,
        _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, _______,_______, _______,
        _______,  RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, _______,_______,_______,_______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,TO(_DVORAKR),  _______
                     ),
    [_MOUSE] = LAYOUT(
        _______, KC_MS_UP, KC_MS_DOWN, KC_MS_LEFT, KC_MS_RIGHT,_______, _______,_______,  _______, _______,_______, _______,_______, _______,
        _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______,  _______, _______, _______, _______, _______,_______, _______, _______,_______, 
        _______, KC_MS_WH_UP, KC_MS_WH_DOWN, _______, _______, _______, _______,_______,_______, _______,_______, _______,_______,
        KC_PWR, KC_MUTE, KC_VOLU, KC_VOLD, KC_MNXT, KC_MPRV, KC_MSTP, KC_MPLY, _______, _______, _______, _______,_______, _______,
        KC_MY_COMPUTER,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_DVORAKR)
                     )
};

void keyboard_post_init_user() {
    #ifdef IS31FL3737
    // Shutdown IS31FL3737 if rgb disabled
    if (!rgb_matrix_config.enable) {
        i2c_stop();
    }
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  switch (keycode) {
        case RM_TOG:
            if (record->event.pressed) {
            	#ifdef RGB_MATRIX_ENABLE
                if (rgb_matrix_config.enable) {
                    i2c_stop();
                } else {
                    i2c_start();
                }
           #endif
            }
            return true;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
      
        case REBOOT:
                NVIC_SystemReset();
 return false;
            
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      #ifdef RGBLIGHT_ENABLE
          rgblight_disable();
      #endif
      deep_sleep_mode_enter();
      return false;
    }
  }

  return true;
}
