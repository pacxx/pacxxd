#include "Dispatcher.h"
#include "Log.h"
#include "PACXXHandler.h"
#include "Protocol.h"
#include "TCPServer.h"

#include <csignal>
#include <functional>

using namespace pacxxd;

namespace {
std::function<void(int)> shutdown_handler;

void signal_handler(int signal) { shutdown_handler(signal); }

} // namespace

int main(int argc, char *argv[]) {

  //std::signal(SIGINT, signal_handler);

  TCPServer server;
  server.initialize(1312);
  __message("Server initialized...");
  Dispatcher dispatcher;
  PACXXHandler handler;

  shutdown_handler = [&](int signal) {
    __message("Server shutdown...");
    server.shutdown();
  };

  populateProtocolHandling(server, dispatcher, handler);

  server.accept([&] {
    while (dispatcher.dispatch(server.recive(true, true)));
  });

  return 0;
}