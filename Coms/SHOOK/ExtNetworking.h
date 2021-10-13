#pragma once
#include "INetworking.h"
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
class ExtNetworking:public INetworking 
{
private:
    INetworking* orig;
    SWBFLogger* logger;
public:
	ExtNetworking(INetworking* o) {
        orig = o;
        logger = new SWBFLogger();
	}

    bool SendP2PPacket(ISGalaxyId galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel = 0) {
        
        return orig->SendP2PPacket(galaxyID, data, dataSize, sendType, channel);
    };

    bool PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, ISGalaxyId& outGalaxyID, uint8_t channel = 0) {
    
        return orig->PeekP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);
    };

    bool IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel = 0) {
        return orig->IsP2PPacketAvailable(outMsgSize, channel);
    };

    bool ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, ISGalaxyId& outGalaxyID, uint8_t channel = 0) {
        return orig->ReadP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);
    };

    void PopP2PPacket(uint8_t channel = 0) {
        return orig->PopP2PPacket(channel);
    };

    int GetPingWith(ISGalaxyId galaxyID) {
        return orig->GetPingWith(galaxyID);
    };

    void RequestNatTypeDetection() {
        return orig->RequestNatTypeDetection();
    };

    void* GetNatType() {
        return orig->GetNatType();
    };

    void* GetConnectionType(ISGalaxyId userID) {
        return orig->GetConnectionType(userID);
    };
};

