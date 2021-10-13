#pragma once
#include "IGalaxyID.h"
#include "IGalaxyListener.h"
#include "IListenerType.h"
#include "IFailureReason.h"
class ILobbyMemberDataUpdateListener: public IGalaxyTypeAwareListener<IListenerType::LOBBY_MEMBER_DATA_UPDATE_LISTENER>
{
public:
	virtual ~ILobbyMemberDataUpdateListener() {

	}
    virtual void OnLobbyMemberDataUpdateSuccess(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID) = 0;
 

    virtual void OnLobbyMemberDataUpdateFailure(const ISGalaxyId& lobbyID, const ISGalaxyId& memberID, void* failureReason) = 0;
};

