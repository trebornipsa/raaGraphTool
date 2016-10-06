#pragma once

#include <raaUtilities/raaVector.h>

#include "raaDataObject.h"

#include "raaDataEngine2Defs.h"

namespace raaDE2
{
	class RAADATAENGINE2_DLL_DEF raaDataNode: public raaDataObject
	{
	private:
		friend raaDataModel;
		friend raaDataArc;
		friend raaDataPeriod;
	public:

		void setPosition(raaVector& vPos);
		void addDisplacment(raaVector &vDisp);
		const raaVector& position();

		void setVelocity(raaVector &vVel);
		const raaVector& velocity();

		void setForce(raaVector &vForce);
		void addForce(raaVector &vForce);
		const raaVector& force();

		void zeroForce();

		void setPinned(bool bPinned);
		bool pinned();



		void useAttributeAsMass(std::string sName);
		void useAttributeAsDamping(std::string sName);
		void useAttributeAsSize(std::string sName);

		float mass();
		float damping();
		float size();

		void setMass(float fMass);
		void setDamping(float fDamping);
		void setSize(float fSize);

		const raaStringList& groups();

	protected:
		raaVector m_vPosition;
		raaVector m_vVelocity;
		raaVector m_vForce;

		bool m_bPinned;

		std::string m_sMassAttribute;
		float m_fMass;

		std::string m_sDampingAttribute;
		float m_fDamping;

		std::string m_sSizeAttribute;
		float m_fSize;

		raaDataArcList m_lArcs;

		raaStringList m_lGroups;

		raaDataNode(std::string sName);
		virtual ~raaDataNode();
		virtual void aboutToDelete();
		virtual void activeChanged(std::string sName);
		virtual void attributeChanged(std::string sName);
	};
}
