cmake_minimum_required(VERSION 3.10)

project(localized_program)

add_custom_target(
        clean_all
        COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile *.pot *.po *.po~
)

add_custom_target(
        new.pot
        ALL
        DEPENDS main.c
        COMMAND cp ${PROJECT_SOURCE_DIR}/po/ru.po ${PROJECT_BINARY_DIR}
        COMMAND xgettext ${PROJECT_SOURCE_DIR}/main.c -k_ -o ${PROJECT_BINARY_DIR}/main.pot
        COMMAND echo Now you have to create your own translation into russian language: po/ru.po file based on main.pot
)
add_custom_target(
        ru.po
        ALL
        DEPENDS main.c
        COMMAND msgmerge -U ${PROJECT_BINARY_DIR}/ru.po ${PROJECT_BINARY_DIR}/main.pot
)
add_custom_target(
        prog.mo
        ALL
        DEPENDS ru.po
        COMMAND mkdir -p ru/LC_MESSAGES/
        COMMAND msgfmt ${PROJECT_BINARY_DIR}/ru.po -o ru/LC_MESSAGES/this.mo
)

add_custom_target(
        run
        ALL
        DEPENDS prog.mo localized_program
        COMMAND ./localized_program
)

include_directories(${PROJECT_SOURCE_DIR})
include(GNUInstallDirs)
add_definitions(-DLOCALE_DIR="../${CMAKE_INSTALL_LOCALEDIR}")
add_executable(localized_program main.c)

install(FILES ${PROJECT_BINARY_DIR}/ru/LC_MESSAGES/this.mo
        DESTINATION share/locale/ru/LC_MESSAGES)

install(FILES ${PROJECT_SOURCE_DIR}/man/localized_program.1
        DESTINATION share/man/man1)

install(TARGETS localized_program
        DESTINATION bin)
