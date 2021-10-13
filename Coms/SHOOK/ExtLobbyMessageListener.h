#pragma once
#include "IGalaxyID.h";
#include "ILobbyMessageListener.h"
#include "IMatchmaking.h"
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
class ExtLobbyMessageListener: public ILobbyMessageListener
{
private:
	SWBFLogger* logger;
	IMatchmaking* match;
public:
	ExtLobbyMessageListener(IMatchmaking* m) {
		logger = new SWBFLogger();
		match = m;

	}

	void OnLobbyMessageReceived(const ISGalaxyId& lobbyID, const ISGalaxyId& senderID, uint32_t messageID, uint32_t messageLength) {
			
		logger->Write("<ExtLobbyMessageListener> New Message!");
		 
		char msg[1024];
		match->GetLobbyMessage(lobbyID, messageID, (ISGalaxyId&)senderID, msg, messageLength);

		logger->Write(msg);

	}
};

