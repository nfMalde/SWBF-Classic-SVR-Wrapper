#pragma once
#include "IGalaxyID.h"
enum class P2PSendType
{
    P2P_SEND_UNRELIABLE,
    P2P_SEND_RELIABLE,
    P2P_SEND_UNRELIABLE_IMMEDIATE,
    P2P_SEND_RELIABLE_IMMEDIATE
};

enum class ConnectionType
{
    CONNECTION_TYPE_NONE,
    CONNECTION_TYPE_DIRECT,
    CONNECTION_TYPE_PROXY
};
class INetworking
{
public:

    virtual ~INetworking()
    {
    }

    virtual bool SendP2PPacket(ISGalaxyId galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel = 0) = 0;

    virtual bool PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, ISGalaxyId& outGalaxyID, uint8_t channel = 0) = 0;

    virtual bool IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel = 0) = 0;

    virtual bool ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, ISGalaxyId& outGalaxyID, uint8_t channel = 0) = 0;

    virtual void PopP2PPacket(uint8_t channel = 0) = 0;

    virtual int GetPingWith(ISGalaxyId galaxyID) = 0;

    virtual void RequestNatTypeDetection() = 0;

    virtual void* GetNatType() = 0;

    virtual void* GetConnectionType(ISGalaxyId userID) = 0;

};