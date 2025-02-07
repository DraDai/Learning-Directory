#pragma once
#include"Network.h"
struct RNode {
	string name;
	string NextJump;
	RNode* next;
};
typedef RNode* RLink;//路由表节点

struct PNode {
	string name;
	int dist;
	string parent;
	bool flag;
	PNode* next;
};
typedef PNode* Path;	//路径结构，用于构建路由表

class RoutList
{
public:
	RLink routerlist;	//路由表

	//无参构造函数，初始化路由表
	RoutList() : routerlist(new RNode{"", "", nullptr}) {}

	//根据路由器的地址以及它的网络拓扑图构建路由表
	void Make_routerlist(Graph& G, const string& name)
	{
		routerlist->name = name;
		//通过网络拓扑图和路由器地址初始化路径结构表
		Path P = CreatePath(G, name);
		//迪杰斯特拉构造Path表
		Dijkstra(P, G);
		//通过Path表构造路由表
		_make_routers(P);
	}

	//查找路由表
	string FindRoutlist(const string& to) {
		RLink RL = routerlist->next;
		while (RL) {
			if (RL->name == to) {
				return RL->NextJump;
			}
			RL = RL->next;
		}
		return "";
	}

	//清除路由表，只留头节点
	void deleteRouterList()
	{
		//内置清除函数
		_delete_routerlist(routerlist->next);
	}

	//输出路由表
	void printRouters()
	{
		RLink t = routerlist->next;
		cout << routerlist->name << " 的路由表:" << endl;
		while (t)
		{
			cout << "To ---> " << t->name << "  NextJump: " << FindRouters(t->name) << endl;
			t = t->next;
		}
	}

private:
	//通过网络拓扑图初始化路径结构表
	Path CreatePath(Graph& G, const string& name)
	{
		//初始化头节点
		Path P = new PNode{};

		P->name = name;
		P->dist = 0;
		P->flag = true;
		P->parent = "";
		P->next = nullptr;

		Vert t = G.head->vp;
		while (t)
		{
			//将与本地路由器联通的且不是本地路由器的路由器插入Path
			if (t != G.FindV(name) && G.IsConnectivity(name, t->name))
			{
				Path pp = new PNode{};

				//元素赋值
				pp->name = t->name;
				pp->dist = G.Getpower(name, t->name);
				pp->flag = false;
				pp->parent = name;

				//头插法插入P链表
				pp->next = P->next;
				P->next = pp;
			}
			t = t->vp;
		}
		return P;
	}

	//迪杰斯特拉寻找单源最短路径
	void Dijkstra(Path P, Graph& G)
	{
		//图中与本地路由器联通的路由器都被标记，则退出
		if (IsFullFlag(P))
			return;

		//找未被标记的与本地路由器dist最小的路由器，并将其标记
		Path minp = FindMinPath(P);

		//更新dist
		UpDist(P, minp, G);
		Dijkstra(P, G);
	}

	//判断标记是否已满
	bool IsFullFlag(Path P)
	{
		Path pp = P->next;
		while (pp)
		{
			//有未被标记的节点返回标记未满
			if (!pp->flag)
			{
				return false;
			}
			
			//检查下一个节点
			pp = pp->next;
		}
		return true;
	}

	//找最小dist未标记顶点
	Path FindMinPath(Path P)
	{
		Path pp = P->next;
		int min = INF;
		Path minp = pp;

		//循环找到最小dist值
		while (pp)
		{
			//如果该节点未被标记且dist比min小，则将dist赋给min,将节点指针赋给minp
			if (!pp->flag && pp->dist < min)
			{
				min = pp->dist;
				minp = pp;
			}
			pp = pp->next;
		}

		//给找到的最小dist节点打上标记
		minp->flag = true;
		//返回最下dist节点
		return minp;
	}

	//更新dist
	void UpDist(Path P, Path minp, Graph& G)
	{
		Path p = P->next;

		//循环更新dist
		while (p)
			{
			//如果p节点未被标记，且它到最小dist节点的权值和最小dist相加小于自己的dist，则更新自己的dist
			if (!p->flag && p->dist > G.Getpower(p->name, minp->name) + minp->dist)
			{
				p->dist = G.Getpower(p->name, minp->name) + minp->dist;
				//更新自己的parent为最小dist节点地址
				p->parent = minp->name;

			}
			p = p->next;
		}
	}
	//通过Path表构造路由表,结束后删除Path表
	void _make_routers(Path P)
	{
		Path p = P->next;
		//循环遍历Path表构造路由表
		while (p)
		{
			RLink r = new RNode{};
			//赋值
			r->name = p->name;
			//找到本地路由器到p节点的下一跳
			r->NextJump = NextJump(P, p);
			//头插法将r节点插入路由表
			r->next = routerlist->next;
			routerlist->next = r;
			//下一个path节点
			p = p->next;
		}
		//删除Path表
		deletePath(P);
	}

	//找到本地路由器到to节点的下一跳
	string NextJump(Path P, Path to)
	{
		//当to节点的parent不是本地路由器地址时，将parent的指针赋给to
		while (to->parent != P->name)
		{
			//找到parent在P表中的位置
			to = GetPath(P, to->parent);
		}
		//返回to
		return to->name;
	}

	//找到str在P表中的位置
	Path GetPath(Path P, string str)
	{
		Path p = P;
		while (p)
		{
			if (p->name == str)
			{
				return p;
			}
			p = p->next;
		}
		return nullptr;
	}
	
	//删除Path表
	void deletePath(Path P)
	{
		if (P == nullptr)
			return;
		//递归删除后面的节点
		deletePath(P->next);
		//删除本本结点
		delete P;
		//将p置空
		P = nullptr;
	}

	string FindRouters(string to)
	{
		RLink t = routerlist->next;
		while (t)
		{
			if (t->name == to)
				return t->NextJump;
			t = t->next;
		}
	}
	
	//内置清除路由表函数
	void _delete_routerlist(RLink& Rp)
	{
		if (Rp == nullptr)
			return;
		_delete_routerlist(Rp->next);
		delete Rp;
		Rp = nullptr;
	}
};

