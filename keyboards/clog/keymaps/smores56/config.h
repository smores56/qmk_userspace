#pragma once

// 200/150 matches the ZMK hold-tap behaviors. Permissive hold keeps mod-tap
// and layer-tap chords fast; T=GUI is exempt so a fast T->H roll in "th"/"the"
// taps instead of holding Shift+GUI.
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 150
#define PERMISSIVE_HOLD_PER_KEY

// Combos fire on the second press with per-combo windows: Esc/Tab 15ms,
// everything else 20ms. No must-tap, strict timer, hold term, or layer gate.
#define COMBO_TERM 20
#define COMBO_TERM_PER_COMBO

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
