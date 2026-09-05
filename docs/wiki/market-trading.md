# Market pricing and goods trading

These functions describe the native trading behavior used by automated market
callers. They preserve the original game rules; callers remain responsible for
deciding whether a trade should be attempted.

| Function | Crusader 1.41 address | Behavior |
| --- | --- | --- |
| `GameStateStructures::getBuyPrice` | `0x004588A0` | Returns `(buyPrice / 5) * amount`. |
| `GameStateStructures::getSellPrice` | `0x00458910` | Returns `(salesPrice / 5) * amount`. |
| `AICState::buyGoods` | `0x004CC000` | Attempts resource storage, then deducts gold and displays the trade on success. |
| `AICState::sellGoods` | `0x004CBFA0` | Credits gold and final-result statistics, removes resources, then displays the trade. |

## Details relevant to callers

Both price functions read the price array through their `this` pointer (ECX in
the original assembly). The player argument is unused. Division happens before
multiplication, so a price of 14 and an amount of 5 produce 10, not 14. A
decompilation that substitutes a fixed global for `this` loses this behavior.

`buyGoods` returns false when `processResourceGain` fails. In that case it does
not deduct gold or display a trade. It contains no affordability check of its
own. On success it subtracts the cost from both the player's gold resource and
`marketGold`.

`sellGoods` adds the reward to those same two fields and to
`finalResults.finalGold[playerID]` before calling `processResourceLoss`. Its
trade visual uses the sell flag and a negative amount; the buy visual uses the
buy flag and a positive amount. Neither native function applies an Automarket
plugin fee.

## Verification

The implementations were compared against the Crusader executable with SHA256
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`,
using the project's MSVC 2005 SP1 x86 toolchain and RelWithDebInfo configuration.
Both price functions match at 100% in reccmp. The trade functions score 81.82%
(`sellGoods`) and 85.71% (`buyGoods`) with inactive resolvers. A separate
instruction check confirmed that every non-call instruction is byte-identical
and all six resolver call thunks target the corresponding original callees.

This is a static binary comparison, not an in-game multiplayer test. Default
source selection and resolver activation remain separate from these
implementations.
