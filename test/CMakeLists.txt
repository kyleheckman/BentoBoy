project(test_scripts
    LANGUAGES C)
set(TEST_SCRIPTS test-ld8.c)
add_executable(${PROJECT_NAME} ${TEST_SCRIPTS})
target_link_libraries(${PROJECT_NAME} isa)

# LD_8 tests, reg->reg
add_test(ld_8_valid_1 test_scripts "1 35")    # accepts values in valid range 0-255
add_test(ld_8_valid_2 test_scripts "1 170")
add_test(ld_8_negative test_scripts "1 -100") # accepts negative values, interpretting as unsigned
add_test(ld_8_large test_scripts "1 1234")    # accepts values larger than 255, will truncate to fit

# LD_16 tests
add_test(ld_16_imm test_scripts "2 1234")