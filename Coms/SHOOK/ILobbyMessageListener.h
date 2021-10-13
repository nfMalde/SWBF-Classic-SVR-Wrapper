#pragma once
#include "IGalaxyID.h"
#include "IGalaxyListener.h"
#include "IListenerType.h"
class ILobbyMessageListener: public IGalaxyTypeAwareListener<IListenerType::LOBBY_MESSAGE>
{public:
	virtual ~ILobbyMessageListener() {}
	virtual void OnLobbyMessageReceived(const ISGalaxyId& lobbyID, const ISGalaxyId& senderID, uint32_t messageID, uint32_t messageLength) = 0;
};

