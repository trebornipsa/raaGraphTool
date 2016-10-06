#include "StdAfx.h"

#include <osg/Switch>
#include <osg/ShapeDrawable>
#include <osgManipulator/Translate1DDragger>
#include <osgManipulator/Translate2DDragger>
#include <osgManipulator/TranslateAxisDragger>
#include <osg/Billboard>
#include <osgText/Text>

#include "raaVertexHandler.h"
#include "raaVertex.h"

std::string raaVertex::csm_sFont="fonts/arial.ttf";
float raaVertex::csm_SpecCoef=0.1f;
float raaVertex::csm_DiffCoef=0.8f;
float raaVertex::csm_AmbCoef=1.0f;


raaNode* raaVertexFactory::create(std::string sID, std::string sName, raaGraph *pGraph)
{
	return new raaVertex(sID, sName, pGraph);
}


raaVertex::raaVertex(std::string sID, std::string sName, raaGraph *pGraph) : raaNode(sID, sName, pGraph)
{
	m_bLocked=false;
	m_uiIndex=0;
	m_fEnergy=0;
	m_bActive=false;
	m_pDraggerTransform=0;

	m_pGroup=new osg::Group();
	m_pGroup->setName("manip");
	m_pGroup->ref();

	osg::MatrixTransform *pMT=new osg::MatrixTransform();
	pMT->setMatrix(osg::Matrix::translate(m_vPos));
	m_pGroup->addChild(pMT);

	osg::Switch *pDraggerSwitch=new osg::Switch();
	m_pGroup->addChild(pDraggerSwitch);

	m_pMaterialSwitch=new osg::Switch(); 
	pMT->addChild(m_pMaterialSwitch);

	osg::ShapeDrawable *pSD=new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.1f));

	osg::Geode *pGeode0=new osg::Geode();
	pGeode0->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.2f, 1.0f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pGeode0->addDrawable(pSD);
	m_pMaterialSwitch->addChild(pGeode0);

	osg::Geode *pGeode1=new osg::Geode();
	pGeode1->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(1.0f, 0.2f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pGeode1->addDrawable(pSD);
	m_pMaterialSwitch->addChild(pGeode1);

	m_pMaterialSwitch->setSingleChildOn(0);

	addDragger(new osgManipulator::TranslateAxisDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate1DDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate2DDragger(), pDraggerSwitch, pMT);
	pDraggerSwitch->setAllChildrenOff();

	osg::Switch *pSwitch=new osg::Switch();
	pSwitch->setAllChildrenOn();

	osg::Billboard *pBB=new osg::Billboard();

	osgText::Text *pText=new osgText::Text();
	pText->setCharacterSize(0.1f);
	pText->setFont(csm_sFont);
	pText->setText(sName);

	pBB->addDrawable(pText);
	pSwitch->addChild(pBB);
	pMT->addChild(pSwitch);

	pBB->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.6f, 0.2f, 0.2f, 1.0f)), osg::StateAttribute::ON);

	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.15f, 0.0f, 0.0f));

	m_pGroup->setUpdateCallback(this);
}

raaVertex::~raaVertex()
{
	m_pGroup->unref();
}


osg::Vec3f raaVertex::getPos()
{
	return raaNode::getPos();
}

void raaVertex::setPos(osg::Vec3f v)
{
	if(m_pGroup)
	{
		osg::MatrixTransform *pMT=(osg::MatrixTransform*)m_pGroup->getChild(0);

		osg::Matrixf m;
		m.makeTranslate(v);
		pMT->setMatrix(m);

		osg::Switch *pSwitch=(osg::Switch*)m_pGroup->getChild(1);

		for(unsigned int i=0;i<pSwitch->getNumChildren();i++)
			((osg::MatrixTransform*)pSwitch->getChild(i))->setMatrix(m);
	}
	raaNode::setPos(v);
}

osg::Group* raaVertex::getGroup()
{
	return m_pGroup;
}

void raaVertex::setGroup(osg::Group *pGroup)
{
	m_pGroup=pGroup;
}

void raaVertex::addDragger(osgManipulator::Dragger *pDragger, osg::Switch *pSwitch, osg::MatrixTransform *pMT)
{
	pDragger->setupDefaultGeometry();
	pDragger->setHandleEvents(true);
	pDragger->addTransformUpdating(pMT);
	pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
	pDragger->setMatrix(raaVertexHandler::sm_Scale*pMT->getMatrix());
	pSwitch->addChild(pDragger);
}

osg::Material* raaVertex::makeMaterial(osg::Vec4f vCol)
{
	osg::Material *pMat=new osg::Material();

	pMat->setAmbient(osg::Material::FRONT, osg::Vec4(vCol[0]*csm_AmbCoef, vCol[1]*csm_AmbCoef, vCol[2]*csm_AmbCoef, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(vCol[0]*csm_DiffCoef, vCol[1]*csm_DiffCoef, vCol[2]*csm_DiffCoef, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4(vCol[0]*csm_SpecCoef, vCol[1]*csm_SpecCoef, vCol[2]*csm_SpecCoef, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 2.0f);

	return pMat;
}

void raaVertex::setIndex( unsigned int uiIndex )
{
	m_uiIndex=uiIndex;
}

unsigned int raaVertex::index()
{
	return m_uiIndex;
}

void raaVertex::setVelocity( osg::Vec3f vVel )
{
	m_vVelocity=vVel;
}

osg::Vec3f raaVertex::velocity()
{
	return m_vVelocity;
}

void raaVertex::setForces( osg::Vec3f vForce )
{
	m_vForces=vForce;
}

void raaVertex::addForce( osg::Vec3f vForce )
{
	m_vForces+=vForce;
}

osg::Vec3f raaVertex::getForces()
{
	return m_vForces;
}

float raaVertex::update()
{
	if(m_bFixed || m_bLocked)
	{
		m_vVelocity=osg::Vec3f(0.0f, 0.0f, 0.0f);
		return m_fEnergy=0.0f;
	}
	else
	{
		float fTime = 0.02f;
		m_vVelocity+=((m_vForces/m_fMass)*fTime);
		m_vVelocity*=0.9f;
		setPos(getPos()+m_vVelocity*fTime);
		return m_fEnergy=m_fMass*m_vVelocity.length();
	}
}
float raaVertex::energy()
{
	return m_fEnergy;
}

void raaVertex::operator()( osg::Node *pNode, osg::NodeVisitor *pNV )
{
	if(m_bActive && m_pDraggerTransform) 
		setPos(m_pDraggerTransform->getMatrix().getTrans());
		
	pNV->traverse(*pNode);
}

void raaVertex::setActive( bool bActive )
{
	setFixed(m_bActive=bActive);
}

void raaVertex::setDraggerTransform( osg::MatrixTransform *pDMT )
{
	m_pDraggerTransform=pDMT;
}

void raaVertex::toggleFixed()
{
	m_bLocked=!m_bLocked;

	if(m_bLocked) m_pMaterialSwitch->setSingleChildOn(1);
	else m_pMaterialSwitch->setSingleChildOn(0);
}



