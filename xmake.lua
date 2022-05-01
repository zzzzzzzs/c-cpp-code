add_rules("mode.debug", "mode.release")
-- 优化级别
set_optimize("faster")
-- 设置c代码标准：c99， c++代码标准：c++11
set_languages("c11", "cxx11")

toolchain("mingw")
    set_kind("standalone")
    set_sdkdir("D:/software/mingw64")
toolchain_end()

target("hello")
    set_kind("binary")
    add_files("src/hello/main.c")

target("array")
    set_kind("binary")
    add_files("src/collection/array*.c")

target("list")
    set_kind("binary")
    add_files("src/collection/list*.c")

target("map")
    set_kind("binary")
    add_files("src/collection/map*.c")

target("dict")
    set_kind("binary")
    add_files("src/collection/dict*.c")

target("vec")
    set_kind("binary")
    add_files("src/collection/vec*.c")

target("cjson")
    set_kind("binary")
    add_files("src/cJSON/*.c")

target("malloc_dbg")
    set_kind("binary")
    add_files("src/tools/malloc_dbg*.c")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

