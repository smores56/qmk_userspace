# smores56 QMK userspace

External [QMK userspace](https://docs.qmk.fm/newbs_external_userspace) for my boards.
Keymaps are ported from the ZMK layout in [`smores56/zmk-config`](https://github.com/smores56/zmk-config)
(`config/34-key.keymap`), which is the source of truth for the layout.

## Keymaps

| Board | QMK keyboard | Keymap | Firmware |
| ----- | ------------ | ------ | -------- |
| Clog / Clog V3 / **Steel Toe** / Sephirette | `clog` (upstream) | `smores56` | `clog_smores56_proton_c.bin`, `clog_smores56_blok.uf2` |
| Osprette | `osprette` (not upstream) | `smores56` | — |

Both keymaps implement the same physical layout:

- Layers: `MAIN`, `SYM`, `NAV`, `FN`. FN matches ZMK's Bluetooth layer per
  physical key; QMK uses `BT_PRF*`/`BT_UNPR` placeholders (no-ops on the wired
  boards). F-keys live on `NAV`.
- Combos (main layer only): `S+N`→Esc (15ms), `N+T`→Tab (15ms),
  `F+M`→Z, `M+P`→Q, `M+V`→J, `/ + \`→Caps Lock (20ms). `C+L` and `L+D` are free.
- `\` is back on the top-right-ring key; hold it for FN. F also holds FN.
- ZMK `mod-morph`s become QMK key overrides scoped to `MAIN`: `Shift+dot`→`!`,
  `Shift+comma`→`|`.
- ZMK sticky-shift becomes `OSM(MOD_RSFT)`. Tap-hold is 200ms with a 150ms
  quick tap; permissive/balanced holds keep layer and mod chords fast. T=GUI is
  tap-preferred to prevent the "th"/"the" roll; all other mod-taps use
  permissive hold.

## Steel Toe hardware notes

The Steel Toe uses **two Pro Micro-compatible controllers**. Upstream `clog` is
defined for an AVR `elite_c`, so build with the Pro Micro→target converter:

```sh
qmk compile -kb clog -km smores56 -e CONVERT_TO=proton_c   # STM32F303
qmk compile -kb clog -km smores56 -e CONVERT_TO=blok       # RP2040
# or
make clog:smores56 CONVERT_TO=proton_c
make clog:smores56 CONVERT_TO=blok
```

Outputs: `clog_smores56_proton_c.bin` (DFU) and `clog_smores56_blok.uf2` (UF2).

Both halves must run the **same controller type** — QMK's split transport is not
compatible across MCU families, so do not mix Proton C and Blok.

## Building with GitHub Actions (no local toolchain)

`qmk.json` lists the build targets (`CONVERT_TO=proton_c` and `CONVERT_TO=blok`). Push
to `main`; the `Build QMK firmware` workflow compiles them and publishes the artifacts.
Enable Actions once under **Settings → Actions** if it is off.

## Flashing on smoresbook (NixOS)

Both halves use the same firmware and must be the same controller type. Flash
**each half separately**; each has its own USB port.

### Proton C (STM32F303) — DFU

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

### Blok (RP2040) — UF2

No `dfu-util` or udev rules needed: the RP2040 exposes a USB mass-storage bootloader.

1. Hold `BOOTSEL` on the half (or press `QK_BOOT` on the `FN` layer if QMK is already
   running) and plug in USB; it mounts as `RPI-RP2`.
2. Copy the firmware onto it:
   ```sh
   cp clog_smores56_blok.uf2 /run/media/$USER/RPI-RP2/
   ```
   If it isn't auto-mounted: `udisksctl mount -b /dev/sdX1`.
3. It reboots into QMK automatically.

Repeat for the other half. Keep USB in the **left** half once you're done.

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
qmk compile -kb clog -km smores56 -e CONVERT_TO=blok
```
