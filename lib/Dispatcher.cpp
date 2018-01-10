#include "Dispatcher.h"
#include "Log.h"
#include <algorithm>
#include <iostream>

namespace pacxxd {
void Dispatcher::register_handler(std::string opcode,
                                  std::function<void(void)> handler) {
  _functions[opcode] = handler;
}

void Dispatcher::register_end(std::string opcode) { _end_message = opcode; }

bool Dispatcher::dispatch(std::string opcode) {
  __message("dispatching ", opcode);
  if (_functions.find(opcode) != _functions.end()){
    _functions[opcode]();
  }
  else {
    std::cout << "DISPATCHER ERROR: " << opcode << "not registerd" << std::endl;
  }
  return !std::equal(opcode.begin(), opcode.end(), _end_message.begin());
}
} // namespace pacxxd