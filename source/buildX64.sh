#!/bin/bash
mkdir -p libs/_tmpBuild
make arch=X64 dbg=1 clean
make arch=X64 dbg=1
/bin/cp -rf libs/_tmpBuild/raumkernel.so libs/linux_x64/raumkernel.so
make arch=X64 dbg=1 clean
