require("premake", ">=5.0.0-alpha10")

---
---
---

local libDir = "../Libraries/"

solution "F4Sandbox"
    configurations {"Debug32", "Debug64", "Release64", "Release32"}

    filter "configurations:*32"
        architecture "x86"

    filter "configurations:*64"
        architecture "x86_64"

    includedirs {
        libDir
    }

    project "Server"
        ---Set the kind of the app
        kind "ConsoleApp"

        ---Set the app language
        language "C++"
        ---Setting the language version
        cppdialect "C++20"

        includedirs {
            "../Code/Server/include/",
            "../Code/Server/src/"
        }

        files {
            "../Code/Server/include/**.hpp",
            "../Code/Server/include/**.h",
            "../Code/Server/src/**.cpp",
            "../Code/Server/src/**.c",
        }

    project "Client"
        kind "SharedLib"
        
        language "C++"

        cppdialect "C++20"

        includedirs {
            "../Code/Client/include/"
        }

        files {
            "../Code/Client/include/**.hpp",
            "../Code/Client/include/**.h",
            "../Code/Client/src/**.cpp",
            "../Code/Client/src/**.c",
        }