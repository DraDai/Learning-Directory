#pragma once
#include"RoutList.h"
#include<fstream>
struct Router {//路由器结构
	string name;	//路由器地址
	RoutList rlist;	//路由表类
	Graph network;	//网络拓扑图类
};

struct RTNode {
	Router R;	//路由器节点
	RTNode* left;	//左子树
	RTNode* right;	//右子树
	bool visited;	//标记
	int Height;	//树高
};
typedef RTNode* RAVL;	//平衡二叉树

struct Node {	//链表，用来构造队列
	Router R;	//路由器地址
	Node* next;
};
typedef Node* Position;

struct QNode {	//队列的头尾指针
	Position front, Rear;
};
typedef QNode* Queue;//队列结构
class OSPF {
public:
	//成员
	Graph AllNetwork;	//网络拓扑总图
	RAVL head;	//路由器平衡二叉树

	//初始化OSPF类
	OSPF() {
		//初始化网络拓扑总图
		InitOSPF();
	}

	//保存AllNetwork到文件流中
	void SaveAllNetwork() {
		ofstream outputFile("AllNetWork.txt");

		if (!outputFile.is_open()) {
			cerr << "文件打开失败：" << "AllNetWork.txt" << endl;
			return;
		}

		Vert p = AllNetwork.head;
		while (p->vp) {
			p = p->vp;

			Edge t = p->ep;
			while (t) {
				outputFile <<p->name<< " " << t->name << " " << t->power << endl;
				t = t->ep;
			}
		}
		outputFile.close();
		cout << "网络信息保存成功!" << endl;
	}

	//显示网络拓扑总图
	void printAllNetwork()
	{
		cout << "网络拓扑总图：" << endl;
		AllNetwork.printG();
	}

	//查看某路由器的所有邻接点
	void printAllNetWork(const string& name) {
		if (!AllNetwork.FindV(name)) {
			cout << "该路由器不存在\n";
			return;
		}
		AllNetwork.printNE(name);
	}

	//通过两个路由器地址，显示最短路径以及经过的路由器
	void printMinPath(const string& from, const string& to) {
		//找到from路由器在树中的位置
		RAVL F, T;
		F = FindRAVL(head, from);
		T = FindRAVL(head, to);
		if (!F || !T) {
			cout << "无法显示 " << from << " 到 " << to << " 的最短路径" << endl;
			return;
		}
		string nextjump = F->R.rlist.FindRoutlist(to);
		if (nextjump == "") {
			cout << from << " 到 " << to << " 无连接" << endl;
			return;
		}
		int sum = 0;
		cout << from << " 到 " << to << " 的最短路径所经过的路由器有：" << endl;
		cout << from;
		while (nextjump != to) {
			cout << " -> " << nextjump;
			sum += F->R.network.Getpower(F->R.name, nextjump);
			F = FindRAVL(head, nextjump);
			nextjump = F->R.rlist.FindRoutlist(to);
		}
		cout << " -> " << nextjump << endl << endl;
		sum += F->R.network.Getpower(F->R.name, nextjump);
		cout << "最短路径的总权值为：" << sum << endl;
		//从路由表读取路径
	}

	//字典序显示路由器地址信息
	void printRAVL()
	{
		cout << "平台内现有路由器：" << endl;
		//内置函数
		_print_ravl(head);
		cout << endl;
	}

	//通过路由地址显示路由器内部的网络拓扑图
	void printRouterNetwork(const string& name)
	{
		RAVL Rp = FindRAVL(head, name);
		if (Rp == nullptr)
			cout << "该路由器不存在！" << endl;
		else
		{
			cout << name << " 的网络拓扑图:" << endl;
			Rp->R.network.printG();
		}
	}

	//通过路由器地址显示路由器内部的路由表
	void printRouterRoutlist(const string& name) {
		RAVL Rp = FindRAVL(head, name);
		if (Rp) {
			Rp->R.rlist.printRouters();
		}
		else
			cout << "路由器不存在！" << endl;
	}

	//输出网络权值
	void printPower() {
		AllNetwork.SortPrintEdge();
	}

