/*
 * Copyright (C) 2019 Purism SPC
 * Copyright (C) 2021 Manuel Genovés <manuel.genoves@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#pragma once

#if !defined(_ADVAITA_INSIDE) && !defined(ADVAITA_COMPILATION)
#error "Only <advaita.h> can be included directly."
#endif

#include "adw-version.h"

#include <gtk/gtk.h>

G_BEGIN_DECLS

ADW_AVAILABLE_IN_ALL
double adw_lerp (double a,
                 double b,
                 double t);

ADW_AVAILABLE_IN_ALL
gboolean adw_get_enable_animations (GtkWidget *widget);

G_END_DECLS
