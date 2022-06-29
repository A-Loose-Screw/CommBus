  // auto server = nng::pub::open();
  // // server.dial(SOCKET_BUS_ADDR);
  // server.listen(SOCKET_BUS_ADDR);

  // auto client1 = nng::sub::open();
  // auto client2 = nng::sub::open();

  // nng::set_opt_recv_timeout(client1, 100);
  // nng::set_opt_recv_timeout(client2, 100);

  // nng::sub::set_opt_subscribe(client1, {"DATE:", 5});
  // nng::sub::set_opt_subscribe(client2, {"TIME:", 5});

  // client1.dial(SOCKET_BUS_ADDR);
  // client2.dial(SOCKET_BUS_ADDR);

  // server.send("DATE: it's actually not a date");
  // server.send("TIME: but more");

  // nng::buffer buffer1;
  // try {
  //   buffer1 = client1.recv(NNG_FLAG_NONBLOCK);
  //   if (buffer1.data() != NULL) {
  //     std::cout << "Client 1 recv " << buffer1.data<char>() << std::endl;
  //   }
  // } catch(const std::exception& e) {
  //   // std::cerr << e.what() << '\n';
  //   std::cout << e.what() << std::endl;
  // }

  // nng::buffer buffer2;
  // try {
  //   buffer2 = client2.recv(NNG_FLAG_NONBLOCK);
  //   if (buffer2.data() != NULL) {
  //     std::cout << "Client 2 recv " << buffer2.data<char>() << std::endl;
  //   }
  // } catch(const std::exception& e) {
  //   // std::cerr << e.what() << '\n';
  //   std::cout << e.what() << std::endl;
  // }