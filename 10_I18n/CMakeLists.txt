cmake_minimum_required(VERSION 3.10)

project(localized_program)

add_custom_target(
        clean_all
        COMMAND rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile *.pot
)

add_custom_target(
        new.pot
        ALL
        DEPENDS main.c
        COMMAND xgettext main.c -k_ -o main.pot
        COMMAND echo Now you have to create your own translation into russian language: ru.po file based on main.pot
)
add_custom_target(
        ru.po
        ALL
        DEPENDS main.pot main.c
        COMMAND msgmerge -U ru.po main.pot
)
add_custom_target(
        prog.mo
        ALL
        DEPENDS ru.po
        COMMAND mkdir -p ru/LC_MESSAGES/
        COMMAND msgfmt ru.po -o ru/LC_MESSAGES/this.mo
)

add_custom_target(
        run
        ALL
        DEPENDS prog.mo localized_program
        COMMAND ./localized_program
)

add_executable(localized_program main.c)
