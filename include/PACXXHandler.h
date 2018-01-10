#pragma once

#include <pacxx/Executor.h>
#include <pacxx/detail/KernelConfiguration.h>
#include <pacxx/detail/IRRuntime.h>
#include <pacxx/detail/cuda/CUDARuntime.h>
#include <pacxx/detail/native/NativeRuntime.h>
#include <pacxx/detail/rocm/HIPRuntime.h>
#include <vector>
#include <exception>
#include <memory>


namespace pacxxd {
class PACXXHandler {
public:
  PACXXHandler() = default;
  virtual ~PACXXHandler() = default;

  template <typename... Ts>
  void createExecutor(pacxx::v2::IRRuntime::RuntimeKind type, Ts&&... args) {
    using namespace pacxx::v2; 

    std::unique_ptr<IRRuntime> rt;

    switch (type) {
    case IRRuntime::RK_CUDA:
      rt.reset(new CUDARuntime(std::forward<Ts>(args)...));
      break;
    case IRRuntime::RK_Native:
      rt.reset(new NativeRuntime(std::forward<Ts>(args)...));
      break;
    case IRRuntime::RK_HIP:
      rt.reset(new HIPRuntime(std::forward<Ts>(args)...));
      break;
    default:
      throw std::logic_error("no such rutime");
    }

    _exec.reset(new Executor(std::move(rt)));
  }

  pacxx::v2::Executor& getExecutor();

  void setLLVMBytes(const std::vector<char> &bytes);

  void* allocateMemory(size_t size);
  void freeMemory(void* ptr);

  void uploadData(void* dest, const void* src, size_t size);
  void downloadData(void* dest, const void* src, size_t size);

  void launchKernel(const std::string& name, const void* args, size_t size, pacxx::v2::KernelConfiguration config);

private:
    std::unique_ptr<pacxx::v2::Executor> _exec;
    std::map<void*, pacxx::v2::RawDeviceBuffer*> _memory;
};
} // namespace pacxxd