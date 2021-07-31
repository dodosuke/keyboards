/* Copyright 2020 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"
#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "debug.h"

#include "report_parser.h"

#include "print.h"

#define GESTURE_MOVE_THRESHOLD 30

enum custom_keycodes {
    GEST = SAFE_RANGE,
};

typedef enum {
    GESTURE_NONE = 0,
    GESTURE_UP,
    GESTURE_DOWN,
    GESTURE_LEFT,
    GESTURE_RIGHT,
} gesture_id_t;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {{KC_BTN1, KC_BTN2, TG(1),   KC_BTN4, KC_BTN5, KC_NO, KC_NO,      KC_NO        }},
    [1] = {{_______, _______, _______, GEST,    LGUI(KC_RBRC),  LCTL(KC_LEFT), LCTL(KC_L), LCTL(KC_RGHT)}},
};
// clang-format on

extern bool mouse_send_flag;

static int16_t      gesture_move_x   = 0;
static int16_t      gesture_move_y   = 0;
static bool         gesture_wait     = false;
static gesture_id_t gesture_id       = 0;
static uint8_t      btn_release_flag = 0;

void recognize_gesture(int16_t x, int16_t y) {
    
    if (abs(x) > abs(y)) {
    	if (abs(x) < GESTURE_MOVE_THRESHOLD) {
	    gesture_id = GESTURE_NONE;
	} else if (x >= 0) {
	    gesture_id = GESTURE_RIGHT; 
	} else {
	    gesture_id = GESTURE_LEFT;
	}
    } else {
    	if (abs(y) < GESTURE_MOVE_THRESHOLD) {
            gesture_id = GESTURE_NONE;
    	} else if (y >= 0) {
  	    gesture_id = GESTURE_UP;
    	} else {
            gesture_id = GESTURE_DOWN;
    	}
    }

}

void process_gesture(void) {
    
    recognize_gesture(gesture_move_x, gesture_move_y);

    switch (gesture_id) {
        case GESTURE_UP:
	    tap_code16(LCTL(KC_UP));
	    gesture_wait = false;
	    break;
	case GESTURE_DOWN:
	    tap_code16(LCTL(KC_L));
	    gesture_wait = false;
	    break;
	case GESTURE_LEFT:
	    tap_code16(LCTL(KC_LEFT));
	    gesture_wait = false;
	    break;
	case GESTURE_RIGHT:
	    tap_code16(LCTL(KC_RGHT));
	    gesture_wait = false;
	    break;
	case GESTURE_NONE:
	    break;
	default:
	    break;
    }
}

// Start gesture recognition
static void gesture_start(void) {
    dprint("Gesture start\n");
    gesture_wait   = true;
    gesture_move_x = 0;
    gesture_move_y = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_BTN1 ... KC_BTN5: {
            report_mouse_t mouse = pointing_device_get_report();
            if (record->event.pressed) {
                mouse.buttons |= (1 << (keycode - KC_BTN1));
            } else {
                mouse.buttons &= ~(1 << (keycode - KC_BTN1));
            }
            pointing_device_set_report(mouse);
            
	    return false;
        } break;
	
	case GEST: 
	    if (record -> event.pressed) {	
	        gesture_start();
	    } else if (gesture_wait) {
		tap_code16(LGUI(KC_LBRC));
		gesture_wait = false;
	    }    
            break;    	
	default:
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    if (btn_release_flag) {
        report_mouse_t mouse = pointing_device_get_report();
        mouse.buttons &= ~btn_release_flag;
        btn_release_flag = 0;
        pointing_device_set_report(mouse);
        mouse_send_flag = true;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {

    return TAPPING_TERM;
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {

}

extern bool          matrix_has_changed;
extern matrix_row_t* matrix_dest;

void mouse_report_hook(mouse_parse_result_t const* report) {
    // Assign buttons to matrix
    // 8 button mouse is assumed
    //
    uint8_t button_prev    = matrix_dest[0];
    uint8_t button_current = report->button;

    if (button_current != button_prev) {
        matrix_has_changed = true;
    }
    matrix_dest[0] = button_current;

    //
    // Assign mouse movement
    //
    mouse_send_flag      = true;
    report_mouse_t mouse = pointing_device_get_report();

    mouse.x += report->x;
    mouse.y += report->y;
    mouse.h += report->h;
    
    if (IS_LAYER_ON(1)) {
    	mouse.v -= report->v;
    } else {
    	mouse.v += report->v;
    }

    pointing_device_set_report(mouse);

    //
    // Save movement to recognize gesture
    //
    if (gesture_wait) {
        gesture_move_x += report->x;
        gesture_move_y += report->y;
	process_gesture();
    }
}
