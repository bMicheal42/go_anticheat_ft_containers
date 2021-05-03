#! /bin/zsh

  clang++ ft_multiset_test.cpp -o user_bin_for_leaks &&
  valgrind ./user_bin_for_leaks
