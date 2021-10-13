#pragma once
#include "ILobbyCreatedListener.h"
#include "IGalaxyID.h"
#include "ILobbyCreatedListener.h"
#include "IListenerRegistrar.h"
#include "IListenerType.h"
#include <format>
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
#include "ExtMemberUpdateListener.h"
namespace {
	class ExtLobbyCreatedListener:public ILobbyCreatedListener
	{
	private:
		SWBFLogger* com;
		IListenerRegistrar* registerer;
	public:
		ExtLobbyCreatedListener(IListenerRegistrar* reg) {
			com = new SWBFLogger();
			registerer = reg;
		}

		void OnLobbyCreated(const ISGalaxyId& lobbyID, ILobbyCreateResult result) {
		 
		 


			com->Write("Lobby Created!");
			com->Write("Trying to save lobby ID");
			if (lobbyID != NULL) {
				 
				uint64_t rID =	lobbyID.GetRealID();

				if (rID > 0) {
					com->Write("Real ID found!");
				}

				com->Write("Now trying to ge the lobby id (UINT_64)...");

				uint64_t lID = lobbyID.ToUint64();

				if (lID > 0) {
					com->Write("Lobby ID is parsable and valid.");

					string msg = string("Lobby id=");
					msg.append(to_string(lID));
					msg.append("; Real ID=");
					msg.append(to_string(rID));

					com->Write(msg); 
				}
			}

			

		};
		 
	};
}
