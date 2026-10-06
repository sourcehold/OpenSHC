#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
            int _state = (short)this->units[unitIndex].state.generic;
            if (this->units[unitIndex].dying != 0) {
                /*
                  "Dying"
                 */

                return 0xc;
            }
            if (_state == 0x79 || MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(unitIndex) != FALSE) {
                /*
                  This is an optimized % 4, producing -3 to 3
                 */

                uint _rng_0x79 = (int)this->units[unitIndex].fixedRng % 4;
                /*
                  "Wandering around
                   Eating fire
                   (go to goodthing)
                   Having a rest
                   Enjoying a break
                   Taking some time off
                   Wandering randomly"
                 */

                return (int)(_rng_0x79 + 0x5f);
            }
            if (_state == 0x6a) {
                /*
                  "Fighting"
                 */

                return 0x73;
            }
            switch (this->units[unitIndex].unitType) {
            case OpenSHC::Map::Units::UT_PEASANT:
                if (_state == 5) {
                    /*
                      "Swearing loyalty"
                     */

                    return 0x26;
                }
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
                    case 0x6a:
                        return 0x1e;
                    case 0x6b:
                        return 0x1f;
                    case 0x6e:
                        return 0x20;
                    case 0x6f:
                        return 0x21;
                    case 0x72:
                        return 0x22;
                    case 0x73:
                        return 0x23;
                    case 0x74:
                        return 0x24;
                    case 0x75:
                        return 0x25;
                    }
                }
                /*
                  "Waiting for job"
                 */

                return 0x1d;
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
                case 0:
                    return 1;
                case 1:
                    /*
                      "Going to chop wood"
                     */

                    return 0x6b;
                case 2:
                    /*
                      "Felling a tree"
                     */

                    return 0x6c;
                case 3:
                    /*
                      "Chopping a tree"
                     */

                    return 0x6d;
                case 4:
                    /*
                      "Returning with log"
                     */

                    return 0x6e;
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_FLETCHER:
                *pResourceType = OpenSHC::Game::Resources::RT_WOOD;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_TUNNELER:
                switch (_state) {
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
                    return 0xb;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
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
                case 0:
                case 8:
                    return 1;
                case 1:
                case 0xb:
                    return 0x71;
                case 2:
                    return 0x72;
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
                        ? 0x70
                        : 0x73;
                case 10:
                    return (uint)(this->units[this->units[unitIndex].shootTargetedUnit].isStalked == 0) * 2 + 0x71;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_QUARRYMASON:
                switch (_state) {
                case 0:
                    return 1;
                default:
                    return 7;
                case 2:
                    return 5;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
                *pResourceType = OpenSHC::Game::Resources::RT_STONE;
                switch (_state) {
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
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_QUARRYOX:
                *pResourceType = OpenSHC::Game::Resources::RT_STONE;
                switch (_state) {
                case 1:
                    return 10;
                case 2:
                    return 1;
                case 3:
                    return 5;
                case 4:
                    return 0x28;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_PITCHMAN:
                *pResourceType = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_WHEAT;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_HOPSFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_HOPS;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_APPLE;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                *pResourceType = OpenSHC::Game::Resources::RT_CHEESE;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_MILLER:
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_BAKER:
                *pResourceType = OpenSHC::Game::Resources::RT_BREAD;
                switch (_state) {
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
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_BREWER:
                switch (_state) {
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
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_POLETURNER:
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_SMITH:
                switch (_state) {
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
                                         .buildings[this->units[unitIndex].workplaceBuildingID_1]
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_ARMORER:
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_TANNER:
                switch (_state) {
                case 0:
                case 1:
                    return 1;
                case 2:
                    return 0x68;
                case 3:
                    return 0x69;
                case 4:
                    return 5;
                default:
                    return 7;
                case 7:
                    return 2;
                case 8:
                    *pResourceType = OpenSHC::Game::Resources::RT_LEATHERARMOR;
                    return 10;
                case 0x6a:
                    return 8;
                }
            default:
                return 0;
            case OpenSHC::Map::Units::UT_MINER:
                if (_state == 1) {
                    return 7;
                }
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                switch (_state) {
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
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_PRIEST:
                switch (_state) {
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
                case 0xb:
                    return 7;
                case 3:
                    return 0x2b;
                case 5:
                    return 0x2a;
                case 9:
                    return this->units[unitIndex].substate + 0x18;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_HEALER:
                switch (_state) {
                case 0:
                    return 1;
                case 1:
                    return 5;
                default:
                    return 7;
                case 3:
                    return 0x2d;
                case 4:
                    return 0x2e;
                case 5:
                    return 0x2f;
                case 6:
                    return 0x30;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_DRUNK:
                return DAT_GameState::instance.mapAndTime.drunkenManStatus + 0x75;
            case OpenSHC::Map::Units::UT_INNKEEPER:
                *pResourceType = OpenSHC::Game::Resources::RT_ALE;
                switch (_state) {
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
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_TRADER:
                switch (_state) {
                case 0:
                    return 1;
                case 1:
                    return 0x37;
                case 2:
                    return 7;
                case 3:
                    return 0x38;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_TRADERHORSE:
                if (_state == 1) {
                    return 0x37;
                }
                if (_state != 3) {
                    if (_state == 0x6a) {
                        return 8;
                    }
                    return 1;
                }
                return 0x38;
            case OpenSHC::Map::Units::UT_COW:
                switch (_state) {
                case 0:
                    if (this->units[unitIndex].substate == 0x66 || this->units[unitIndex].substate == 0x67) {
                        return 0x3c;
                    }
                default:
                    return 0x3d;
                case 2:
                case 4:
                case 5:
                    return 0x3a;
                case 3:
                    return 0x3b;
                case 6:
                case 0x6e:
                    return 0xc;
                }
            case OpenSHC::Map::Units::UT_HUNTERDOG:
                switch (_state) {
                case 3:
                    return 0x3f;
                case 4:
                case 5:
                    return 0x40;
                case 7:
                case 8:
                    return 0x41;
                case 9:
                    return 0x42;
                case 0x78:
                    return 0x43;
                }
                return 1;
            case OpenSHC::Map::Units::UT_FIREFIGHTER:
                switch (_state) {
                case 0:
                case 2:
                    return 4;
                case 1:
                    return 0x97;
                case 3:
                    return 0x96;
                case 4:
                    return 0x98;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_GHOST:
                return (DAT_GameState::instance.mapAndTime.drunkenManStatus & 3U) + 0x99;
            case OpenSHC::Map::Units::UT_LADY:
                switch (_state) {
                case 1:
                case 9:
                    return 0x12;
                case 3:
                    return 0x13;
                case 4:
                case 8:
                    return 0x14;
                case 5:
                    return 0x15;
                case 6:
                    return this->units[unitIndex].substate + 0xe;
                case 7:
                    return 0x16;
                case ((UnitType)10):
                    return 0;
                case 0x6a:
                    return 8;
                }
                return 4;
            case OpenSHC::Map::Units::UT_JESTER:
                switch (_state) {
                case 1:
                    return 0x45;
                default:
                    return 0x49;
                case 3:
                case 4:
                    return 0x46;
                case 5:
                    return 0x47;
                case 7:
                case 8:
                    return 0x48;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_CHICKEN:
                if (_state == 2) {
                    return 0x4c;
                }
                return 0x4b;
            case OpenSHC::Map::Units::UT_MOTHER:
                switch (_state) {
                case 3:
                case 5:
                case 6:
                case 7:
                    return 0x4f;
                case 4:
                    return 0x50;
                default:
                    return 0x51;
                case 0x65:
                    if (DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CHAPEL
                        && DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CHURCH
                        && DAT_BuildingsState::instance.buildings[this->units[unitIndex].targetID_OR_targetBuildingID]
                                .buildingType
                            != OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                        return 0x4f;
                    }
                    return 0x4e;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_CHILD:
                switch (_state) {
                case 0:
                case 1:
                    return 1;
                default:
                    return 0x57;
                case 3:
                    return 0x53;
                case 4:
                case 5:
                    return 0x54;
                case 6:
                case 9:
                    return 0x55;
                case 10:
                case 0xb:
                case 0xc:
                case 0xd:
                    return 0x56;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_JUGGLER:
                switch (_state) {
                case 0:
                    return 1;
                case 1:
                    return 0x59;
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    return 0x5a;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            case OpenSHC::Map::Units::UT_FIREEATER:
                switch (_state) {
                case 0:
                    return 1;
                case 1:
                    return 0x5c;
                case 2:
                case 3:
                case 4:
                    return 0x5d;
                default:
                    return 0;
                case 0x6a:
                    return 8;
                }
            }
        }

    }
}
}
