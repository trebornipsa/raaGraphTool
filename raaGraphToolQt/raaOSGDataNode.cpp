#include "stdafx.h"

#include <windows.h>

#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Billboard>
#include <osg/Switch>

#include <raaDataEngine/raaDataEngine.h>
#include <raaDataEngine/raaDataModel.h>

//#include "raaHistory.h"
#include "raaGraphInterface.h"
#include "raaOSGDataNode.h"

osg::Material *raaOSGDataNode::sm_pNormalMaterial=0;
osg::Material *raaOSGDataNode::sm_pPinMaterial=0;
osg::Material *raaOSGDataNode::sm_pTextMaterial = 0;
osg::Material *raaOSGDataNode::sm_pSelectedMaterial = 0;
osgManipulator::TranslateAxisDragger *raaOSGDataNode::sm_pDragger=0;

osg::Matrixf raaOSGDataNode::sm_DraggerScale;
osg::Matrixf raaOSGDataNode::sm_DraggerInvScale;
osg::Sphere *raaOSGDataNode::sm_pSphere=0;
//osg::MatrixTransform *raaOSGDataNode::sm_pNodeScale=0;

raaOSGDataNode::raaOSGDataNode(std::string sName, raaGraphInterface *pInterface, std::string sGroup) : raaDataNode(sName, sGroup)
{
	m_pInterface = pInterface;
	m_bSelected = false;
	m_bPinned = false;
	m_pMaterial = 0;
	initMaterial();


	osg::Callback::setName("raaOSGDataNode");

	m_pGroup = new osg::Group();
	m_pGroup->ref();


	m_pMT = new osg::MatrixTransform();
	m_pMT->setName(sName);
	m_pMT->setUpdateCallback(this);

	m_pGroup->addChild(m_pMT);

	m_pScale = new osg::MatrixTransform();

	m_pGeode = new osg::Geode();
	m_pGeode->ref();

	if (!sm_pSphere) sm_pSphere = new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.5f);

	osg::ShapeDrawable *pSD = new osg::ShapeDrawable(sm_pSphere);
	pSD->setName("raaOSGMouseOverData");
	pSD->setUserData(this);

	m_pGeode->addDrawable(pSD);
	m_pGeode->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	m_pMT->addChild(m_pScale);
	m_pScale->addChild(m_pGeode);
/*
	if (!sm_pNodeScale)
	{
		sm_pNodeScale = new osg::MatrixTransform();
		osg::Matrixf mNS;
		mNS.makeScale(osg::Vec3f(1.0f, 1.0f, 1.0f));
		sm_pNodeScale->setMatrix(mNS);
	}
*/
//	sm_pSphere->

	m_pText = new osgText::Text();
	m_pText->setCharacterSize(0.3f);
	m_pText->setText(std::string("   ")+sName);

	osg::Billboard *pBB = new osg::Billboard();
	pBB->addDrawable(m_pText);
	pBB->getOrCreateStateSet()->setAttributeAndModes(sm_pTextMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
//	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.0f, 0.0f, 0.0f));
//	pBB->setPosition(0, osg::Vec3f(0.5f, 0.0f, 0.0f));
	
	m_pBillboardSwitch = new osg::Switch();
	m_pBillboardSwitch->addChild(pBB);
	m_pScale->addChild(m_pBillboardSwitch);
	m_pBillboardSwitch->setAllChildrenOff();
}

raaOSGDataNode::raaOSGDataNode(std::string sName, raaGraphInterface *pInterface, raaNodeGroups &groups) : raaDataNode(sName, groups)
{
	m_pInterface = pInterface;
	m_bSelected = false;
	m_bPinned = false;
	initMaterial();

	osg::Callback::setName("raaOSGDataNode");

	m_pGroup = new osg::Group();
	m_pGroup->ref();

	m_pMT = new osg::MatrixTransform();
	m_pMT->setName(sName);
	m_pMT->setUpdateCallback(this);
	m_pGroup->addChild(m_pMT);

	m_pScale = new osg::MatrixTransform();

	if (!sm_pSphere) sm_pSphere = new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), 0.5f);
	
	m_pGeode = new osg::Geode();
	m_pGeode->ref();
	osg::ShapeDrawable *pSD = new osg::ShapeDrawable(sm_pSphere);
	pSD->setUserData(this);
	pSD->setName("raaOSGMouseOverData");

	m_pGeode->addDrawable(pSD);
	m_pGeode->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
