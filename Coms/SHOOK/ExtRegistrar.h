#pragma once 

#include "ExtRegistrar.h"
#include "IListenerRegistrar.h"
#include "IListenerType.h"
#include "IPCCommucator.h"; 
#include "../Lib/SWBFLogger/SWBFLogger.cpp"
class ExtRegistrar : public IListenerRegistrar {

private:
	IListenerRegistrar* original;
	SWBFLogger* ipc;

public:
	ExtRegistrar(IListenerRegistrar* o, SWBFLogger* _ipc) {
		original = o;
		ipc = _ipc;
	}

	void Register(IListenerType listenerType, void* listener) {
		 
		ipc->Write("Register called!!!");
		if (listenerType == IListenerType::LOBBY_CREATED) {
			ipc->Write("Lobby Created Listener is registered!");
		 }

		original->Register(listenerType, listener);
	}

	void Unregister(IListenerType listenerType, void* listener) {
		original->Unregister(listenerType, listener);
	}

};