add_library(utils STATIC
            utils.c
            ${CMAKE_SOURCE_DIR}/inc/puf/utils.h
           )

target_include_directories(utils
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf
                           )

add_library(puf SHARED
            puf.cpp
            ${CMAKE_SOURCE_DIR}/inc/puf/puf.h
           )

target_include_directories(puf
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf
                           )

add_library(pufChain SHARED
           pufChain.cpp
           ${CMAKE_SOURCE_DIR}/inc/puf/pufChain.h
          )

target_include_directories(pufChain
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf
                          )

add_library(pufChainFromFile SHARED
           pufChainFromFile.cpp
           ${CMAKE_SOURCE_DIR}/inc/puf/pufChainFromFile.h
          )

target_include_directories(pufChainFromFile
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf
                          )

target_link_libraries(pufChainFromFile PRIVATE pufChain)


add_library(dummyPuf SHARED
           dummyPuf.cpp
           ${CMAKE_SOURCE_DIR}/inc/puf/dummyPuf.h
          )

target_include_directories(dummyPuf
                           PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap
                           )

target_link_libraries(dummyPuf PRIVATE puf md5 utils)
