project(test_scripts
    LANGUAGES C)

    # LD_8 tests
add_executable(test-ld8 test-ld8.c)
target_link_libraries(test-ld8 isa)

add_test(ld_8_reg_1 test-ld8 1 35)    # test copying value from reg to reg
add_test(ld_8_reg_2 test-ld8 1 170)
add_test(ld_8_to_mem test-ld8 2 100)    # test saving value from reg to memory
add_test(ld_8_imm test-ld8 3 96)        # test storing immediate value to reg
add_test(ld_8_from_mem test-ld8 4 177)    # test copying value from memory to reg

# LD_16 tests
add_executable(test-ld16 test-ld16.c)
target_link_libraries(test-ld16 isa)

add_test(ld_16_imm test-ld16 1234)      # test saving immediate value to reg

