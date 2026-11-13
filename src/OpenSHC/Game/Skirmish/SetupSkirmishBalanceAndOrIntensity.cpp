#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        // FUNCTION: STRONGHOLDCRUSADER 0x00429710
        void SetupSkirmishBalanceAndOrIntensity()
        {
            switch (DAT_GameSynchronyState::instance.skirmishTechLevel) {
            case 0:
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = 1;
                DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 0;
                DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
                break;
            case 1:
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = 1;
                DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 1;
                DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
                break;
            case 2:
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = 2;
                DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 1;
                DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
                break;
            case 3:
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = 2;
                DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 2;
                DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
                break;
            case 4:
                DAT_GameSynchronyState::instance.skirmishGameIntensityType = 3;
                DAT_GameSynchronyState::instance.skirmishGameIntensityType2 = 3;
                DAT_GameSynchronyState::instance.skirmishDefaultPopularity = 80;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[0] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[1] = 1;
                DAT_GameSynchronyState::instance.skirmishUnknownSetting1[3] = 1;
                break;
            }

            switch (DAT_GameSynchronyState::instance.skirmishGameIntensityType) {
            case 1:
                for (int i = 0; i < 20; ++i) {
                    DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[i]
                        = DAT_RenderingDefinedData::instance
                              .SkirmishIntensityRelatedArray[0][DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            case 2:
                for (int i = 0; i < 20; ++i) {
                    DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[i]
                        = DAT_RenderingDefinedData::instance
                              .SkirmishIntensityRelatedArray[1][DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            case 3:
                for (int i = 0; i < 20; ++i) {
                    DAT_GameSynchronyState::instance.skirmishIntensityRelatedArray[i]
                        = DAT_RenderingDefinedData::instance
                              .SkirmishIntensityRelatedArray[2][DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            }

            switch (DAT_GameSynchronyState::instance.skirmishGameIntensityType2) {
            case 0:
                for (int i = 0; i < 10; ++i) {
                    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[i] = 0;
                }
                break;
            case 1:
                for (int i = 0; i < 10; ++i) {
                    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[i]
                        = DAT_RenderingDefinedData::instance
                              .SkirmishIntensityRelatedArray2[DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            case 2:
                for (int i = 0; i < 10; ++i) {
                    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[i]
                        = DAT_RenderingDefinedData::instance.SkirmishIntensityRelatedArray2[5
                            + DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            case 3:
                for (int i = 0; i < 10; ++i) {
                    DAT_GameSynchronyState::instance.skirmishBalanceRelatedArrayUnk1[i]
                        = DAT_RenderingDefinedData::instance.SkirmishIntensityRelatedArray2[10
                            + DAT_GameSynchronyState::instance.skirmishTechLevel][i];
                }
                break;
            }

            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
            DAT_GameSynchronyState::instance.field_0x1072e8 = -1;
            DAT_GameSynchronyState::instance.field_0x1072ec = -1;
        }

    }
}
}
