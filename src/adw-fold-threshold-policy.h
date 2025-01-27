/*
 * Copyright (C) 2021 Christopher Davis <christopherdavis@gnome.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#if !defined(_ADVAITA_INSIDE) && !defined(ADVAITA_COMPILATION)
#error "Only <advaita.h> can be included directly."
#endif

#include <glib-object.h>
#include "adw-enums.h"

G_BEGIN_DECLS

typedef enum {
  ADW_FOLD_THRESHOLD_POLICY_MINIMUM,
  ADW_FOLD_THRESHOLD_POLICY_NATURAL,
} AdwFoldThresholdPolicy;

G_END_DECLS
