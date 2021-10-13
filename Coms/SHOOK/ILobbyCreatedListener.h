#pragma once
#include "IGalaxyListener.h"
#include "IListenerType.h"
#include "ILobbyCreateResult.h"
#include "IGalaxyID.h"
class ILobbyCreatedListener: public IGalaxyTypeAwareListener<IListenerType::LOBBY_CREATED>
{
public:
	virtual ~ILobbyCreatedListener() {}

	virtual void OnLobbyCreated(const ISGalaxyId& lobbyID, ILobbyCreateResult result) = 0;
};

