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

# INC_8, INC_16 tests
add_executable(test-inc test-inc.c)
target_link_libraries(test-inc isa)

add_test(inc_8_norm test-inc 1 0 0)
add_test(inc_8_half_carry test-inc 1 15 32)
add_test(inc_8_zero test-inc 1 255 160)

add_test(inc_16_norm test-inc 2 357 0)
add_test(inc_16_half_carry test-inc 2 255 0)
add_test(inc_16_zero test-inc 2 65535 0)

# DEC_8, DEC_16 tests
add_executable(test-dec test-dec.c)
target_link_libraries(test-dec isa)

add_test(dec_8_norm test-dec 1 25 64)
add_test(dec_8_half_carry test-dec 1 0 96)
add_test(dec_8_zero test-dec 1 1 192)

add_test(dec_16_norm test-dec 2 455 0)
add_test(dec_16_half_carry test-dec 2 0 0)
add_test(dec_16_zero test-dec 2 1 -)

# ADD_16 tests
add_executable(test-add16 test-add16.c)
target_link_libraries(test-add16 isa)

add_test(add_16_norm test-add16 768 15 0)
add_test(add_16_half_carry test-add16 255 255 32)
add_test(add_16_carry test-add16 65535 1 48)

# PUSH and POP tests
add_executable(test-pushpop test-pushpop.c)
target_link_libraries(test-pushpop isa)

add_test(push_single test-pushpop 1 37)
add_test(push_multiple test-pushpop 1 37 275 1234)