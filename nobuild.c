#define NOBUILD_IMPLEMENTATION
#include "nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-std=c99", "-pedantic"

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);
    Cstr day;
    if (argc == 1) {
        WARN("No day provided");
        return 0;
    } else {
        day = CONCAT("day_", argv[1]);
    }
    Cstr c_name = CONCAT(day, ".c");
    Cstr o_name = CONCAT(day, ".o");
    Cstr dll_name = CONCAT(day, ".dll");
    Cstr l_name = CONCAT("-l", day);

    Cstr include = CONCAT("-I", ".");
    Cstr define = CONCAT("-DDAY_", argv[1]);

    CMD("gcc", "-c", c_name, "-o", o_name, include);
    CMD("gcc", "-shared", "-o", dll_name, o_name);
    CMD("gcc", CFLAGS, include, "main.c", "-o", "main", "-L.", l_name, define);
    return 0;
}