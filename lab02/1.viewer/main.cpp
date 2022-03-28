#include "viewer-application.hpp"

int main(int argc, char *argv[])
{
	return g_application_run(G_APPLICATION(viewer_application_new()), argc, argv);
}
