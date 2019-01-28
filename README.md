# IL-2-Plane-Stat-Spreadsheet-Generator
Small Project to create a spreadsheet of aircraft statistics from the IL-2 Forum HTML.

## Requirements

-GNU GCC/G++ compiler

-If running straight from bin\debug, just an x86 Windows machine.

-Not guaranteed to work on Linux, or anything other than Windows

-Alternatively, you may be able to open the .cbp and easily compile it with codeblocks (however I am unsure if this will still work)

## Installation/Compilation/Use

1. Download/clone repository into whichever directory you require

2. Run "g++ main.cpp" from command line (Windows)

3. Paste the raw HTML from the IL-2 forum's plane statistics page into html.txt in the same directory as the new .exe

4. Paste every plane's name (exactly as it appears on the forum page/HTML) into planes.txt, each plane separated by a newline.

4. run the program via command line for hints about program status / errors.

5. All stats should appear in IL-2 Plane Data.csv, as a comma separated value spreadsheet.
