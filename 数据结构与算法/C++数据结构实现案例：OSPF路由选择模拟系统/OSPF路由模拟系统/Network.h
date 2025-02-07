#pragma once
#include<string>
#include<iostream>
using namespace std;
const int INF = 65505;
//顶点结构
struct ENode {
	string name;
	int power;
	ENode* ep;
};
typedef ENode* Edge;
struct VNode {
	string name;
	//指向下一顶点指针
	VNode* vp;
	Edge ep;
	//标记
	bool visited;
	//初始化标记
	VNode() :visited(false) {};
};
typedef VNode* Vert;
//权值结构

//带权重边的结构
struct WeightEdge {
	string from;
	string to;
	int weight;

};

class Graph{
public:
	Vert head;	//邻接表
	int Vsum;
	int Esum;	
	//默认构造函数初始化网络拓扑图
	Graph() :head(new VNode{}), Vsum(0), Esum(0) {
		head->name = "";
		head->ep = nullptr;
		head->vp = nullptr;
	}
	//复制构造网络拓扑图,即自定义深拷贝函数,这里用重载赋值运算符实现深拷贝
	Graph& operator = (const Graph& other)
	{ 
		//避免自我赋值
		if (this == &other)
		{
			return *this;
		}
		//删除现有资源
		deleteGraph(head->vp);

		//进行深拷贝
		copyV(other.head->vp, head->vp);
		Vsum = other.Vsum;
		Esum = other.Esum;

		return *this;
	}

	//析构函数用于释放深拷贝的资源
	~Graph() {
		deleteGraph(head->vp);
		delete head;
	}

	//增添构造网络拓扑图
	void InitGraph(const Graph& other)
	{
		//根据传来的其他网络拓扑图，补充自己缺少的信息
		Vert otherV = other.head->vp;
		//补充不存在的顶点信息
		while (otherV != nullptr)
		{
			if (!FindV(otherV->name))
				AddV(otherV->name);
			//处理下一个顶点
			otherV = otherV->vp;
		}

		//补充边信息
		otherV = other.head->vp;
		//查找所有顶点
		while (otherV != nullptr)
		{
			Edge otherE = otherV->ep;
			//查找other顶点的所有边
			while (otherE != nullptr)
			{
				if (!FindE(otherV->name, otherE->name))
					AddEdge(otherV->name, otherE->name, otherE->power);
				//继续处理下一个边
				otherE = otherE->ep;
			}
			//继续处理下一个顶点
			otherV = otherV->vp;
		}
	}

	//找顶点
	Vert FindV(string V)
	{
		Vert p = head;
		while (p->vp)
		{
			p = p->vp;
			if (p->name == V)
				return p;
		}
		return nullptr;
	}


	//找邻接点
	Edge FindE(string from, string to)
	{
		Vert p = FindV(from);
		Edge Ep;
		Ep = p->ep;
		while (Ep)
		{
			if (Ep->name == to)
				return Ep;
			Ep = Ep->ep;
		}
		return nullptr;
	}

	//判断某顶点是否有邻接顶点
	bool IsEmptyE(string name)
	{
		Vert V = FindV(name);
		if (V->ep)
			return false;
		return true;
	}
	
	//添加顶点
	void AddV(string str)
	{

		Vert v = FindV(str);
		if (v)
			return;
		v = new VNode;	//尾插法
		v->name = str;
		v->ep = nullptr;
		v->vp = head->vp;
		head->vp = v;
		Vsum++;
	}
	
	//修改图权值
	bool AddEdge(string From, string To, int power)
	{
		if (!_AddEdge(From, To, power))
			return false;
		_AddEdge(To, From, power);
		Esum++;
		return true;
	}
	
