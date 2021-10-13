#pragma once
#include "IGalaxyID.h";
#include "IIDType.h"; 
namespace SWBFWrapper {
	class PlayerManager
	{
	private:
		
		
	public:
		PlayerManager() {

		}

		void AddPlayer(ISGalaxyId* playerId) {
			if (playerId->GetIDType() == IIDType::ID_TYPE_USER) {

			}
		}
	};
}


