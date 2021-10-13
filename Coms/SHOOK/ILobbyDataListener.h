#pragma once
#include "IGalaxyListener.h"
#include "IListenerType.h"
#include "IGalaxyID.h"
class ILobbyDataListener : public IGalaxyTypeAwareListener<IListenerType::LOBBY_DATA>
{
public:
	virtual ~ILobbyDataListener() {

	}

	virtual void OnLobbyDataUpdated(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID) = 0;
};

