#include "../CrusadeMap.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SkirmishTrailRelated1.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DWORD_00ed27a8.hpp"
#include "OpenSHC/Globals/DWORD_00ed311c.hpp"
#include "OpenSHC/Globals/INT_00eb9b48.hpp"
#include "OpenSHC/Globals/INT_00ed2bdc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Game::TrailType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8CB0
        void CrusadeMap::MenuView_CrusadeMap_Prepare()
        {
            int iVar1;
            char* tgxFileName;
            DWORD_00ed311c::instance = 0;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                tgxFileName = "shcx_map.tgx";
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                tgxFileName = "skirmish_trail2.tgx";
            } else {
                tgxFileName = "skirmish_trail.tgx";
            }
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)(tgxFileName);
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            if (0x31 < (int)DAT_GameCore::instance.skirmishTrailProgress) {
                DAT_GameCore::instance.skirmishTrailProgress = 0x31;
            }
            if (0x1d < (int)DAT_GameCore::instance.warchestTrailProgress) {
                DAT_GameCore::instance.warchestTrailProgress = 0x1d;
            }
            if (0x13 < DAT_GameCore::instance.extremeTrailProgress) {
                DAT_GameCore::instance.warchestTrailProgress = 0x13;
            }
            INT_00eb9b48::instance = 1;
            DWORD_00ed27a8::instance = timeGetTime();
            DAT_SkirmishTrailRelated1::instance = 3;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                iVar1 = 0;
                if (DAT_GameCore::instance.furthestSkirmishTrailMission < 1) {
                    DAT_SkirmishTrailRelated1::instance = 3;
                    INT_00ed2bdc::instance = 0;
                }
                do {
                    if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[iVar1] == -0x4b0) {
                        DAT_SkirmishTrailRelated1::instance = DAT_SkirmishTrailRelated1::instance + -1;
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < DAT_GameCore::instance.furthestSkirmishTrailMission);
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                iVar1 = 0;
                if (DAT_GameCore::instance.furthestWarchestTrailMission < 1) {
                    DAT_SkirmishTrailRelated1::instance = 3;
                    INT_00ed2bdc::instance = 0;
                }
                do {
                    if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[iVar1] == -0x4b0) {
                        DAT_SkirmishTrailRelated1::instance = DAT_SkirmishTrailRelated1::instance + -1;
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < DAT_GameCore::instance.furthestWarchestTrailMission);
            } else {
                if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME) {
                    DAT_SkirmishTrailRelated1::instance = 3;
                    INT_00ed2bdc::instance = 0;
                }
                iVar1 = 0;
                if (DAT_GameCore::instance.furthestExtremeTrailMission < 1) {
                    DAT_SkirmishTrailRelated1::instance = 3;
                    INT_00ed2bdc::instance = 0;
                }
                do {
                    if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[iVar1] == -0x4b0) {
                        DAT_SkirmishTrailRelated1::instance = DAT_SkirmishTrailRelated1::instance + -1;
                    }
                    iVar1 = iVar1 + 1;
                } while (iVar1 < DAT_GameCore::instance.furthestExtremeTrailMission);
            }
            if (DAT_SkirmishTrailRelated1::instance < 0) {
                DAT_SkirmishTrailRelated1::instance = 0;
            }
            INT_00ed2bdc::instance = 0;
        }

    }
}
}
