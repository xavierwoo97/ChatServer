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

# MySQL 表设计
【user表】

| 字段名称 | 字段类型                  | 字段说明     | 约束                        |
| -------- | ------------------------- | ------------ | --------------------------- |
| id       | INT                       | 用户id       | PRIMARY_KEY、AUTO_INCREMENT |
| name     | VARCHAR(50)               | 用户名       | NOT NULL,  UNIQUE           |
| password | VARCHAR(50)               | 用户密码     | NOT NULL                    |
| state    | ENUM(‘online', 'offline') | 当前登录状态 | DEFAULT 'offline'           |

【Frined表】

| 字段名称 | 字段类型 | 字段说明 | 约束                |
| -------- | -------- | -------- | ------------------- |
| userid   | INT      | 用户id   | NOT NULL、 联合主键 |
| friendid | INT      | 好友id   | NOT NULL、 联合主键 |

【AllGroup表】

| 字段名称  | 字段类型     | 字段说明   | 约束                        |
| --------- | ------------ | ---------- | --------------------------- |
| id        | INT          | 组id       | PRIMARY_KEY、AUTO_INCREMENT |
| groupname | VARCHAR(50)  | 组名称     | NOT NULL,UNIQUE             |
| gruopdesc | VARCHAR(200) | 组功能描述 | DEFAULT ' '                 |

【GroupUser表】

| 字段名称  | 字段类型                  | 字段说明 | 约束               |
| --------- | ------------------------- | -------- | ------------------ |
| groupid   | INT                       | 组id     | NOT NULL、联合主键 |
| userid    | INT                       | 组员id   | NOT NULL、联合主键 |
| grouprole | ENUM('creator', 'normal') | 组内角色 | DEFAULT ‘normal’   |

【OfflineMessage表】

| 字段名称 | 字段类型     | 字段说明                   | 约束     |
| -------- | ------------ | -------------------------- | -------- |
| userid   | INT          | 用户id                     | NOT NULL |
| message  | VARCHAR(500) | 离线消息（存储Json字符串） | NOT NULL |

