#!/bin/env python

import os
import sys
import platform
import subprocess as sp

CC = "gcc"
CFLAGS_DEBUG = "-g3 -Og"
CFLAGS_RELEASE = "-O2 -march=native"


def build(cflags: str, run_tests: bool):

    ext = ".exe" if platform.system() == "Windows" else ""

    for mod in os.listdir("."):
        if os.path.isdir(mod) and os.listdir(mod) and mod != "bin":
            if not os.path.isdir("bin"):
                os.mkdir("bin")

            sp.run(f"{CC} {cflags} -c {mod}/{mod}.c -o bin/{mod}.o".split(' '))
            if run_tests:
                sp.run(
                    f"{CC} {cflags} bin/{mod}.o {mod}/test.c -o bin/{mod}_test{ext}".split(' '))
                sp.run(f"{os.path.abspath(f'bin/{mod}_test')}")


def main():

    run_tests = True
    cflags = "-Wall -Wextra -std=c99"

    if len(sys.argv) > 1:

        if "help" in sys.argv[1]:
            print("Usage: build.py [debug|release] [--no-tests]")
            return

        elif sys.argv[1] == "debug":
            cflags += " " + CFLAGS_DEBUG

        elif sys.argv[1] == "clear":
            for file in os.listdir("bin"):
                if file.endswith(".o") or file.endswith(".exe") or file.endswith("_test"):
                    os.remove(os.path.join("bin", file))
            return

        if "--no-tests" in sys.argv:
            run_tests = False

    else:
        cflags += " " + CFLAGS_RELEASE

    build(cflags, run_tests)


if __name__ == "__main__":
    main()
