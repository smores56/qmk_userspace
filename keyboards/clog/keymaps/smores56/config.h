#pragma once

// Base tapping term from the ZMK devicetree (&mt tapping-term <150>), raised to
// QMK's 200ms default: at 150ms a fast same-hand mod-tap roll (e.g. Ctrl+T via
// CTL_T(KC_N) + GUI_T(KC_T)) releases the hold-tap key before the term, so the
// hold resolves as its tap and the chord is silently dropped.
#define TAPPING_TERM 200

// ZMK used `flavor = "tap-preferred"` (QMK's default), which ignores interrupts:
// tapping another key while a mod-tap is undecided does not settle it as a hold.
// PERMISSIVE_HOLD settles the hold when that other key is tapped and released
// within the term, which is how modifier chords are actually typed.
#define PERMISSIVE_HOLD

#define COMBO_TERM 20

#define ONESHOT_TAP_TOGGLE 0
#define ONESHOT_TIMEOUT 750

// CONVERT_TO=proton_c inherits the AVR-oriented bitbang split serial default
// (137kbaud), which is marginal over the TRRS link on the 72MHz STM32F303;
// QMK documents split support on converted ARM boards as "partial". Lowering
// the soft serial speed is the documented remedy for failed transactions.
// Scoped to proton_c: the RP2040 PIO vendor driver reads this too, and its
// 230400 baud default is already reliable.
#ifdef CONVERT_TO_PROTON_C
#    define SELECT_SOFT_SERIAL_SPEED 3
#endif
