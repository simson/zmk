/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_cycle_layer

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/keymap.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int cycle_layer_pressed(struct zmk_behavior_binding *binding,
                               const struct zmk_behavior_binding_event event) {
    // Get the highest active layer
    int current = zmk_keymap_highest_layer_active();

    // Compute next layer (wrap around at maximum layers)
    int next_layer = (current + 1) % ZMK_KEYMAP_LAYERS_LEN;

    LOG_DBG("Activating layer %d\n", next_layer);

    zmk_keymap_layer_deactivate(current);
    zmk_keymap_layer_activate(next_layer);

    return 0;
}

static int cycle_layer_released(struct zmk_behavior_binding *binding,
                                const struct zmk_behavior_binding_event event) {
    // No action on release
    return 0;
}

static const struct behavior_driver_api cycle_layer_driver_api = {
    .binding_pressed = cycle_layer_pressed,
    .binding_released = cycle_layer_released,
};
#define KT_INST(n)                                                                                 \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,            \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &cycle_layer_driver_api);

DT_INST_FOREACH_STATUS_OKAY(KT_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
