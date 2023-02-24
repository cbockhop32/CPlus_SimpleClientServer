#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include "helper_functions.hpp"





int main()
{

    boost::system::error_code ec;

    // Creating context
    boost::asio::io_context ioContext;

    // Give context idle work so it doesnt finish
    boost::asio::io_context::work idleWork(ioContext);

    // Run context in its own thread
    std::thread threadContext = std::thread([&](){ ioContext.run();});

    // Endpoint (TCP)
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);

    // Creating a socket that will run within the context
    boost::asio::ip::tcp::socket socket(ioContext);

    // Connecting socket
    socket.connect(endpoint, ec);

    if(!ec)
    {
        std::cout <<"Connected" << '\n';

    } else{
        std::cout << "Did not connect to the address: " << ec.message() << "\n";
    }

    if(socket.is_open()) 
    {
        ReadSomeData(socket);

        std::string request = 
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(boost::asio::buffer(request.data(), request.size()), ec);


        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);


        // close context
        ioContext.stop();
        if(threadContext.joinable()) threadContext.join();
      
    }

    return 0;
}