=======================
Contributing to OpenSHC
=======================

Ready to dive in? Here's how you can start contributing to OpenSHC.

1. **Clone the Repository**

.. code-block:: bash

   git clone https://github.com/sourcehold/OpenSHC.git
   cd OpenSHC


2. **Install Dependencies**

   Make sure you have the required libraries:

   - Python 3: ``python -m pip install -r requirements.txt``
   - `MSVC 1400 <https://github.com/sourcehold/MSVC1400>`_

3. **Build the Project**

   Open a prompt and load the MSVC 1400 environment (.bat file)

.. code-block:: bash

   mkdir build && cd build
   cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo
   nmake

4. **Run reccmp**
   This compares the functions in the dll to those in the original game.
   
.. code-block:: bash

   reccmp-reccmp --paths "path\to\Stronghold Crusader.exe" "build\OpenSHC.dll" "build\OpenSHC.pdb" .


Developing contributions
=========================

Contributions are done by contributing either:

* reimplemented source code for functions of the original game.
* data structures.
* other code.

Contributing functions
+++++++++++++++++++++++

The functions of the original game are referenced by address.

The 1.41 Latin version of the Stronghold Crusader.exe is used as the reference version.

For example, the function that checks if X and Y coordinates are valid coordinates lives at address 0x401000.

Since the names of functions and variables may change (improve), you can refer to the function using the address instead.

Compilation
++++++++++++

When compiling OpenSHC, the addresses are resolved for the build target.
For example, if OpenSHC is being compiled for Extreme, the addresses resolve to the address for the Stronghold_Crusader_Extreme.exe

In order to make explicit which version you are referring to, or in case a function does not exist in the reference version, you can use the ``shce::0x401000`` syntax.
Note that the part between `::` is for specifying a specific hash if necessary, e.g. ``shc:92fac0d0:0x401000``