#include"User.h"
using namespace std;

void adFunction();
void userFunction();
void _userFunction();
int main()
{
	//text:Container
		//text:G1 = G2;
		//text data:
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 5
		4 5 1
		5 1 2*/
		/*Graph G1;
		Graph G2;
		for (int i = 1; i <= 5; i++)
		{
			string s;
			cin >> s;
			G2.AddV(s);
		}
		for (int i = 1; i <= 5; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1 >> s2 >> p;
			G2.AddEdge(s1, s2, p);
		}
		G1 = G2;
		G2.printG();
		G1.printG();*/


		//text:InitGraph()
		//text:data
		/*1 2 3 4
		1 2 3
		2 3 4
		3 4 1
		4 1 2
		2 3 4 5
		2 3 4
		3 4 5
		4 5 2
		5 2 3*/
		/*Graph G1, G2;
		for (int i = 1; i <= 4; i++)
		{
			string s;
			cin >> s;
			G1.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G1.AddEdge(s1, s2, p);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s;
			cin >> s;
			G2.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G2.AddEdge(s1, s2, p);
		}
		G1.printG();
		cout << endl;
		G2.printG();
		cout << endl;
		G1.InitGraph(G2);
		G1.printG();
		cout << endl;
		G2.InitGraph(G1);
		G2.printG();*/


		//text:DeleteAllDisconnect()
		//text:data
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 1
		4 1 2*/
		/*Graph G;
		for (int i = 1; i <= 5; i++)
		{
			string s;
			cin >> s;
			G.AddV(s);
		}
		for (int i = 1; i <= 4; i++)
		{
			string s1;
			string s2;
			int p;
			cin >> s1;
			cin >> s2;
			cin >> p;
			G.AddEdge(s1, s2, p);
		}
		G.DeleteAllDisconnect("3");
		G.printG();*/


	//text:RoutList
		//text:Make_routerlist()
		//text:data
		/*1 2 3 4 5
		1 2 3
		2 3 4
		3 4 5
		4 5 1
		5 1 3*/
		/*Graph G;
		for (int i = 1; i <= 5; i++)
		{
			string name;
			cin >> name;
			G.AddV(name);
		}
		for (int i = 1; i <= 3; i++)
		{
			string s1, s2;
			int power;
			cin >> s1 >> s2 >> power;
			G.AddEdge(s1, s2, power);
		}
		RoutList R;
		R.Make_routerlist(G, "1");
		R.printRouters();*/
	//text:OSPF.h
		//text:InitAllNetWork()+SaveAllNetwork()
		/*OSPF O;
		O.AllNetwork.printG();
		for (int i = 1; i <= 2;i++) {
			string s;
			cin >> s;
			O.AllNetwork.AddV(s);
		}
		for (int i = 1; i <= 4; i++) {
			string s1;
			string s2;
			int power;
			cin >> s1 >> s2 >> power;
			O.AllNetwork.AddEdge(s1, s2, power);
		}
		O.AllNetwork.printG();
		O.SaveAllNetwork();*/
	
		//text:InsertRAVL()+DeleteRAVL()
		//text data:
		/*1 2 3 4 5 6 7 8 9 10
		2 4 6 10*/
		/*OSPF O;
		for (int i = 1; i <= 10; i++) {
			string name;
			cin >> name;
			O.InsertRAVL(O.head, name);
		}
		O.printRAVL();
		for (int i = 1; i <= 4; i++)
		{
			string name;
			cin >> name;
			O.DeleteRAVL(O.head, name);
		}
		O.printRAVL();*/

		//text:AddPower()+AddRouter()
		//text data:
		/*1 2 3 4 5
		1 2 3
		2 3 4
		4 5 6
		4 2 5*/
		//OSPF O;
		//for (int i = 1; i <= 5; i++)
		//{
		//	string name;
		//	cin >> name;
		//	O.AddRouter(name);
		//}
		//O.printRAVL();
		//for (int i = 1; i <= 4; i++)
		//{
		//	string s1, s2;
		//	int power;
		//	cin >> s1 >> s2 >> power;
		//	O.AddPower(s1, s2, power);
		//	O.printRouterNetwork(s1);
		//	cout << endl;
		//	O.printRouterNetwork(s2);
		//	cout << endl;
		//}

		//text:DeletePower()
		//text data:
		/*1 2 3 4
		1 2 3
		2 3 4
		3 4 1
		4 1 2
		1 4
		2 3
		1 2*/
		/*OSPF O;
		for (int i = 1; i <= 4; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 4; i++) {
			string s1, s2;
			int power;
			cin >> s1 >> s2 >> power;
			O.AddPower(s1, s2, power);
		}
		O.AllNetwork.printG();
		cout << endl;
		for (int i = 1; i <= 3; i++)
		{
			string s1, s2;
			cin >> s1 >> s2;
			O.DeletePower(s1, s2);
			O.printRouterNetwork(s1);
			cout << endl;
			O.printRouterRoutlist(s1);
			cout << endl;
			O.printRouterNetwork(s2);
			cout << endl;
			O.printRouterRoutlist(s2);
			cout << endl;
		}*/

		//text:DeleteNearPower()
		//text data
		/*1 2 3 4 5 6
		1 2 3
		1 3 4
		1 4 5
		1 5 6
		1 6 7*/
		/*OSPF O;
		for (int i = 1; i <= 6; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 5; i++)
		{
			string s1, s2;
			int p;
			cin >> s1 >> s2 >> p;
			O.AddPower(s1, s2, p);
		}
		O.AllNetwork.printG();
		O.DeleteNearPower("1");
		O.AllNetwork.printG();*/

		//text DeleteRouter()
		//text data:
		/*1 2 3 4 5 6
		1 2 3
		1 3 4
		1 4 5
		1 5 6
		1 6 1*/
		/*OSPF O;
		for (int i = 1; i <= 6; i++) {
			string s;
			cin >> s;
			O.AddRouter(s);
		}
		O.printRAVL();
		for (int i = 1; i <= 5; i++)
		{
			string s1, s2;
			int p;
			cin >> s1 >> s2 >> p;
			O.AddPower(s1, s2, p);
		}
		O.AllNetwork.printG();
		O.DeleteRouter("1");
		O.AllNetwork.printG();
		O.printRAVL();*/

		//text printMinPath()
		/*OSPF O;
		O.printMinPath("1", "9");
		O.printAllNetwork();*/

	//text：User.h
		//text:User()、InsertUser()、printUser()
		/*User U;

		U.printUsers();
		string s1;
		cin >> s1;		
		U.DeleteUser(s1);
		U.printUsers();
		U.SaveUserBST();*/
	cout << "欢迎来到OSPF路由模拟系统！" << endl<<endl;
	cout << "如果您需要以管理员的身份登录，请输入A。" << endl;
	cout << "普通用户登录请输入B" << endl;
	cout << "普通用户注册请输入C" << endl;
	cout << "退出OSPF路由模拟系统请输入D" << endl;
	cout << "您的输入：";
	char ch;
	cin >> ch;
	while(ch != 'D')
	{

		switch (ch)
		{
		case 'A':
			adFunction();
			cout << endl;
			break;
		case'B':
			userFunction();
			cout << endl;
			break;
		case'C':
			_userFunction();
			cout << endl;
			break;
		default:
			break;
		}
		cout << "如果您需要以管理员的身份登录，请输入A。" << endl;
		cout << "普通用户登录请输入B" << endl;
		cout << "普通用户注册请输入C" << endl;
		cout << "退出OSPF路由模拟系统请输入D" << endl<<endl;
		cout << "您的输入：";
		cin >> ch;
	}
	return 0;
}//任务：补充无向图的顶点删除、邻接顶点删除