	//添加路由器
	void AddRouter(const string& name)
	{
		//插入平衡二叉树
		InsertRAVL(head, name);
		//插入网络拓扑总图
		AllNetwork.AddV(name);
	}

	//查找权值
	int FindPower(const string& from, const string& to)
	{
		return AllNetwork.Getpower(from, to);
	}

	//添加权值
	bool AddPower(const string& from, const string& to, int power)
	{
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return false;
		//插入网络拓扑总图
		AllNetwork.AddEdge(from, to, power);
		//在各自的网络拓扑图中先添加对方的路由地址，再添加权值
		RAVL F = FindRAVL(head, from);
		F->R.network.AddV(to);
		F->R.network.AddV(from);
		F->R.network.AddEdge(from, to, power);

		RAVL T = FindRAVL(head, to);
		T->R.network.AddV(to);
		T->R.network.AddV(from);
		T->R.network.AddEdge(to, from, power);

		//两者交换网图添加本身没有的信息
		F->R.network.InitGraph(T->R.network);
		T->R.network.InitGraph(F->R.network);

		//更新两路由表
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);

		//任选其一进行泛洪
		Flood_Fill(from);
		return true;
	}

	//删除权值
	bool DeletePower(const string& from, string to)
	{
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return true;
		if (AllNetwork.Getpower(from, to) == INF)
			return true;
		//删除网络拓扑总图权值
		AllNetwork.DeleteE(from, to);
		//在各自的网络拓扑图中删除权值
		RAVL F = FindRAVL(head, from);
		RAVL T = FindRAVL(head, to);

		F->R.network.DeleteE(from, to);
		T->R.network.DeleteE(to, from);

		//把不与自己联通的所有路由器信息全部删除
		F->R.network.DeleteAllDisconnect(from);
		T->R.network.DeleteAllDisconnect(to);

		//更新路由表
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);

		//两者都进行泛洪（因为两路由器可能不连通）
		Flood_Fill(from);
		Flood_Fill(to);
		return true;
	}

	//修改权值
	bool ModifyPower(const string& from, const string& to, int power) {
		if (!FindRAVL(head, from) || !FindRAVL(head, to))
			return false;
		if (AllNetwork.Getpower(from, to) == INF) {
			AddPower(from, to, power);
			return true;
		}
		//修改网络拓扑总图权值
		AllNetwork.AddEdge(from, to, power);

		//修改各自的网络拓扑图的权值
		RAVL F = FindRAVL(head, from);
		RAVL T = FindRAVL(head, to);

		F->R.network.AddEdge(from, to, power);
		T->R.network.AddEdge(from, to, power);

		//更新两路由表
		F->R.rlist.deleteRouterList();
		F->R.rlist.Make_routerlist(F->R.network, from);

		T->R.rlist.deleteRouterList();
		T->R.rlist.Make_routerlist(T->R.network, to);
		//任选其一进行泛洪

		Flood_Fill(from);
		return true;
	}
	
	//删除某路由器所有邻接边
	bool DeleteNearPower(const string& from) {
		Vert p = AllNetwork.FindV(from);
		if (!p)
			return true;
		if (!p->ep)
			return true;
		Edge t = p->ep;
		_delete_power(p, t);
		p->ep = nullptr;
	}

	//删除路由器
	bool DeleteRouter(const string& from) {
		if (!FindRAVL(head, from))
			return true;
		DeleteNearPower(from);
		AllNetwork.DeleteV(from);
		DeleteRAVL(head, from);
		return true;
	}


