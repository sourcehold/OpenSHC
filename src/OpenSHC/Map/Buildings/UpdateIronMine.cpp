#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041CC70
    void Buildings::UpdateIronMine()
    {
        DAT_GameState::instance
            .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .countIronMines += 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter <= 1) {
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;

        // The miners: state cycles 0-6 over campgroundVclock. The IronMineAnimationFrames* tables are declared byte,
        // but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        } else {
            int wrapped = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames1
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames3
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames2
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 0
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 24
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 48
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 72) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_PULL);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames4
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                wrapped = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames5
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames6
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    <= 0) {
                    wrapped = 1;
                }
            }
            if (wrapped != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state
                        = MACRO_CALL_MEMBER(
                              OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                              DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance,
                              DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid,
                              OpenSHC::Game::Resources::RT_IRON)
                            < 7
                        ? 0
                        : 6;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state
                        = MACRO_CALL_MEMBER(
                              OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                              DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance,
                              DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid,
                              OpenSHC::Game::Resources::RT_IRON)
                            < 7
                        ? 0
                        : 6;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    + 118;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames4
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    + 38;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 59;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames5
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    + 58;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames6
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                    + 78;
            }
        }

        // The ore cart, in killingPitField and extraAnimationFrame2
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        } else {
            int wrapped = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                wrapped = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames7
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 2) {
                wrapped = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames8
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    <= 0) {
                    wrapped = 1;
                }
            }
            if (wrapped != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3
                        && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock
                            == 80) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    == 2) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 3;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames7
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    + 50;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames8
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    + 50;
            }
        }

        // The smelter, in field117_0x11a and extraAnimationFrame1, with its glow in field168_0x292
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        } else {
            int wrapped = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames9
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                    == 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_STRAIN);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                    == 55) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_DUMP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                    == 65) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_LDUMP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 == 100
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                        == 190
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                        == 280
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1
                        == 370) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_BOIL);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames10
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    <= 0) {
                    wrapped = 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames11
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    <= 0) {
                    wrapped = 1;
                }
            }
            if (wrapped != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 2) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames9
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    + 126;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames10
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    + 134;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames11
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                    + 134;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
                char const heat
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames10[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (heat < 4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 24;
                } else if (heat < 8) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 20;
                } else if (heat < 12) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 16;
                } else if (heat < 16) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 12;
                } else if (heat < 20) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 16;
                } else if (heat < 24) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 20;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 24;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                char const heat
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames11[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (heat < 4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 24;
                } else if (heat < 8) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 20;
                } else if (heat < 12) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 16;
                } else if (heat < 16) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 12;
                } else if (heat < 20) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 16;
                } else if (heat < 24) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 20;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field168_0x292 = 24;
                }
            }
        }

        // The pour, in field119_0x11e and extraAnimationFrame3; finishing it deposits the iron
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        } else {
            int wrapped = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                wrapped = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 1) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_IRON_POUR);
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                if ((char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames12
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                    <= 0) {
                    wrapped = 1;
                }
            }
            if (wrapped != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e
                    == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].uid,
                        OpenSHC::Game::Resources::RT_IRON, 1, 8, 1);
                }
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                    = (char)DAT_BuildingDefinedData::instance.IronMineAnimationFrames12
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                    + 94;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                .resources[OpenSHC::Game::Resources::RT_IRON]
            <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                       .resources[OpenSHC::Game::Resources::RT_IRON]
            >= 8) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 170;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                      .resources[OpenSHC::Game::Resources::RT_IRON]
                + 162;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
    }

}
}
