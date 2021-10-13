#pragma once
#include "ILobbyMemberStateListener.h"
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
#include "IGalaxyID.h"
#include "ILobbyMemberStateChange.h"
#include <string>
#include "IMatchmaking.h"
#include "IFriends.h"
#include "ExtLobbyDataListenerWhenMemberJoined.h"
#include "INetworking.h"
#include <vector>

using namespace std; 
class ExtMemberStateListener: public ILobbyMemberStateListener
{

	/**
	
		Even if it shows the types you still need to include them. Visual Studio knows the types but the compiler not.
	*/

private:
	SWBFLogger* logger;
	IMatchmaking* matchmaking;
	IFriends* friends;
	INetworking* networking;
public:
	ExtMemberStateListener(IMatchmaking* m, IFriends* f, INetworking* n) {
		logger = new SWBFLogger();
		matchmaking = m;
		friends = f;
		networking = n;
	}
	void OnLobbyMemberStateChanged(const ISGalaxyId& lobbyID, const ISGalaxyId&  memberID, ILobbyMemberStateChange memberStateChange) {
		string msg1("OnLobbyMemberStateChanged called with id:");
		msg1.append(to_string(memberID.GetRealID()));


		logger->Write(msg1);

		if (memberStateChange == ILobbyMemberStateChange::LOBBY_MEMBER_STATE_CHANGED_ENTERED) {
			string msg;
			msg = msg.append("Member with ID <").append(to_string(memberID.GetRealID())).append("> joined.");
			logger->Write(msg); // this is the new logger i made
			const char* name = friends->GetFriendPersonaName(memberID);
			// IFriends here
			string namstr = string("Name of player:<").append(name).append(">");
			
			logger->Write(namstr);

			logger->Write("Lets find out some data...");
			 
			int c = matchmaking->GetLobbyMemberDataCount(lobbyID,memberID);
			logger->Write("Member Data Count:");
			logger->Write(to_string(c));

		 
		}
		
		if (memberStateChange == ILobbyMemberStateChange::LOBBY_MEMBER_STATE_CHANGED_LEFT) {
			string msg;
			msg = msg.append("Member with ID <").append(to_string(memberID.GetRealID())).append("> left.");
			logger->Write(msg); // this is the new logger i made 
		}

	}

};

