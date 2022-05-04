#include <algorithm>
#include <gl-context.hpp>
#include "ice.hpp"

static void AddSymmetricalHLines(std::initializer_list<Vector2f> const& profile)
{
	for (auto & v: profile)
	{
		glVertex2f(-v[0], v[1]);
		glVertex2f(v[0], v[1]);
	}
}

static void FillConnectedSemicircles(GLContext & ctx, GLfloat xc1, GLfloat yc1, GLfloat r1, GLfloat xc2, GLfloat yc2, GLfloat r2)
{
	const GLfloat angle = atan2(xc2 - xc1, yc1 - yc2);

	glBegin(GL_TRIANGLE_FAN);
	ctx.AddArc(xc1, yc1, r1, angle, angle + M_PI);
	ctx.AddArc(xc2, yc2, r2, angle + M_PI, angle + TAU);
	glEnd();
}

static void RenderCylinderBlock()
{
	glColor3ub(0, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	AddSymmetricalHLines({
		{.22f, .67f},
		{.22f, .003f},
		{.25707f, -.09707f},
		{.41f, -.24586f},
		{.41f, -.75414f},
		{.25414f, -.91f}
	});
	glEnd();

	glColor3ub(160, 160, 160);
	glBegin(GL_TRIANGLE_STRIP);
	AddSymmetricalHLines({
		{.21f, .66f},
		{.21f, .0f},
		{.25f, -.1f},
		{.4f, -.25f},
		{.4f, -.75f},
		{.25f, -.9f}
	});
	glEnd();
}

static void RenderConrod(GLContext & ctx, Vector2f const& crankpin, Vector2f const& wristpin)
{
	constexpr static GLfloat
		BIG_END_RADIUS = .1f,
		SMALL_END_RADIUS = .05f;

	glColor3ub(128, 128, 128);
	FillConnectedSemicircles(ctx, wristpin[0], wristpin[1], SMALL_END_RADIUS, crankpin[0], crankpin[1], BIG_END_RADIUS);
}

static void RenderCrankshaft(GLContext & ctx, Vector2f const& crankpin)
{
	constexpr static GLfloat
		CRANK_ARM_WIDTH_2 = .1f,
		CRANKPIN_RADIUS = .05f;

	glColor3ub(192, 192, 192);
	FillConnectedSemicircles(ctx, crankpin[0], crankpin[1], CRANK_ARM_WIDTH_2, .0f, .0f, CRANK_ARM_WIDTH_2);

	glColor3ub(160, 160, 160);
	ctx.FillCircle(crankpin[0], crankpin[1], CRANKPIN_RADIUS);
	ctx.FillCircle(.0f, .0f, CRANKPIN_RADIUS);
}

static void RenderPiston(GLContext & ctx, Vector2f const& wristpin)
{
	constexpr static GLfloat
		RADIUS = .2f,
		TOP = .17f,
		BOTTOM = -.07f,
		RING_RADIUS = .21f,
		WRISTPIN_RADIUS = .03f;

	glTranslatef(wristpin[0], wristpin[1], 0.f);

	glColor3ub(192, 192, 192);
	ctx.FillRectangle(-RADIUS, TOP, RADIUS, BOTTOM);

	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	AddSymmetricalHLines({
		{RING_RADIUS, .095f},
		{RING_RADIUS, .12f},
		{RING_RADIUS, .145f}
	});
	glEnd();

	glColor3ub(160, 160, 160);
	ctx.FillCircle(.0f, .0f, WRISTPIN_RADIUS);
}

static void RenderCylinder(GLContext & ctx, Vector2f const& crankshaft, GLfloat phase)
{
	constexpr static GLfloat
		CRANK_ARM_RADIUS = .25f,
		CONROD_LENGTH_SQR = .49f;

	glTranslatef(crankshaft[0], crankshaft[1], .0f);

	const Vector2f crankpin{
		-CRANK_ARM_RADIUS * sin(phase),
		CRANK_ARM_RADIUS * cos(phase)
	};
	const Vector2f wristpin{
		.0f,
		crankpin[1] + sqrt(CONROD_LENGTH_SQR - crankpin[0] * crankpin[0])
	};

	RenderConrod(ctx, crankpin, wristpin);
	RenderCrankshaft(ctx, crankpin);
	RenderPiston(ctx, wristpin);
}

static void RenderValveBlock(Vector2f const& camshaft, bool isRight)
{
	glTranslatef(camshaft[0], camshaft[1], .0f);
	if (isRight)
	{
		glScalef(-1.f, 1.f, 1.f);
	}

	glColor3ub(0, 0, 0);
	GLContext::FillRectangle(-.075f, .075f, .075f, -.18f);

	glColor3ub(160, 160, 160);
	GLContext::FillRectangle(-.065f, .065f, .065f, -.065f);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-.075f, -.075f);
	glVertex2f(-.075f, -.125f);
	glVertex2f(.065f, -.075f);
	AddSymmetricalHLines({
		{.065f, -.125f},
		{.04f, -.18f},
		{.05f, -.19f}
	});
	glEnd();

	if (isRight)
	{
		glScalef(-1.f, 1.f, 1.f);
	}
}

