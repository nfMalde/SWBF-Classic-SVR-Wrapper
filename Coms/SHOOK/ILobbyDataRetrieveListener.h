#include "IListenerType.h"
#include "IGalaxyListener.h"
#include "IGalaxyID.h";
#include "IFailureReason.h"

#pragma once
class ILobbyDataRetrieveListener:public IGalaxyTypeAwareListener<IListenerType::LOBBY_DATA_RETRIEVE>
{
public:
	virtual ~ILobbyDataRetrieveListener() {}

	virtual void OnLobbyDataRetrieveSuccess(const ISGalaxyId& lobbyID) = 0;

	virtual void OnLobbyDataRetrieveFailure(const ISGalaxyId& lobbyID, IFailureReason failureReason) = 0;
};

