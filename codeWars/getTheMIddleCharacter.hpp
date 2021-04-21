std::string get_middle(std::string input) {
  return input.size() % 2 == 0 ? input.substr(input.size() / 2 - 1, 2)
                               : input.substr(input.size() / 2, 1);
}