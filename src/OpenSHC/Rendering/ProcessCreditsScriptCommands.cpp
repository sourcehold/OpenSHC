#include "../Rendering.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0e40.hpp"
#include "OpenSHC/Globals/DAT_00eb1234.hpp"
#include "OpenSHC/Globals/DAT_00eb9af4.hpp"
#include "OpenSHC/Globals/DAT_00ed2bd8.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedX.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedY.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/FLOAT_00eb0e2c.hpp"
#include "OpenSHC/Globals/FLOAT_00ec083c.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb0e30.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"
#include "OpenSHC/Globals/INT_00ec082c.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"

namespace OpenSHC {

using Audio::MSS::enums::SHC_SoundStream;
using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x004E0A50
void Rendering::ProcessCreditsScriptCommands()
{
    int lastIndex = DAT_UnknownBinkIndex::instance;
    if (DAT_GameCore::instance.menuViewToSwitchTo != DAT_GameCore::instance.currentMenuViewType) {
        return;
    }
    while (
        DAT_UnknownBinkIndex::instance >= 0 && DAT_UnknownBinkIndex::instance < (int)DAT_UnknownBinkCount::instance) {
        bool advance = true;
        switch (DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType) {
        case 1:
            FLOAT_00ec083c::instance = FLOAT_Between1And5::instance + FLOAT_00ec083c::instance;
            if (!(FLOAT_00ec083c::instance
                    > (float)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream)) {
                return;
            }
            FLOAT_00ec083c::instance = 0.0f;
            break;
        case 44:
            FLOAT_00ec083c::instance = FLOAT_Between1And5::instance + FLOAT_00ec083c::instance;
            if (!(FLOAT_00ec083c::instance
                    > (float)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream)) {
                if (!DAT_MouseState::instance.draggingStopped) {
                    return;
                }
            }
            FLOAT_00ec083c::instance = 0.0f;
            break;
        case 2: {
            int k;
            for (k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 1
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    if (DAT_ARRAY_00ec0348::instance[k].fadeMode == 0) {
                        DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance + 1;
                    }
                    break;
                }
            }
            if (k != 24) {
                advance = false;
            }
            break;
        }
        case 3: {
            int k;
            for (k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 2
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    if (DAT_ARRAY_00ec0348::instance[k].fadeMode == 0) {
                        DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance + 1;
                    }
                    break;
                }
            }
            if (k != 24) {
                advance = false;
            }
            break;
        }
        case 4:
            if (MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    (SHC_SoundStream)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream)) {
                advance = false;
            }
            break;
        case 5:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(1,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x38,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x28);
            break;
        case 6:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(1,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x38,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height, 1,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x28);
            break;
        case 7:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 1
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    DAT_ARRAY_00ec0348::instance[k].blendStrength = 1.0f;
                    DAT_ARRAY_00ec0348::instance[k].fadeMode = 2;
                }
            }
            break;
        case 8:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 1
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    DAT_ARRAY_00ec0348::instance[k].type = 0;
                }
            }
            break;
        case 9:
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                (Audio::MSS::enums::SHC_SoundStream)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance]
                    .soundStream);
            break;
        case 10:
            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream);
            break;
        case 11:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 2
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    DAT_ARRAY_00ec0348::instance[k].type = 0;
                }
            }
            break;
        case 12:
            MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].binkObjIndex,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].binkFileName,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].flagLoopCount, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x
                    + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y
                    + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x28);
            break;
        case 13:
            DAT_SoundSystemState::instance
                .streamFileVolumeNextUnk_0x48[DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].binkObjIndex]
                = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].volume;
            MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundStreamUnk, DAT_SoundSystemState::ptr)(
                (SHC_SoundStream)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].binkObjIndex,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].binkFileName,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].flagLoopCount);
            break;
        case 14:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_2)(2,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x18,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x34,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x30);
            break;
        case 15:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_2)(2,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x18,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x34,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y, 1,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x30);
            break;
        case 16:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 2
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    DAT_ARRAY_00ec0348::instance[k].blendStrength = 1.0f;
                    DAT_ARRAY_00ec0348::instance[k].fadeMode = 2;
                }
            }
            break;
        case 17:
            INT_00ed27a4::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream;
            if (INT_00ed27a4::instance == Audio::MSS::enums::SND_STR_SFX_1Unk) {
                DAT_00eb9af4::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x;
            }
            break;
        case 18:
            DAT_00eb0e40::instance = 1;
            FLOAT_00eb0e2c::instance = 0.0f;
            break;
        case 19:
            DAT_00eb0e40::instance = 2;
            FLOAT_00eb0e2c::instance = 31.0f;
            break;
        case 43:
            DAT_00eb0e40::instance = 5;
            FLOAT_00eb0e2c::instance = 31.0f;
            break;
        case 20:
            if (DAT_00eb0e40::instance) {
                return;
            }
            break;
        case 36:
            DAT_00eb0e40::instance = 3;
            FLOAT_00eb0e2c::instance = 0.0f;
            DAT_RenderRelatedX::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x;
            DAT_RenderRelatedY::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y;
            DAT_00eb1234::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width;
            INT_00eb0e30::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height;
            break;
        case 37:
            DAT_00eb0e40::instance = 4;
            FLOAT_00eb0e2c::instance = 31.0f;
            DAT_RenderRelatedX::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x;
            DAT_RenderRelatedY::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y;
            DAT_00eb1234::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width;
            INT_00eb0e30::instance = DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height;
            break;
        case 21:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_3)(3,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x28);
            break;
        case 23:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 3) {
                    DAT_ARRAY_00ec0348::instance[k].type = 0;
                }
            }
            break;
        case 22: {
            if (!DAT_MouseState::instance.draggingStopped) {
                return;
            }
            int k;
            for (k = 0; k != 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 3
                    && DAT_ARRAY_00ec0348::instance[k].x
                        <= DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < DAT_ARRAY_00ec0348::instance[k].x + DAT_ARRAY_00ec0348::instance[k].width
                    && DAT_ARRAY_00ec0348::instance[k].y <= DAT_MouseState::instance.screenSpaceY
                            - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                    && DAT_MouseState::instance.screenSpaceY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                        < DAT_ARRAY_00ec0348::instance[k].y + DAT_ARRAY_00ec0348::instance[k].height) {
                    break;
                }
            }
            if (k == 24) {
                return;
            }
            break;
        }
        case 24:
            if (DAT_BinkControlState::instance.binkObjPtrArray[0]) {
                return;
            }
            break;
        case 25:
            if (INT_00ed27a4::instance != 2 && DAT_BinkControlState::instance.binkObjPtrArray[0]) {
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(
                    0);
            }
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type) {
                    DAT_ARRAY_00ec0348::instance[k].type = 0;
                }
            }
            break;
        case 26:
            DAT_00ed2bd8::instance = 1;
            break;
        case 32:
            DAT_00ed2bd8::instance = 2;
            break;
        case 27:
            MACRO_CALL(UI::Rendering_Func::DisplayFullScreenTextPage)(
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream);
            DWORD_00eb9ac4::instance = 1;
            break;
        case 28:
            DWORD_00eb9ac4::instance = 0;
            DAT_00ed2bd8::instance = 0;
            break;
        case 39:
            if (DAT_SoundSystemState::instance.sec_Section1055_0x3274
                != DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                    (DE::SHCDE::eMusicIDs)DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream);
            }
            break;
        case 40:
            // jump back to the most recent loop marker
            for (DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance - 1;
                DAT_UnknownBinkIndex::instance > 0;
                DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance - 1) {
                if (DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].commandType == 31) {
                    break;
                }
            }
            break;
        case 41:
            MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(4,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].x,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].y,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].width,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].height, 0,
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].field_0x28);
            break;
        case 42:
            for (int k = 0; k < 24; k++) {
                if (DAT_ARRAY_00ec0348::instance[k].type == 4
                    && DAT_ARRAY_00ec0348::instance[k].xSpace
                        == DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance].soundStream) {
                    DAT_ARRAY_00ec0348::instance[k].blendStrength = 1.0f;
                    DAT_ARRAY_00ec0348::instance[k].fadeMode = 2;
                }
            }
            break;
        }
        if (advance) {
            DAT_UnknownBinkIndex::instance = DAT_UnknownBinkIndex::instance + 1;
        }
        if (DAT_UnknownBinkIndex::instance == lastIndex) {
            return;
        }
        lastIndex = DAT_UnknownBinkIndex::instance;
    }
}

}
