#pragma once
#include <cstdint>
#include "IIDType.h";
struct ISGalaxyId {
    

    uint64_t value;



    static const uint64_t UNASSIGNED_VALUE = 0;

    static ISGalaxyId FromRealID(IIDType type, uint64_t value)
    { 
        return ISGalaxyId(static_cast<uint64_t>(type) << 56 | value);
    }

    ISGalaxyId(void) : value(UNASSIGNED_VALUE)
    {
    }

    ISGalaxyId(uint64_t _value) : value(_value)
    {
    }

    ISGalaxyId(const ISGalaxyId& galaxyID) : value(galaxyID.value)
    {
    }

    ISGalaxyId& operator=(const ISGalaxyId& other)
    {
        value = other.value;
        return *this;
    }

    bool operator<(const ISGalaxyId& other) const
    {
         
        return value < other.value;
    }

    bool operator==(const ISGalaxyId& other) const
    {
        return value == other.value;
    }

    bool operator!=(const ISGalaxyId& other) const
    {
        return !(*this == other);
    }

    bool IsValid() const
    {
        return value != UNASSIGNED_VALUE;
    }

    uint64_t ToUint64() const
    {
        return value;
    }

    uint64_t GetRealID() const
    {
        return value & 0xffffffffffffff;
    }

    IIDType GetIDType() const
    {
        return static_cast<IIDType>(value >> 56);
    }

};