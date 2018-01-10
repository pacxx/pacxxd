#pragma once
#include "TCPServer.h"
#include "Dispatcher.h"
#include "PACXXHandler.h"

#include <pacxx/detail/IRRuntime.h>

namespace pacxxd{
    static void populateProtocolHandling(TCPServer& server, Dispatcher& dispatcher, PACXXHandler& handler){
        using namespace pacxx::v2;
        
 dispatcher.register_end("BYE");

    dispatcher.register_handler("HELLO", [&]{ 
    });

    dispatcher.register_handler("NATIVE", [&]{ 
  	  handler.createExecutor(IRRuntime::RK_Native, 0);
    });  

    dispatcher.register_handler("CUDA", [&]{ 
  	  handler.createExecutor(IRRuntime::RK_CUDA, 0);
    });  

    dispatcher.register_handler("HIP", [&]{ 
  	  handler.createExecutor(IRRuntime::RK_HIP, 0);
    });  

    dispatcher.register_handler("LLVM", [&]{
      std::cout << "LENGTH: " << std::endl;
      auto length = server.recive(false); 
      std::cout << length << std::endl;
      auto size = std::stoul(length);
      std::vector<char> IR; 
      IR.resize(size);
      server.send("ACK");
      server.recive_data(IR.data(), IR.size(), false);
      handler.setLLVMBytes(IR);
      server.send("ACK");
    });

    dispatcher.register_handler("ALLOC", [&]{
      auto size = std::stoul(server.recive(false)); 
      auto ptr = handler.allocateMemory(size);
      server.send(std::to_string(reinterpret_cast<uint64_t>(ptr)));
    });

    dispatcher.register_handler("FREE", [&]{
      auto message = server.recive(false); 
      std::cout << "ERROR: " << message << std::endl;
      auto ptr = reinterpret_cast<void*>(std::stoul(message)); 
      handler.freeMemory(ptr);
      server.send("ACK");
    });
    
    dispatcher.register_handler("UPLOAD", [&]{
      auto ptr = reinterpret_cast<void*>(std::stoul(server.recive())); 
      auto size = std::stoul(server.recive()); 
      std::vector<char> bytes; 
      bytes.resize(size);
      server.recive_data(bytes.data(), bytes.size(), false);
      handler.uploadData(ptr, bytes.data(), size);
      server.send("ACK");
    });

    dispatcher.register_handler("DOWNLOAD", [&]{
      auto ptr = reinterpret_cast<void*>(std::stoul(server.recive())); 
      auto size = std::stoul(server.recive()); 
      std::vector<char> bytes(size);
      bytes.resize(size);
      std::cout << "sending " << bytes.size() << " bytes" << std::endl;
      handler.downloadData(bytes.data(), ptr, size);
      server.send(bytes);
      dispatcher.dispatch(server.recive());
    });

    dispatcher.register_handler("BYE", [&]{ 
      server.disconnect();
    });

    dispatcher.register_handler("LAUNCH", [&]{
      auto kernel_name = server.recive(); 
      auto blocks_x = std::stoul(server.recive());
      auto blocks_y = std::stoul(server.recive());
      auto blocks_z = std::stoul(server.recive());
      auto threads_x = std::stoul(server.recive());
      auto threads_y = std::stoul(server.recive());
      auto threads_z = std::stoul(server.recive());
      auto arg_size =  std::stoul(server.recive(false));
      std::cout << arg_size << std::endl;

      server.send("ACK");
      std::vector<char> bytes; 
      bytes.resize(arg_size);
      server.recive_data(bytes.data(), bytes.size(), false);

      handler.launchKernel(kernel_name, bytes.data(), bytes.size(), {{blocks_x, blocks_y, blocks_z}, {threads_x, threads_y, threads_z}});

      server.send("ACK");
    });

    dispatcher.register_handler("ERROR", [&]{ 
      server.disconnect();
    });

    dispatcher.register_handler("ACK", [&]{ 
    });

    }
}