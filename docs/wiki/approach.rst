Approach
===========

This project's approach fulfills two aims as outlined in :ref:`Aims <About_Aims>`. Below a few examples are given to illustrate the approach.

Essentially, the approach recreates source code for the original game, and in the meantime adds macro's to support mods.

Two criteria define succesful code:

#. Faithful to the original. Byte-code similarity can be tested using the `reccmp` framework. A higher similarity indicates better code, but 100% similarity isn't a requirement, as incremental improvements are also great.
#. Modding abilities. The new source code should clarify value constants and possibilities to add moddability.

Note that mods itself are outside the scope of this project. This project is meant to facilitate mods, not implement them.

Examples
--------

Example 1: using macros and constants
++++++++++++++++++++++++++++++++++++++

If the pseudo-C code of the original machine code looks like this:

.. code-block:: c++
    
    void dealDamageToUnitFromFlyingEntity(int entityID, int unitID)
    {
        int entityType = entities[entityID].type;
        if (entityType == ARROW)
        {
            units[unitID].health -= 30;
        } else if(entityType == PEBBLE)
        {
            units[unitID].health -= 50;    
        } else {
            units[unitID].health -= 20;    
        }
    }

Then a reimplementation could look like below. A mod would remove the `const` modifiers and define an interface for customisations from users and creators.

`View on godbolt.org <https://godbolt.org/z/5e485dh8r>`_

.. code-block:: c++

    namespace Damage {
        namespace Entities {
            // A struct is used here to make modding easier as it strictly defines the ints
            // as next to each other in memory.
            typedef struct UnitDamage {
                int const fromArrow = 30;
                int const fromPebble = 50;
                int const fromOther = 20;
            } UnitDamage;
            UnitDamage const unitDamages;
        }
    }

    /** These are stubs to make the godbolt compiler happy */
    // Note these are always const, as changing these values would break
    // compatibility with the original game
    namespace EntityTypes {
        int const ARROW = 10;
        int const PEBBLE = 20;
    }

    typedef struct Entity {
        int type;
    } Entity;

    typedef struct Unit {
        int health;
    } Unit;

    Entity entities[100] {};
    Unit units[100] {};

    /** End of stubs */
    void dealDamageToUnitFromFlyingEntity(int entityID, int unitID)
    {
        int entityType = entities[entityID].type;
        if (entityType == EntityTypes::ARROW)
        {
            units[unitID].health -= Damage::Entities::unitDamages.fromArrow;
        } else if(entityType == EntityTypes::PEBBLE)
        {
            units[unitID].health -= Damage::Entities::unitDamages.fromPebble;   
        } else {
            units[unitID].health -= Damage::Entities::unitDamages.fromOther;  
        }
    }

    #pragma optimize("", off)
    int main(int argc, char** argv) {
        // This is written like this to avoid optimization by the compiler
        dealDamageToUnitFromFlyingEntity(atol(argv[0]), atol(argv[1]));

        return 0;
    }
