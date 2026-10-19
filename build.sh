#!/usr/bin/env bash
# Build gmmk_pro_rev1_iso_jeakob.bin from keymap/jeakob against a pinned QMK commit.
# Needs: git, python3 (with venv), arm-none-eabi-gcc + newlib
#   Debian/Ubuntu: sudo apt install git python3-venv gcc-arm-none-eabi libnewlib-arm-none-eabi
set -euo pipefail

QMK_COMMIT=180f394b489c238cb231c2bf8b080262155e03c0 # QMK mainline, 2026-10-16
REPO="$(cd "$(dirname "$0")" && pwd)"
QMK="$REPO/qmk_firmware"

# Regenerate autocorrect data from the dictionary
python3 "$REPO/gen_autocorrect.py" "$REPO/autocorrect_dict.txt" "$REPO/keymap/jeakob/autocorrect_data.h"

if [ ! -d "$QMK" ]; then
    git clone https://github.com/qmk/qmk_firmware "$QMK"
fi
git -C "$QMK" fetch --quiet origin "$QMK_COMMIT"
git -C "$QMK" checkout --quiet "$QMK_COMMIT"
git -C "$QMK" submodule update --init --recursive --depth 1

[ -d "$REPO/.venv" ] || python3 -m venv "$REPO/.venv"
"$REPO/.venv/bin/pip" install --quiet qmk -r "$QMK/requirements.txt"

ln -sfn "$REPO/keymap/jeakob" "$QMK/keyboards/gmmk/pro/rev1/iso/keymaps/jeakob"
(cd "$QMK" && PATH="$REPO/.venv/bin:$PATH" QMK_HOME="$QMK" qmk compile -kb gmmk/pro/rev1/iso -km jeakob)
cp "$QMK/gmmk_pro_rev1_iso_jeakob.bin" "$REPO/"
echo "Built $REPO/gmmk_pro_rev1_iso_jeakob.bin"
