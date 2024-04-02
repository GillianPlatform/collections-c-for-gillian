#!/bin/bash

set -e

./clean.sh

TESTS_DIR="gillian-cbmc/bugs"
LIB_HEADERS_DIR="libs/bugged/include"
LIB_SRC_DIR="libs/bugged"
UTILS_HEADERS_DIR="gillian-cbmc/utils"
UTILS_SRC_DIR="gillian-cbmc/utils"

echo "Running buggy tests using Kanillian..."
kanillian bulk-wpst ${TESTS_DIR} -I ${LIB_HEADERS_DIR} -I ${UTILS_HEADERS_DIR} \
    -S ${LIB_SRC_DIR} -S ${UTILS_SRC_DIR} --ignore-undef --allocated-functions
