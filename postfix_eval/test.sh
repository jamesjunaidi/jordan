#!/bin/bash

# Safer execution
# -e: exit immediately if a command fails
# -E: Safer -e option for traps
# -u: fail if a variable is used unset
# -o pipefail: exit immediately if command in a pipe fails
#set -eEuo pipefail
# -x: print each command before executing (great for debugging)
#set -x

# Convenient values
SCRIPT_NAME=$(basename $BASH_SOURCE)

# Default program values
EXEC="${PWD}/postfix_eval"
TEST_CASE="all"

#
# Logging helpers
#
log() {
    echo -e "${*}"
}
info() {
    log "Info: ${*}"
}
warning() {
    log "Warning: ${*}"
}
error() {
    log "Error: ${*}"
}
die() {
    error "${*}"
    exit 1
}

#
# Line comparison
#
select_line() {
    # 1: string
    # 2: line to select
    echo "$(echo "${1}" | sed "${2}q;d")"
}

fail() {
    # 1: got
    # 2: expected
    log "Fail: got '${1}' but expected '${2}'"
}

pass() {
    # got
    log "Pass: ${1}"
}

compare_lines() {
    # 1: output
    # 2: expected
    # 3: score (output)
    declare -a output_lines=("${!1}")
    declare -a expect_lines=("${!2}")
    local __score=$3
    local partial="0"

    # Amount of partial credit for each correct output line
    local step=$(bc -l <<< "1.0 / ${#expect_lines[@]}")

    # Compare lines, two by two
    for i in ${!output_lines[*]}; do
        # The right hand expression of pattern matching must be unquoted
        if [[ "${output_lines[${i}]}" =~ ${expect_lines[${i}]} ]]; then
            pass "${output_lines[${i}]}"
            partial=$(bc <<< "${partial} + ${step}")
        else
            fail "${output_lines[${i}]}" "${expect_lines[${i}]}" ]]
        fi
    done

    # Return final score
    eval ${__score}="'${partial}'"
}

#
# Run generic test case
#
run_test() {

    # These are global variables after the test has run so clear them out now
    unset STDOUT STDERR RET

    # Create temp files for getting stdout and stderr
    local outfile=$(mktemp)
    local errfile=$(mktemp)

    bash -c "echo -e \"${1}\" | ${EXEC}" \
        >${outfile} 2>${errfile}

    # Get the return status, stdout and stderr of the test case
    RET="${?}"
    STDOUT=$(cat "${outfile}")
    STDERR=$(cat "${errfile}")

    # Clean up temp files
    rm -f "${outfile}"
    rm -f "${errfile}"
}

#
# Test cases
#
TEST_CASES=()

## Bye
TEST_CASES+=("bye")
bye() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test ""

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("Bye!")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}


## Simple addition int
TEST_CASES+=("oneline_add")
oneline_add() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1 2 +"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("3")
    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Simple subtract double
TEST_CASES+=("oneline_sub")
oneline_sub() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "1 2.5 -"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("-1.5")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Simple mult int double
TEST_CASES+=("oneline_mult")
oneline_mult() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "12 3.4 *"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("40.8")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Simple div int double
TEST_CASES+=("oneline_div")
oneline_div() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "12 3.4 /"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("3.52941")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Two ops: add, sub
TEST_CASES+=("oneline_2ops_addsub")
oneline_2ops_addsub() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "48.3 29.3 + 5 -"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("72.6")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Two ops: mult, div
TEST_CASES+=("oneline_2ops_muldiv")
oneline_2ops_muldiv() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "48.3 29.3 * 5 /"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("283.038")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Many ops
TEST_CASES+=("oneline_manyops")
oneline_manyops() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "15 7 1 1 + - / 3 * 2 1 1 + + -"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    local corr_array=()
    corr_array+=("5")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Many lines
TEST_CASES+=("manylines")
manylines() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "6 28 / 5 +\n4 24 + 3 51 1 - * +\n9.8 7 2.3521 - *\n4 2.3 + 3 52 12.023 - * +"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    line_array+=("$(select_line "${STDOUT}" "2")")
    line_array+=("$(select_line "${STDOUT}" "3")")
    line_array+=("$(select_line "${STDOUT}" "4")")
    local corr_array=()
    corr_array+=("5.21429")
    corr_array+=("178")
    corr_array+=("45.5494")
    corr_array+=("126.231")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Inval expr alone
TEST_CASES+=("oneline_inval_expr")
oneline_inval_expr() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "394.2 3"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: invalid expression")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Unknown symbol 1 ('$')
TEST_CASES+=("oneline_unknown_symbol_1")
oneline_unknown_symbol_1() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "394.2 3 $"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: unknown symbol '\\$'")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Unknown symbol 2 ('++')
TEST_CASES+=("oneline_unknown_symbol_2")
oneline_unknown_symbol_2() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "394.2 3 ++"

    local line_array=()
    line_array+=("$(select_line "${STDERR}" "1")")
    local corr_array=()
    corr_array+=("Error: unknown symbol '\+\+'")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Inval expr multiline
TEST_CASES+=("manylines_inval_expr")
manylines_inval_expr() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "5 7 + 6 2 - *\n54 52 &\n56.3 4 * 2\n3 4 + 2 * 7 /"

    local line_array=()
    line_array+=("$(select_line "${STDOUT}" "1")")
    line_array+=("$(select_line "${STDERR}" "1")")
    line_array+=("$(select_line "${STDERR}" "2")")
    line_array+=("$(select_line "${STDOUT}" "2")")
    local corr_array=()
    corr_array+=("48")
    corr_array+=("Error: unknown symbol '&'")
    corr_array+=("Error: invalid expression")
    corr_array+=("2")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}

## Error code 0
TEST_CASES+=("error_code")
error_code() {
    log "--- Running test case: ${FUNCNAME} ---"
    run_test "12 3.4 /"

    local line_array=()
    line_array+=("Return code: '${RET}'")
    local corr_array=()
    corr_array+=("Return code: '0'")

    local score
    compare_lines line_array[@] corr_array[@] score
    log "${score}"
}


#
# Main functions
#
parse_argvs() {
    local OPTIND opt

    while getopts "h?s:t:" opt; do
        case "$opt" in
        h|\?)
            echo "${SCRIPT_NAME}: [-s <exec_path>] [-t <test_case>]" 1>&2
            exit 0
            ;;
        s)  EXEC="$(readlink -f ${OPTARG})"
            ;;
        t)  TEST_CASE="${OPTARG}"
            ;;
        esac
    done
}

check_vals() {
    # Check exec path
    [[ -x ${EXEC} ]] || \
        die "Cannot find executable '${EXEC}'"

    # Check test case
    [[ " ${TEST_CASES[@]} all " =~ " ${TEST_CASE} " ]] || \
        die "Cannot find test case '${TEST_CASE}'"
}

grade() {
    # Make testing directory
    local tmpdir=$(mktemp -d --tmpdir=.)
    cd ${tmpdir}

    # Run test case(s)
    if [[ "${TEST_CASE}" == "all" ]]; then
        # Run all test cases
    for t in "${TEST_CASES[@]}"; do
        ${t}
            log "\n"
    done
    else
        # Run specific test case
        ${TEST_CASE}
    fi

    # Cleanup testing directory
    cd ..
    rm -rf "${tmpdir}"
}

parse_argvs "$@"
check_vals
grade

