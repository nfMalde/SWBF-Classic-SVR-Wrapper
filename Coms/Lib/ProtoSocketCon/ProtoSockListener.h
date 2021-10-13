#pragma once
#include <google/protobuf/message.h>
template<typename google::protobuf::Message* TMessage>
class ProtoSockListener
{
public:
	virtual ~ProtoSockListener() {

	}

	virtual void OnPackageReceived(google::protobuf::Message* message) = 0;
};

