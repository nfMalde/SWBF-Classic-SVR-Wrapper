#pragma once
#include <cstdint>
class IGalaxyInitOptions
{
public:
	virtual ~IGalaxyInitOptions() {}

    const char* clientID;
    const char* clientSecret;
    const char* configFilePath;
    const char* storagePath; 
    const char* host;
    uint16_t port;
};

