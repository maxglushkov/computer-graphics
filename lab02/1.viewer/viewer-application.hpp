#pragma once
#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(ViewerApplication, viewer_application, VIEWER, APPLICATION, GtkApplication)

ViewerApplication *viewer_application_new();
