#pragma once

#include <string>
#include <list>
#include <map>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Switch>
#include <osg/Drawable>

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glu.h>

#include <raaGraphEngine/raaGraph.h>
#include <raaGraphEngine/raaGraphFactory.h>

typedef std::list<raaNode*> raaNodeList;
typedef std::map<int, raaNodeList> raaNodeMap;
typedef std::map<int, raaNode*> raaNodeArray;

typedef std::list<double>raaVecList;

class raaCull : public osg::Drawable::CullCallback
{
public:
	virtual bool cull(osg::NodeVisitor *nv, osg::Drawable *drawable, osg::RenderInfo *renderInfor) const
	{
		return false;
	}
};

class raaDrawable : public osg::Drawable::DrawCallback
{
public:
	raaDrawable()
	{
		m_pQuat = gluNewQuadric();
	};
	virtual ~raaDrawable()
	{
		gluDeleteQuadric(m_pQuat);
	};
/*
	void setData(float fRad, osg::Vec3f vCen)
	{
		m_fRadius = fRad;
		m_vCentre = vCen;
	}
*/
	virtual void drawImplementation(osg::RenderInfo& r,const osg::Drawable* pDrawable) const
	{
		glPushMatrix();
//		glTranslatef(m_vCentre[0], m_vCentre[1], m_vCentre[2]);

//		gluSphere(m_pQuat, m_fRadius, 10, 10);

		glBegin(GL_TRIANGLES);

		raaVecList::const_iterator itV = m_vVerts.begin();
		raaVecList::const_iterator itN = m_vNorms.begin();

		while (itN != m_vNorms.end() && itV != m_vVerts.end())
		{
			const double nx=*itN; itN++;
			const double ny=*itN; itN++;
			const double nz =*itN; itN++;
			glNormal3d(nx, ny, nz);

			const double vx0 = *itV; itV++;
			const double vy0 = *itV; itV++;
			const double vz0 = *itV; itV++;
			glVertex3d(vx0, vy0, vz0);
			const double vx1 = *itV; itV++;
			const double vy1 = *itV; itV++;
			const double vz1 = *itV; itV++;
			glVertex3d(vx1, vy1, vz1);
			const double vx2 = *itV; itV++;
			const double vy2 = *itV; itV++;
			const double vz2 = *itV; itV++;
			glVertex3d(vx2, vy2, vz2);



		};

		glEnd();

		glPopMatrix();

		pDrawable->drawImplementation(r);
	}

	raaVecList m_vNorms;
	raaVecList m_vVerts;

protected:
	GLUquadricObj *m_pQuat;

	

//	osg::Vec3f m_vCentre;
//	float m_fRadius;


};

class raaUndirectedGraph : public raaGraph, osg::NodeCallback
{
	friend class raaUndirectedGraphFactory;
public:
	virtual raaNode* addNode(std::string sID, std::string sType, std::string sName);
	virtual raaEdge* addEdge(std::string sType, raaNode *pStart, raaNode *pEnd, float fWeight=1.0f);
	
	virtual void updateNode(raaNode *pNode, std::string sUpdate);
	virtual void updateEdge(raaEdge *pEdge, std::string sUpdate);

	virtual bool solve(unsigned int uiNumIterations);

	virtual float energy();
	virtual void operator()(osg::Node *pNode, osg::NodeVisitor *pNV);

	void contSolve(bool bCont);

	void applyMasses();

	osg::Switch* createClusterRender();

protected:
	float m_fEPS;
	int m_iMinClusterSize;

	osg::Switch *m_pClusterSwitch;
	osg::Group *m_pClusterGroup;
	osg::Geode *m_pClusterGeode;
	osg::ShapeDrawable *m_pClusterShapeDrawable;
	raaDrawable *m_pDrawable;



	void clusterRegion(raaNode *pNodeTarget, raaNodeList &l);
	float distance(raaNode *pN1, raaNode *pN2);
	float distance(osg::Vec3f vOrigin, raaNode* pN2);

	raaUndirectedGraph(std::string sName, osg::Group *pRoot);

	virtual ~raaUndirectedGraph();

	osg::Group *m_pArcGroup;
	osg::Group *m_pVertexGroup;
	osg::Geometry *m_pGeom;
	osg::Vec4Array *m_pCols;
	osg::Vec3Array *m_pVerts;
	osg::DrawElementsUByte *m_pIndex;

	unsigned int m_uiVertex;
	unsigned int m_uiArc;

	float m_fEnergy;
	bool m_bContSolve;

	void cluster();
	raaNodeList m_lNoise;
	raaNodeMap m_mClusters;

	float m_fRadius;
	osg::Vec3f m_vCentre;

};

class raaUndirectedGraphFactory : public raaGraphFactory
{
public:
	virtual raaGraph* create(std::string sName);
	void setRoot(osg::Group *pRoot);
protected:
	osg::Group *m_pRoot;

};
