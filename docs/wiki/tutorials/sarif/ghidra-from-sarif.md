# Importing SARIF file into a Ghidra project

## Overview

This tutorial describes how to import a SARIF export into your Ghidra project containing the original `Stronghold Crusader.exe` binary.

## Step by step

### Prerequisites

- Ghidra 11.4.1 or higher

### Launch Ghidra

Launch ghidra using e.g. `ghidraRun.bat` found in the Ghidra installation folder.

### Create a Ghidra project

Create a new project:

![alt text](./images/Screenshot%202026-06-06%20230601.png)

Make it a non-shared project:

![alt text](./images/Screenshot%202026-06-06%20230614.png)

Browse to a directory of your liking and name the project `ghidra-OpenSHC` (or something else you like better)

![alt text](./images/Screenshot%202026-06-06%20230653.png)

### Importing Stronghold Crusader.exe into Ghidra

Now, we import the original game binary into Ghidra (make sure it is exactly the right version, `SHA256: 3BB0A8C1E72331B3A30A5AA93ED94BECA0081B476B04C1960E26D5B45387AC5A`):

![alt text](./images/Screenshot%202026-06-06%20230709.png)

Browse to the exe file in your game's installation directory. You will be prompted with a window like this:

![alt text](./images/Screenshot%202026-06-06%20230745.png)

Hit OK and let it crunch. It will result in a window like this:

![alt text](./images/Screenshot%202026-06-06%20230756.png)

### Opening the exe in Ghidra

Now we open the exe file in Ghidra by double-clicking it:

![alt text](./images/Screenshot%202026-06-06%20230808.png)

Ghidra will ask us whether to analyze the binary. Click NO.

![alt text](./images/Screenshot%202026-06-06%20230820.png)

### Importing SARIF into Ghidra

Then, we import the sarif file into Ghidra. You can find the latest [here](https://github.com/gynt/OpenSHC/releases/tag/latest-sarif) (unzip the file into a directory).

Then, from inside the "CodeBrowser", click "Add to Program":

![alt text](./images/Screenshot%202026-06-06%20230831.png)

Then, browse to the sarif file and you will be prompted with a window like this:

![alt text](./images/Screenshot%202026-06-06%20230958.png)

After this is finished, the sarif file has been imported. However, we need some post-processing.

### Post-processing

In order to get decompilations of functions, Ghidra needs to disassemble all functions we just learned about via the SARIF file.

Go to Windows => Python (or PyGhidra or Jython).

![alt text](./images/Screenshot%202026-06-06%20231019.png)

Then input the following script in the interpreter window and hit enter:

```py
all(disassemble(f.getEntryPoint()) for f in getCurrentProgram().getFunctionManager().getFunctions(False))
```

![alt text](./images/Screenshot%202026-06-06%20231114.png)

After a while, it will have decompiled all functions.

Happy browsing!

## Known limitations

Calling conventions that preserve registers such as ECX are not supported for import.
