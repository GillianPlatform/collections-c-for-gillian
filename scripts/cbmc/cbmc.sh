LIB_DIR="../../libs/fixed"
INCLUDE_DIR="$LIB_DIR/include"
TEST_FOLDER="../../gillian-cbmc/normal"
UTILS_FOLDER="../../gillian-cbmc/utils"

ARGS="$LIB_DIR/*.c $UTILS_FOLDER/utils.c -I$INCLUDE_DIR -I$UTILS_FOLDER --bounds-check --pointer-check --div-by-zero-check --pointer-primitive-check --havoc-undefined-functions --unwind 10 --os macos --arch x86_64 --function main --drop-unused-functions --timestamp wall --trace --beautify"


cbmc $TEST_FOLDER/$1 $ARGS