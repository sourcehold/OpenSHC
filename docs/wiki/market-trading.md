# AI market pricing and goods trading

This article describes the AI's market behavior. The AI buys and sells resources
using the game's shared price table. Its trade routines handle storage and gold
accounting; the decision to trade is made by their AI callers.

| Function | Crusader 1.41 address | Behavior |
| --- | --- | --- |
| `GameStateStructures::getBuyPrice` | `0x004588A0` | Returns `(buyPrice / 5) * amount`. |
| `GameStateStructures::getSellPrice` | `0x00458910` | Returns `(salesPrice / 5) * amount`. |
| `AICState::buyGoods` | `0x004CC000` | Attempts resource storage, then deducts gold and displays the trade on success. |
| `AICState::sellGoods` | `0x004CBFA0` | Credits gold and final-result statistics, removes resources, then displays the trade. |

## Prices

Prices are stored for lots of five goods. The game divides that price by five
using integer division, then multiplies by the amount traded. For example, a
table price of 14 and a trade of five goods produce a price of 10. The player
argument does not affect the price calculation.

## AI buying and selling

An AI purchase first attempts to store the goods. If storage fails, it returns
without deducting gold or displaying a trade. The routine itself does not check
whether the player can afford the purchase. Successful purchases reduce both
the player's gold and their net market-gold total.

An AI sale increases those two totals and the final-results gold statistic, then
removes the sold goods. Both successful purchases and sales display the trade
amount to the player.
