#pragma once

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <iostream>

namespace raaDE2Kernal
{
	const static char csm_Sepperator[] = "<raa>";

	// major types
	const static unsigned short csm_usDE2Engine = 0;
	const static unsigned short csm_usDE2Model = 1;
	const static unsigned short csm_usDE2Period = 2;
	const static unsigned short csm_usDE2Layer = 3;
	const static unsigned short csm_usDE2Arc = 4;
	const static unsigned short csm_usDE2Node = 5;

	// engine types
	const static unsigned short csm_usDE2LoadModel = 0;
	const static unsigned short csm_usDE2UnloadModel = 1;
	const static unsigned short csm_usDE2RequestModels = 2;
	const static unsigned short csm_usDE2ModelsList = 3;
	const static unsigned short csm_usDE2TrackModel = 4;
	const static unsigned short csm_usDE2ModelAdded = 5;
	const static unsigned short csm_usDE2ModelRemoved = 6;

	// model types
	const static unsigned short csm_usDE2StopSim = 0;
	const static unsigned short csm_usDE2StartSim = 1;
	const static unsigned short csm_usDE2Energy = 2;
	const static unsigned short csm_usDE2TimeStep = 3;
	const static unsigned short csm_usDE2PeriodTransitionOn = 4;
	const static unsigned short csm_usDE2PeriodTransitionOff = 5;
	const static unsigned short csm_usDE2PeriodTransitionStart = 6;
	const static unsigned short csm_usDE2PeriodTransitionEnd = 7;
	const static unsigned short csm_usDE2ModelName = 8;
	const static unsigned short csm_usDE2RequestModelData = 9;
	const static unsigned short csm_usDE2ModelStatus = 10;
	const static unsigned short csm_usDE2Solve = 11;
	const static unsigned short csm_usDE2UdpConnection = 12;

	// period types
	const static unsigned short csm_usDE2PeriodInactive = 0;
	const static unsigned short csm_usDE2PeriodActive = 1;

	// arc types
	const static unsigned short csm_usDE2NewArc = 0;
	const static unsigned short csm_usDE2updateArc = 1;

	//node types
	const static unsigned short csm_usDE2NewNode = 0;
	const static unsigned short csm_usDE2UpdateNode = 1;
	const static unsigned short csm_usDE2UpdateNodePositions = 2;

	typedef struct raaVec {
		float x;
		float y;
		float z;
	} raaVec;
}
