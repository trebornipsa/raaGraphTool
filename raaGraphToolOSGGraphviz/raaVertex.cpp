#include "StdAfx.h"
#include "raaVertex.h"

raaNode* raaVertexFactory::create(std::string sName, raaGraph *pGraph)
{
	return new raaVertex(sName, pGraph);
}


raaVertex::raaVertex(std::string sName, raaGraph *pGraph) : raaNode(sName, pGraph)
{
	m_pGroup=new osg::Group();
	m_pGroup->setName("manip");
	m_pGroup->ref();

	osg::MatrixTransform *pMT=new osg::MatrixTransform();
	pMT->setMatrix(osg::Matrix::translate(vPos));
	m_pGroup->addChild(pMT);

	osg::Switch *pDraggerSwitch=new osg::Switch();
	m_pGroup->addChild(pDraggerSwitch);

	osg::Geode *pGeode=new osg::Geode();
	pGeode->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.2f, 1.0f, 0.3f, 1.0f)), osg::StateAttribute::ON);
	pMT->addChild(pGeode);

	pGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.1f)));

	addDragger(new osgManipulator::TranslateAxisDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate1DDragger(), pDraggerSwitch, pMT);
	addDragger(new osgManipulator::Translate2DDragger(), pDraggerSwitch, pMT);
	pDraggerSwitch->setAllChildrenOff();

	osg::Switch *pSwitch=new osg::Switch();
	pSwitch->setAllChildrenOn();

	osg::Billboard *pBB=new osg::Billboard();

	osgText::Text *pText=new osgText::Text();
	pText->setCharacterSize(0.1f);
	pText->setFont(csg_sFont);
	pText->setText(sName);

	pBB->addDrawable(pText);
	pSwitch->addChild(pBB);
	pMT->addChild(pSwitch);

	pBB->getOrCreateStateSet()->setAttributeAndModes(makeMaterial(osg::Vec4f(0.6f, 0.2f, 0.2f, 1.0f)), osg::StateAttribute::ON);

	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.15f, 0.0f, 0.0f));
	setRandPos();
}

virtual ~raaVertex::raaVertex()
{
	m_pGroup->unref();
}


osg::Vec3f raaVertex::getPos()
{
	return raaNode::getPos();
}

void raaVertex::setPos(osg::Vec3f v)
{
	raaNode::setPos(v);
	if(m_pGroup)
	{
		osg::MatrixTransform *pMT=(osg::MatrixTransform*)m_pGroup->getChild(0);

		osg::Matrixf m;
		m.makeTranslate(v);
		pMT->setMatrix(m);
	}
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

	pMat->setAmbient(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_AmbCoef, vCol[1]*csg_AmbCoef, vCol[2]*csg_AmbCoef, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_DiffCoef, vCol[1]*csg_DiffCoef, vCol[2]*csg_DiffCoef, 1.0f));
	pMat->setSpecular(osg::Material::FRONT, osg::Vec4(vCol[0]*csg_SpecCoef, vCol[1]*csg_SpecCoef, vCol[2]*csg_SpecCoef, 1.0f));
	pMat->setShininess(osg::Material::FRONT, 2.0f);

	return pMat;
}


