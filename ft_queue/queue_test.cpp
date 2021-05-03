#include <iostream>
#include <queue>

#include "ft_queue.hpp"

void member_func_test() {

	std::queue< int > std_queue;
	ft::Queue< int >   ft_queue;

	std::cout << "\nEmpty()" << std::endl;
	std::cout << "std: " << std_queue.empty() << std::endl;
	std::cout << "ft : " << ft_queue.empty()  << std::endl;
	std::cout << std::endl;

	std::cout << "\nsize()" << std::endl;
	std::cout << "std: " << std_queue.size() << std::endl;
	std::cout << "ft : " << ft_queue.size()  << std::endl;
	std::cout << std::endl;

	std::cout << "\npush(10)" << std::endl;
	std_queue.push(10);
	ft_queue.push(10);
	std::cout << std::endl;

	std::cout << "\nfront()" << std::endl;
	std::cout << "std: " << std_queue.front() << std::endl;
	std::cout << "ft : " << ft_queue.front()  << std::endl;
	std::cout << std::endl;

	std::cout << "\nback()" << std::endl;
	std::cout << "std: " << std_queue.back() << std::endl;
	std::cout << "ft : " << ft_queue.back()  << std::endl;
	std::cout << std::endl;

	std::cout << "\npush(20)" << std::endl;
	std_queue.push(20);
	ft_queue.push(20);
	std::cout << std::endl;

	std::cout << "\nEmpty()" << std::endl;
	std::cout << "std: " << std_queue.empty() << std::endl;
	std::cout << "ft : " << ft_queue.empty()  << std::endl;
	std::cout << std::endl;

	std::cout << "\nsize()" << std::endl;
	std::cout << "std: " << std_queue.size() << std::endl;
	std::cout << "ft : " << ft_queue.size()  << std::endl;
	std::cout << std::endl;

	std::cout << "\nfront()" << std::endl;
	std::cout << "std: " << std_queue.front() << std::endl;
	std::cout << "ft : " << ft_queue.front()  << std::endl;
	std::cout << std::endl;

	std::cout << "\nback()" << std::endl;
	std::cout << "std: " << std_queue.back() << std::endl;
	std::cout << "ft : " << ft_queue.back()  << std::endl;
	std::cout << std::endl;
}

void relational_operators_test() {

	std::queue<int > std1;
	for (int i = 0; i < 10; ++i) {
		std1.push(10);
	}

	std::queue<int > std2;
	for (int i = 0; i < 10; ++i) {
		std1.push(5);
	}

	ft::Queue<int > ft1;
	for (int i = 0; i < 10; ++i) {
		ft1.push(10);
	}

	ft::Queue<int > ft2;
	for (int i = 0; i < 10; ++i) {
		ft2.push(5);
	}

	std::cout << "\n==" << std::endl;
	std::cout << "std: " << (std1 == std1) << std::endl;
	std::cout << "ft: " <<   (ft1 == ft1) << std::endl;
	std::cout << "std: " << (std1 == std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 == ft2) << std::endl;

	std::cout << "\n!=" << std::endl;
	std::cout << "std: " << (std1 != std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 != ft2) << std::endl;
	std::cout << "std: " << (std1 != std1)  << std::endl;
	std::cout << "ft: " <<   (ft1 != ft1) << std::endl;
	std::cout << std::endl;

	std::cout << "\n<" << std::endl;
	std::cout << "std: " << (std1 < std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 < ft2) << std::endl;
	std::cout << "std: " << (std1 < std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 < ft2) << std::endl;
	std::cout << std::endl;

	std::cout << "\n>" << std::endl;
	std::cout << "std: " << (std1 > std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 > ft2) << std::endl;
	std::cout << "std: " << (std1 > std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 > ft2) << std::endl;
	std::cout << std::endl;

	std::cout << "\n<=" << std::endl;
	std::cout << "std: " << (std1 <= std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 <= ft2) << std::endl;
	std::cout << "std: " << (std1 <= std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 <= ft2) << std::endl;
	std::cout << std::endl;

	std::cout << "\n>=" << std::endl;
	std::cout << "std: " << (std1 >= std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 >= ft2) << std::endl;
	std::cout << "std: " << (std1 >= std2)  << std::endl;
	std::cout << "ft: " <<   (ft1 >= ft2) << std::endl;
	std::cout << std::endl;
}

int main()
{
	member_func_test();
	relational_operators_test();
	return 0;
}
