#pragma once

// Matches the ZMK devicetree: &mt tapping-term <150>, combos timeout <15ms>.
#define TAPPING_TERM 150
#define COMBO_TERM 20

#define ONESHOT_TAP_TOGGLE 0
#define ONESHOT_TIMEOUT 750

// CONVERT_TO=proton_c inherits the AVR-oriented bitbang split serial default
// (137kbaud), which is marginal over the TRRS link on the 72MHz STM32F303;
// QMK documents split support on converted ARM boards as "partial". Lowering
// the soft serial speed is the documented remedy for failed transactions.
#define SELECT_SOFT_SERIAL_SPEED 3
