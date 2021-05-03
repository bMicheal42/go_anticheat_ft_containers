#! /bin/zsh

  clang++ -Wall -Wextra -Werror ft_stack_test.cpp -o user_bin_for_leaks &&
  valgrind ./user_bin_for_leaks
