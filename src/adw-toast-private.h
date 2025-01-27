/*
 * Copyright (C) 2021 Purism SPC
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * Author: Alice Mikhaylenko <alice.mikhaylenko@puri.sm>
 */

#pragma once

#if !defined(_ADVAITA_INSIDE) && !defined(ADVAITA_COMPILATION)
#error "Only <advaita.h> can be included directly."
#endif

#include "adw-toast.h"
#include "adw-toast-overlay.h"

G_BEGIN_DECLS

AdwToastOverlay *adw_toast_get_overlay (AdwToast        *self);
void             adw_toast_set_overlay (AdwToast        *self,
                                        AdwToastOverlay *overlay);

G_END_DECLS
