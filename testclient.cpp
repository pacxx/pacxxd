#include <asio.hpp>
#include <iostream>
#include <array>

#include <pacxx/detail/IRRuntime.h>

const char* module = R"LLVM(
; ModuleID = 'kernel.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }
%class.anon = type { i64, i32*, i32*, i32* }

$_ZN5pacxx2v25range10get_globalEj = comdat any

$_ZN5pacxx2v25range13get_global_idEj = comdat any

@_ZN4llvm29VerifyEnableABIBreakingChecksE = weak hidden global i32* @_ZN4llvm23EnableABIBreakingChecksE, align 8
@_ZN4llvm23EnableABIBreakingChecksE = external global i32, align 4
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_vadd_low_level.cpp, i8* null }]
@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external hidden global i8

; Function Attrs: noinline uwtable
define internal void @_GLOBAL__sub_I_vadd_low_level.cpp() #0 section ".text.startup" {
entry:
  call void @__cxx_global_var_init()
  ret void
}

; Function Attrs: noinline uwtable
define internal void @__cxx_global_var_init() #0 section ".text.startup" {
entry:
  call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* @_ZStL8__ioinit)
  %0 = call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i32 0, i32 0), i8* @__dso_handle) #3
  ret void
}

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) unnamed_addr #1

; Function Attrs: nounwind
declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) unnamed_addr #2

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) #3

; Function Attrs: noinline nounwind uwtable
define void @"_ZN5pacxx2v213genericKernelIZL19test_vadd_low_leveliPPcE3$_0EEvT_"(i64 %callable.coerce0, i32* %callable.coerce1, i32* %callable.coerce2, i32* %callable.coerce3) #4 !pacxx.target !4 !kernel_arg_addr_space !5 !kernel_arg_access_qual !6 !kernel_arg_type !7 !kernel_arg_base_type !7 !kernel_arg_type_qual !8 {
entry:
  %callable = alloca %class.anon, align 8
  %0 = getelementptr inbounds %class.anon, %class.anon* %callable, i32 0, i32 0
  store i64 %callable.coerce0, i64* %0, align 8
  %1 = getelementptr inbounds %class.anon, %class.anon* %callable, i32 0, i32 1
  store i32* %callable.coerce1, i32** %1, align 8
  %2 = getelementptr inbounds %class.anon, %class.anon* %callable, i32 0, i32 2
  store i32* %callable.coerce2, i32** %2, align 8
  %3 = getelementptr inbounds %class.anon, %class.anon* %callable, i32 0, i32 3
  store i32* %callable.coerce3, i32** %3, align 8
  call void @"_ZN5pacxx2v210kernelBodyIRZL19test_vadd_low_leveliPPcE3$_0EEvOT_"(%class.anon* dereferenceable(32) %callable)
  ret void
}

; Function Attrs: noinline optnone uwtable
define internal void @"_ZN5pacxx2v210kernelBodyIRZL19test_vadd_low_leveliPPcE3$_0EEvOT_"(%class.anon* dereferenceable(32) %callable) #5 {
entry:
  %callable.addr = alloca %class.anon*, align 8
  %thread = alloca %"class.std::ios_base::Init", align 1
  store %class.anon* %callable, %class.anon** %callable.addr, align 8
  %0 = load %class.anon*, %class.anon** %callable.addr, align 8
  call void @"_ZZL19test_vadd_low_leveliPPcENK3$_0clERN5pacxx2v25rangeE"(%class.anon* %0, %"class.std::ios_base::Init"* dereferenceable(1) %thread)
  ret void
}

