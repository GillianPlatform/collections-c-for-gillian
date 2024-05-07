#/bin/bash

set -e

find . -name \*.csm -type f -delete
find . -name \*.i -type f -delete
find . -name \*.gil -type f -delete
find . -name \*.deps -type f -delete
rm -rf $(find . -name \*.dSYM -type d | xargs);
find . -name \*.plist -type f -delete
find . -name \*.yml -type f -delete
rm -f *.log

find . -name \*.bc -type f -delete
rm -rf klee-out-*
rm -f klee_output.log
rm -rf klee-last
rm -rf klee_build
