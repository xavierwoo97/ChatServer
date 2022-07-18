#ifndef GROUPUSER_H
#define GROUPUSER_H

#include"user.hpp"

//群组用户,多一个role角色
class GroupUser:public User{
public:
    GroupUser(string role=""){
        this->role = role;
    }
    
    string getRole(){return this->role;}
    void setRole(string role){this->role = role;}
private:
    string role;
};

#endif