; Function Attrs: noinline optnone uwtable
define internal void @"_ZZL19test_vadd_low_leveliPPcENK3$_0clERN5pacxx2v25rangeE"(%class.anon* %this, %"class.std::ios_base::Init"* dereferenceable(1) %config) #5 align 2 {
entry:
  %this.addr = alloca %class.anon*, align 8
  %config.addr = alloca %"class.std::ios_base::Init"*, align 8
  %i = alloca i32, align 4
  store %class.anon* %this, %class.anon** %this.addr, align 8
  store %"class.std::ios_base::Init"* %config, %"class.std::ios_base::Init"** %config.addr, align 8
  %this1 = load %class.anon*, %class.anon** %this.addr, align 8
  %0 = load %"class.std::ios_base::Init"*, %"class.std::ios_base::Init"** %config.addr, align 8
  %call = call i32 @_ZN5pacxx2v25range10get_globalEj(%"class.std::ios_base::Init"* %0, i32 0)
  store i32 %call, i32* %i, align 4
  %1 = load i32, i32* %i, align 4
  %conv = sext i32 %1 to i64
  %2 = getelementptr inbounds %class.anon, %class.anon* %this1, i32 0, i32 0
  %3 = load i64, i64* %2, align 8
  %cmp = icmp ult i64 %conv, %3
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
 %4 = getelementptr inbounds %class.anon, %class.anon* %this1, i32 0, i32 2
  %5 = load i32*, i32** %4, align 8
  %6 = load i32, i32* %i, align 4
  %idxprom = sext i32 %6 to i64
  %arrayidx = getelementptr inbounds i32, i32* %5, i64 %idxprom
  %7 = load i32, i32* %arrayidx, align 4
  %8 = getelementptr inbounds %class.anon, %class.anon* %this1, i32 0, i32 3
  %9 = load i32*, i32** %8, align 8
  %10 = load i32, i32* %i, align 4
  %idxprom2 = sext i32 %10 to i64
  %arrayidx3 = getelementptr inbounds i32, i32* %9, i64 %idxprom2
  %11 = load i32, i32* %arrayidx3, align 4
  %add = add nsw i32 %7, %11
  %add4 = add nsw i32 %add, 2
  %12 = getelementptr inbounds %class.anon, %class.anon* %this1, i32 0, i32 1
  %13 = load i32*, i32** %12, align 8
  %14 = load i32, i32* %i, align 4
  %idxprom5 = sext i32 %14 to i64
  %arrayidx6 = getelementptr inbounds i32, i32* %13, i64 %idxprom5
  store i32 %add4, i32* %arrayidx6, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  ret void
}

; Function Attrs: noinline optnone uwtable
define internal i32 @_ZN5pacxx2v25range10get_globalEj(%"class.std::ios_base::Init"* %this, i32 %dim) #5 comdat align 2 {
entry:
  %this.addr = alloca %"class.std::ios_base::Init"*, align 8
  %dim.addr = alloca i32, align 4
  store %"class.std::ios_base::Init"* %this, %"class.std::ios_base::Init"** %this.addr, align 8
  store i32 %dim, i32* %dim.addr, align 4
  %this1 = load %"class.std::ios_base::Init"*, %"class.std::ios_base::Init"** %this.addr, align 8
  %0 = load i32, i32* %dim.addr, align 4
  %call = call i32 @_ZN5pacxx2v25range13get_global_idEj(%"class.std::ios_base::Init"* %this1, i32 %0)
  ret i32 %call
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @_ZN5pacxx2v25range13get_global_idEj(%"class.std::ios_base::Init"* %this, i32 %dimindx) #6 comdat align 2 {
entry:
  %retval = alloca i32, align 4
  %this.addr = alloca %"class.std::ios_base::Init"*, align 8
  %dimindx.addr = alloca i32, align 4
  store %"class.std::ios_base::Init"* %this, %"class.std::ios_base::Init"** %this.addr, align 8
  store i32 %dimindx, i32* %dimindx.addr, align 4
  %this1 = load %"class.std::ios_base::Init"*, %"class.std::ios_base::Init"** %this.addr, align 8
  %0 = load i32, i32* %dimindx.addr, align 4
  switch i32 %0, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb2
    i32 2, label %sw.bb5
  ]

sw.bb:                                            ; preds = %entry
  %1 = call i32 @llvm.pacxx.read.ntid.x()
  %2 = call i32 @llvm.pacxx.read.ctaid.x()
  %mul = mul nsw i32 %1, %2
  %3 = call i32 @llvm.pacxx.read.tid.x()
  %add = add nsw i32 %mul, %3
  store i32 %add, i32* %retval, align 4
  br label %return

