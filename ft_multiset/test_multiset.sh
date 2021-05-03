#! /bin/zsh

rm logs/user.output | echo -n
rm logs/std.output  | echo -n
rm -rf logs         | echo -n
mkdir logs          | echo -n

  clang++ -fsanitize=address ft_multiset_test.cpp -o logs/user_bin &&
  ./logs/user_bin > logs/user.output &&
  clang++ -fsanitize=address std_multiset_test.cpp -o logs/bin &&
  ./logs/bin > logs/std.output &&
  diff logs/user.output logs/std.output
