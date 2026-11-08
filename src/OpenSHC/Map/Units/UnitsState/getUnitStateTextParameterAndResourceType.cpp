#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537F60
        int UnitsState::getUnitStateTextParameterAndResourceType(int unitIndex, ResourceType* pResourceType)

        {
            *pResourceType = (ResourceType)0;
            int _state = this->units[unitIndex].state.generic;
            if (this->units[unitIndex].dying != 0) {
                /*
                  "Dying"
                 */

                return 12;
            }
            if (_state == 121 || MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(unitIndex) != FALSE) {
                /*
                  This is an optimized % 4, producing -3 to 3
                 */

                int const _breakTextVariant = this->units[unitIndex].fixedRng % 4;
                /*
                  "Wandering around
                   Eating fire
                   (go to goodthing)
                   Having a rest
                   Enjoying a break
                   Taking some time off
                   Wandering randomly"
                 */

                return _breakTextVariant + 95;
            }
            if (_state == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                /*
                  "Fighting"
                 */

                return 115;
            }
            switch (this->units[unitIndex].unitType) {
            case OpenSHC::Map::Units::UT_PEASANT:
                if (_state != 5) {
                    if (_state == 8) {
                        /*
                          "Listening
                           Waiting for job
                           Hanging around
                           Waiting
                           Talking
                           Making a speech
                           Telling a joke
                           Recounting a story"
                         */

                        /*
                          Waiting at campfire
                         */

                        switch (this->units[unitIndex].substate) {
                        case 106:
                            return 30;
                        case 107:
                            return 31;
                        case 110:
                            return 32;
                        case 111:
                            return 33;
                        case 114:
                            return 34;
                        case 115:
                            return 35;
                        case 116:
                            return 36;
                        case 117:
                            return 37;
                        }
                    }
                    /*
                      "Waiting for job"
                     */

                    return 29;
                }
                /*
                  "Swearing loyalty"
                 */

                return 38;
            case OpenSHC::Map::Units::UT_BURNINGMAN:
                /*
                  "Burning"
                 */

                return 3;
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                *pResourceType = OpenSHC::Game::Resources::RT_WOOD;
                /*
                  0x1: Waiting
                   0x6b: Going to chop wood
                   0x6c: Felling a tree
                   0x6d: Chopping a tree
                   0x6e: Returning with log
                   0x7: Working
                   0x7: Working
                   0x2: Awaiting store space
                   0xa: Taking goods to store
                   0x5: Going to workplace
                   0x4: Resting
                   0x0: (Unit actions) -
                   0x8: Attacking
                 */

                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    /*
                      "Going to chop wood"
                     */

                    return 107;
                case 2:
                    /*
                      "Felling a tree"
                     */

                    return 108;
                case 3:
                    /*
                      "Chopping a tree"
                     */

                    return 109;
                case 4:
                    /*
                      "Returning with log"
                     */

                    return 110;
                case 5:
                case 6:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    return 10;
                case 9:
                    return 5;
                case 10:
                    return 4;
                }
                break;
            case OpenSHC::Map::Units::UT_FLETCHER:
                *pResourceType = OpenSHC::Game::Resources::RT_WOOD;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 9;
                case 2:
                    return 6;
                case 3:
                    return 5;
                case 4:
                case 5:
                    return 7;
                case 6:
                    return 2;
                case 7:
                    *pResourceType = OpenSHC::Game::Resources::RT_BOW;
                    return 10;
                case 8:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitIndex].owner)
                        != 0) {
                        return 4;
                    }
                    return 1;
                }
                break;
            case OpenSHC::Map::Units::UT_TUNNELER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                case 4:
                case 5:
                case 6:
                    return 1;
                case 2:
                case 3:
                case 8:
                case 9:
                    return 7;
                case 7:
                    return 11;
                }
                break;
            case OpenSHC::Map::Units::UT_HUNTER:
                *pResourceType = OpenSHC::Game::Resources::RT_MEAT;
                /*
                  0x1: Waiting
                   0x71: Hunting
                   0x72: Returning with kill
                   0x7: Working
                   0x2: Awaiting store space
                   0xa: Taking goods to store
                   0x5: Going to workplace
                   0x4: Resting
                   0x70: Stalking prey
                   0x73: Fighting
                   0x71: Hunting
                   0x73: Fighting
                   0x0: (Unit actions) -
                   0x8: Attacking
                 */

                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 8:
                    return 1;
                case 2:
                    return 114;
                case 3:
                    return 7;
                case 4:
                    return 2;
                case 5:
                    return 10;
                case 6:
                    return 5;
                case 7:
                    return 4;
                case 9:
                    /*
                      115 or 112
                     */

                    return this->units[DAT_UnitsState::instance.units[unitIndex].shootTargetedUnit].isStalked != 0
                        ? 112
                        : 115;
                case 10:
                    return (this->units[this->units[unitIndex].shootTargetedUnit].isStalked == 0) * 2 + 113;
                case 1:
                case 11:
                    return 113;
                }
                break;
            case OpenSHC::Map::Units::UT_FIREFIGHTER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 2:
                    return 4;
                case 1:
                    return 151;
                case 3:
                    return 150;
                case 4:
                    return 152;
                }
                break;
            case OpenSHC::Map::Units::UT_GHOST:
                return (DAT_GameState::instance.mapAndTime.drunkenManStatus & 3U) + 153;
            case OpenSHC::Map::Units::UT_QUARRYMASON:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                default:
                    return 7;
                case 2:
                    return 5;
                }
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
                *pResourceType = OpenSHC::Game::Resources::RT_STONE;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                default:
                    return 7;
                case 1:
                case 6:
                    return 1;
                case 2:
                    return 2;
                case 3:
                    return 10;
                case 4:
                    return 5;
                case 5:
                    return 4;
                }
            case OpenSHC::Map::Units::UT_QUARRYOX:
                *pResourceType = OpenSHC::Game::Resources::RT_STONE;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 1:
                    return 10;
                case 2:
                    return 1;
                case 3:
                    return 5;
                case 4:
                    return 40;
                }
                break;
            case OpenSHC::Map::Units::UT_PITCHMAN:
                *pResourceType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 7;
                case 2:
                    return 2;
                case 3:
                    return 10;
                case 4:
                    return 5;
                }
                break;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_WHEAT;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 5;
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    return 7;
                case 9:
                    return 2;
                case 10:
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_HOPSFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_HOPS;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 5;
                case 3:
                case 4:
                case 5:
                case 6:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_APPLE;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                case 3:
                case 4:
                case 8:
                    return 7;
                case 5:
                    return 5;
                case 6:
                    return 2;
                case 7:
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_CHEESE;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 5;
                case 3:
                    return 7;
                case 4:
                    return 2;
                case 5:
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_MILLER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                case 6:
                    return 1;
                case 2:
                    return 5;
                case 3:
                    return 9;
                case 4:
                    *pResourceType = OpenSHC::Game::Resources::RT_WHEAT;
                    return 6;
                case 5:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_FLOUR;
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_BAKER:
                *pResourceType = OpenSHC::Game::Resources::RT_BREAD;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 5;
                default:
                    return 7;
                case 5:
                    return 2;
                case 6:
                    return 10;
                case 7:
                    *pResourceType = OpenSHC::Game::Resources::RT_FLOUR;
                    return 9;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_FLOUR;
                    return 6;
                }
            case OpenSHC::Map::Units::UT_BREWER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    *pResourceType = OpenSHC::Game::Resources::RT_HOPS;
                    return 9;
                case 3:
                    *pResourceType = OpenSHC::Game::Resources::RT_HOPS;
                    return 6;
                case 4:
                    return 5;
                default:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_ALE;
                    return 10;
                case 9:
                    return 4;
                }
            case OpenSHC::Map::Units::UT_POLETURNER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    *pResourceType = OpenSHC::Game::Resources::RT_WOOD;
                    return 9;
                case 3:
                    *pResourceType = OpenSHC::Game::Resources::RT_WOOD;
                    return 6;
                case 4:
                    return 5;
                case 5:
                case 6:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = (ResourceType)(short)DAT_BuildingsState::instance
                                         .buildings[DAT_UnitsState::instance.units[unitIndex].workplaceBuildingID_1]
                                         .producedItemTypeNext;
                    return 10;
                }
                break;
            case OpenSHC::Map::Units::UT_SMITH:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    *pResourceType = OpenSHC::Game::Resources::RT_IRON;
                    return 9;
                case 3:
                    *pResourceType = OpenSHC::Game::Resources::RT_IRON;
                    return 6;
                case 4:
                    return 5;
                case 5:
                case 6:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = (ResourceType)(short)DAT_BuildingsState::instance
                                         .buildings[DAT_UnitsState::instance.units[unitIndex].workplaceBuildingID_1]
                                         .producedItemTypeNext;
                    return 10;
                case 9:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_IRON, 1, this->units[unitIndex].owner)
                        != 0) {
                        return 4;
                    }
                    return 1;
                }
                break;
            case OpenSHC::Map::Units::UT_ARMORER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    *pResourceType = OpenSHC::Game::Resources::RT_IRON;
                    return 9;
                case 3:
                    *pResourceType = OpenSHC::Game::Resources::RT_IRON;
                    return 6;
                case 4:
                    return 5;
                case 5:
                case 6:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_IRONARMOR;
                    return 10;
                case 9:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_IRON, 1, this->units[unitIndex].owner)
                        != 0) {
                        return 4;
                    }
                    return 1;
                }
                break;
            case OpenSHC::Map::Units::UT_TANNER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 104;
                case 3:
                    return 105;
                case 4:
                    return 5;
                default:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_LEATHERARMOR;
                    return 10;
                }
            case OpenSHC::Map::Units::UT_MINER:
                if (_state == 1) {
                    return 7;
                }
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                case 5:
                    return 1;
                case 2:
                    return 5;
                case 3:
                    return 2;
                case 4:
                    return 10;
                default:
                    return 7;
                }
            case OpenSHC::Map::Units::UT_PRIEST:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 5;
                case 2:
                case 4:
                case 6:
                case 7:
                case 8:
                case 10:
                case 11:
                    return 7;
                case 3:
                    return 43;
                case 5:
                    return 42;
                case 9:
                    return this->units[unitIndex].substate + 24;
                }
                break;
            case OpenSHC::Map::Units::UT_HEALER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 5;
                default:
                    return 7;
                case 3:
                    return 45;
                case 4:
                    return 46;
                case 5:
                    return 47;
                case 6:
                    return 48;
                }
            case OpenSHC::Map::Units::UT_DRUNK:
                return DAT_GameState::instance.mapAndTime.drunkenManStatus + 117;
            case OpenSHC::Map::Units::UT_INNKEEPER:
                *pResourceType = OpenSHC::Game::Resources::RT_ALE;
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 9;
                case 3:
                    return 6;
                case 4:
                    return 5;
                case 5:
                    return 7;
                }
                break;
            case OpenSHC::Map::Units::UT_TRADER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 55;
                case 2:
                    return 7;
                case 3:
                    return 56;
                }
                break;
            case OpenSHC::Map::Units::UT_TRADERHORSE:
                switch (_state) {
                case 1:
                    return 55;
                case 3:
                    return 56;
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                }
                return 1;
            case OpenSHC::Map::Units::UT_COW:
                switch (_state) {
                case 2:
                case 4:
                case 5:
                    return 58;
                case 3:
                    return 59;
                case 0:
                    if (this->units[unitIndex].substate != 102 && this->units[unitIndex].substate != 103) {
                        return 61;
                    }
                    return 60;
                default:
                    return 61;
                case 6:
                case 110:
                    return 12;
                }
            case OpenSHC::Map::Units::UT_HUNTERDOG:
                switch (_state) {
                case 120:
                    return 67;
                case 3:
                    return 63;
                case 4:
                case 5:
                    return 64;
                case 7:
                case 8:
                    return 65;
                case 9:
                    return 66;
                }
                return 1;
            case OpenSHC::Map::Units::UT_LADY:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 6:
                    return this->units[unitIndex].substate + 14;
                case 1:
                case 9:
                    return 18;
                case 3:
                    return 19;
                case 4:
                case 8:
                    return 20;
                case 5:
                    return 21;
                case 7:
                    return 22;
                case 10:
                    return 0;
                }
                return 4;
            case OpenSHC::Map::Units::UT_JESTER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 1:
                    return 69;
                default:
                    return 73;
                case 3:
                case 4:
                    return 70;
                case 5:
                    return 71;
                case 7:
                case 8:
                    return 72;
                }
            case OpenSHC::Map::Units::UT_CHICKEN:
                switch (_state) {
                case 2:
                    return 76;
                }
                return 75;
            case OpenSHC::Map::Units::UT_MOTHER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 101:
                    if (DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CHAPEL
                        && DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CHURCH
                        && DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                        return 79;
                    }
                    return 78;
                case 3:
                case 5:
                case 6:
                case 7:
                    return 79;
                case 4:
                    return 80;
                default:
                    return 81;
                }
            case OpenSHC::Map::Units::UT_CHILD:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                case 1:
                    return 1;
                default:
                    return 87;
                case 3:
                    return 83;
                case 4:
                case 5:
                    return 84;
                case 6:
                case 9:
                    return 85;
                case 10:
                case 11:
                case 12:
                case 13:
                    return 86;
                }
            case OpenSHC::Map::Units::UT_JUGGLER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 89;
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    return 90;
                }
                break;
            case OpenSHC::Map::Units::UT_FIREEATER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_MELEE_ATTACK:
                    return 8;
                case 0:
                    return 1;
                case 1:
                    return 92;
                case 2:
                case 3:
                case 4:
                    return 93;
                }
                break;
            }
            return 0;
        }

    }
}
}
