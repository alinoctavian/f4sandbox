require("premake", ">=5.0.0-alpha10")

---
---
---

local libDir = "../Libraries/"

solution "F4Sandbox"
    configurations {"Debug64", "Release64"}

    filter "configurations:*64"
        architecture "x86_64"

    includedirs {
        libDir,
        libDir .. "detours/include/",
        libDir .. "steam/include/",
        libDir .. "spdlog/include/",
        libDir .. "steamnetwork/include/",
        libDir .. "json/include/",
    }

    project "Common"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"

        includedirs {
            "../Code/Common/include"
        }

        files {
            "../Code/Common/include/**.hpp",
            "../Code/Common/include/**.h",
            "../Code/Common/src/**.cpp",
            "../Code/Common/src/**.c",
        }

    project "Client"
        kind "SharedLib"
        
        language "C++"

        cppdialect "C++20"

        includedirs {
            "../Code/Client/include/",
            "../Code/Common/include/",
        }

        files {
            "../Code/Client/include/**.hpp",
            "../Code/Client/include/**.h",
            "../Code/Client/src/**.cpp",
            "../Code/Client/src/**.c",
        }

        links {
            "Common",
            libDir .. "detours/x64/detours.lib",
            libDir .. "spdlogd/x64/spdlogd.lib",
            libDir .. "steam/x64/steam_api64.lib",
            libDir .. "steamnetwork/x64/GameNetworkingSockets_s.lib",
        }