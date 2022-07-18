# chatserver
    本项目使用开源muduo网络库实现网络模块,配合nginx和redis发布订阅功能实现了一个简单的集群聊天服务器。该服务器支持一对一聊天，群聊，离线消息查看等功能。

# 快速上手
    本项目基于一下环境开发：
    * ubuntu 20.04
    * muduo 
    * nginx 1.12.2
    * mysql 8.0.29-0ubuntu0.20.04.3
    * redis-server
    * CMake
    autobuild.sh为一键式编译脚本,使用者需自行更改src/server/db/db.cpp中关于mysql的配置信息,以及配置nginx负载均衡.

