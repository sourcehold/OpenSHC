#include "../CrusadeMap.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DWORD_00ed27a8.hpp"
#include "OpenSHC/Globals/DWORD_00ed311c.hpp"
#include "OpenSHC/Globals/INT_00eb9b48.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Game::TrailType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8EC0
        void CrusadeMap::MenuItemActionHandler_CrusadeMap_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            dword dVar3;
            dword dVar4;
            int _clickX;
            int _clickY;
            int iVar5;
            if (param_1 == 1000) {
                if (0 < DAT_SkirmishTrailRelated1::instance) {
                    if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                        if (((DAT_GameCore::instance.furthestSkirmishTrailMission < 0x31)
                                && (DAT_GameCore::instance.skirmishTrailProgress
                                    = DAT_GameCore::instance.furthestSkirmishTrailMission,
                                    DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                            .furthestSkirmishTrailMission]
                                        == -1))
                            && (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                        .furthestSkirmishTrailMission] = -0x4b0,
                                DAT_GameCore::instance.skirmishTrailProgress != 0x31)) {
                            DAT_GameCore::instance.skirmishTrailProgress
                                = DAT_GameCore::instance.skirmishTrailProgress + 1;
                            DAT_GameCore::instance.furthestSkirmishTrailMission
                                = DAT_GameCore::instance.furthestSkirmishTrailMission + 1;
                            iVar5 = 1;
                            goto LAB_004d8f31;
                        }
                    } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                        if (((DAT_GameCore::instance.furthestWarchestTrailMission < 0x1d)
                                && (DAT_GameCore::instance.warchestTrailProgress
                                    = DAT_GameCore::instance.furthestWarchestTrailMission,
                                    DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                            .furthestWarchestTrailMission]
                                        == -1))
                            && (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                        .furthestWarchestTrailMission] = -0x4b0,
                                DAT_GameCore::instance.warchestTrailProgress != 0x1d)) {
                            DAT_GameCore::instance.warchestTrailProgress
                                = DAT_GameCore::instance.warchestTrailProgress + 1;
                            DAT_GameCore::instance.furthestWarchestTrailMission
                                = DAT_GameCore::instance.furthestWarchestTrailMission + 1;
                            iVar5 = 2;
                        LAB_004d8f31:
                            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::setStartDateUnk, DAT_GameCore::ptr)(iVar5);
                            DAT_SkirmishTrailRelated1::instance = DAT_SkirmishTrailRelated1::instance + -1;
                            DWORD_00ed311c::instance = timeGetTime();
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::setSoundWithVariation, DAT_SFXState::ptr)(258, 100);
                        }
                    } else if ((((DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)
                                    && (DAT_GameCore::instance.furthestExtremeTrailMission < 0x13))
                                   && (DAT_GameCore::instance.extremeTrailProgress
                                       = DAT_GameCore::instance.furthestExtremeTrailMission,
                                       DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance
                                               .furthestExtremeTrailMission]
                                           == -1))
                        && (DAT_GameCore::instance
                                .extremeTrailMonthsTakenOrChicken[DAT_GameCore::instance.furthestExtremeTrailMission]
                            = -0x4b0,
                            DAT_GameCore::instance.extremeTrailProgress != 0x13)) {
                        DAT_GameCore::instance.extremeTrailProgress = DAT_GameCore::instance.extremeTrailProgress + 1;
                        DAT_GameCore::instance.furthestExtremeTrailMission
                            = DAT_GameCore::instance.furthestExtremeTrailMission + 1;
                        iVar5 = 3;
                        goto LAB_004d8f31;
                    }
                }
            } else {
                if (param_1 == 10) {
                    /*
                      copy bitmap of icon
                     */
                    MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                        (void*)((DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13) * 0x2100
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        (void*)((DAT_GameCore::instance.lordIconUnk + -2) * 0x2100
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        0x2100);
                    DAT_TextureRenderCoreObject::instance
                        .field69_0x98[DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13] = 0x2100;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO, 0);
                }
                if (param_1 == 0xb) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_SELECT_CRUSADE, 0);
                }
                if (param_1 == 1) {
                    _clickX = DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance;
                    _clickY = DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance;
                    dVar4 = DAT_GameCore::instance.warchestTrailProgress;
                    iVar5 = DAT_GameCore::instance.extremeTrailProgress;
                    if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                        dVar3 = 0;
                        do {
                            if (DAT_GameCore::instance.furthestSkirmishTrailMission < (int)dVar3) {}
                            iVar1 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar3][0];
                            iVar2 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar3][1];
                            if (((iVar1 + -10 <= _clickX) && (_clickX <= iVar1 + 10))
                                && ((iVar2 + -10 <= _clickY && (_clickY <= iVar2 + 10)))) {
                            LAB_004d9190:
                                DAT_GameCore::instance.extremeTrailProgress = iVar5;
                                DAT_GameCore::instance.warchestTrailProgress = dVar4;
                                DAT_GameCore::instance.skirmishTrailProgress = dVar3;
                                INT_00eb9b48::instance = 1;
                                DWORD_00ed27a8::instance = timeGetTime();
                            }
                            dVar3 = dVar3 + 1;
                        } while ((int)dVar3 < 50);
                    } else {
                        dVar3 = DAT_GameCore::instance.skirmishTrailProgress;
                        if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                            dVar4 = 0;
                            while ((int)dVar4 <= DAT_GameCore::instance.furthestWarchestTrailMission) {
                                iVar1 = DAT_MissionDefinedData::instance.field33_0xd4c[dVar4][0];
                                iVar2 = DAT_MissionDefinedData::instance.field33_0xd4c[dVar4][1];
                                if (((iVar1 + -10 <= _clickX) && (_clickX <= iVar1 + 10))
                                    && ((iVar2 + -10 <= _clickY && (_clickY <= iVar2 + 10))))
                                    goto LAB_004d9190;
                                dVar4 = dVar4 + 1;
                                if (30 < (int)dVar4) {}
                            }
                        } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                            iVar5 = 0;
                            while (iVar5 <= DAT_GameCore::instance.furthestExtremeTrailMission) {
                                iVar1 = DAT_MissionDefinedData::instance.field34_0xe3c[iVar5][0];
                                iVar2 = DAT_MissionDefinedData::instance.field34_0xe3c[iVar5][1];
                                if ((((iVar1 + -10 <= _clickX) && (_clickX <= iVar1 + 10)) && (iVar2 + -10 <= _clickY))
                                    && (_clickY <= iVar2 + 10))
                                    goto LAB_004d9190;
                                iVar5 = iVar5 + 1;
                                if (20 < iVar5) {}
                            }
                        }
                    }
                } else if (param_1 == 99) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_RANKING_GAMES, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                        (OpenSHC::Audio::SFX::SoundEffectID)(OpenSHC::Audio::SFX::SEID_UNIT_DAMAGE3
                            | OpenSHC::Audio::SFX::SEID_ARROW_SHOOT));
                }
            }
        }

    }
}
}
