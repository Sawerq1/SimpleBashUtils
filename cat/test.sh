#!/bin/bash

S21_CAT_EXEC="./s21_cat"

TEST_DIR="test_dir"
mkdir -p "$TEST_DIR"
TEST_SUCCESS=0

FLAGS=("-s" "-n" "-e" "-t" "-v" "-b" "-n -s" "-n -s -b" "-e -n" "-v -s -n" "-s -b" "-e -s")
FLAGS+=("-t -b" "-n -t" "-v -b" "-n -e" "-s -t" "-e -t -b" "-v -n -t -e -s" "-e -s -n" "-n -b" "-e -t")

cp file1 "$TEST_DIR/file1"
echo "Test1" > "$TEST_DIR/test1.txt"
echo "Another line" > "$TEST_DIR/test2.txt"
echo -e "Line\t1\nLine 2\nLine 3" > "$TEST_DIR/test3.txt"
: > "$TEST_DIR/empty.txt"

run_test_case() {
    TEST_DESC=$1
    CAT_ARGS=$2
    shift 2
    cat $CAT_ARGS "$@" > "$TEST_DIR/cat_output.txt"
    $S21_CAT_EXEC $CAT_ARGS "$@" > "$TEST_DIR/s21_cat_output.txt"

    DIFF=$(diff "$TEST_DIR/cat_output.txt" "$TEST_DIR/s21_cat_output.txt")
    if [ "$DIFF" == "" ]; then
        ((SUCCESS++))
    fi
}


for flag in "${FLAGS[@]}"; do
    SUCCESS=0
    run_test_case "Single file" "$flag" "$TEST_DIR/test1.txt"
    run_test_case "Multiple files" "$flag" "$TEST_DIR/test1.txt" "$TEST_DIR/test2.txt"
    run_test_case "Empty file" "$flag" "$TEST_DIR/empty.txt"
    run_test_case "File with multiple lines" "$flag" "$TEST_DIR/test3.txt"
    run_test_case "Non-existent file" "$flag" "no.txt" 2>/dev/null
    if [[ "$SUCCESS" -eq 5 ]]; then
        ((TEST_SUCCESS++))
        echo "Tests with flags" "$flag"": success"
    else
        echo "Tests with flags" "$flag"": fail" $SUCCESS
    fi
done


rm -rf "$TEST_DIR"

if [[ "$TEST_SUCCESS" -eq "${#FLAGS[@]}" ]]; then
    echo "TESTING SUCCESS"
else
    echo "TESTING FAIL: success tests"
    echo "$TEST_SUCCESS" "from" "${#FLAGS[@]}"
fi
