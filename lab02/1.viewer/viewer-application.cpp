#include "viewer-application.hpp"
#include "viewer-window.hpp"

struct _ViewerApplication
{
	GtkApplication parent;
};
G_DEFINE_TYPE(ViewerApplication, viewer_application, GTK_TYPE_APPLICATION)

static void viewer_application_class_init(ViewerApplicationClass *cls);
static void viewer_application_init(ViewerApplication *app);

static void viewer_application_activate(GApplication *app);
static void viewer_application_open(GApplication *app, GFile **files, gint nFiles, gchar const*);
static void viewer_application_startup(GApplication *app);

static void OnFileOpenAction(GSimpleAction *, GVariant *, gpointer app);
static void OnFileOpenResponse(GtkDialog *dialog, int response);

ViewerApplication *viewer_application_new()
{
	return VIEWER_APPLICATION(g_object_new(
		viewer_application_get_type(),
		"flags", G_APPLICATION_HANDLES_OPEN,
		NULL
	));
}

void viewer_application_class_init(ViewerApplicationClass *cls)
{
	GApplicationClass *const gAppCls = G_APPLICATION_CLASS(cls);
	gAppCls->activate = viewer_application_activate;
	gAppCls->open = viewer_application_open;
	gAppCls->startup = viewer_application_startup;
}

void viewer_application_init(ViewerApplication *app)
{}

void viewer_application_activate(GApplication *app)
{
	ViewerWindow *const window = viewer_window_new(VIEWER_APPLICATION(app));
	gtk_window_present(GTK_WINDOW(window));
}

void viewer_application_open(GApplication *app, GFile **files, gint nFiles, gchar const*)
{
	ViewerWindow *const window =
		VIEWER_WINDOW(gtk_application_get_active_window(GTK_APPLICATION(app))) ?:
		viewer_window_new(VIEWER_APPLICATION(app));

	if (nFiles > 0)
	{
		viewer_window_open(window, *files);
		gtk_window_present(GTK_WINDOW(window));
	}
}

void viewer_application_startup(GApplication *app)
{
	G_APPLICATION_CLASS(viewer_application_parent_class)->startup(app);

	GtkBuilder *const builder = gtk_builder_new_from_resource("/viewer-menu.ui");
	GMenuModel *const menu = G_MENU_MODEL(gtk_builder_get_object(builder, "appMenu"));
	gtk_application_set_menubar(GTK_APPLICATION(app), menu);
	g_object_unref(builder);

	constexpr static GActionEntry ACTIONS[] = {
		{"file_open", OnFileOpenAction}
	};
	g_action_map_add_action_entries(G_ACTION_MAP(app), ACTIONS, G_N_ELEMENTS(ACTIONS), app);

	constexpr static const char *ACCELS_APP_FILE_OPEN[] = {"<Ctrl>O", NULL};
	gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.file_open", ACCELS_APP_FILE_OPEN);
}

void OnFileOpenAction(GSimpleAction *, GVariant *, gpointer app)
{
	GtkWindow *const parent = gtk_application_get_active_window(GTK_APPLICATION(app));
	GtkWidget *const dialog = gtk_file_chooser_dialog_new(
		"Open Image", parent, GTK_FILE_CHOOSER_ACTION_OPEN,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		NULL
	);
	g_signal_connect(dialog, "response", G_CALLBACK(OnFileOpenResponse), NULL);
	gtk_widget_show(dialog);
}

void OnFileOpenResponse(GtkDialog *dialog, int response)
{
	GtkWindow *const window = GTK_WINDOW(dialog);
	if (response == GTK_RESPONSE_ACCEPT)
	{
		GtkApplication *const app = gtk_window_get_application(gtk_window_get_transient_for(window));
		GFile *file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
		viewer_application_open(G_APPLICATION(app), &file, 1, NULL);
		g_object_unref(file);
	}
	gtk_window_destroy(window);
}
