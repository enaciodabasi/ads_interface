cmake_minimum_required(VERSION 3.0.0)
project(ads_lib)

include(GNUInstallDirs)

set(AdsLib_INCLUDE_DIRS "ADS/AdsLib/")

add_library(ads_lib SHARED
    ${AdsLib_INCLUDE_DIRS}/standalone/AdsLib.cpp
    ${AdsLib_INCLUDE_DIRS}/standalone/AmsConnection.cpp
    ${AdsLib_INCLUDE_DIRS}/standalone/AmsNetId.cpp
    ${AdsLib_INCLUDE_DIRS}/standalone/AmsPort.cpp
    ${AdsLib_INCLUDE_DIRS}/standalone/AmsRouter.cpp
    ${AdsLib_INCLUDE_DIRS}/standalone/NotificationDispatcher.cpp    
    ${AdsLib_INCLUDE_DIRS}/AdsDef.cpp
    ${AdsLib_INCLUDE_DIRS}/AdsDevice.cpp
    ${AdsLib_INCLUDE_DIRS}/AdsFile.cpp
    ${AdsLib_INCLUDE_DIRS}/AdsLib.cpp
    ${AdsLib_INCLUDE_DIRS}/Frame.cpp
    ${AdsLib_INCLUDE_DIRS}/LicenseAccess.cpp
    ${AdsLib_INCLUDE_DIRS}/Log.cpp
    ${AdsLib_INCLUDE_DIRS}/RouterAccess.cpp
    ${AdsLib_INCLUDE_DIRS}/RTimeAccess.cpp
    ${AdsLib_INCLUDE_DIRS}/Sockets.cpp
)
target_include_directories(ads_lib PUBLIC ${AdsLib_INCLUDE_DIRS})
install(TARGETS ads_lib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})