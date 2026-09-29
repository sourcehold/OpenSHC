#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00531000
        BOOLEnum UnitsState::shouldUnitsEngageInMelee(int unitID_1, int unitID_2)
        {
            UnitTypeShort _type1 = this->units[unitID_1].unitType;
            if (_type1 == OpenSHC::Map::Units::UT_TRADER || _type1 == OpenSHC::Map::Units::UT_TRADERHORSE) {
                return TRUE;
            }
            UnitTypeShort _type2 = this->units[unitID_2].unitType;
            if (_type2 == OpenSHC::Map::Units::UT_TRADER || _type2 == OpenSHC::Map::Units::UT_TRADERHORSE
                || _type1 == OpenSHC::Map::Units::UT_GHOST || _type2 == OpenSHC::Map::Units::UT_GHOST) {
                return TRUE;
            }
            if (_type1 == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                if (_type2 == OpenSHC::Map::Units::UT_WOODCUTTER) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                return TRUE;
            }
            if (_type2 == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                if (_type1 == OpenSHC::Map::Units::UT_WOODCUTTER || _type1 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                return TRUE;
            }
            if (this->units[unitID_1].isStalked == 0) {
                if (this->units[unitID_2].isStalked != 0) {
                    if (_type2 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                        return FALSE;
                    }
                    if (_type2 == OpenSHC::Map::Units::UT_CAGEDOG) {
                        return (BOOLEnum)(DAT_GameState::instance.mapAndTime
                                              .playerTeams[this->units[unitID_2].displayColorPlayerID]
                            == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID_1].owner]);
                    }
                    if (_type2 == OpenSHC::Map::Units::UT_RABBIT || _type2 == OpenSHC::Map::Units::UT_QUARRYOX
                        || _type2 == OpenSHC::Map::Units::UT_COW) {
                        return FALSE;
                    }
                    return (BOOLEnum)(_type2 != OpenSHC::Map::Units::UT_HUNTERDOG);
                }
                if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0
                    || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                    || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    return FALSE;
                }
                return TRUE;
            }
            if (_type1 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                if (_type2 == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_COW) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_RABBIT) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_HUNTERDOG) {
                    return FALSE;
                }
            } else if (_type1 == OpenSHC::Map::Units::UT_CAGEDOG) {
                if (_type2 == OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_COW) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_RABBIT) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_HUNTERDOG) {
                    return FALSE;
                }
                if (this->units[unitID_2].isStalked != 0) {
                    return TRUE;
                }
                return (
                    BOOLEnum)(DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID_1].displayColorPlayerID]
                    == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID_2].owner]);
            } else if (_type1 != OpenSHC::Map::Units::UT_HUNTERDOG) {
                return TRUE;
            } else {
                if (_type2 == OpenSHC::Map::Units::UT_RABBIT) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_LIONSHWOLF) {
                    return FALSE;
                }
                if (_type2 == OpenSHC::Map::Units::UT_CAGEDOG) {
                    return FALSE;
                }
            }
            if (this->units[unitID_2].isStalked == 0) {
                return FALSE;
            }
            return TRUE;
        }

    }
}
}
