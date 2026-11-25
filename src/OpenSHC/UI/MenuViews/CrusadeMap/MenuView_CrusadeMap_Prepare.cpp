#include "../CrusadeMap.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/string-literals.hpp"

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
        namespace CrusadeMap {

            // FUNCTION: STRONGHOLDCRUSADER 0x004D8CB0
            void MenuView_CrusadeMap_Prepare()
            {
                DWORD_00ed311c::instance = 0;
                // the trail's map (one totalLoadedGfx store after picking the name: quick_diff 0.9708 -> 0.9123)
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "shcx_map.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_shcx_map_tgx_005aafcc);
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "skirmish_trail2.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_skirmish_trail2_tgx_005aafb8);
                } else {
                    DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                    // "skirmish_trail.tgx"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                        DAT_TextureRenderCoreObject::ptr)(s_skirmish_trail_tgx_005aafa4);
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
                // each trail's progress stays within its 50, 30 and 20 missions
                if (DAT_GameCore::instance.skirmishTrailProgress > 49) {
                    DAT_GameCore::instance.skirmishTrailProgress = 49;
                }
                if (DAT_GameCore::instance.warchestTrailProgress > 29) {
                    DAT_GameCore::instance.warchestTrailProgress = 29;
                }
                // fixme: the original clamps the warchest progress here, not the extreme one
                if (DAT_GameCore::instance.extremeTrailProgress > 19) {
                    DAT_GameCore::instance.warchestTrailProgress = 19;
                }
                INT_00eb9b48::instance = 1;
                DWORD_00ed27a8::instance = timeGetTime();
                // three, less one for each mission of the trail skipped with the chicken (-1200), but not below 0
                DAT_SkirmishTrailRelated1::instance = 3;
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                    int const furthestMission = DAT_GameCore::instance.furthestSkirmishTrailMission;
                    // the counter outside the for (in it: quick_diff 0.9708 -> 0.9379)
                    int mission = 0;
                    if (furthestMission > 0) {
                        for (; mission < furthestMission; ++mission) {
                            if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[mission] == -1200) {
                                --DAT_SkirmishTrailRelated1::instance;
                            }
                        }
                        if (DAT_SkirmishTrailRelated1::instance < 0) {
                            DAT_SkirmishTrailRelated1::instance = 0;
                        }
                    }
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    int const furthestMission = DAT_GameCore::instance.furthestWarchestTrailMission;
                    int mission = 0;
                    if (furthestMission > 0) {
                        for (; mission < furthestMission; ++mission) {
                            if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[mission] == -1200) {
                                --DAT_SkirmishTrailRelated1::instance;
                            }
                        }
                        if (DAT_SkirmishTrailRelated1::instance < 0) {
                            DAT_SkirmishTrailRelated1::instance = 0;
                        }
                    }
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    int const furthestMission = DAT_GameCore::instance.furthestExtremeTrailMission;
                    int mission = 0;
                    if (furthestMission > 0) {
                        for (; mission < furthestMission; ++mission) {
                            if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[mission] == -1200) {
                                --DAT_SkirmishTrailRelated1::instance;
                            }
                        }
                        if (DAT_SkirmishTrailRelated1::instance < 0) {
                            DAT_SkirmishTrailRelated1::instance = 0;
                        }
                    }
                }
                INT_00ed2bdc::instance = FALSE;
            }

        }
    }
}
}
