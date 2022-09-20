#include <iostream>
#include "helper_functions.hpp"

std::vector<char> vectBuffer(1*1024);


void ReadSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vectBuffer.data(), vectBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cout << "\n\nRead " << length << "bytes\n\n";

                for (int i = 0; i < length; i++)
                    std::cout << vectBuffer[i];
                    
                ReadSomeData(socket);
                
            }
        }
    );

}