/*
	if (!sm_pNodeScale)
	{
		sm_pNodeScale = new osg::MatrixTransform();
		osg::Matrixf mNS;
		mNS.makeScale(osg::Vec3f(1.0f, 1.0f, 1.0f));
		sm_pNodeScale->setMatrix(mNS);
	}
*/

	m_pMT->addChild(m_pScale);
//	m_pScale->addChild(sm_pNodeScale);
	m_pScale->addChild(m_pGeode);

	m_pText = new osgText::Text();
	m_pText->setCharacterSize(0.3f);
	m_pText->setText(std::string("   ") + sName);

	osg::Billboard *pBB = new osg::Billboard();
	pBB->addDrawable(m_pText);
	pBB->getOrCreateStateSet()->setAttributeAndModes(sm_pTextMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
	//	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setMode(osg::Billboard::POINT_ROT_EYE);
	pBB->setAxis(osg::Vec3f(0.0f, 1.0f, 0.0f));
	pBB->setNormal(osg::Vec3f(0.0f, 0.0f, 1.0f));
	pBB->setPosition(0, osg::Vec3f(0.0f, 0.0f, 0.0f));
	//	pBB->setPosition(0, osg::Vec3f(0.5f, 0.0f, 0.0f));
	m_pBillboardSwitch = new osg::Switch();
	m_pBillboardSwitch->addChild(pBB);
	m_pScale->addChild(m_pBillboardSwitch);
	m_pBillboardSwitch->setAllChildrenOff();
	
}


raaOSGDataNode::~raaOSGDataNode()
{
	if(m_pMT)
	{
		osg::Group *pGroup = dynamic_cast<osg::Group*>(m_pGroup->getParents()[0]);
		if (pGroup) pGroup->removeChild(m_pGroup);
		m_pGroup->unref();
	}

//	if (m_pGeode) m_pGeode->unref();
}

void raaOSGDataNode::initMaterial()
{
	if (!sm_pNormalMaterial)
	{
		sm_pNormalMaterial = new osg::Material();
		sm_pNormalMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.1f, 0.2f, 0.15f, 1.0f));
		sm_pNormalMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.4f, 1.0f, 0.5f, 1.0f));
		sm_pNormalMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.4f, 1.0f, 0.8f, 1.0f));
		sm_pNormalMaterial->setShininess(osg::Material::FRONT_AND_BACK, 20.0f);
		sm_pNormalMaterial->ref();

		sm_DraggerScale.makeScale(5.0f, 5.0f, 5.0f);
		sm_DraggerInvScale = osg::Matrixf::inverse(sm_DraggerScale);

	}

	if (!sm_pSelectedMaterial)
	{
		sm_pSelectedMaterial = new osg::Material();
		sm_pSelectedMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.2f, 0.2f, 0.2f, 1.0f));
		sm_pSelectedMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.8f, 0.8f, 0.8f, 1.0f));
		sm_pSelectedMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
		sm_pSelectedMaterial->setShininess(osg::Material::FRONT_AND_BACK, 80.0f);
		sm_pSelectedMaterial->ref();
	}

	if (!sm_pPinMaterial)
	{
		sm_pPinMaterial = new osg::Material();
		sm_pPinMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.2f, 0.0f, 0.15f, 1.0f));
		sm_pPinMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 0.5f, 0.5f, 1.0f));
		sm_pPinMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 0.6f, 1.0f, 1.0f));
		sm_pPinMaterial->setShininess(osg::Material::FRONT_AND_BACK, 20.0f);
		sm_pPinMaterial->ref();
	}

	if (!sm_pTextMaterial)
	{
		sm_pTextMaterial = new osg::Material();
		sm_pTextMaterial->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.4f, 0.4f, 0.25f, 1.0f));
		sm_pTextMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4f(0.8f, 0.8f, 0.5f, 1.0f));
		sm_pTextMaterial->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4f(1.0f, 1.0f, 0.8f, 1.0f));
		sm_pTextMaterial->setShininess(osg::Material::FRONT_AND_BACK, 2.0f);
		sm_pTextMaterial->ref();
	}

	if(!sm_pDragger)
	{
		sm_pDragger = new osgManipulator::TranslateAxisDragger();
		sm_pDragger->setAxisLineWidth(sm_pDragger->getAxisLineWidth()*5.0f);
		sm_pDragger->setPickCylinderRadius(sm_pDragger->getPickCylinderRadius()*10.0f);
		sm_pDragger->ref();
		sm_pDragger->setupDefaultGeometry();
		sm_pDragger->setHandleEvents(true);
		sm_pDragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_CTRL);
	}


}

