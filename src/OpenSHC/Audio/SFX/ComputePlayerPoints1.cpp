#include "../SFX.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        using namespace OpenSHC::Game::Resources;

        // FUNCTION: STRONGHOLDCRUSADER 0x0044A830
        int ComputePlayerPoints1(int playerID)
        {
            int const goldPoints = DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_GOLD] / 10;
            int const troopPoints = DAT_GameState::instance.playerDataArray[playerID].totalTroopValue;
            int const foodPoints
                = (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_BREAD)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_BREAD]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_CHEESE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_CHEESE]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_MEAT)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_MEAT]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_APPLE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_APPLE])
                / 10;
            int const weaponPoints
                = (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_BOW)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_BOW]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_CROSSBOW)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_CROSSBOW]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_SPEAR)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_SPEAR]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_PIKE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_PIKE]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_MACE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_MACE]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_SWORD)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_SWORD]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_LEATHERARMOR)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_LEATHERARMOR]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_IRONARMOR)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_IRONARMOR])
                / 10;
            int const materialPoints
                = (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(RT_WOOD)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_WOOD]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_HOPS)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_HOPS]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_STONE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_STONE]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_IRON)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_IRON]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_PARTIALPITCH)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_PARTIALPITCH]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_ALE)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_ALE]
                      + MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalePriceOfGood, DAT_GameState::ptr)(
                            RT_FLOUR)
                          * DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_FLOUR])
                / 10;
            return DAT_GameState::instance.playerDataArray[playerID].currentPopulation * 10 + materialPoints
                + weaponPoints + foodPoints + troopPoints + goldPoints;
        }

    }
}
}
