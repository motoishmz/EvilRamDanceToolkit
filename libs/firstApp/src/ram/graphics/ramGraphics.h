#pragma once

void ramBillboard()
{
	ofMatrix4x4 m;
	glGetFloatv(GL_MODELVIEW_MATRIX, m.getPtr());
	
	const ofVec3f& s = m.getScale();
	
	m(0, 0) = s.x;
	m(0, 1) = 0;
	m(0, 2) = 0;
	
	m(1, 0) = 0;
	m(1, 1) = s.y;
	m(1, 2) = 0;
	
	m(2, 0) = 0;
	m(2, 1) = 0;
	m(2, 2) = s.z;
	
	glLoadMatrixf(m.getPtr());
}