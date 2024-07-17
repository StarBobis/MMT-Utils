# MMT-Utils

This is a dependency project for MigotoModTool (MMT-Community).

# How to build 

Some preconfig you will need to have:
- VisualStudio 2022 VS143 toolset. 
- Install Boost 1.84.0  (or latest version)
- (1) Download Boost 1.84.0 and unzip it to somewhere.
- (2) Open your terminal and switch into your boost unziped folder.
- (3) to initialize boost config, type this command in your terminal: .\bootstrap.bat
- (4) then type this in your terminal to build boost library for MMT:

- .\b2.exe variant=release link=static runtime-link=static threading=multi runtime-debugging=off
- (5) Change your project's setting path, on my computer i put the unziped boost on C:\AppLibraries, so for my computer it's path looks like below,but you need to change it to your own path:
The following directory should be added to compiler include paths:

    C:\AppLibraries\boost_1_84_0

The following directory should be added to linker library paths:

    C:\AppLibraries\boost_1_84_0\stage\lib

After these steps above ,you will be able to build MMT on X64 DEBUG or RELEASE, x32-bit is also work but not official supported by MMT for low speed reason.

# Third party used
- easylogging
- Json for morden C++ (nlohmann json)
- Boost 1_84_0.