bool raaOSGDataNode::run(osg::Object* object, osg::Object* data)
{

	if (m_bSelected)
	{
		osg::Matrixf m = sm_DraggerInvScale*sm_pDragger->getMatrix();
//		osg::Matrixf m = sm_pDragger->getMatrix();
		osg::Vec3d v = m.getTrans();

//		v = sm_DraggerInvScale*v;
		setPosition(raaVector(v[0], v[1], v[2]));
		raaDataEngine::instance()->currentModel()->nodeMoved(this);
	}

	return traverse(object, data);
}

void raaOSGDataNode::setModel(osg::Node* pNode)
{
	if (m_pNode)
		m_pScale->removeChild(m_pNode);
	else
		m_pScale->removeChild(m_pGeode);

	m_pNode = pNode;

	if(pNode)
	{
		m_pScale->addChild(m_pNode);
	}
	else
	{
		m_pScale->addChild(m_pGeode);
	}

}

/*
void raaOSGDataNode::operator()(osg::Node* pNode, osg::NodeVisitor* pNV)
{

//	if(m_pMT)
//	{
//		osg::Matrix m;
//		m.makeTranslate(osg::Vec3f(m_vPosition[0], m_vPosition[1], m_vPosition[2]));
//		m_pMT->setMatrix(m);
//	}

	if(m_bSelected)
	{
		osg::Matrixf m = sm_pDragger->getMatrix();
		osg::Vec3d v=m.getTrans();
		setPosition(raaVector(v[0], v[1], v[2]));
	}


	pNV->traverse(*pNode);

}
*/

osg::Group* raaOSGDataNode::node()
{
	return m_pGroup;
}

void raaOSGDataNode::setPosition(raaVector v)
{
	raaDataNode::setPosition(v);
	if(m_pMT)
	{
		osg::Matrix m;
		m.makeTranslate(osg::Vec3f(v[0], v[1], v[2]));
		m_pMT->setMatrix(m);

//		raaHistory::instance()->setNodePosition(instance(), v[0], v[1], v[2]);
	}
}

void raaOSGDataNode::select(bool bSelect)
{
	if (bSelect != m_bSelected)
	{ 
		m_bSelected = bSelect;
		if (m_bSelected)
		{
			m_pGroup->addChild(sm_pDragger);
			sm_pDragger->addTransformUpdating(m_pMT);
			sm_pDragger->setMatrix(sm_DraggerScale*m_pMT->getMatrix());

			suspendActive(true);
//			m_bActive = false;
			if (m_pScale)
			{
				m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pSelectedMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			}
		}
		else
		{
			if (!pinned()) suspendActive(false);

			if (m_pScale)
			{
				if (pinned())
					m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pPinMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				else
					m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			}

			osg::Matrixf m=sm_pDragger->getMatrix();
			m_pMT->setMatrix(sm_DraggerInvScale*m);
			m_pGroup->removeChild(sm_pDragger);
			sm_pDragger->removeTransformUpdating(m_pMT);
		}
	}
}

