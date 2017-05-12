add_library(messages STATIC
            msg1.cpp
            msg2.cpp
            msg3.cpp
            ${CMAKE_SOURCE_DIR}/inc/communication/msg1.h
            ${CMAKE_SOURCE_DIR}/inc/communication/msg2.h
            ${CMAKE_SOURCE_DIR}/inc/communication/msg3.h
          )

target_include_directories(messages
                          PRIVATE ${CMAKE_SOURCE_DIR}/inc ${CMAKE_SOURCE_DIR}/inc/puf ${CMAKE_SOURCE_DIR}/inc/phemap ${CMAKE_SOURCE_DIR}/inc/communication
                          )
