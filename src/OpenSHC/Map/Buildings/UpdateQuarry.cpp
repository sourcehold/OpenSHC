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
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041D510
    void Buildings::UpdateQuarry()
    {
        int const variant = SEC_RNG::instance.currentNumber2 & 3;
        int const stockpileID
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].quarryStockpileID;
        int workerCount = 0;
        DAT_GameState::instance
            .playerDataArray[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
            .countStoneQuarries += 1;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter == 1
            && DAT_GameSynchronyState::instance.currentGameMode == 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0) {
            workerCount = 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[1] != 0) {
            workerCount += 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[2] != 0) {
            workerCount += 1;
        }

        // The puller (state, campgroundVclock), the ox (field117_0x11a, extraAnimationFrame1), the pryer
        // (killingPitField, extraAnimationFrame2) and the mason (field119_0x11e, extraAnimationFrame3) wait on each
        // other. The QuarryAnimationFrames* tables are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[1] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        } else if (workerCount < 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 1;
        } else {
            int done = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 1;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames1
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = f;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PULLER_LOWER);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 33;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames2
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                        = f + 1;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 3) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PULLER_STRAIN);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 56) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PULLER_IMPACT);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 18;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames3
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                        = f + 1;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PULLER_ROCK);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames4
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                        = f + 1;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PULLER_RETURN);
                }
            }
            if (done != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 7) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 2) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 9) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 3;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 4;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 4) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 5;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 5) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 6;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state == 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                }
            }
        }

        {
            int done = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 122;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames5[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = f + 61;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 85;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames6[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = f + 83;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 102;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.SomeAnimationNumbersUnk[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = f + 102;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames7[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame1];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                        = f + 108;
                }
            }
            if (done != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 7) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 2;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 2) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 9) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 3;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 4;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 4) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 5;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 5) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 6;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a
                    == 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
                }
            }
        }

        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        } else if (workerCount < 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 123;
        } else {
            int done = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames8[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 122;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames9[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 122;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames10[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 122;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames11[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 134;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames12[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 134;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    == 23) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 5) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames13[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 134;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    == 23) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    == 45) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames14[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 134;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    == 24) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    == 56) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PRYER_LEVER);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 7) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 141;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 8) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames15[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 141;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 9) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames16[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 165;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 10) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames17[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame2];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                        = f + 185;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 11) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2
                    >= 10) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    done = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 191;
            }
            if (done != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField <= 2) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                        = variant + 3;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 6) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 7;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 7) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 2) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 8;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 8) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 9;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 9) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 10;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 10) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 11;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField
                    <= 11) {
                    // Wait while the linked stockpile holds 47 stone or more
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(stockpileID,
                            DAT_BuildingsState::instance.buildings[stockpileID].uid, OpenSHC::Game::Resources::RT_STONE)
                        < 47) {
                        if (variant == 0) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
                        } else if (variant == 1) {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 2;
                        } else {
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 1;
                        }
                    }
                }
            }
        }

        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[2] == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        } else if (workerCount < 3) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 193;
        } else {
            int done = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 193;
                done = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames18[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame3];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                        = f + 193;
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 42) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 52) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 65) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 115) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 142) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CHIP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3
                    == 150) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_MASON_CRUMBLE);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames19[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame3];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                        = f + 193;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames20[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame3];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                        = f + 193;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                char const f
                    = (char)DAT_BuildingDefinedData::instance.QuarryAnimationFrames21[DAT_BuildingsState::instance
                            .buildings[DAT_CurrentBuildingID::instance]
                            .extraAnimationFrame3];
                if (f <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
                    done = 1;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                        = f + 193;
                }
            }
            if (done != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e == 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a == 6) {
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 1;
                    }
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e
                    <= 4) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field119_0x11e = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::addResourceToStockpile,
                        DAT_BuildingsState::ptr)(stockpileID, DAT_BuildingsState::instance.buildings[stockpileID].uid,
                        OpenSHC::Game::Resources::RT_STONE, 1, 48, 1);
                }
            }
        }

        // displayOwnerFlag was already set above, so the flag block does not set it again
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
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
