#include "viewer-window.hpp"

struct _ViewerWindow
{
	GtkApplicationWindow parent;
	GtkWidget *viewArea;
	GdkPixbuf *image = NULL;
};
G_DEFINE_TYPE(ViewerWindow, viewer_window, GTK_TYPE_APPLICATION_WINDOW)

static void viewer_window_class_init(ViewerWindowClass *cls);
static void viewer_window_init(ViewerWindow *window);

static void viewer_window_destroy(ViewerWindow *window);

static void OnViewAreaDraw(GtkDrawingArea *viewArea, cairo_t *cr, int width, int height, gpointer window);
static void ShowErrorMessage(GtkWindow *parent, const gchar *message);

ViewerWindow *viewer_window_new(ViewerApplication *app)
{
	return VIEWER_WINDOW(g_object_new(
		viewer_window_get_type(),
		"application", app,
		"show-menubar", TRUE,
		NULL
	));
}

void viewer_window_open(ViewerWindow *window, GFile *file)
{
	GdkPixbuf *image;

	GError *error = NULL;
	GFileInputStream *const stream = g_file_read(file, NULL, &error);
	if (!error)
	{
		image = gdk_pixbuf_new_from_stream(G_INPUT_STREAM(stream), NULL, &error);
		g_object_unref(stream);
	}
	if (error)
	{
		ShowErrorMessage(GTK_WINDOW(window), error->message);
		g_error_free(error);
		return;
	}

	if (window->image)
	{
		g_object_unref(window->image);
	}
	window->image = image;
	gtk_widget_queue_draw(window->viewArea);
}

void viewer_window_class_init(ViewerWindowClass *cls)
{}

void viewer_window_init(ViewerWindow *window)
{
	g_signal_connect(window, "destroy", G_CALLBACK(viewer_window_destroy), window);

	window->viewArea = gtk_drawing_area_new();
	gtk_window_set_child(GTK_WINDOW(window), window->viewArea);
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(window->viewArea), OnViewAreaDraw, window, NULL);
}

void viewer_window_destroy(ViewerWindow *window)
{
	if (window->image)
	{
		g_object_unref(window->image);
	}
}

void OnViewAreaDraw(GtkDrawingArea *viewArea, cairo_t *cr, int width, int height, gpointer window)
{
	if (GdkPixbuf const* image = VIEWER_WINDOW(window)->image)
	{
		const int imageWidth = gdk_pixbuf_get_width(image);
		const int imageHeight = gdk_pixbuf_get_height(image);
		int vaWidth = imageWidth;
		int vaHeight = imageHeight;
		if (vaWidth > width || vaHeight > height)
		{
			vaWidth = imageWidth * height / imageHeight;
			vaHeight = height;
		}
		if (vaWidth > width)
		{
			vaWidth = width;
			vaHeight = imageHeight * width / imageWidth;
		}

		GdkPixbuf *const vaImage = gdk_pixbuf_scale_simple(image, vaWidth, vaHeight, GDK_INTERP_BILINEAR);
		gdk_cairo_set_source_pixbuf(cr, vaImage, (width - vaWidth) / 2.0, (height - vaHeight) / 2.0);
		cairo_paint(cr);
		g_object_unref(vaImage);
	}
}

void ShowErrorMessage(GtkWindow *parent, const gchar *message)
{
	GtkWidget *const dialog = gtk_message_dialog_new(
		parent,
		GtkDialogFlags(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT),
		GTK_MESSAGE_WARNING,
		GTK_BUTTONS_OK,
		"%s",
		message
	);
	g_signal_connect(dialog, "response", G_CALLBACK(gtk_window_destroy), NULL);
	gtk_widget_show(dialog);
}
