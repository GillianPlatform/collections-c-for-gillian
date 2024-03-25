#!/bin/bash

set -e

./clean.sh

TESTS_DIR="gillian/bugs"
LIB_HEADERS_DIR="libs/bugged/include"
LIB_SRC_DIR="libs/bugged"
UTILS_HEADERS_DIR="gillian/utils"
UTILS_SRC_DIR="gillian/utils"

echo "Running buggy tests using Gillian-C..."
gillian-c bulk-wpst ${TESTS_DIR} -I ${LIB_HEADERS_DIR} -I ${UTILS_HEADERS_DIR} \
    -S ${LIB_SRC_DIR} -S ${UTILS_SRC_DIR} --ignore-undef --allocated-functions