private:

	//将文件流导入网络拓扑总图
	void InitOSPF()
	{
		ifstream inputFile("./AllNetWork.txt");

		if (!inputFile.is_open()) {
			cerr << "文件打开失败：" << "AllNetWork.txt" << endl;
			return;
		}

		string from, to;
		int power;

		//读取文件中的每一行，每行包含一条边的信息
		while (inputFile >> from >> to >> power) {
			AddRouter(from);
			AddRouter(to);
			AddPower(from, to, power);
		}
		//关闭文件流
		inputFile.close();
	}

	//查找树高
	int GetHeight(RAVL& Head)
	{
		int HL, HR, MaxH;
		if (Head)
		{
			HL = GetHeight(Head->left);
			HR = GetHeight(Head->right);
			MaxH = max(HL, HR) + 1;
			return MaxH;
		}
		else
			return 0;
	}

	//寻找平衡树的最小节点
	RAVL FindMinRAVL(const RAVL& Head)
	{
		if (!Head)
			return nullptr;
		RAVL current = Head;

		while (current->left)
			current = current->left;
		return current;
	}

	//左旋函数
	RAVL LL_Rotion(RAVL& Head)
	{
		RAVL temp = Head->left;
		Head->left = temp->right;
		temp->right = Head;
		Head->Height = max(GetHeight(Head->right), GetHeight(Head->left)) + 1;
		temp->Height = max(GetHeight(temp->left), Head->Height) + 1;
		return temp;
	}

	//右旋函数
	RAVL RR_Rotion(RAVL& Head)
	{
		RAVL temp = Head->right;
		Head->right = temp->left;
		temp->left = Head;
		Head->Height = max(GetHeight(Head->right), GetHeight(Head->left)) + 1;
		temp->Height = max(GetHeight(temp->right), Head->Height) + 1;
		return temp;
	}

	//左右旋函数
	RAVL LR_Rotion(RAVL& Head)
	{
		Head->right = LL_Rotion(Head->right);
		return RR_Rotion(Head);
	}

	// 右左旋函数
	RAVL RL_Rotion(RAVL& Head)
	{
		Head->left = RR_Rotion(Head->left);
		return LL_Rotion(Head);
	}

	// 构建路由器平衡树
	RAVL InsertRAVL(RAVL& Head, const string& name)
	{
		if (!Head)
		{
			//插入新节点
			Head = new RTNode{};
			Head->R.name = name;
			Head->left = Head->right = nullptr;
			Head->visited = false;
			Head->Height = 1;
		}
		else if (name < Head->R.name)
		{
			//插入左子树
			Head->left = InsertRAVL(Head->left, name);
			//检测是否需要旋转
			if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
				if (name < Head->left->R.name)
					Head = LL_Rotion(Head);
				else
					Head = RL_Rotion(Head);
		}
		else if (name > Head->R.name)
		{
			//插入右子树
			Head->right = InsertRAVL(Head->right, name);
			//判断是否需要旋转
			if (GetHeight(Head->right) - GetHeight(Head->left) == 2)
				if (name > Head->right->R.name)
					Head = RR_Rotion(Head);
				else
					Head = LR_Rotion(Head);
		}
		//更新树高
		Head->Height = max(GetHeight(Head->left), GetHeight(Head->right)) + 1;
		return Head;
	}

	//平衡树删除
	RAVL DeleteRAVL(RAVL& Head, const string& name)
	{
		if (!Head)
			return nullptr;
		if (name < Head->R.name)
		{
			//删除左子树
			Head->left = DeleteRAVL(Head->left, name);
			//判断是否旋转
			if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
				if (name < Head->left->R.name)
					Head = LL_Rotion(Head);
				else
					Head = RL_Rotion(Head);
		}
		else if (name > Head->R.name)
		{
			//删除右子树
			Head->right = DeleteRAVL(Head->right, name);
			//判断是否旋转
			if (GetHeight(Head->right) - GetHeight(Head->left) == 2)
				if (name > Head->right->R.name)
					Head = RR_Rotion(Head);
				else
					Head = LR_Rotion(Head);
		}
		else
		{
			//找到了要删除顶点
			if (Head->left && Head->right)
			{
				RAVL MinNode = FindMinRAVL(Head->right);
				Head->R.name = MinNode->R.name;
				Head->R.network = MinNode->R.network;
				Head->R.rlist = MinNode->R.rlist;
				Head->right = DeleteRAVL(Head->right, MinNode->R.name);
				//删除后判断左右子树是否平衡
				if (GetHeight(Head->right) - GetHeight(Head->left) == -2)
					if (Head->R.name < Head->left->R.name)
						Head = LL_Rotion(Head);
					else
						Head = RL_Rotion(Head);
			}
			else
			{
				RAVL temp = Head;
				if (Head->left)
					Head = Head->left;
				else
					Head = Head->right;
				delete temp;
			}
		}
		//更新树高
		if (Head)
		{
			Head->Height = GetHeight(Head);
		}
		return Head;
	}
	//平衡二叉树查找
	RAVL FindRAVL(const RAVL& Head, const string& name)
	{
		if (!Head)
		{
			return nullptr;
		}
		if (name < Head->R.name)
		{
			return FindRAVL(Head->left, name);
		}
		else if (name > Head->R.name)
		{
			return FindRAVL(Head->right, name);
		}
		else
			return Head;
	}
	//创建空队列
	Queue CreateQueue()
	{
		Queue Q = new QNode;
		Q->front = Q->Rear = NULL;
		return Q;
	}
	//判断队列是否为空
	bool IsEmptyQ(Queue Q)
	{
		return (Q->front == nullptr);
	}
	//压入队列
	void PushQ(Queue Q, Router& R)
	{
		Position RearCell = new Node;
		RearCell->R = R;
		RearCell->next = nullptr;
		if (IsEmptyQ(Q))
			Q->front = Q->Rear = RearCell;
		else
		{
			Q->Rear->next = RearCell;
			Q->Rear = RearCell;
		}
	}
	//弹出队列
	Router PopQ(Queue Q)
	{
		Position FrontCell;
		Router FrontR;

		FrontCell = Q->front;
		if (Q->front == Q->Rear)
			Q->front = Q->Rear = nullptr;
		else
			Q->front = Q->front->next;
		FrontR = FrontCell->R;
		delete FrontCell;
		return FrontR;
	}
	//重置标记
	void ReserVisited(RAVL Head)
	{
		if (Head)
		{
			ReserVisited(Head->left);
			Head->visited = false;
			ReserVisited(Head->right);
		}
	}

	//字典输出路由器地址内置函数
	void _print_ravl(RAVL& Head)
	{
		if(Head){
			_print_ravl(Head->left);
			cout << Head->R.name << " ";
			_print_ravl(Head->right);
		}
	}


	//用bps模拟的路由器报文泛洪传播函数
	bool Flood_Fill(const string& name)
	{
		//创建一个队列
		Queue q = CreateQueue();
		//树内无name直接返回false
		if (!FindRAVL(head, name))
			return false;
		//找到路由器在树中的位置
		RAVL Rp = FindRAVL(head, name);
		//将路由器入队
		PushQ(q, Rp->R);

		//循环出队入队复制网图
		while (!IsEmptyQ(q))
		{
			//出队
			Router R = PopQ(q);
			//找到路由器在自己的网图中的位置
			Edge E = R.network.FindV(R.name)->ep;

			//寻找邻接顶点
			while (E)
			{
				//用邻接点的路由名寻找邻接路由在树中的位置
				Rp = FindRAVL(head, E->name);
				//如果该邻接路由未被标记
				if (!Rp->visited)
				{
					//标记
					Rp->visited = true;
					//将路由的网图赋给邻接顶点的网图
					Rp->R.network = R.network;
					//邻接节点更新路由表
					Rp->R.rlist.deleteRouterList();
					Rp->R.rlist.Make_routerlist(Rp->R.network, Rp->R.name);
					//入队
					PushQ(q, Rp->R);
				}
				E = E->ep;
			}
		}
		//重置标记
		ReserVisited(head);
		return true;
	}

	//递归删除所有的邻接顶点
	void _delete_power(Vert& v, Edge& e) {
		if (e == nullptr)
			return;
		_delete_power(v, e->ep);
		DeletePower(v->name, e->name);
		e = nullptr;
	}
};
//普通用户类
//class user :private OSPF {
//public:
//	//查看某路由器的路由表
//	using OSPF::printRouterlist;
//	//查看从A到B的最小权值路径
//	using OSPF::printMinPath;
//	//查看网络拓扑图
//	using OSPF::printNetwork;
//};
//
////管理员类
//class Administrator :public OSPF {
//
//};