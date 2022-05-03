#include "vertex-controller.hpp"

void VertexController::BeginDrag(GLContext const& ctx, Vector2f *vControlled, size_t nControlled, Vector2i const& start, int allowance)
{
	const Vector2f glStart = ctx.ScreenPointToGL(start);
	const GLfloat glAllowance = ctx.ScreenToGL(allowance);

	for (; nControlled; --nControlled, ++vControlled)
	{
		if (glStart[0] + glAllowance >= (*vControlled)[0] && glStart[0] - glAllowance <= (*vControlled)[0]
		 && glStart[1] + glAllowance >= (*vControlled)[1] && glStart[1] - glAllowance <= (*vControlled)[1])
		{
			m_controlled = vControlled;
			m_glStartPos = *vControlled;
			m_screenOffset = {};
			return;
		}
	}
}
