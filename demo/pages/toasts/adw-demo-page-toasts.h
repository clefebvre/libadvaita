#pragma once

#include <advaita.h>

G_BEGIN_DECLS

#define ADW_TYPE_DEMO_PAGE_TOASTS (adw_demo_page_toasts_get_type())

G_DECLARE_FINAL_TYPE (AdwDemoPageToasts, adw_demo_page_toasts, ADW, DEMO_PAGE_TOASTS, AdwBin)

void adw_demo_page_toasts_undo (AdwDemoPageToasts *self);

G_END_DECLS
