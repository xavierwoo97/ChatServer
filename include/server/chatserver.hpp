#ifndef CHATSERVER_H
#define CHATSERVER_H

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>

//聊天服务器的主类
class ChatServer
{
public:

    //初始化聊天服务器对象
    ChatServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr,
            const std::string& nameArg);

    //启动服务
    void start();

    
private:
    //上报连接相关信息的回调函数
    void onConnection(const muduo::net::TcpConnectionPtr&);
    void onMessage(const muduo::net::TcpConnectionPtr&,
                            muduo::net::Buffer*,
                            muduo::Timestamp);
    
    //上报读写相关信息的回调函数
    muduo::net::TcpServer _server;  //组合的muduo库,实现服务器功能的类对象
    muduo::net::EventLoop *_loop;   //指向事件循环对象的指针
};

#endif