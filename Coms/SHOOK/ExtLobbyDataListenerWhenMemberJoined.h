#pragma once
#include "ILobbyDataRetrieveListener.h"
#include "IGalaxyID.h"
#include "IMatchmaking.h"
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
class ExtLobbyDataListenerWhenMemberJoined: public ILobbyDataRetrieveListener
{

public: 
	ExtLobbyDataListenerWhenMemberJoined(const ISGalaxyId& memberid, IMatchmaking* matchmaking_) {
		member = memberid;
		logger = new SWBFLogger();
		m = matchmaking_;
	}
	void OnLobbyDataRetrieveSuccess(const ISGalaxyId& lobbyID) {

		logger->Write("Lobby Data retrieved");
		logger->Write("MemberData::");
		logger->Write(to_string(m->GetLobbyMemberDataCount(lobbyID, member)));
	}

	void OnLobbyDataRetrieveFailure(const ISGalaxyId& lobbyID, IFailureReason failureReason) {
		logger->Write("Lobby Data retrieval failed");
	}

private:
	ISGalaxyId member;
	SWBFLogger* logger;
	IMatchmaking* m;
};

