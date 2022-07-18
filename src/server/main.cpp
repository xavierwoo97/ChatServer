#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

// 处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "command invalid! example: ./ChatServer 127.0.0.1 6000" << std::endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的ip和port
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // SIGINT对应事件Ctrl+c 
    signal(SIGINT, resetHandler);

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");
    
    server.start();
    loop.loop();

    return 0;
}