sw.bb2:                                           ; preds = %entry
  %4 = call i32 @llvm.pacxx.read.ntid.y()
  %5 = call i32 @llvm.pacxx.read.ctaid.y()
  %mul3 = mul nsw i32 %4, %5
  %6 = call i32 @llvm.pacxx.read.tid.y()
  %add4 = add nsw i32 %mul3, %6
  store i32 %add4, i32* %retval, align 4
  br label %return

sw.bb5:                                           ; preds = %entry
  %7 = call i32 @llvm.pacxx.read.ntid.z()
  %8 = call i32 @llvm.pacxx.read.ctaid.z()
  %mul6 = mul nsw i32 %7, %8
  %9 = call i32 @llvm.pacxx.read.tid.z()
  %add7 = add nsw i32 %mul6, %9
  store i32 %add7, i32* %retval, align 4
  br label %return

sw.default:                                       ; preds = %entry
  store i32 0, i32* %retval, align 4
  br label %return

return:                                           ; preds = %sw.default, %sw.bb5, %sw.bb2, %sw.bb
  %10 = load i32, i32* %retval, align 4
  ret i32 %10
}

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ntid.x() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ctaid.x() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.tid.x() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ntid.y() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ctaid.y() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.tid.y() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ntid.z() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.ctaid.z() #7

; Function Attrs: nounwind readnone
declare i32 @llvm.pacxx.read.tid.z() #7

attributes #0 = { noinline uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone }

!nvvm.annotations = !{!0}
!pacxx.kernel = !{!1}
!pacxx.kernel._ZN5pacxx2v213genericKernelIZL19test_vadd_low_leveliPPcE3$_0EEvT_ = !{}
!llvm.ident = !{!2}
!llvm.module.flags = !{!3}

!0 = !{void (i64, i32*, i32*, i32*)* @"_ZN5pacxx2v213genericKernelIZL19test_vadd_low_leveliPPcE3$_0EEvT_", !"kernel", i32 1}
!1 = !{void (i64, i32*, i32*, i32*)* @"_ZN5pacxx2v213genericKernelIZL19test_vadd_low_leveliPPcE3$_0EEvT_"}
!2 = !{!"clang version 6.0.0 (git@bitbucket.org:mhaidl/pacxx-clang.git ccb8438611dd19ed9989f2002afe1a5f15fc7efa) (git@bitbucket.org:mhaidl/pacxx-llvm.git e75fa4e6e8d37f4b4dddb0ce0c138ae14d754339)"}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{!"Generic"}
!5 = !{i32 0}
!6 = !{!"none"}
!7 = !{!"(lambda at /home/m_haid02/pacxx_samples/vadd_low_level/vadd_low_level.h:38:15)"}
!8 = !{!""}
)LLVM";


using asio::ip::tcp;

std::unique_ptr<asio::io_service> _service; 
std::unique_ptr<asio::ip::tcp::socket> _socket;

    std::string send_message(std::string message){
      std::string answer;
      asio::streambuf buffer;
      asio::write(*_socket, asio::buffer(message + "\r"));
      std::cout << message << " -> ";
      asio::read_until(*_socket, buffer, '\r');
      std::istream is(&buffer);
      is >> answer;
      std::cout << answer << std::endl;
      return answer;
    }

    std::string send_data(const void* data, size_t size){
      std::string answer;
      asio::streambuf buffer;
      asio::write(*_socket, asio::buffer(data, size));
      std::cout << data << " -> ";
      asio::read_until(*_socket, buffer, '\r');
      std::istream is(&buffer);
      is >> answer;
      std::cout << answer << std::endl;
      return answer;
    }

    std::string read_data(void* ptr, size_t size){
      asio::read(*_socket, asio::buffer(ptr, size), asio::transfer_exactly(size));
      return send_message("ACK");
    }

