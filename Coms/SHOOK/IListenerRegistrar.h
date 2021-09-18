#pragma once
#include "IListenerType.h"

class IListenerRegistrar
{
public: 
	virtual ~IListenerRegistrar() {

	}

	virtual void Register(IListenerType listenerType, void* listener) = 0;
	virtual void Unregister(IListenerType listenerType, void* listener) = 0;
};