static void RenderCamshaft(GLContext & ctx, Vector2f const& camCenter, GLfloat phase)
{
	constexpr static GLfloat
		RADIUS = .05f,
		SHAFT_RADIUS = .03f,
		CAM_RADIUS = .03f;

	glColor3ub(192, 192, 192);
	glBegin(GL_TRIANGLE_FAN);
	ctx.AddArc(.0f, .0f, RADIUS, phase - M_PI_2, phase + M_PI);
	ctx.AddArc(camCenter[0], camCenter[1], CAM_RADIUS, phase + M_PI, phase + M_PI + M_PI_2);
	glEnd();

	glColor3ub(160, 160, 160);
	ctx.FillCircle(.0f, .0f, SHAFT_RADIUS);

	glTranslatef(.0f, std::min(camCenter[1] - CAM_RADIUS, -RADIUS), .0f);
}

static void RenderValve(GLContext & ctx, GLfloat phase)
{
	constexpr static GLfloat
		DISC_RADIUS = .05f,
		DISC_TOP = -.14f,
		DISC_BOTTOM = -.15f,
		STEM_RADIUS = .02f,
		STEM_TOP = .0f,
		STEM_BOTTOM = -.11f,
		CAM_OFFSET = M_SQRT2 * STEM_RADIUS;

	const Vector2f camCenter{
		CAM_OFFSET * sin(phase - float(M_PI_4)),
		-CAM_OFFSET * cos(phase - float(M_PI_4)),
	};

	RenderCamshaft(ctx, camCenter, phase);

	glColor3ub(64, 64, 64);
	glBegin(GL_TRIANGLE_STRIP);
	AddSymmetricalHLines({
		{STEM_RADIUS, STEM_TOP},
		{STEM_RADIUS, STEM_BOTTOM},
		{DISC_RADIUS, DISC_TOP},
		{DISC_RADIUS, DISC_BOTTOM}
	});
	glEnd();
}

static void RenderSparkPlug(Vector2f const& mount, bool withSpark)
{
	constexpr static GLfloat
		CONTACT_RADIUS = .015f,
		CONTACT_TOP = .2f,
		INSULATOR_RADIUS = .03f,
		INSULATOR_TOP = .15f,
		SIDE_ELECTRODE_RADIUS = .03f,
		SIDE_ELECTRODE_TOP = .01f,
		SIDE_ELECTRODE_INSIDE = .015f,
		SIDE_ELECTRODE_OUTSIDE = .025f,
		CENTRAL_ELECTRODE_RADIUS = .005f,
		CENTRAL_ELECTRODE_TOP = .0f,
		CENTRAL_ELECTRODE_BOTTOM = -.01f;

	glTranslatef(mount[0], mount[1], .0f);

	glColor3ub(128, 128, 128);
	GLContext::FillRectangle(-CONTACT_RADIUS, CONTACT_TOP, CONTACT_RADIUS, INSULATOR_TOP);
	GLContext::FillRectangle(-SIDE_ELECTRODE_RADIUS, SIDE_ELECTRODE_TOP, SIDE_ELECTRODE_RADIUS, CENTRAL_ELECTRODE_TOP);

	glColor3ub(224, 224, 224);
	GLContext::FillRectangle(-INSULATOR_RADIUS, INSULATOR_TOP, INSULATOR_RADIUS, SIDE_ELECTRODE_TOP);

	glColor3ub(0, 0, 0);
	GLContext::FillRectangle(-CENTRAL_ELECTRODE_RADIUS, CENTRAL_ELECTRODE_TOP, CENTRAL_ELECTRODE_RADIUS, CENTRAL_ELECTRODE_BOTTOM);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(SIDE_ELECTRODE_INSIDE, CENTRAL_ELECTRODE_TOP);
	glVertex2f(SIDE_ELECTRODE_OUTSIDE, CENTRAL_ELECTRODE_TOP);
	glVertex2f(SIDE_ELECTRODE_INSIDE, -SIDE_ELECTRODE_INSIDE);
	glVertex2f(SIDE_ELECTRODE_OUTSIDE, -SIDE_ELECTRODE_OUTSIDE);
	glVertex2f(-CENTRAL_ELECTRODE_RADIUS, -SIDE_ELECTRODE_INSIDE);
	glVertex2f(-CENTRAL_ELECTRODE_RADIUS, -SIDE_ELECTRODE_OUTSIDE);
	glEnd();

	if (withSpark)
	{
		glColor3ub(255, 255, 255);
		GLContext::FillRectangle(-CENTRAL_ELECTRODE_RADIUS, CENTRAL_ELECTRODE_BOTTOM, CENTRAL_ELECTRODE_RADIUS, -SIDE_ELECTRODE_INSIDE);
	}
}

void RenderICE(GLContext & ctx, GLfloat phase)
{
	constexpr static GLfloat
		Y_CRANKSHAFT = -.5f,
		X_CAMSHAFT_OFFSET = .125f,
		Y_CAMSHAFT = .85f,
		Y_SPARK_PLUG = .66f;

	glLoadIdentity();
	RenderCylinderBlock();
	RenderCylinder(ctx, {.0f, Y_CRANKSHAFT}, phase);

	glLoadIdentity();
	RenderValveBlock({-X_CAMSHAFT_OFFSET, Y_CAMSHAFT}, false);
	RenderValve(ctx, phase / 2.f);

	glLoadIdentity();
	RenderValveBlock({X_CAMSHAFT_OFFSET, Y_CAMSHAFT}, true);
	RenderValve(ctx, phase / 2.f + M_PI_2);

	glLoadIdentity();
	RenderSparkPlug({.0f, Y_SPARK_PLUG}, phase > TAU && phase <= TAU + M_PI_4);
}
