cmake_minimum_required(VERSION 3.0.0)
project(ads_interface VERSION 0.1.0)


set(AdsLib_INCLUDE_DIRS lib/ADS/AdsLib/)

include_directories(
    include/ads_interface
    ${AdsLib_INCLUDE_DIRS}
)

include(CTest)
enable_testing()

add_library(AdsLib SHARED
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


add_library(ads_interface STATIC
    src/ads_interface.cpp 
    src/interface_data.cpp
    src/interface_data_container.cpp
)
target_link_libraries(ads_interface PUBLIC AdsLib)
target_include_directories(ads_interface PUBLIC include/ads_interface ${AdsLib_INCLUDE_DIRS})

add_executable(data_test test/data_type_test.cpp)
target_include_directories(data_test PUBLIC include/ads_interface)
target_link_libraries(data_test PUBLIC ads_interface)
#target_link_directories(data_test PUBLIC include/ads_interface)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
