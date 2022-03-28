#pragma once
#include <gtk/gtk.h>
typedef struct _ViewerApplication ViewerApplication;

G_DECLARE_FINAL_TYPE(ViewerWindow, viewer_window, VIEWER, WINDOW, GtkApplicationWindow)

ViewerWindow *viewer_window_new(ViewerApplication *app);

void viewer_window_open(ViewerWindow *window, GFile *file);
