#include "json.hpp"
using json = nlohmann::json;

#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

string fun1()
{
    json js;
    js["messgetype"] = 2;
    js["from"] = "zhangsan";
    js["to"] = "li si";
    js["messageCnt"] = "What are you doing now?";

    // 将json对象转换为字符串,即序列化
    string buf = js.dump();
    return buf;
}

void fun2()
{
    // json中value类型可以很多
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu si"] = "hello china";
    cout<<js<<endl;
}

string fun3()
{
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;

    map<int,string> m;
    m.insert({1,"黄山"});
    m.insert({2,"华山"});
    m.insert({3,"泰山"});
    js["path"] = m;

    return js.dump();
}

int main()
{
    string strbuf = fun3();
    json jsBuf = json::parse(strbuf);
    vector<int> vec = jsBuf["list"];
    for(auto val: vec)
    {
        cout<<val<<" ";
    }
    cout<<endl;

    map<int,string> m = jsBuf["path"];
    for(auto it:m)
    {
        cout<<it.first<<" "<<it.second<<endl;
    }
    return 0;
}