#! /bin/zsh

rm logs/user.output
rm logs/std.output
rm -rf logs
mkdir logs

  clang++ -Wall -Wextra -Werror -fsanitize=address ft_stack_test.cpp -o logs/user_bin &&
  ./logs/user_bin > logs/user.output &&
  clang++ -Wall -Wextra -Werror -fsanitize=address std_stack_test.cpp -o logs/bin &&
  ./logs/bin > logs/std.output &&
  diff logs/user.output logs/std.output
