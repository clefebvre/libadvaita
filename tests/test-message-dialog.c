/*
 * Copyright (C) 2022 Purism SPC
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * Author: Alice Mikhaylenko <alice.mikhaylenko@puri.sm>
 */

#include <advaita.h>

static void
increment (int *data)
{
  (*data)++;
}

static void
test_adw_message_dialog_heading (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  char *heading;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::heading", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "heading", &heading, NULL);
  g_assert_cmpstr (heading, ==, "");

  adw_message_dialog_set_heading (dialog, "Heading");
  g_assert_cmpstr (adw_message_dialog_get_heading (dialog), ==, "Heading");
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "heading", "Heading 2", NULL);
  g_assert_cmpstr (adw_message_dialog_get_heading (dialog), ==, "Heading 2");
  g_assert_cmpint (notified, ==, 2);

  g_free (heading);
  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_heading_use_markup (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  gboolean use_markup;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::heading-use-markup", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "heading-use-markup", &use_markup, NULL);
  g_assert_false (use_markup);

  adw_message_dialog_set_heading_use_markup (dialog, TRUE);
  g_assert_true (adw_message_dialog_get_heading_use_markup (dialog));
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "heading-use-markup", FALSE, NULL);
  g_assert_false (adw_message_dialog_get_heading_use_markup (dialog));
  g_assert_cmpint (notified, ==, 2);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_body (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  char *body;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::body", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "body", &body, NULL);
  g_assert_cmpstr (body, ==, "");

  adw_message_dialog_set_body (dialog, "Body");
  g_assert_cmpstr (adw_message_dialog_get_body (dialog), ==, "Body");
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "body", "Body 2", NULL);
  g_assert_cmpstr (adw_message_dialog_get_body (dialog), ==, "Body 2");
  g_assert_cmpint (notified, ==, 2);

  g_free (body);
  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_body_use_markup (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  gboolean use_markup;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::body-use-markup", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "body-use-markup", &use_markup, NULL);
  g_assert_false (use_markup);

  adw_message_dialog_set_body_use_markup (dialog, TRUE);
  g_assert_true (adw_message_dialog_get_body_use_markup (dialog));
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "body-use-markup", FALSE, NULL);
  g_assert_false (adw_message_dialog_get_body_use_markup (dialog));
  g_assert_cmpint (notified, ==, 2);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_format (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_format_heading_markup (dialog, "Heading <b>%d</b>", 42);
  g_assert_cmpstr (adw_message_dialog_get_heading (dialog), ==, "Heading <b>42</b>");
  g_assert_true (adw_message_dialog_get_heading_use_markup (dialog));

  adw_message_dialog_format_heading (dialog, "Heading %d", 42);
  g_assert_cmpstr (adw_message_dialog_get_heading (dialog), ==, "Heading 42");
  g_assert_false (adw_message_dialog_get_heading_use_markup (dialog));

  adw_message_dialog_format_body_markup (dialog, "Body <b>%d</b>", 42);
  g_assert_cmpstr (adw_message_dialog_get_body (dialog), ==, "Body <b>42</b>");
  g_assert_true (adw_message_dialog_get_body_use_markup (dialog));

  adw_message_dialog_format_body (dialog, "Body %d", 42);
  g_assert_cmpstr (adw_message_dialog_get_body (dialog), ==, "Body 42");
  g_assert_false (adw_message_dialog_get_body_use_markup (dialog));

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_extra_child (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  GtkWidget *widget = NULL;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::extra-child", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "extra-child", &widget, NULL);
  g_assert_null (widget);

  adw_message_dialog_set_extra_child (dialog, NULL);
  g_assert_cmpint (notified, ==, 0);

  widget = gtk_button_new ();
  adw_message_dialog_set_extra_child (dialog, widget);
  g_assert_true (adw_message_dialog_get_extra_child (dialog) == widget);
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "extra-child", NULL, NULL);
  g_assert_null (adw_message_dialog_get_extra_child (dialog));
  g_assert_cmpint (notified, ==, 2);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_add_response (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_response (dialog, "response1", "Response 1");
  adw_message_dialog_add_response (dialog, "response2", "Response 2");

  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response1"), ==, "Response 1");
  g_assert_true (adw_message_dialog_get_response_enabled (dialog, "response1"));
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response1"), ==, ADW_RESPONSE_DEFAULT);

  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response2"), ==, "Response 2");
  g_assert_true (adw_message_dialog_get_response_enabled (dialog, "response2"));
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response2"), ==, ADW_RESPONSE_DEFAULT);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_add_responses (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_responses (dialog,
                                    "response1", "Response 1",
                                    "response2", "Response 2",
                                    NULL);

  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response1"), ==, "Response 1");
  g_assert_true (adw_message_dialog_get_response_enabled (dialog, "response1"));
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response1"), ==, ADW_RESPONSE_DEFAULT);

  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response2"), ==, "Response 2");
  g_assert_true (adw_message_dialog_get_response_enabled (dialog, "response2"));
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response2"), ==, ADW_RESPONSE_DEFAULT);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_remove_response (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_response (dialog, "response1", "Response 1");
  adw_message_dialog_add_response (dialog, "response2", "Response 2");
  adw_message_dialog_remove_response (dialog, "response1");

  g_assert_false (adw_message_dialog_has_response (dialog, "response1"));
  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response2"), ==, "Response 2");

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_response_label (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_response (dialog, "response", "Response");
  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response"), ==, "Response");

  adw_message_dialog_set_response_label (dialog, "response", "Label");
  g_assert_cmpstr (adw_message_dialog_get_response_label (dialog, "response"), ==, "Label");

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_response_enabled (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_response (dialog, "response", "Response");
  g_assert_true (adw_message_dialog_get_response_enabled (dialog, "response"));

  adw_message_dialog_set_response_enabled (dialog, "response", FALSE);
  g_assert_false (adw_message_dialog_get_response_enabled (dialog, "response"));

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_response_appearance (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));

  g_assert_nonnull (dialog);

  adw_message_dialog_add_response (dialog, "response", "Response");
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response"), ==, ADW_RESPONSE_DEFAULT);

  adw_message_dialog_set_response_appearance (dialog, "response", ADW_RESPONSE_DESTRUCTIVE);
  g_assert_cmpint (adw_message_dialog_get_response_appearance (dialog, "response"), ==, ADW_RESPONSE_DESTRUCTIVE);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_response_signal (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  int responses = 0, responses_cancel = 0, responses_save = 0;

  g_signal_connect_swapped (dialog, "response", G_CALLBACK (increment), &responses);
  g_signal_connect_swapped (dialog, "response::cancel", G_CALLBACK (increment), &responses_cancel);
  g_signal_connect_swapped (dialog, "response::save", G_CALLBACK (increment), &responses_save);

  adw_message_dialog_add_response (dialog, "cancel", "Cancel");
  adw_message_dialog_add_response (dialog, "save", "Save");

  adw_message_dialog_response (dialog, "cancel");
  g_assert_cmpint (responses, ==, 1);
  g_assert_cmpint (responses_cancel, ==, 1);
  g_assert_cmpint (responses_save, ==, 0);

  adw_message_dialog_response (dialog, "save");
  g_assert_cmpint (responses, ==, 2);
  g_assert_cmpint (responses_cancel, ==, 1);
  g_assert_cmpint (responses_save, ==, 1);

  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_default_response (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  char *response;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::default-response", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "default-response", &response, NULL);
  g_assert_null (response);

  adw_message_dialog_set_default_response (dialog, "save");
  g_assert_cmpstr (adw_message_dialog_get_default_response (dialog), ==, "save");
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "default-response", "load", NULL);
  g_assert_cmpstr (adw_message_dialog_get_default_response (dialog), ==, "load");
  g_assert_cmpint (notified, ==, 2);

  g_free (response);
  g_assert_finalize_object (dialog);
}

static void
test_adw_message_dialog_close_response (void)
{
  AdwMessageDialog *dialog = ADW_MESSAGE_DIALOG (adw_message_dialog_new (NULL, NULL, NULL));
  char *response;
  int notified = 0;

  g_assert_nonnull (dialog);

  g_signal_connect_swapped (dialog, "notify::close-response", G_CALLBACK (increment), &notified);

  g_object_get (dialog, "close-response", &response, NULL);
  g_assert_cmpstr (response, ==, "close");

  adw_message_dialog_set_close_response (dialog, "save");
  g_assert_cmpstr (adw_message_dialog_get_close_response (dialog), ==, "save");
  g_assert_cmpint (notified, ==, 1);

  g_object_set (dialog, "close-response", "cancel", NULL);
  g_assert_cmpstr (adw_message_dialog_get_close_response (dialog), ==, "cancel");
  g_assert_cmpint (notified, ==, 2);

  g_free (response);
  g_assert_finalize_object (dialog);
}

int
main (int   argc,
      char *argv[])
{
  gtk_test_init (&argc, &argv, NULL);
  adw_init ();

  g_test_add_func ("/Advaita/MessageDialog/heading", test_adw_message_dialog_heading);
  g_test_add_func ("/Advaita/MessageDialog/heading_use_markup", test_adw_message_dialog_heading_use_markup);
  g_test_add_func ("/Advaita/MessageDialog/body", test_adw_message_dialog_body);
  g_test_add_func ("/Advaita/MessageDialog/body_use_markup", test_adw_message_dialog_body_use_markup);
  g_test_add_func ("/Advaita/MessageDialog/format", test_adw_message_dialog_format);
  g_test_add_func ("/Advaita/MessageDialog/extra_child", test_adw_message_dialog_extra_child);
  g_test_add_func ("/Advaita/MessageDialog/add_response", test_adw_message_dialog_add_response);
  g_test_add_func ("/Advaita/MessageDialog/add_responses", test_adw_message_dialog_add_responses);
  g_test_add_func ("/Advaita/MessageDialog/remove_response", test_adw_message_dialog_remove_response);
  g_test_add_func ("/Advaita/MessageDialog/response_label", test_adw_message_dialog_response_label);
  g_test_add_func ("/Advaita/MessageDialog/response_enabled", test_adw_message_dialog_response_enabled);
  g_test_add_func ("/Advaita/MessageDialog/response_appearance", test_adw_message_dialog_response_appearance);
  g_test_add_func ("/Advaita/MessageDialog/response_signal", test_adw_message_dialog_response_signal);
  g_test_add_func ("/Advaita/MessageDialog/default_response", test_adw_message_dialog_default_response);
  g_test_add_func ("/Advaita/MessageDialog/close_response", test_adw_message_dialog_close_response);

  return g_test_run ();
}
