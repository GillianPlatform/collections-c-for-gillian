#!/bin/bash

set -e

./clean.sh

TESTS_DIR="gillian-compcert/bugs"
LIB_HEADERS_DIR="libs/bugged/include"
LIB_SRC_DIR="libs/bugged"
UTILS_HEADERS_DIR="gillian-compcert/utils"
UTILS_SRC_DIR="gillian-compcert/utils"

echo "Running buggy tests using Gillian-C..."
gillian-c bulk-wpst ${TESTS_DIR} -I ${LIB_HEADERS_DIR} -I ${UTILS_HEADERS_DIR} \
    -S ${LIB_SRC_DIR} -S ${UTILS_SRC_DIR} --ignore-undef --allocated-functions
