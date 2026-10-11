cmake_minimum_required(VERSION 3.21)
project(LogGuardian LANGUAGES CXX)

# 1. 明确指定 C++20 标准（LLMQore 强制要求）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 查找 Qt 组件，必须包含 Network 和 Concurrent
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Concurrent)

# 3. 引入本地 LLMQore 源码（替换掉 FetchContent）
set(LLMQORE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLMQORE_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(llmqore-0.8.0)     # ← 改成你解压后的实际文件夹名

# 4. Qt 项目标准初始化
qt_standard_project_setup()

# 5. 定义可执行文件
qt_add_executable(LogGuardian
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ThemeColors.h
    thememanager.h
    thememanager.cpp
    ToastNotification.cpp
    ToastNotification.h
    settingsdialog.h settingsdialog.cpp settingsdialog.ui
    config/ai_providers.json
)

# 6. 链接所有需要的 Qt 模块和 LLMQore
target_link_libraries(LogGuardian PRIVATE
    LLMQore::LLMQore
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Concurrent
)

# 7. 安装与部署配置
install(TARGETS LogGuardian
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET LogGuardian
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})