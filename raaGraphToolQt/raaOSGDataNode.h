#pragma once

#include <windows.h>


#include <osg/Callback>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Material>
#include <osgText/Text>


#include <osgManipulator/TranslateAxisDragger>


#include <raaQTOSGWidget/raaOSGMouseOver.h>
#include <raaDataEngine/raaDataNode.h>

class raaGraphInterface;

class raaOSGDataNode : public raaDataNode, public osg::Callback, public raaOSGMouseOverPayload
{
public:
	raaOSGDataNode(std::string sName, raaGraphInterface *pInterface, std::string sGroup = "default");
	raaOSGDataNode(std::string sName, raaGraphInterface *pInterface, raaNodeGroups &groups);
	virtual bool run(osg::Object* object, osg::Object* data);

	void setModel(osg::Node *pNode);

//	virtual void operator() (osg::Node *pNode, osg::NodeVisitor *pNV);

	osg::Group* node();

	virtual void setPosition(raaVector v);

	void select(bool bSelect);
	virtual void pin(bool bPin);

	virtual void activityRef();
	virtual void activityUnref();

	void setTextOn(bool bOn);
	
	void setDescription(std::string sDesc);
	std::string description();

	void setMaterial(osg::Vec3f vCol);

	static void setRadius(float fRad);

protected:
	virtual ~raaOSGDataNode();

	void initMaterial();

	osg::Group *m_pGroup;
	osg::MatrixTransform *m_pMT;
	osg::MatrixTransform *m_pScale;
//	static osg::MatrixTransform *sm_pNodeScale;
	osg::Geode *m_pGeode;
	osg::Switch *m_pBillboardSwitch;
	osg::Node *m_pNode;
	osgText::Text *m_pText;
	static osg::Sphere *sm_pSphere;


	static osg::Material *sm_pNormalMaterial;
	static osg::Material *sm_pPinMaterial;
	static osg::Material *sm_pTextMaterial;
	static osg::Material *sm_pSelectedMaterial;
	osg::Material *m_pMaterial;

	bool m_bSelected;
//	bool m_bPinned;

	static osgManipulator::TranslateAxisDragger *sm_pDragger;

	static osg::Matrixf sm_DraggerScale;
	static osg::Matrixf sm_DraggerInvScale;
	std::string m_sDescription;
	raaGraphInterface *m_pInterface;
};

