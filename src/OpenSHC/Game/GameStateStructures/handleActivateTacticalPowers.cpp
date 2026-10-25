#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using Audio::SFX::SoundEffectID;
    using Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00459E40
    void GameStateStructures::handleActivateTacticalPowers(int playerID, int powerType, int tile)
    {
        int const powerCost = (powerType + 1) * 0x27c;
        if (DAT_GameState::instance.playerDataArray[playerID].tacticalPowersBarLevel < powerCost) {
            return;
        }
        switch (powerType) {
        case 2:
        case 3:
        case 4:
        case 6:
        case 0xd:
        case 0x10: {
            UnitType unitType = ((UnitType)0);
            int unitCount = 0x14;
            switch (powerType) {
            case 2:
                unitType = Map::Units::UT_E_SPEAR;
                break;
            case 0xd:
                unitType = Map::Units::UT_E_ARCHER;
                unitCount = 0xf;
                break;
            case 4:
                unitType = Map::Units::UT_E_MACE;
                break;
            case 0x10:
                unitType = Map::Units::UT_A_FIRETHROWER;
                unitCount = 0xc;
                break;
            case 3:
                unitType = Map::Units::UT_E_ENGINEER;
                unitCount = 0xe;
                break;
            case 6:
                unitType = Map::Units::UT_E_KNIGHT;
                unitCount = 10;
            }
            int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int const x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            dword const tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnUnitsAroundLocation,
                DAT_TribesState::ptr)(1, x, y, playerID, unitType, unitCount);
            if ((int)tribeID > 0) {
                DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            }
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    ((SoundEffectID)0x104));
            }
            break;
        }
        case 1:
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::healUnitsOfPlayerWithinRadius,
                DAT_PathFindingState::ptr)(tile, 6, playerID, 8000);
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    Audio::SFX::SEID_CHAPEL_BELL);
            }
            break;
        case 5:
            DAT_GameState::instance.playerDataArray[playerID].goldDonation
                += SEC_RNG::instance.currentNumber2 % 0x5dc + 1000;
            MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            break;
        case 0:
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::certainDamageToUnitsUnk,
                DAT_PathFindingState::ptr)(tile, 6, playerID, 6000, 1);
            break;
        case 7:
            MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::certainDamageToUnitsUnk,
                DAT_PathFindingState::ptr)(tile, 9, playerID, 18000, 0);
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    ((SoundEffectID)0x105));
            }
            break;
        default:
            return;
        }
        DAT_GameState::instance.playerDataArray[playerID].tacticalPowersBarLevel -= powerCost;
    }

}
}
