add_library(md5 SHARED
            md5.cpp
            ${CMAKE_SOURCE_DIR}/inc/phemap/md5.h
           )

target_include_directories(md5
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/phemap
                           )

add_library(device SHARED
           deviceSkeleton.cpp
           device.cpp
           ${CMAKE_SOURCE_DIR}/inc/phemap/deviceSkeleton.h
           ${CMAKE_SOURCE_DIR}/inc/phemap/device.h
          )

target_include_directories(device
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(device PRIVATE verifierProxy messages)

add_library(verifierProxy SHARED
           verifierProxy.cpp
           ${CMAKE_SOURCE_DIR}/inc/phemap/verifierProxy.h
           ${CMAKE_SOURCE_DIR}/inc/phemap/verifierSkeleton.h
          )

target_link_libraries(verifierProxy PRIVATE utils)


target_include_directories(verifierProxy
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap
                          )

add_library(deviceProxy SHARED
           deviceSkeleton.cpp
           deviceProxy.cpp
           ${CMAKE_SOURCE_DIR}/inc/phemap/deviceSkeleton.h
           ${CMAKE_SOURCE_DIR}/inc/phemap/deviceProxy.h
          )

target_include_directories(deviceProxy
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(deviceProxy PRIVATE pufChain messages utils)


add_library(deviceManager SHARED
           deviceManager.cpp
           ${CMAKE_SOURCE_DIR}/inc/phemap/deviceManager.h
          )

target_include_directories(deviceManager
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(deviceManager PRIVATE deviceProxy pufChain utils messages)

add_library(verifier SHARED
           verifier.cpp
           ${CMAKE_SOURCE_DIR}/inc/phemap/verifier.h
           ${CMAKE_SOURCE_DIR}/inc/phemap/verifierSkeleton.h
          )

target_include_directories(verifier
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(verifier PRIVATE deviceManager)

add_library(deviceServer SHARED
            deviceSkeleton.cpp
            deviceServer.cpp
            ${CMAKE_SOURCE_DIR}/inc/phemap/deviceSkeleton.h
            ${CMAKE_SOURCE_DIR}/inc/phemap/deviceServer.h
          )

target_include_directories(deviceServer
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(deviceServer PRIVATE device utils)

add_library(verifierServer SHARED
            verifierServer.cpp
            ${CMAKE_SOURCE_DIR}/inc/phemap/verifierServer.h
            ${CMAKE_SOURCE_DIR}/inc/phemap/verifierSkeleton.h
          )

target_include_directories(verifierServer
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )

target_link_libraries(verifierServer PRIVATE verifier utils)
