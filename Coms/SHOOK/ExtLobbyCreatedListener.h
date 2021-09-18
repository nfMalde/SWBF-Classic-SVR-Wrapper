#pragma once
#include "ILobbyCreatedListener.h"
#include "IGalaxyID.h"
#include "ILobbyCreatedListener.h"
#include "IPCCommucator.h" 
namespace {
	class ExtLobbyCreatedListener:public ILobbyCreatedListener
	{
	private:
		IPCCom* com;
	public:
		ExtLobbyCreatedListener() {
			com = new IPCCom();
		}

		void OnLobbyCreated(ISGalaxyId* lobbyID, ILobbyCreateResult result) {
		 
			 
			com->sendMessage("Lobby Created!");
			com->sendMessage("Trying to save lobby ID"); 
			if (lobbyID != NULL) {
				 
				uint64_t rID =	lobbyID->GetRealID();

				if (rID > 0) {
					com->sendMessage("Real ID found!");
				}

				com->sendMessage("Now trying to ge the lobby id (UINT_64)...");

				uint64_t lID = lobbyID->ToUint64();

				if (lID > 0) {
					com->sendMessage("Lobby ID is parsable and valid.");

					string msg = string("Lobby id=");
					msg.append(to_string(lID));
					msg.append("; Real ID=");
					msg.append(to_string(rID));

					com->sendMessage(msg);
				}
			}

			

		};
		 
	};
}
