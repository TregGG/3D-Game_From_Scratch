-- premake5.lua
workspace "Cubbed-Server-Headless"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Cubbed-Server-Headless"

   -- Workspace-wide defines
   defines
   {
       "WL_HEADLESS"
   }

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

-- Directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
WalnutNetworkingBinDir = "Walnut/Walnut-Modules/Walnut-Networking/vendor/GameNetworkingSockets/bin/%{cfg.system}/%{cfg.buildcfg}/"

include "Walnut/Build-Walnut-Headless-External.lua"

group "App"
    include "Cubbed-Common/Build-Cubbed-Common-Headless.lua"
    include "Cubbed-Server/Build-Cubbed-Server-Headless.lua"
group ""