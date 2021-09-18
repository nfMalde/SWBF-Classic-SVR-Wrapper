#pragma once 

#include "ExtRegistrar.h"
#include "IListenerRegistrar.h"
#include "IListenerType.h"
#include "IPCCommucator.h"; 
class ExtRegistrar : public IListenerRegistrar {

private:
	IListenerRegistrar* original;
	IPCCom* ipc;

public:
	ExtRegistrar(IListenerRegistrar* o, IPCCom* _ipc) {
		original = o;
		ipc = _ipc;
	}

	void Register(IListenerType listenerType, void* listener) {
		 
		ipc->sendMessage("Register called!!!");
		if (listenerType == IListenerType::LOBBY_CREATED) {
			ipc->sendMessage("Lobby Created Listener is registered!");
		 }

		original->Register(listenerType, listener);
	}

	void Unregister(IListenerType listenerType, void* listener) {
		original->Unregister(listenerType, listener);
	}

};