	//删除图权值
	void DeleteE(string from, string to)
	{
		_DeleteE(from, to);
		_DeleteE(to, from);
		Esum--;
	}
	//删除某点的所有邻接顶点(也就是所有边)
	void DeleteNE(string from)
	{
		Vert p = FindV(from);
		if (!p)
			return;
		if (!p->ep)
			return;
		Edge t = p->ep;
		_delete_ne(p, t);
		p->ep = nullptr;
	}

	//删除图顶点
	void DeleteV(string str)
	{
		if (!FindV(str))
			return;
		DeleteNE(str);
		Vert p = head;
		while (p->vp)
		{
			if (p->vp->name == str)
			{
				Vert t = p->vp;
				p->vp = t->vp;
				delete t;
				Vsum--;
				return;
			}
			p = p->vp;
		}
	}
	
	//删除与某路由器不连通的所有顶点
	void DeleteAllDisconnect(string name)
	{
		if (!FindV(name))
			return;
		Vert V = FindV(name);
		Vert P = head->vp;
		while (P != nullptr)
		{
			if (IsConnectivity(name, P->name))
				P = P->vp;
			else
			{
				Vert temp = P;
				P = P->vp;
				DeleteV(temp->name);
			}
		}
	}

	//查找权值
	int Getpower(string from, string to)
	{
		Edge t = FindE(from, to);
		if (t)
			return t->power;
		return INF;
	}

	//判断联通性
	bool IsConnectivity(const string& from, const string& to)
	{
		if (!FindV(from) || !FindV(to))
			return false;
		//找到from的位置
		Vert V = FindV(from);
		if (V->name == to)
			return true;
		//重置标记
		resetVisited();
		//深度优先搜索判断连通性
		return dfs(from, to);
	}

	//判断图是否为空
	bool IsEmptyGraph()
	{
		if (head->vp == nullptr)
			return true;
		return false;
	}
	//输出顶点
	void printV()
	{
		Vert p = head;
		if (!head->vp)
			cout << "图为空" << endl;
		while (p->vp)
		{
			p = p->vp;
			cout << p->name << " ";
		}
		cout << endl;
	}
	//输出图表
	void printG()
	{
		if (IsEmptyGraph())
			cout << "图为空" << endl;
		Vert p = head;
		while (p->vp)
		{
			p = p->vp;
			cout << p->name;
			Edge t = p->ep;
			while (t)
			{
				cout <<"---->" << t->name;
				t = t->ep;
			}
			cout << endl;
		}
	}
	//输出权值
	void printP(string from, string to)
	{
		int n = Getpower(from, to);
		if (n == INF)
		{
			cout << "两顶点间无权值" << endl;
			return;
		}
		cout << n << endl;
	}
	//输出邻接顶点
	void printNE(string from)
	{
		Vert p = FindV(from);
		if (!p)
			return;
			Edge t = p->ep;
		while (t)
		{
			cout << t->name << " ";
			t = t->ep;
		}
		cout << endl;
	}

	//对权值进行排序并打印
	void SortPrintEdge() {
		const int MAX_EDGE = 1000;	//假设边的最大数
		WeightEdge edges[MAX_EDGE];
		int size = 0;
		//获取所有边
		GetAllEdges(edges, size);

		//使用快排排序
		QuickSortEdges(edges, 0, size - 1);

		cout << "网络线路状况：\n";
		if (size > 0) {
			cout << edges[0].from << " -- " << edges[0].to << "    " << edges[0].weight << endl;
		}
		
		for (int i = 1; i < size; i++) {
			if (edges[i].from != edges[i - 1].from || edges[i].to != edges[i - 1].to || edges[i].weight != edges[i - 1].weight)
				cout << edges[i].from << " -- " << edges[i].to << "    " << edges[i].weight << std::endl;
		}
	}
private:
	//递归深拷贝顶点
	void copyV(Vert otherV, Vert& V)
	{
		if (otherV == nullptr)
		{
			V = nullptr;
			return;
		}
		//复制当前顶点
		V = new VNode;
		V->name = otherV->name;
		V->ep = nullptr;
			
		//递归复制邻接边
		copyE(otherV->ep, V->ep);

		//递归复制下一顶点
		copyV(otherV->vp, V->vp);
	}

