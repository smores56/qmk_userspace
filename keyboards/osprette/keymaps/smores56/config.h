#pragma once

// 200/150 matches the ZMK hold-tap behaviors. T=GUI is exempt from permissive
// hold so a fast T->H roll in "th"/"the" taps instead of holding Shift+GUI.
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 150

// Chordal hold applies to mod-taps only; layer-taps stay tap-preferred on both
// firmwares so NAV/SYM/FN remain usable with the same hand.
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// Must-tap combos would otherwise inherit TAPPING_TERM and feel dead for 200 ms.
#define COMBO_HOLD_TERM 50
// ZMK starts its combo timeout on the first press; keep QMK strict for parity.
#define COMBO_STRICT_TIMER
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_TAP_PER_COMBO
#define COMBO_SHOULD_TRIGGER

#define ONESHOT_TAP_TOGGLE 0
#define ONESHOT_TIMEOUT 750
