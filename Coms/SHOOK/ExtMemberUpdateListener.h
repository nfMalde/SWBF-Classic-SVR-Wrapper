#pragma once
#include "ILobbyMemberDataUpdateListener.h"
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
#include "IGalaxyID.h";
class ExtMemberUpdateListener: public ILobbyMemberDataUpdateListener
{
public:
	ExtMemberUpdateListener() {
		logger = new SWBFLogger();
	}
	void OnLobbyMemberDataUpdateSuccess(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID) {
		logger->Write("Member Data Updated!");
	};

	void OnLobbyMemberDataUpdateFailure(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID, void* failureReason) {

	}
private:
	SWBFLogger* logger ;
};

