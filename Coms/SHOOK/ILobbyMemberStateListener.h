#pragma once
#include"IListenerType.h"
#include "IGalaxyListener.h"
#include "IGalaxyID.h"
#include "ILobbyMemberStateChange.h"
class ILobbyMemberStateListener: public IGalaxyTypeAwareListener<IListenerType::LOBBY_MEMBER_STATE>
{
public:
	virtual ~ILobbyMemberStateListener() {

	}

	virtual void OnLobbyMemberStateChanged( const ISGalaxyId& lobbyID, const ISGalaxyId& memberID, ILobbyMemberStateChange memberStateChange) = 0;
};

