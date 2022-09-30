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
		 
	};
};

