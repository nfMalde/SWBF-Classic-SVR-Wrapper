#pragma once
#include <cstdint>
#include "IGalaxyListener.h"
#include "IListenerType.h"
class INetworkingListener : public IGalaxyTypeAwareListener<IListenerType::NETWORKING>
{
public:
        
    virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) = 0;
};
