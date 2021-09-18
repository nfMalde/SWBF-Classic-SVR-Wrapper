#pragma once
#include "IListenerType.h"
class IGalaxyListener
{
public:
	virtual ~IGalaxyListener() {

	}

};

template<IListenerType type> class IGalaxyTypeAwareListener : public IGalaxyListener
{
public:
    virtual ~IGalaxyTypeAwareListener(){}

    static IListenerType GetListenerType()
    {
        return type;
    }
};