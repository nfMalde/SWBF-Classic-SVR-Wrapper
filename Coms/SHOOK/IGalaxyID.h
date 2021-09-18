#pragma once
#include <cstdint>
#include "IIDType.h";
class IGalaxyID
{
public:

    virtual ~IGalaxyID() 
    {
    } 
    virtual bool IsValid() = 0;
    virtual uint64_t ToUint64() = 0;
    virtual uint64_t GetRealID() = 0;
    virtual IIDType GetIDType()  = 0;
};
 

struct ISGalaxyId {
    uint64_t GetRealID() { return value & 0xffffffffffffff; };
    uint64_t ToUint64() { return value; };
    IIDType GetIDType() const
    {
        return static_cast<IIDType>(value >> 56);
    }

    uint64_t value;

};