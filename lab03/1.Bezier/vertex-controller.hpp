#pragma once
#include <gl-context.hpp>

class VertexController
{
public:
	void BeginDrag(GLContext const& ctx, Vector2f *vControlled, size_t nControlled, Vector2i const& start, int allowance);

	void EndDrag()
	{
		m_controlled = nullptr;
	}

	void UpdateDrag(GLContext const& ctx, Vector2i const& offset)
	{
		if (m_controlled)
		{
			m_screenOffset += offset;
			(*m_controlled)[0] = m_glStartPos[0] + ctx.ScreenToGL(m_screenOffset[0]);
			(*m_controlled)[1] = m_glStartPos[1] - ctx.ScreenToGL(m_screenOffset[1]);
		}
	}

private:
	Vector2f *m_controlled = nullptr;
	Vector2f m_glStartPos;
	Vector2i m_screenOffset;
};
