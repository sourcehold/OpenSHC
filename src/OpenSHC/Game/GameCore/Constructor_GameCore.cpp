#include "../GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046B1F0
    GameCore* GameCore::Constructor_GameCore()
    {
        this->currentMenuViewType = UI::Enums::MVT_NO_VIEW;
        this->unknownAlwaysZero01 = 0;
        this->currentlyInGameUnk_0xa4 = FALSE;
        this->mapTimeInTicks = 0;
        this->unknownAlwaysZero02 = 0;
        this->field26_0x74 = 0;
        this->field24_0x6c = 0;
        this->isTimeHalted2 = 0;
        this->unlockAllHistoricalCampaigns = 0;
        this->unused1 = 0;
        this->solitaryAltUDungeon = FALSE;
        this->currentTrailType = TT_FIRST_EDITION;
        this->field59_0xf8 = 0;
        this->specialMultiplayerState = 0;
        this->cheatModeFlag = FALSE;
        this->solitaryAllBuildingsAreFree = FALSE;
        this->unknownAlwaysZero = 0;
        this->newPlayerID = 0;
        this->menuType7_MenuItemClickHandlerUnk = NULL;
        this->activeMenuTab.buildMenuTab = UI::Enums::BMTT_CASTLE;
        this->gameSpeedMultiplicator = 1;
        this->forty = 40;
        this->countdown = 1;
        this->uniqueGameObjectTracker = 1;
        this->gameSpeedLevel = 40;
        this->settingBubbleHelp = 1;
        this->twohundred = 200;
        this->field62_0x104 = 1;
        this->field63_0x108 = 1;
        this->field52_0xdc = 1;
        this->scenarioProgress.progressCallToArms = 1;
        this->scenarioProgress.progressSaladinsConquest = 6;
        this->scenarioProgress.progressTheKingsCrusade = 11;
        this->scenarioProgress.progressCrusaderStates = 16;
        this->furthestMission = 33;
        this->viewportFocusBeforeBarracksHotkey = -1;
        this->viewportFocusBeforeMercenaryHotkey = -1;
        this->viewportFocusBeforeGranaryHotkey = -1;
        this->viewportFocusBeforeMarketHotkey = -1;
        this->viewportFocusBeforeKeepHotkey = -1;
        this->viewportFocusBeforeArmoryHotkey = -1;
        return this;
    }

}
}
