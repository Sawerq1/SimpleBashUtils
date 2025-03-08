#!/bin/bash

TEST_FILE="test_file.txt"
ORIGINAL_GREP="grep"
CUSTOM_GREP="./s21_grep"

echo -e "Hello World\nThis is a test file.\nGrep is powerful.\nGoodbye World" > $TEST_FILE

run_test() {
    local pattern="$1"
    echo "Testing pattern: '$pattern'"

    echo "Original grep output:"
    $ORIGINAL_GREP "$pattern" $TEST_FILE

    echo "Custom grep output:"
    $CUSTOM_GREP "$pattern" $TEST_FILE

    echo "-----------------------------------"
}

run_test_with_flags() {
    local flag="$1"
    local pattern="$2"
    echo "Testing pattern: '$pattern' with flag: '$flag'"

    echo "Original grep output:"
    $ORIGINAL_GREP $flag "$pattern" $TEST_FILE

    echo "Custom grep output:"
    $CUSTOM_GREP $flag "$pattern" $TEST_FILE

    echo "-----------------------------------"
}

run_test "Hello"
run_test "test"
run_test "Grep"
run_test "World"
run_test "not_found"

run_test_with_flags "-e" "Hello"
run_test_with_flags "-i" "hello"
run_test_with_flags "-v" "Hello"
run_test_with_flags "-c" "World"
run_test_with_flags "-l" "test"
run_test_with_flags "-n" "World"

rm $TEST_FILE

echo "Tests completed."
