#include "TCPServer.h"
#include <asio.hpp>
#include <istream>
#include <string>
#include <vector>
#include <future>

#include <pacxx/detail/common/Log.h>

using namespace asio::ip;

namespace pacxxd {
void TCPServer::initialize(unsigned short port) {
  _service.reset(new asio::io_service());
  _acceptor.reset(new tcp::acceptor(*_service, tcp::endpoint(tcp::v4(), port)));
  _socket.reset(new tcp::socket(*_service));
  _work.reset(new asio::io_service::work(*_service));

  _io_future = std::async(std::launch::async, [this]{
    _service->run();
  });
  _accept = true;
}

void TCPServer::shutdown(){
  _accept = false; 
  _acceptor->cancel(); 
  _acceptor->close();
  _service->stop();
}

void TCPServer::send(const std::string& message) {
  asio::error_code ignored;
  asio::write(*_socket, asio::buffer(message + "\r"), ignored);
}

void TCPServer::send(const std::vector<char>& message) {
  asio::error_code ignored;
  auto len = asio::write(*_socket, asio::buffer(message.data(), message.size()), ignored);
}

std::string TCPServer::recive(bool auto_ack, bool no_timeout) {
  std::string message;
  asio::streambuf buffer;
  asio::error_code error;
  if (no_timeout){
    asio::read_until(*_socket, buffer, '\r');
  }
  else {
    sema.reset();
    asio::async_read_until(*_socket, buffer, '\r', 
        [this](auto& ec, size_t recived) {
            // if the timeout runs out do nothing
            if (ec == asio::error::operation_aborted)
              return;
            sema.signal();
        });

    if(!sema.wait_for(std::chrono::seconds(2)))
    {
        _socket->cancel();
        __error("read operation timeout");
        return "ERROR";
    }
  }

  std::istream is(&buffer);
  is >> message;
  __debug("network message recived: ", message);
  if (auto_ack)
    send("ACK"); // send ACK to the client to acknoledge the message
  return message;
}

void TCPServer::recive_data(void* ptr, size_t size, bool auto_ack) {
  asio::read(*_socket, asio::buffer(ptr, size), asio::transfer_exactly(size));
  if (auto_ack)
    send("ACK"); // send ACK to the client to acknoledge the message
}

void TCPServer::disconnect() {
  asio::error_code ignored;
  _socket->shutdown(tcp::socket::shutdown_both, ignored);
  _socket->close();
}

} // namespace pacxxd
