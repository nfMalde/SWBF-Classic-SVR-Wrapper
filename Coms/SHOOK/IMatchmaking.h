#pragma once
#include "ILobbyType.h"
#include <cstdint>
#include "ILobbyTopologyType.h"
#include "ILobbyCreatedListener.h"
#include "ILobbyComparisonType.h"
#include "IGalaxyID.h"
#include "ILobbyDataRetrieveListener.h"
#include "ILobbyMemberDataUpdateListener.h" 
/// <summary>
/// 
/// </summary>
///  
class IMatchmaking
{
public:
	/// <summary>
	/// Finalizes an instance of the <see cref="IMatchmaking"/> class.
	/// </summary>
	virtual ~IMatchmaking() {

	}

    virtual void CreateLobby(
        ILobbyType lobbyType,
        uint32_t maxMembers,
        bool joinable,
        ILobbyTopologyType lobbyTopologyType,
        ILobbyCreatedListener* const lobbyCreatedListener = NULL,
        void* const lobbyEnteredListener = NULL) = 0;

    virtual void RequestLobbyList(bool allowFullLobbies = false, void* const listener = NULL) = 0;

    virtual void AddRequestLobbyListResultCountFilter(uint32_t limit) = 0;

    virtual void AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, ILobbyComparisonType comparisonType) = 0;

    virtual void AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, ILobbyComparisonType comparisonType) = 0;

    virtual void AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) = 0;

    virtual ISGalaxyId GetLobbyByIndex(uint32_t index) = 0;

    virtual void JoinLobby(ISGalaxyId lobbyID, void* const listener = NULL) = 0;

    virtual void LeaveLobby(ISGalaxyId lobbyID, void* const listener = NULL) = 0;

    virtual void SetMaxNumLobbyMembers(ISGalaxyId lobbyID, uint32_t maxNumLobbyMembers, void* const listener = NULL) = 0;

    virtual uint32_t GetMaxNumLobbyMembers(ISGalaxyId lobbyID) = 0;

    virtual uint32_t GetNumLobbyMembers(ISGalaxyId lobbyID) = 0;

    virtual ISGalaxyId GetLobbyMemberByIndex(ISGalaxyId lobbyID, uint32_t index) = 0;

    virtual void SetLobbyType(ISGalaxyId lobbyID, ILobbyType lobbyType, void* const listener = NULL) = 0;

    virtual ILobbyType GetLobbyType(ISGalaxyId lobbyID) = 0;

    virtual void SetLobbyJoinable(ISGalaxyId lobbyID, bool joinable, void* const listener = NULL) = 0;

    virtual bool IsLobbyJoinable(ISGalaxyId lobbyID) = 0;

    virtual void RequestLobbyData(ISGalaxyId lobbyID, ILobbyDataRetrieveListener* const listener = NULL) = 0;

    virtual const char* GetLobbyData(ISGalaxyId lobbyID, const char* key) = 0;

    virtual void GetLobbyDataCopy(ISGalaxyId lobbyID, const char* key, char* buffer, uint32_t bufferLength) = 0;

    virtual void SetLobbyData(ISGalaxyId lobbyID, const char* key, const char* value, void* const listener = NULL) = 0;

    virtual uint32_t GetLobbyDataCount(ISGalaxyId lobbyID) = 0;

    virtual bool GetLobbyDataByIndex(ISGalaxyId lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) = 0;

    virtual void DeleteLobbyData(ISGalaxyId lobbyID, const char* key, void* const listener = NULL) = 0;

    virtual const char* GetLobbyMemberData(ISGalaxyId lobbyID, ISGalaxyId memberID, const char* key) = 0;

    virtual void GetLobbyMemberDataCopy(ISGalaxyId lobbyID, ISGalaxyId memberID, const char* key, char* buffer, uint32_t bufferLength) = 0;

    virtual void SetLobbyMemberData(ISGalaxyId lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener = NULL) = 0;

    virtual uint32_t GetLobbyMemberDataCount(ISGalaxyId lobbyID, ISGalaxyId memberID) = 0;

    virtual bool GetLobbyMemberDataByIndex(ISGalaxyId lobbyID, ISGalaxyId memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) = 0;

    virtual void DeleteLobbyMemberData(ISGalaxyId lobbyID, const char* key, ILobbyMemberDataUpdateListener* const listener = NULL) = 0;

    virtual ISGalaxyId GetLobbyOwner(ISGalaxyId lobbyID) = 0;

    virtual bool SendLobbyMessage(ISGalaxyId lobbyID, const void* data, uint32_t dataSize) = 0;

    virtual uint32_t GetLobbyMessage(ISGalaxyId lobbyID, uint32_t messageID, ISGalaxyId& senderID, char* msg, uint32_t msgLength) = 0;

};

