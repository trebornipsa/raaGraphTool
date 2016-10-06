#pragma once

#include <raaUtilities/raaVector.h>

#include "raaDataObject.h"
#include "raaDataEngineTypes.h"
#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataArc : public raaDataObject
	{
		friend raaDataModel;
		friend raaDataLayer;
	public:
		bool hasNode(raaDataNode *pNode);
		const raaDataNodeList& nodes();

		void setCentre(raaVector &v);
		const raaVector& centre();

		void useAttributeAsIdealLength(std::string sName);
		void setIdealLength(float fIdealLength);
		float idealLength();

		void useAttributeAsSpringCoef(std::string sName);
		void setSpringCoef(float fSpringCoef);
		float springCoef();
	protected:
		raaDataNodeList m_lNodes;
		raaVector m_vCentre;

		raaDataArc(std::string sName);
		virtual ~raaDataArc();
		virtual void aboutToDelete();
		virtual void activeChanged(std::string sName);
		virtual void attributeChanged(std::string sName);

		float m_fIdealLength;
		std::string m_sIdealLengthAttribute;

		float m_fSpringCoef;
		std::string m_sSpringCoefAttribute;
	};
}
