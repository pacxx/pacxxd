#include "PACXXHandler.h"

#include <vector>

#include <pacxx/Executor.h>
#include <pacxx/ModuleLoader.h>
#include <pacxx/detail/IRRuntime.h>
#include <pacxx/detail/common/ExecutorHelper.h>

using namespace pacxx::v2; 

namespace pacxxd {

void PACXXHandler::setLLVMBytes(const std::vector<char>& bytes) {
    initializeModule(*_exec, bytes.data(), bytes.size());
}

pacxx::v2::Executor& PACXXHandler::getExecutor() {
  return *_exec;
}

void* PACXXHandler::allocateMemory(size_t size){
  auto& DB = _exec->allocateRaw(size);
  void* ptr = DB.get(); 
  _memory[ptr] = &DB;
  return ptr;
}

void PACXXHandler::freeMemory(void* ptr){
  auto DB = _memory[ptr];
  if (DB){
    _exec->freeRaw(*DB);
    _memory[ptr] = nullptr;
  }
}

void PACXXHandler::uploadData(void* dest, const void* src, size_t size){
  auto DB = _memory[dest];
  DB->upload(src, size);
}

void PACXXHandler::downloadData(void* dest, const void* src, size_t size){
  auto DB = _memory[const_cast<void*>(src)];
  DB->download(dest, size);
}

void PACXXHandler::launchKernel(const std::string& name, const void* args, size_t size, pacxx::v2::KernelConfiguration config){
  _exec->run_by_name(name, args, size, config);
}

} // namespace pacxxd