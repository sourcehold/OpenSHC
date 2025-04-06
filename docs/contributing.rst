Contributing to OpenSHC
=======================

Ready to dive in? Here's how you can start contributing to OpenSHC.

1. **Clone the Repository**

   ```bash
   git clone https://github.com/sourcehold/OpenSHC.git
   cd OpenSHC
   ```

2. **Install Dependencies**

   Make sure you have the required libraries:

   - Python
   - `MSVC 1400 <https://github.com/sourcehold/MSVC1400>`_

3. **Build the Project**

   Open a prompt and load the MSVC 1400 environment (.bat file)
   
   ```bash
   mkdir build && cd build
   cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=%1
   nmake
   ```

4. **Run reccmp**
   This compares 
   ```bash
   reccmp-reccmp --paths "path\to\Stronghold Crusader.exe" build\OpenSHC.dll build\OpenSHC.pdb . %2 %3
   ```