	//递归深拷贝边
	void copyE(Edge otherE, Edge& E)
	{
		if (otherE == nullptr)
		{
			E = nullptr;
			return;
		}

		//复制当前边
		E = new ENode;
		E->name = otherE->name;
		E->power = otherE->power;
		E->ep = nullptr;

		//递归复制下一边
		copyE(otherE->ep, E->ep);
	}

	//释放顶点和边的资源
	void deleteGraph(Vert& V)
	{
		if (V == nullptr)
			return;

		//递归释放邻接边
		deleteE(V->ep);

		//递归释放下一顶点
		deleteGraph(V->vp);
	
		//释放当前顶点
		delete V;
		V = nullptr;
	}

	//递归释放边的资源
	void deleteE(Edge& E)
	{
		if (E == nullptr)
			return;

		//递归释放下一边
		if(E->ep != nullptr)
			deleteE(E->ep);
		//释放当前边
		delete E;
		E = nullptr;
	}



	//修改图权值内置函数
	bool _AddEdge(string From, string To, int power)
	{
		Vert p = FindV(From);
		if (!p)
			return false;
		Edge t = FindE(From, To);
		if (!p)
			return false;
		if (t)
		{
			t->power = power;
			return true;
		}
		t = new ENode;		//尾插法
		t->name = To;
		t->power = power;
		t->ep = p->ep;
		p->ep = t;
		return true;
	}

	//删除图权值内置函数
	void _DeleteE(const string& from, string to)
	{
		Vert p = FindV(from);
		if (!p)
			return;
		Edge t = p->ep;
		if (!t)
		{
			return;
		}
		if (t->name == to)
		{
			p->ep = t->ep;
			delete t;
			return;
		}
		while (t->ep)
		{
			if (t->ep->name == to)
			{
				Edge T = t->ep;
				t->ep = T->ep;
				delete T;
				Esum--;
				return;
			}
			t = t->ep;
		}
	}

	//深搜判断联通性
	bool dfs(const string& from, const string& to)
	{
		//查找当前顶点
		Vert V = FindV(from);
		
		if (V && V->visited)
			return false;

		if (V)
			V->visited = true;

		if (from == to)
			return true;

		Edge E = V ? V->ep : nullptr;

		while (E) {
			if (dfs(E->name, to))
				return true;
			E = E->ep;
		}

		return false;
	}

	//重置标记
	void resetVisited() {
		Vert V = head->vp;
		while (V) {
			V->visited = false;
			V = V->vp;
		}
	}

	//递归删除所有邻接边
	void _delete_ne(const Vert& v, Edge& e) {
		if (e == nullptr)
			return;
		_delete_ne(v, e->ep);
		DeleteE(v->name, e->name);
		e = nullptr;
	}

	//获取图中所有边
	void GetAllEdges(WeightEdge* edges, int& size) {
		size = 0;
		Vert p = head;
		while (p->vp) {
			p = p->vp;
			Edge t = p->ep;
			while (t) {
				edges[size].from = p->name;
				edges[size].to = t->name;
				edges[size].weight = t->power;
				size++;
				t = t->ep;
			}
		}
	}

	//快速排序
	void QuickSortEdges(WeightEdge* edges, int low, int high) {
		if (low < high) {
			int pivot = low;
			int i = low + 1;
			int j = high;

			while (i <= j) {
				if (edges[i].weight < edges[pivot].weight)
					i++;
				else if (edges[j].weight > edges[pivot].weight)
					j--;
				else
				{
					swap(edges[i], edges[j]);
					i++;
					j--;
				}
			}

			swap(edges[pivot], edges[j]);

			QuickSortEdges(edges, low, j - 1);
			QuickSortEdges(edges, j + 1, high);
		}
	}
};