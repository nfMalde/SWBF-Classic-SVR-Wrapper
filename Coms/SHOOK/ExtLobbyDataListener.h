#pragma once
#include "ILobbyDataListener.h"
#include "IGalaxyID.h"
#include "IMatchmaking.h"
#include "IFriends.h"; 
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
class ExtLobbyDataListener: public ILobbyDataListener
{

public:
	ExtLobbyDataListener(IMatchmaking* m, IFriends* f) {
		logger = new SWBFLogger();
		match = m;
		friends = f;
	}

	void OnLobbyDataUpdated(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID) {
		if (memberID.IsValid()) {
			logger->Write("Member updated!");
			logger->Write(to_string(match->GetLobbyMemberDataCount(lobbyID, memberID)));
		}
		else {
			logger->Write("Lobby Updated!");
			int numPlayers = match->GetNumLobbyMembers(lobbyID);

			logger->Write("Current Number of player: ");
			logger->Write(to_string(numPlayers));
			match->JoinLobby(lobbyID);

			for (int J = 0; J < numPlayers; J++) {
				if (J == 0) {
					continue;
				}
				const ISGalaxyId& pid = match->GetLobbyMemberByIndex(lobbyID, J);

				if (pid.IsValid()) {
				 
					const char* name = friends->GetFriendPersonaName(pid);
					
					if (!name)
					{
						logger->Write("No name!");
					}

					string s = string("Name=").append(name);
					logger->Write(s);
				}


			}


	 
		/*	int lbbbyDataCount = match->GetLobbyDataCount(lobbyID);
			logger->Write("Lobby Data COUNT?");
			logger->Write(to_string(lbbbyDataCount));

			if (lbbbyDataCount > 0) {
				for (int j = 0; j < lbbbyDataCount; j++) {
					char* key =  new char[200];
					uint32_t keyLength = 200;
					char* value = new char[200];
					 
					uint32_t valueLength = 200;
					match->GetLobbyDataByIndex(lobbyID, j, key, keyLength, value, valueLength);

					string dataRow = string("{").append(key).append("}==").append(value);

					logger->Write(dataRow);
				}
			}*/
			


		}
	}

private:
	SWBFLogger* logger;
	IMatchmaking* match;
	IFriends* friends;
};

