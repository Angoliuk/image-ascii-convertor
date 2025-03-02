find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

find_package(stb REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC stb::stb)

set(CMAKE_PREFIX_PATH "/Users/stasangoliuk/Qt/6.8.2/macos")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
set(CMAKE_AUTOMOC ON)
target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)
