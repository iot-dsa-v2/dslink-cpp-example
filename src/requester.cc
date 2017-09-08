#include "dsa/message.h"
#include "dsa/network.h"

#include "network/tcp/tcp_client.h"
#include "network/tcp/tcp_server.h"

#include "module/default_modules.h"

using namespace dsa;

class MockStreamAcceptor : public OutgoingStreamAcceptor {
 public:
  ref_<OutgoingSubscribeStream> last_subscribe_stream;
  std::unique_ptr<SubscribeOptions> last_subscribe_options;
  void add(ref_<OutgoingSubscribeStream> &stream) {
    BOOST_ASSERT_MSG(last_subscribe_stream == nullptr,
                     "receive second subscription stream, not expected");
    last_subscribe_stream = stream;
    stream->send_value(Variant("hello"));
    stream->on_update([=](OutgoingSubscribeStream &stream) {
      last_subscribe_options.reset(new SubscribeOptions(stream.options()));
    });
  }
  void add(ref_<OutgoingListStream> &stream) {}
  void add(ref_<OutgoingInvokeStream> &stream) {}
  void add(ref_<OutgoingSetStream> &stream) {}
};

int main() {
  App app;

  // capture and log request
  auto mock_stream_acceptor = make_shared_<MockStreamAcceptor>();

  auto modules = make_ref_<DefaultModules>(app);
  modules->set_stream_acceptor(mock_stream_acceptor);

  WrapperConfig server_config;
  server_config.tcp_host = "127.0.0.1";
  server_config.tcp_port = 8090;
  server_config.strand = std::move(modules);
  server_config.strand->logger().level = Logger::WARN;

  app.async_start(10);

  //  auto tcp_server(new TcpServer(server_config));
  auto tcp_server = make_shared_<TcpServer>(server_config);
  tcp_server->start();

  WrapperConfig client_config;
  client_config.tcp_host = "127.0.0.1";
  client_config.tcp_port = 8090;
  client_config.strand = make_ref_<DefaultModules>(app);
  client_config.strand->logger().level = Logger::WARN;

  auto tcp_client = make_shared_<TcpClient>(client_config);
  tcp_client->connect();

  app.sleep(500);

  SubscribeOptions initial_options;
  initial_options.queue_time = 0x1234;
  initial_options.queue_size = 0x5678;

  SubscribeOptions update_options;
  update_options.queue_time = 0x9876;
  update_options.queue_size = 0x5432;

  ref_<const SubscribeResponseMessage> last_response;
  auto subscribe_stream = tcp_client->get_session().requester.subscribe(
      "/path",
      [&](ref_<const SubscribeResponseMessage> &&msg,
          IncomingSubscribeStream &stream) {
        last_response = std::move(msg);  // store response
      },
      initial_options);

  app.sleep(500);

  // received request option should be same as the original one
  assert(initial_options ==
              mock_stream_acceptor->last_subscribe_stream->options());

  app.sleep(500);

  assert(last_response->get_value().has_value() &&
              last_response->get_value().value.is_string() &&
              last_response->get_value().value.get_string() == "hello");

  std::cout << last_response->get_value().value.get_string() << std::endl;

  // send an new request to udpate the option of the same stream
  auto second_request = make_ref_<SubscribeRequestMessage>();
  second_request->set_subscribe_option(update_options);
  subscribe_stream->send_message(
      std::move(second_request));  // send update options

  app.sleep(500);

  // request option should be same as the second one
  assert(update_options == *mock_stream_acceptor->last_subscribe_options);
  assert(update_options ==
              mock_stream_acceptor->last_subscribe_stream->options());

  Server::close_in_strand(tcp_server);
  Client::close_in_strand(tcp_client);

  app.close();

  app.sleep(500);

  if (!app.is_stopped()) {
    app.force_stop();
  }

  app.wait();

  return 0;
}