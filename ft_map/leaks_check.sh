#! /bin/zsh

  clang++ -Wall -Wextra -Werror ft_map_test.cpp -o user_bin_for_leaks &&
  valgrind ./user_bin_for_leaks && rm user_bin_for_leaks
