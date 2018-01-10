#pragma once

#include <functional>
#include <map>
#include <string>

namespace pacxxd {
class Dispatcher {
public:
  Dispatcher() = default;
  virtual ~Dispatcher() = default;

  void register_end(std::string opcode);
  void register_handler(std::string opcode, std::function<void(void)> handler);
  bool dispatch(std::string opcode);

private:
  std::map<std::string, std::function<void(void)>> _functions;
  std::string _end_message;
};
} // namespace pacxxd