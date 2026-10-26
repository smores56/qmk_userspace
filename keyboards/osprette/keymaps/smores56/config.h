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