void adFunction() {
	cout << "尊敬的管理员，请输入您的账号以及密码登录本平台" << endl;
	cout << "账号：";
	string account;
	cin >> account;
	cout << "密码：";
	string password;
	cin >> password;
	Ad ad;
	int i = ad.FindAd(account);
	if (i == -1) {
		cout << "登录失败！" << endl<<endl;
		return;
	}
	if (ad.Adarray[i].password != password) {
		cout << "密码错误！" << endl << endl;
		return;
	}

	cout << "登录成功！\n\n";
	cout << "尊敬的管理员，您有以下功能的使用权限：\n\n";
	cout << "通用功能：\n";
	cout << "1、查看网络拓扑总图\n";
	cout << "2、查看与某路由器相邻的所有路由器\n";
	cout << "3、查看两路由器间的最短路径，以及经过的路由器\n";
	cout << "4、查看某路由器内部的网络拓扑图\n";
	cout << "5、查看某路由器内部的路由表\n";
	cout << "6、退出登录\n\n";
	cout << "管理员专用功能：\n";
	cout << "7、添加路由器\n";
	cout << "8、添加权值\n";
	cout << "9、修改权值\n";
	cout << "10、删除权值\n";
	cout << "11、删除某路由器的所有邻接边\n";
	cout << "12、删除某路由器\n";
	cout << "13、查看用户信息\n";
	cout << "14、查看网络的线路拥堵情况\n";
	cout << "15、注销用户\n\n";
	cout << "输入相应的序号表示您要使用的功能：";
	int a;
	cin >> a;
	while (a != 6) {
		string ip;
		string from, to;
		int power;
		string account;
		switch (a)
		{
		case 1:
			ad.printAllNetwork();
			cout << endl;
			break;
		case 2:
			cout << "输入路由器地址来查看它的邻接路由器：";
			cin >> ip;
			ad.printAllNetWork(ip);
			cout << endl;
			break;
		case 3:
			cout << "输入起始路由器和终点路由器来查看最短路径\n";
			cout << "起始路由器地址：";
			cin >> from;
			cout << "终点路由器地址：";
			cin >> to;
			ad.printMinPath(from, to);
			cout << endl;
			break;
		case 4:
			cout << "输入路由器地址来查看它内部的网络拓扑图：";
			cin >> ip;
			ad.printRouterNetwork(ip);
			cout << endl;
			break;
		case 5:
			cout << "输入路由器地址来查看它内部的路由表：";
			cin >> ip;
			ad.printRouterRoutlist(ip);
			cout << endl;
			break;
		case 7:
			cout << "输入路由器地址来添加路由器：";
			cin >> ip;
			ad.AddRouter(ip);
			ad.SaveAllNetwork();
			cout << "添加成功\n";
			cout << endl;
			break;
		case 8:
			cout << "输入起始路由器和终点路由器的地址，以及它们之间的权值来添加权值\n";
			cout << "起始路由器地址：";
			cin >> from;
			cout << "终点路由器地址：";
			cin >> to;
			cout << "权值：";
			cin >> power;
			if (ad.AddPower(from, to, power))
			{
				cout << "添加成功\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "添加失败\n";
			cout << endl;
			break;
		case 9:
			cout << "输入起始路由器和终点路由器的地址，以及新权值，来修改它们之间的权值\n";
			cout << "起始路由器地址：";
			cin >> from;
			cout << "终点路由器地址：";
			cin >> to;
			cout << "权值：";
			cin >> power;
			if (ad.ModifyPower(from, to, power))
			{
				cout << "修改成功\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "修改失败\n";
			cout << endl;
			break;
		case 10:
			cout << "输入起始路由器和终点路由器的地址,来删除它们之间的权值\n";
			cout << "起始路由器地址：";
			cin >> from;
			cout << "终点路由器地址：";
			cin >> to;
			if (ad.DeletePower(from, to)) {
				cout << "删除成功\n";
				ad.SaveAllNetwork();
			}
			else
				cout << "删除失败\n";
			cout << endl;
			break;
		case 11:
			cout << "输入路由器地址来删除它的所有邻接边：";
			cin >> ip;
			ad.DeleteNearPower(ip);
			ad.SaveAllNetwork();
			cout << endl;
			break;
		case 12:
			cout << "输入路由器地址来删除路由器：";
			cin >> ip;
			ad.DeleteRouter(ip);
			ad.SaveAllNetwork();
			cout << endl;
			break;
		case 13:
			ad.printUsers();
			cout << endl;
			break;
		case 14:
			cout << "起始路由器 -- 终点路由器    拥堵情况\n";
			ad.printPower();
			cout << endl;
			break;
		case 15:
			cout << "输入用户账号来删除用户：";
			cin >> account;
			ad.DeleteUser(account);
			ad.SaveUserBST();
			cout << endl;
			break;
		default:
			break;
		}
		cout << "输入相应的序号表示您要使用的功能：";
		cin >> a;
	}
}

void userFunction() {
	cout << "尊敬的用户，请输入您的账号以及密码登录本平台" << endl;
	cout << "账号：";
	string account;
	cin >> account;
	cout << "密码：";
	string password;
	cin >> password;
	User U;
	UsersBST Up = U.FindUser(account);
	if (Up == nullptr) {
		cout << "登录失败！" << endl << endl;
		return;
	}
	if (Up->password != password) {
		cout << "密码错误！" << endl << endl;
		return;
	}

	cout << "登录成功！\n\n";
	cout << "尊敬的用户，您有以下功能的使用权限：\n\n";
	cout << "1、查看网络拓扑总图\n";
	cout << "2、查看与某路由器相邻的所有路由器\n";
	cout << "3、查看两路由器间的最短路径，以及经过的路由器\n";
	cout << "4、查看某路由器内部的网络拓扑图\n";
	cout << "5、查看某路由器内部的路由表\n";
	cout << "6、查看网络的拥堵情况\n";
	cout << "7、注销账户\n";
	cout << "8、退出登录\n\n";
	cout << "输入相应的序号表示您要使用的功能：";
	int a;
	cin >> a;
	while (a != 8) {
		string ip;
		string from, to;
		int power;
		switch (a)
		{
		case 1:
			U.printAllNetwork();
			cout << endl;
			break;
		case 2:
			cout << "输入路由器地址来查看它的邻接路由器：";
			cin >> ip;
			U.printAllNetWork(ip);
			cout << endl;
			break;
		case 3:
			cout << "输入起始路由器和终点路由器来查看最短路径\n";
			cout << "起始路由器地址：";
			cin >> from;
			cout << "终点路由器地址：";
			cin >> to;
			U.printMinPath(from, to);
			cout << endl;
			break;
		case 4:
			cout << "输入路由器地址来查看它内部的网络拓扑图：";
			cin >> ip;
			U.printRouterNetwork(ip);
			cout << endl;
			break;
		case 5:
			cout << "输入路由器地址来查看它内部的路由表：";
			cin >> ip;
			U.printRouterRoutlist(ip);
			cout << endl;
			break;
		case 6:
			cout << "起始路由器 -- 终点路由器    拥堵情况\n";
			U.printPower();
			cout << endl;
			break;
		case 7:
			cout << "输入您的账户和密码来注销账号\n";
			cout << "账号：";
			cin >> account;
			cout << "密码：";
			cin >> password;
			Up = U.FindUser(account);
			if (Up->password != password) {
				cout << "密码错误！" << endl << endl;
				break;
			}
			U.DeleteUser(account);
			U.SaveUserBST();
			cout << "注销成功\n";
			cout << endl;
			return;
		default:
			break;
		}
		cout << "输入相应的序号表示您要使用的功能：";
		cin >> a;
	}
}

void _userFunction() {
	cout << "输入您的用户名、账号和密码来注册账户\n";
	string s1, s2, s3;
	cout << "用户名：";
	cin >> s1;
	cout << "账号：";
	cin >> s2;
	cout << "密码：";
	cin >> s3;
	User U;
	U.InsertUser(s1, s2, s3);
	U.SaveUserBST();
	userFunction();
}