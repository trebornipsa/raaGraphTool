#include "stdafx.h"


#include <windows.h>
#include <gl/gl.h>

#include "raaCudaGraph.h"

#include "raaEdgeDrawable.h"


raaEdgeDrawable::raaEdgeDrawable(raaCudaGraph *pGraph)
{
	m_pGraph=pGraph;
	setSupportsDisplayList(false);
	setUseDisplayList(false);
}

raaEdgeDrawable::~raaEdgeDrawable(void)
{
}

void raaEdgeDrawable::draw( osg::RenderInfo &renderInfo ) const
{
	if(m_pGraph)
	{


		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
		
/*		
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(100.0f, 0.0f, 0.0f);
		glEnd();

*/

/*
		glBegin(GL_LINES);
		for(unsigned int i=0;i<m_pGraph->numArcs();i++)
		{
			glVertex3fv(m_pGraph->vertexArray()+m_pGraph->indexArray()[i*2]*3);
			glVertex3fv(m_pGraph->vertexArray()+m_pGraph->indexArray()[i*2+1]*3);

		}
		glEnd();
*/
		
		glPushClientAttrib(GL_VERTEX_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3,GL_FLOAT, 0, m_pGraph->vertexArray());

		glDrawElements(GL_LINES, m_pGraph->numArcs()<<1, GL_UNSIGNED_INT, m_pGraph->indexArray());

		glPopClientAttrib();

		glPopAttrib();
	}
}

osg::Object * raaEdgeDrawable::cloneType() const
{
	//	return osg::Drawable::cloneType();
	return 0;
}

osg::Object * raaEdgeDrawable::clone( const osg::CopyOp& ) const
{
	return new raaEdgeDrawable(m_pGraph);
}

void raaEdgeDrawable::drawImplementation( osg::RenderInfo& r) const
{
	draw(r);
}
