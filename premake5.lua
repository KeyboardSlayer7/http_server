workspace "Projects"
    configurations {"Debug", "Release"}

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    if _ACTION == "clean" then
      os.rmdir("bin")
      os.rmdir("build")
      os.remove("Makefile")
      os.remove("*.sln")
    end

project "Http_Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files {"src/*.h", "src/*.cpp"}

    location "build"
    targetdir "bin/%{cfg.buildcfg}"

    links {"ws2_32"}