void raaOSGDataNode::pin(bool bPin)
{

	if (bPin != pinned())
	{
		if (!pinned() && bPin)
		{
			if (m_pScale)
			{
				m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pPinMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			}
		}
		else if(pinned() && !bPin)
		{
//			if (!m_bSelected) m_bActive = true;
			if (m_pScale)
			{
				if (m_bSelected)
					m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pSelectedMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				else
					if(m_pMaterial)
						m_pScale->getOrCreateStateSet()->setAttributeAndModes(m_pMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
					else
						m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			}
		}
		raaDataNode::pin(bPin);

	}
//	raaDataNode::pin(bPin);
}

/*
void raaOSGDataNode::togglePin()
{
	pin(!m_bPinned);
}

bool raaOSGDataNode::pinned()
{
	return m_bPinned;
}
*/
void raaOSGDataNode::activityRef()
{
	if(!m_uiActivityCount)
	{
		osg::Matrixf m;
		m.makeScale(osg::Vec3f(1.0f, 1.0f, 1.0f));
		if (m_pScale) m_pScale->setMatrix(m);
		m_pInterface->moveToActiveDisplay(this);
	}
	raaDataNode::activityRef();
}

void raaOSGDataNode::activityUnref()
{	
	raaDataNode::activityUnref();
	
	if (!m_uiActivityCount)
	{
		osg::Matrixf m;
		m.makeScale(osg::Vec3f(0.2f, 0.2f, 0.2f));
		if (m_pScale) m_pScale->setMatrix(m);
		m_pInterface->moveToInactiveDisplay(this);
	}


}

void raaOSGDataNode::setTextOn(bool bOn)
{
	if (m_pBillboardSwitch)
	{
		if (bOn)
			m_pBillboardSwitch->setAllChildrenOn();
		else
			m_pBillboardSwitch->setAllChildrenOff();
	}
}

void raaOSGDataNode::setDescription(std::string sDesc)
{
	m_sDescription = sDesc;

	if(m_pText)
	{
		if (m_sDescription.length())
			m_pText->setText(name() + "\n" + m_sDescription);
		else
			m_pText->setText(name());
	}
}

std::string raaOSGDataNode::description()
{
	return m_sDescription;
}

void raaOSGDataNode::setMaterial(osg::Vec3f vCol)
{
	if(!m_pMaterial) m_pMaterial = new osg::Material();

	osg::Vec4f vAmb, vDiff, vSpec;

	vAmb[0] = vCol[0] * 0.2f;
	vAmb[1] = vCol[1] * 0.2f;
	vAmb[2] = vCol[2] * 0.2f;
	vAmb[3] = 1.0f;

	vDiff[0] = vCol[0];
	vDiff[1] = vCol[1];
	vDiff[2] = vCol[2];
	vDiff[3] = 1.0f;

	vSpec[0] = vCol[0]*0.75f;
	vSpec[1] = vCol[1] * 0.75f;
	vSpec[2] = vCol[2] * 0.75f;
	vSpec[3] = 1.0f;

	m_pMaterial->setAmbient(osg::Material::FRONT_AND_BACK, vAmb);
	m_pMaterial->setDiffuse(osg::Material::FRONT_AND_BACK, vDiff);
	m_pMaterial->setSpecular(osg::Material::FRONT_AND_BACK, vSpec);
	m_pMaterial->setShininess(osg::Material::FRONT_AND_BACK, 2.0f);
	m_pMaterial->ref();

	if (!pinned())
	{
		if (m_pScale)
		{
			if (m_bSelected)
				m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pSelectedMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
			else
				if (m_pMaterial)
					m_pScale->getOrCreateStateSet()->setAttributeAndModes(m_pMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				else
					m_pScale->getOrCreateStateSet()->setAttributeAndModes(sm_pNormalMaterial, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		}
	}
}

void raaOSGDataNode::setRadius(float fRad)
{
	if(sm_pSphere)
	{
		sm_pSphere->setDataVariance(osg::Object::DYNAMIC);
		sm_pSphere->setRadius(fRad);

	}
}
