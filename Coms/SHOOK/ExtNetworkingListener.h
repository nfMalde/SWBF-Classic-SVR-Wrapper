#pragma once
#include "INetworkingListener.h"
#include "INetworking.h"
#include "../Lib/Workers/Workers.cpp"
#include "../Lib/Workers/WorkerThread.h"
#include "IGalaxyID.h" 
#include "../Lib/SWBFLogger/SWBFLogger.cpp"

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "RakNetStatistics.h"
#include "RakNetTypes.h"

class ExtNetworkingListener: public INetworkingListener
{
private:
	WORKERS::WorkerThread* workerThread;
	INetworking* network;

	// Copied from Multiplayer.cpp
	// If the first byte is ID_TIMESTAMP, then we want the 5th byte
	// Otherwise we want the 1st byte
	
public:

	ExtNetworkingListener(INetworking* net) {
		workerThread = CreateWorker();
		network = net;
	}

	// Geerbt über INetworkingListener
	void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) {
		SWBFLogger* logger = new SWBFLogger();
		logger->Write(std::string("OnP2PPacketAvailable").append(" with Message Size ").append(to_string(msgSize)));
   
		ISGalaxyId idBuff = ISGalaxyId();

		logger->Write(std::string("Peeking messsage"));
		char pack[1024];
 
		network->PeekP2PPacket(pack, sizeof(pack), &msgSize, idBuff, channel);
		logger->Write(std::string("MSG Peeked!"));

	};
};

