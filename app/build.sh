#!/bin/sh

set -euio pipefail
set -x
west build  -d build/reset   -b nice_nano_v2 -S zmk-usb-logging -- -DSHIELD=settings_reset                      -DZMK_CONFIG=$(pwd)/zmk-config/config
west build  -d build/left    -b nice_nano_v2 -S zmk-usb-logging -- -DSHIELD=splitkb_aurora_helix_dongle_left    -DZMK_CONFIG=$(pwd)/zmk-config/config
west build  -d build/right   -b nice_nano_v2 -S zmk-usb-logging -- -DSHIELD=splitkb_aurora_helix_dongle_right   -DZMK_CONFIG=$(pwd)/zmk-config/config
west build  -d build/central -b nice_nano_v2 -S zmk-usb-logging -- -DSHIELD=splitkb_aurora_helix_dongle_central -DZMK_CONFIG=$(pwd)/zmk-config/config


