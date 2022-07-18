#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include<functional>
#include<unordered_map>
#include<muduo/net/TcpConnection.h>
#include<mutex>
#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "frindmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"

//处理消息的事件回调方法类型
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr& conn,
                            nlohmann::json &js,
                            muduo::Timestamp time)>;

//聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService* instance();

    //处理登录业务
    void login(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    //处理注册业务
    void reg(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    //一对一聊天业务
    void oneChat(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    //添加好友业务
    void addFriend(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    
    //创建群组业务
    void createGroup(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    //加入群组业务
    void addGroup(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    //群组聊天业务
    void groupChat(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    
    //处理注销业务
    void loginout(const muduo::net::TcpConnectionPtr& conn, nlohmann::json &js,muduo::Timestamp time);
    
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
   
    //处理客户端异常退出
    void clientCloseException(const muduo::net::TcpConnectionPtr& conn);
    
    //服务器异常，业务重置方法
    void reset();

    //从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, std::string msg);

private:
    ChatService();
    //存储消息id及其对应的业务处理方法,提前注册,不用考虑线程安全
    std::unordered_map<int, MsgHandler> _msgHandlerMap;

    //定义互斥锁，保证_userConnMap的线程安全
    std::mutex _connMutex;

    //存储在线用户的通信连接,注意线程安全
    std::unordered_map<int,muduo::net::TcpConnectionPtr> _userConnMap;

    //数据操作类对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel; //提供离线消息表的操作接口方法
    FriendModel _friendModel;       //维护好友信息的操作接口方法
    GroupModel _groupModel;     //管理群组消息的操作接口方法

    //redis操作对象
    Redis _redis;
};

#endif