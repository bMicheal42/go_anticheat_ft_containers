
//================================== LIST ======================================
bool iseven(int n) { return !(n & 1); }
bool b10(int n) { return n > 10; }
bool ab4(int a, int b) { return a + b == 4; }

void    test_list() {
  ft::list<int> fl1;
  ft::list<int> fl2(10, 404);

  int a1[4] = {0, 8, 9, 7};
  ft::list<int> fl3(a1, a1 + 4);
  ft::list<int> fl4(fl3);
  fl1 = fl2;
  fl1.empty();
  fl1.size();
  fl1.max_size();
  fl1.front();
  fl1.push_back(24);
  int a2[5] = {1, 2, 3, 4, 5};
  fl1.assign(a2, a2 + 5);
  fl1.assign(10, -5);
  fl1.push_front(999);
  fl1.push_back(-999);
  fl1.pop_front();
  fl1.pop_back();
  ft::list<int>::iterator fit1 = fl1.begin();
  fl1.insert(fit1, 90);
  fit1 = fl1.end();
  --fit1;
  fl1.insert(fit1, 4, 88);
  fit1 = fl1.begin();
  int a3[3] = {4, 0, 1};
  fl1.insert(fit1, a3, a3 + 3);
  fit1 = fl1.begin();
//  std::advance(fit1, 3);
  fl1.erase(fit1);
  fit1 = fl1.end();
//  std::advance(fit1, -3);
  fl1.erase(fit1, fl1.end());
  fl1.swap(fl2);
  fl2.resize(5);
  fl2.resize(10, 789);
  fl1.clear();
  ft::list<int> fl5;
  for (int i = 1; i <= 4; ++i) {
	fl5.push_back(i);
  }
  fit1 = fl2.begin();
//  std::advance(fit1, 2);
  fl2.splice(fit1, fl5);
  fl5.push_back(9); fl5.push_back(8); fl5.push_back(9);
  fit1 = fl2.end();
  ft::list<int>::iterator fit2 = fl5.begin();
  ++fit2;
  fl2.splice(fit1, fl5, fit2);
  fl5.push_back(1); fl5.push_back(1);
  fit1 = fl5.begin();
  ++fit1;
  fit2 = fit1;
//  std::advance(fit2, 2);
  fl2.splice(fl2.begin(), fl5, fit1, fit2);
  fl2.remove(999);
  fl2.remove(789);
  fl2.remove_if(iseven);
  fl2.remove_if(b10);
  fl2.unique();
  fl2.unique(ab4);

  int a4[10] = {4, 0, 7, 3, -5, 9, 83, -4, -5, 1};
  ft::list<int> fl6(a4, a4 + 10);
  fl6.sort();
  int a5[4] = {-7, 4, 13, 65};
  ft::list<int> fl7(a5, a5 + 4);
  fl6.merge(fl7);
  fl6.reverse();
};

//=================================== MAP ======================================
void    test_map() {
  typedef std::pair<int, std::string> test_pair;

  ft::map<int, std::string> fm1;
  test_pair a1[4] = {test_pair(0, "a"),
                     test_pair(1, "b"),
                     test_pair(2, "c"),
                     test_pair(3, "d")};
  ft::map<int, std::string> fm2(a1, a1 + 4);
  ft::map<int, std::string> fm3(fm2);
  fm1 = fm3;
  ft::map<int, std::string>().empty();
  fm3.empty();
  fm3.size();
  fm3.max_size();
  fm3[2];
  fm3[-1];
  std::pair<ft::map<int, std::string>::iterator, bool> fmr3 = fm3.insert(test_pair(99, "ff"));
  std::cout << (*fmr3.first).first << ", " << fmr3.second << std::endl;
  test_pair a2[3] = {test_pair(7, "q"), test_pair(7, "w"), test_pair(8, "e")};
  fm3.insert(a2, a2 + 3);
  fm3.erase(fm3.begin());
  fm3.erase(7);
  ft::map<int, std::string>::iterator fit1 = fm3.begin();
  ++fit1;
  ft::map<int, std::string>::iterator fit2 = fit1;
  ++fit2; ++fit2;
  fm3.erase(fit1, fit2);
  fm3.swap(fm2);
  fm2.clear();
  fm3.key_comp()(5, 5);
  fm3.value_comp()(test_pair(5, "a"), test_pair(5, "b"));
  fm3.count(3);
  std::cout << (*fm3.find(2)).second << (fm3.find(7) == fm3.end());
  std::cout << fm3.lower_bound(2)->second;
  std::cout << fm3.upper_bound(2)->second;
  std::cout << fm3.equal_range(2).second->second << (fm3.equal_range(9).first == fm3.equal_range(9).second && fm3.equal_range(9).second == fm3.end());

};

//================================ Queue =======================================
void	test_queue() {
  {
	ft::queue<int> MyQueue;
	MyQueue.empty();
	MyQueue.size();
  }
  {
	ft::queue<int> MyQueue;
	MyQueue.empty();
	MyQueue.push(88);
	MyQueue.back();
	MyQueue.push(44);
	MyQueue.back();
	MyQueue.size();
	MyQueue.pop();
  }
};

//============================== STACK =========================================
void    test_stack() {
  ft::stack<int> def;
  def.empty();
  def.size();
  for (int i = 0; i < 10; ++i) {
	def.push(i);
  }
  for (int i = 0; i < 10; ++i) {
	def.top();
	def.pop();
  }
};
//============================== VECTOR ========================================
void    test_vector() {
  ft::vector<int> fv1;
  ft::vector<int> fv2(10, 404);

  int a1[4] = {0, 8, 9, 7};
  ft::vector<int> fv3(a1, a1 + 4);
  ft::vector<int> fv4(fv3);
  fv1 = fv2;
  fv1.empty();
  fv1.size();
  fv1.max_size();
  fv1.capacity();
  fv1.reserve(50);
  fv1.capacity();
  fv1[2];
  fv1.at(1);
  try {
	fv1.at(40);
  } catch (std::exception&) {
  }
  fv1.front();
  fv1.push_back(24);
  fv1.back();
  int a2[5] = {1, 2, 3, 4, 5};
  fv1.assign(a2, a2 + 5);
  fv1.assign(10, -5);
  fv1.push_back(-999);
  fv1.pop_back();
  ft::vector<int>::iterator fit1 = fv1.begin();
  fv1.insert(fit1, 90);
  fit1 = fv1.end();
  --fit1;
  fv1.insert(fit1, 4, 88);
  fit1 = fv1.begin();
  int a3[3] = {4, 0, 1};
  fv1.insert(fit1, a3, a3 + 3);
  fit1 = fv1.begin();
  fv1.erase(fit1);
  fit1 = fv1.end();
//  std::advance(fit1, -3);
  fv1.erase(fit1, fv1.end());
  fv1.swap(fv2);
  fv2.resize(5);
  fv2.resize(10, 789);
  fv1.clear();
};

//==============================================================================
int main() {
  test_map();
  test_list();
  test_queue();
  test_stack();
  test_vector();

  return 0;
}
