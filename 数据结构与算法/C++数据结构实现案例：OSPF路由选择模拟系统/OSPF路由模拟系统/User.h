#pragma once
#include "OSPF.h"
//用户结构
struct UNode {
    string username;    //用户名
    string account;     //账号
    string password;    //密码
    UNode* left;
    UNode* right;
}; 

//管理员结构
struct AdNode {
    string name;
    string account;
    string password;
};
typedef UNode* UsersBST;
class User :
    public OSPF
{
public:
    UsersBST head;  //用户排序树

    //初始化用户排序树
   User() {
        ifstream inputFile("./user.txt",ios::in | ios::binary);

        if (!inputFile.is_open()) {
            cerr << "文件打开失败：" << "user.txt" << endl;
            return;
        }

        string name, account, password;
        while (inputFile >> name >> account >> password) {
            InsertUser(name, account, password);
        }
        inputFile.close();
   }

   //保存用户信息到文件中
   void SaveUserBST() {
       ofstream outputFile("user.txt");

       if (!outputFile.is_open()) {
           cerr << "文件打开失败：" << "user.txt" << endl;
           return;
       }

       _save_userbst(head, outputFile);
       outputFile.close();
       cout << "用户信息保存成功！" << endl;
    }
    //插入用户(账号)
    void InsertUser(const string& username, const string& account, const string& password)
    {
        _insert_user(head, username, account, password);
    }

    //查找用户(账号)
    UsersBST FindUser(const string& account) {
        return _find_user(head, account);
    }

    //输出用户表（不输出密码）
    void printUsers() {
        cout << "用户信息表:" << endl;
        cout << "用户名\t\t账号" << endl;
        _print_users(head);
    }

    //删除用户(账号)
    void DeleteUser(const string& account) {
         _delete_user(head, account);
    }
    
    //修改用户密码
    bool ModifyPassword(const string& account, string& password, string& new_password) {
        UsersBST UBT = FindUser(account);
        if (UBT && UBT->password == password) {
            UBT->password = new_password;
            return true;
        }
        return false;
    }
private:

    //递归插入排序二叉树(账号)
    UsersBST _insert_user(UsersBST& Head, const string& username, const string& account, const string& password) {
        if (!Head) {
            //插入新节点
            Head = new UNode{};
            Head->username = username;
            Head->account = account;
            Head->password = password;
            Head->left = Head->right = nullptr;
        }
        else if (account < Head->account) {
            //插入左子树
            Head->left = _insert_user(Head->left, username, account, password);
        }
        else if (account > Head->account) {
            //插入右子树
            Head->right = _insert_user(Head->right, username, account, password);
        }
        return Head;
    }

    //递归查找用户
    UsersBST _find_user(const UsersBST& Head, const string& account) {
        if (!Head)
            return nullptr;
        if (Head->account == account)
            return Head;
        else if (Head->account > account) {
            //查找左子树
            return _find_user(Head->left, account);
        }
        else if (Head->account < account) {
            //查找右子树
           return  _find_user(Head->right, account);
        }
    }

    //递归删除用户
    UsersBST _delete_user(UsersBST& Head,const string& account) {
        if (!Head)
            return nullptr;
        if (account < Head->account) {
            //删除左子树
            Head->left = _delete_user(Head->left, account);
        }
        else if (account > Head->account) {
            //删除右子树
            Head->right = _delete_user(Head->right, account);
        }
        else {
            //找到了要删除的顶点
            //如果有两颗子树
            if (Head->left && Head->right) {
                //找右子树最小的节点替换
                UsersBST MinNode = FindMinUBST(Head->right);
                Head->account = MinNode->account;
                Head->password = MinNode->password;
                Head->username = MinNode->username;
                //删除最小节点
                Head->right = _delete_user(Head->right, MinNode->account);
            }
            else {
                UsersBST temp = Head;
                if (Head->left)
                    Head = Head->left;
                else
                    Head = Head->right;
                delete temp;
            }
        }
        return Head;
    }

    //找排序树的最小顶点
    UsersBST FindMinUBST(const UsersBST& Head) {
        if (!Head)
            return nullptr;
        UsersBST current = Head;
        while (current->left)
            current = current->left;
        return current;
    }

    //递归输出用户信息
    void _print_users(const UsersBST& Head) {
        if (Head) {
            _print_users(Head->left);
            cout << Head->username << "\t\t" << Head->account << endl;
            _print_users(Head->right);
        }
    }

    //递归保存文件
    void _save_userbst(const UsersBST& Head, ofstream& outputFile) {
        if (Head) {
            _save_userbst(Head->left, outputFile);
            outputFile << Head->username << " " << Head->account << " " << Head->password << endl;
            _save_userbst(Head->right, outputFile);
        }
    }
};

class Ad :
    public User
{
public:
    AdNode* Adarray = new AdNode[20];

    Ad() {
        ifstream inputFile("./administrator.txt");

        if (!inputFile.is_open()) {
            cerr << "文件打开失败：" << "administrator.txt" << endl;
            return;
        }

        string name, account, password;
        int i = 0;
        while (inputFile >> name >> account >> password) {
            AdNode ad;
            ad.name = name;
            ad.account = account;
            ad.password = password;
            Adarray[i] = ad;
            i++;
        }
        inputFile.close();
    }

    //查找管理员
    int FindAd(const string& account) {
        int i = 0;
        while (i < 20 && Adarray[i].account != account) {
            i++;
        }
        if (i == 20)
            return -1;
        return i;
    }
};

