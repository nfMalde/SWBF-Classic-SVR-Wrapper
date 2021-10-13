#pragma once
#include "IGalaxyID.h"
enum class  AvatarType
{
    AVATAR_TYPE_NONE = 0x0000,
    AVATAR_TYPE_SMALL = 0x0001,
    AVATAR_TYPE_MEDIUM = 0x0002,
    AVATAR_TYPE_LARGE = 0x0004
};

enum PersonaState
{
    PERSONA_STATE_OFFLINE,
    PERSONA_STATE_ONLINE
};
typedef uint32_t AvatarCriteria;
class IFriends
{
public:

    virtual ~IFriends()
    {
    }

    virtual AvatarCriteria GetDefaultAvatarCriteria() = 0;

    virtual void SetDefaultAvatarCriteria(AvatarCriteria defaultAvatarCriteria) = 0;

    virtual void RequestUserInformation(
        ISGalaxyId userID,
        AvatarCriteria avatarCriteria = 0x0000,
        void* const listener = NULL) = 0;

    virtual bool IsUserInformationAvailable(ISGalaxyId userID) = 0;

    virtual const char* GetPersonaName() = 0;

    virtual void GetPersonaNameCopy(char* buffer, uint32_t bufferLength) = 0;

    virtual PersonaState GetPersonaState() = 0;

    virtual const char* GetFriendPersonaName(ISGalaxyId userID) = 0;

    virtual void GetFriendPersonaNameCopy(ISGalaxyId userID, char* buffer, uint32_t bufferLength) = 0;

    virtual PersonaState GetFriendPersonaState(ISGalaxyId userID) = 0;

    virtual const char* GetFriendAvatarUrl(ISGalaxyId userID, AvatarType avatarType) = 0;

    virtual void GetFriendAvatarUrlCopy(ISGalaxyId userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) = 0;

    virtual uint32_t GetFriendAvatarImageID(ISGalaxyId userID, AvatarType avatarType) = 0;

    virtual void GetFriendAvatarImageRGBA(ISGalaxyId userID, AvatarType avatarType, void* buffer, uint32_t bufferLength) = 0;

    virtual bool IsFriendAvatarImageRGBAAvailable(ISGalaxyId userID, AvatarType avatarType) = 0;

    virtual void RequestFriendList(void* const listener = NULL) = 0;

    virtual bool IsFriend(ISGalaxyId userID) = 0;

    virtual uint32_t GetFriendCount() = 0;

    virtual ISGalaxyId GetFriendByIndex(uint32_t index) = 0;

    virtual void SendFriendInvitation(ISGalaxyId userID, void* const listener = NULL) = 0;

    virtual void RequestFriendInvitationList(void* const listener = NULL) = 0;

    virtual void RequestSentFriendInvitationList(void* const listener = NULL) = 0;

    virtual uint32_t GetFriendInvitationCount() = 0;

    virtual void GetFriendInvitationByIndex(uint32_t index, ISGalaxyId& userID, uint32_t& sendTime) = 0;

    virtual void RespondToFriendInvitation(ISGalaxyId userID, bool accept, void* const listener = NULL) = 0;

    virtual void DeleteFriend(ISGalaxyId userID, void* const listener = NULL) = 0;

    virtual void SetRichPresence(const char* key, const char* value, void* const listener = NULL) = 0;

    virtual void DeleteRichPresence(const char* key, void* const listener = NULL) = 0;

    virtual void ClearRichPresence(void* const listener = NULL) = 0;

    virtual void RequestRichPresence(ISGalaxyId userID = ISGalaxyId(), void* const listener = NULL) = 0;

    virtual const char* GetRichPresence(const char* key, ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual void GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual uint32_t GetRichPresenceCount(ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual void GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual const char* GetRichPresenceKeyByIndex(uint32_t index, ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual void GetRichPresenceKeyByIndexCopy(uint32_t index, char* buffer, uint32_t bufferLength, ISGalaxyId userID = ISGalaxyId()) = 0;

    virtual void ShowOverlayInviteDialog(const char* connectionString) = 0;

    virtual void SendInvitation(ISGalaxyId userID, const char* connectionString, void* const listener = NULL) = 0;

    virtual void FindUser(const char* userSpecifier, void* const listener = NULL) = 0;

    virtual bool IsUserInTheSameGame(ISGalaxyId userID) const = 0;
};