void connectToDeamon(const std::string& host, const std::string& port){
    _service.reset(new asio::io_service());
    tcp::resolver resolver(*_service);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    _socket.reset(new asio::ip::tcp::socket(*_service));
    asio::connect(*_socket, endpoint_iterator);

    send_message("HELLO");
}


void createRemoteBackend(pacxx::v2::IRRuntime::RuntimeKind kind, const char* llvm, size_t size){
    std::string rtName; 
    using namespace pacxx::v2;
    switch(kind){
      case IRRuntime::RK_CUDA: 
        rtName = "CUDA"; 
        break; 
      case IRRuntime::RK_Native: 
        rtName = "NATIVE"; 
        break; 
      case IRRuntime::RK_HIP: 
        rtName = "HIP"; 
        break; 
    }

    send_message(rtName);
    send_message("LLVM");
    send_message(std::to_string(size));
    send_data(llvm, size);
}

  void* allocateRemoteMemory(size_t size){
    send_message("ALLOC");
    return reinterpret_cast<void*>(std::stoul(send_message(std::to_string(size))));
  }

  void freeRemoteMemory(void* ptr){
    send_message("FREE");
    send_message(std::to_string(reinterpret_cast<uint64_t>(ptr)));
  }

  void uploadToRemoteMemory(void* dest, void* src, size_t size){
    send_message("UPLOAD");
    send_message(std::to_string(reinterpret_cast<uint64_t>(dest)));
    send_message(std::to_string(size));
    send_data(src, size);
  }

  void downloadFromRemoteMemory(void* dest, void* src, size_t size){
    send_message("DOWNLOAD");
    send_message(std::to_string(reinterpret_cast<uint64_t>(src)));
    send_message(std::to_string(size));
    auto answer = read_data(dest, size);
  }

struct dim3{
  dim3(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z){}
  unsigned int x, y, z; 
};

struct KernelConfiguration{
  KernelConfiguration(dim3 b, dim3 t) : threads(t), blocks(b) {}
  dim3 threads, blocks; 
};

  void launchRemoteKernel(const std::string& name, void* args, size_t size, KernelConfiguration config){
    send_message("LAUNCH");
    send_message(name);
    send_message(std::to_string(config.blocks.x));
    send_message(std::to_string(config.blocks.y));
    send_message(std::to_string(config.blocks.z));
    send_message(std::to_string(config.threads.x));
    send_message(std::to_string(config.threads.y));
    send_message(std::to_string(config.threads.z));
    send_message(std::to_string(size));
    send_data(args, size);
  }


int main(int argc, char *argv[]) {
    if (argc != 2) {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    connectToDeamon(argv[1], "1312");

    std::string llvm(module); 
    createRemoteBackend(pacxx::v2::IRRuntime::RK_Native, llvm.data(), llvm.size());

    size_t size = 128 * sizeof(int);
    
    auto ptrA = allocateRemoteMemory(size);
    auto ptrB = allocateRemoteMemory(size);
    auto ptrC = allocateRemoteMemory(size);

    std::vector<int> data(128);
    std::fill(data.begin(), data.end(), 1);
    uploadToRemoteMemory(ptrA, data.data(), size);

    std::fill(data.begin(), data.end(), 2);
    uploadToRemoteMemory(ptrB, data.data(), size);

    std::fill(data.begin(), data.end(), 0);
    uploadToRemoteMemory(ptrC, data.data(), size);

    struct _args{
      size_t N; 
      void* A;
      void* B;
      void* C;
    } args;

    args.N = data.size(); 
    args.A = ptrC; 
    args.B = ptrB;
    args.C = ptrA;

    launchRemoteKernel("ZL19test_vadd_low_leveliPPcE3$_0", &args, sizeof(_args), {{1, 1, 1}, {128, 1, 1}});

    downloadFromRemoteMemory(data.data(), ptrC, size);

    for(auto v : data)
      std::cout << v; 
    std::cout << std::endl;

    freeRemoteMemory(ptrA);
    freeRemoteMemory(ptrB);
    freeRemoteMemory(ptrC);

    send_message("BYE");

  return 0;
}