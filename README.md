# smores56 QMK userspace

External [QMK userspace](https://docs.qmk.fm/newbs_external_userspace) for my boards.
Keymaps are ported from the ZMK layout in [`smores56/zmk-config`](https://github.com/smores56/zmk-config)
(`config/34-key.keymap`), which is the source of truth for the layout.

## Keymaps

| Board | QMK keyboard | Keymap | Firmware |
| ----- | ------------ | ------ | -------- |
| Clog / Clog V3 / **Steel Toe** / Sephirette | `clog` (upstream) | `smores56` | `clog_smores56_proton_c.bin` |
| Osprette / Osprangle | `osprette` (upstream, PR [qmk#26450](https://github.com/qmk/qmk_firmware/pull/26450)) | `smores56` | — |

Both keymaps implement the same physical layout:

- Layers: `MAIN`, `SYM`, `NAV`, `FN` (FN = reset/bootloader + F-keys; ZMK's Bluetooth
  keys are dropped — the boards are wired).
- Combos: `F+M`→Z, `M+P`→Q, `M+V`→J, `C+L`→Esc, `L+D`→Tab.
- ZMK `mod-morph`s become QMK key overrides: `Shift+dot`→`!`, `Shift+comma`→`|`.
- ZMK sticky-shift becomes `OSM(MOD_RSFT)`; tapping term 150ms.

## Steel Toe hardware notes

The Steel Toe uses **two Proton C** controllers (STM32F303, ChibiOS). Upstream `clog`
is defined for an AVR `elite_c`, so build with the Pro Micro→Proton C converter:

```sh
qmk compile -kb clog -km smores56 -e CONVERT_TO=proton_c
# or
make clog:smores56 CONVERT_TO=proton_c
```

Output: `clog_smores56_proton_c.bin`.

## Building with GitHub Actions (no local toolchain)

`qmk.json` lists the build target with `CONVERT_TO=proton_c`. Push to `main`; the
`Build QMK firmware` workflow compiles it and publishes the `.bin` as a release
artifact. Enable Actions once under **Settings → Actions** if it is off.

## Flashing on smoresbook (NixOS)

Both halves use the same firmware. Flash **each half separately**, USB attached to the
**left/master** half (QMK defaults to `MASTER_LEFT`).

`nix-config` does not yet provide `dfu-util` or QMK udev rules. Use it transiently:

```sh
nix shell nixpkgs#dfu-util -c \
  dfu-util -a 0 -d 0483:DF11 -s 0x8000000:leave -D clog_smores56_proton_c.bin
```

or add it declaratively to `nix-config` (recommended):

```nix
# system packages
pkgs.dfu-util

# udev rules so flashing needs no root
services.udev.packages = [ pkgs.qmk-udev-rules ];
```

The Proton C uses the STM32 factory DFU bootloader (`0483:DF11`). Enter it on one
half — the reset button does **not** work:

- press the `QK_BOOT` key on the `FN` layer, **or**
- hold the top-left key (matrix `0,0`) while plugging in USB (bootmagic), **or**
- bridge `BOOT0` to VCC, tap `RESET` to GND, release `BOOT0`.

Then repeat for the other half.

## Osprette

The Osprette board definition is not upstream in QMK. It currently lives on the
`add-osprette` branch of [`smores56/qmk_firmware`](https://github.com/smores56/qmk_firmware).
`keyboards/osprette/keymaps/smores56` here is therefore archival/forward-looking until
that board is upstreamed (planned) or the fork is added as a submodule.

## Local build (NixOS)

```sh
nix shell nixpkgs#qmk
qmk setup
qmk config user.overlay_dir="$(realpath .)"
qmk compile -kb clog -km smores56 -e CONVERT_TO=proton_c
```
