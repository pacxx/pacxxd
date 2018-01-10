#pragma once
#include "Semaphore.h"

#include <asio.hpp>
#include <memory>
#include <string>
#include <vector>
#include <future>

namespace pacxxd {
class TCPServer {
public:
  TCPServer() = default;
  virtual ~TCPServer() = default;

  void initialize(unsigned short port);
  void shutdown();

  template <typename L>
  void accept(L handler) { 
    while (_accept){
      std::async(std::launch::async, [&]{
      _acceptor->async_accept(*_socket, 
      [&](const auto& error) mutable{
        if (!error){ 
          handler();
        }
      });}); 
    }
  }

  void send(const std::string& message);
  void send(const std::vector<char>& message);
  std::string recive(bool auto_ack = true, bool no_timeout = false);
  void recive_data(void* ptr, size_t size, bool auto_ack = true);
  void disconnect();

private:
  std::unique_ptr<asio::io_service> _service;
  std::unique_ptr<asio::io_service::work> _work;
  std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
  std::unique_ptr<asio::ip::tcp::socket> _socket;
  std::future<void> _io_future;
  Semaphore sema;
  bool _accept;
};
} // namespace pacxxd