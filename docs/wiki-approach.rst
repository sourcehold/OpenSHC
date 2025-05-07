Approach
===========

Aims
------

The two main aims are:

#. Replicating the original game's machine code using new source code (reimplementation)
#. Providing modding opportunities in the new source code

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

Then a reimplementation could look like below. Note the use of macros to define the 
damage as an (inline) constant or not depending on whether compilation for replication of the
original code is desired (:ref:`aim 1<Aims>`), or compilation for easier modding (:ref:`aim 2<Aims>`).

`View on godbolt.org <https://godbolt.org/z/5e485dh8r>`_

.. code-block:: c++

    #define PERMIT_MODDING
    #ifdef PERMIT_MODDING
    #define CONST 
    #else
    #define CONST const
    #endif

    namespace Damage {
        namespace Entities {
            // A struct is used here to make modding easier as it strictly defines the ints
            // as next to each other in memory.
            typedef struct UnitDamage {
                int CONST fromArrow = 30;
                int CONST fromPebble = 50;
                int CONST fromOther = 20;
            } UnitDamage;
            UnitDamage CONST unitDamages;
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
