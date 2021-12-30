cmake_minimum_required(VERSION 3.5)

project(OpenType2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OpenType2 main.cpp fontfile.h fontfile.cpp tag.h tag.cpp fontseeker.h fontseeker.cpp
    GSUB/gsub.h GSUB/gsub.cpp
    GSUB/ScriptList/scriptlist.h GSUB/ScriptList/scriptlist.cpp
    GSUB/ScriptList/scriptrecord.h GSUB/ScriptList/scriptrecord.cpp
    GSUB/ScriptList/script.h GSUB/ScriptList/script.cpp
    GSUB/ScriptList/langsysrecord.h GSUB/ScriptList/langsysrecord.cpp
    GSUB/ScriptList/langsys.h GSUB/ScriptList/langsys.cpp
    GSUB/FeatureList/featurelist.h GSUB/FeatureList/featurelist.cpp
    GSUB/FeatureList/featurerecord.h GSUB/FeatureList/featurerecord.cpp
    GSUB/FeatureList/feature.h GSUB/FeatureList/feature.cpp
    GSUB/LookupList/lookuplist.h GSUB/LookupList/lookuplist.cpp
    GSUB/LookupList/lookup.h GSUB/LookupList/lookup.cpp
    GSUB/LookupList/lookupsubtabletype1.h GSUB/LookupList/lookupsubtabletype1.cpp
    GSUB/LookupList/coverage.h GSUB/LookupList/coverage.cpp
    GSUB/LookupList/rangerecord.h GSUB/LookupList/rangerecord.cpp
    Test/test.h Test/test.cpp
    Test/tagtest.h Test/tagtest.cpp
    Test/fontfile_test.h Test/fontfile_test.cpp
    Test/fontseekertest.h Test/fontseekertest.cpp
    Test/gsubtest.h Test/gsubtest.cpp
    image.h image.cpp
    Test/writetest.h Test/writetest.cpp
    )

file(COPY NotoSansCJKjp-Thin.otf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY HinaMincho-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY KaiseiDecol-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY KaiseiHarunoUmi-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY KaiseiOpti-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY KaiseiTokumin-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY KiwiMaru-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY NewTegomin-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY NotoSerifJP-Regular.otf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ShipporiMinchoB1-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ShipporiMincho-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY YujiBoku-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY YujiMai-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY YujiSyuku-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ZenAntique-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ZenAntiqueSoft-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ZenOldMincho-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories("/usr/include/freetype2")
target_link_libraries( OpenType2 freetype )
