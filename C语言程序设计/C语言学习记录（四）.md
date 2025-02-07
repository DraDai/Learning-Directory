# C语言学习记录（四）

## 一，知识要点（程序控制结构）

#### 1、==c语言的执行语句==

- ​	**表达式语句**

  - C语言中最常见的语句，格式为：**表达式；**
  - **赋值语句**
    - 格式：**变量 赋值运算符 表达式；**
    - 赋值语句不能出现在表达式中。
  - **函数调用语句**：通过执行函数调用语句，实现所调用的函数特定功能。

- **空语句**
  - 只在逻辑上起到一个语句的作用，相当于不存在，格式只有一个”；“
  - 常用于：**构成标号语句，表示流程的转向点**或者**构成循环语句中的空循环体**。例如`while(getchar()!='\n');`表示输入的如果不是回车就重新输入。
  
- **复合语句**

  - 用{}把多个语句括起来构成一个整体叫**复合语句**。

  - 复合语句在语法上**是一个语句**，而不是多个语句
  - 复合语句一般作为选择语句**某分支内嵌的语句**或作为**循环语句的循环体**。
  - 复合语句又称**分程序**，他有自己的数据说明部分。

- **控制语句**：用于控制程序的流程，C语言中有9中控制语句，后面会写。

#### 2、==顺序结构==

- 程序运行时自上而下依次运行语句这种程序结构称为顺序结构。

  - 典型的顺序结构由以下三个部分构成：

    - 使 操作对象获得原始数据；
    - 进行运算；
    - 输出运算结果。

  - ```c++
    #include<stdio.h>//输入任意两个整数，求他们的和及平均值。
    #include<math.h>
    int main()
    {
    	int a, b, sum;
    	double aver;
    	printf("请输入两个整数：");
    	scanf("%d%d", &a, &b);
    	sum = a + b;
    	aver = sum / 2.0;
    	printf("sum = %d\naver = %.2lf", sum, aver);
    	return 0; 
    }
    ```

  - ```c++
    #include<stdio.h>//给定一个三位数整数，分别输出它的个位，十位和百位
    #include<math.h>
    int main()
    {
    	int num, m1, m2, m3;
    	printf("请输入一个三位数整数：");
    	scanf("%d", &num);
    	m1 = num / 100;//百位
    	m2 = num / 10 % 10;//十位
    	m3 = num % 10 % 10;//个位
    	printf("百位: %d,十位: %d,个位: %d", m1, m2, m3);
    	return 0; 
    }
    ```

  - ```c++
    #include<stdio.h>//取一个16位二进制数a的7~4位
    #include<math.h>
    int main()
    {
    	int a, b;
    	printf("输入一个整数：");
    	scanf("%d", &a);
    	a = a >> 4;
    	b = ~(~0 << 4);//设置一个后四位都为1的数
    	a = a & b;//清掉a的后四位前的1
    	printf("%d", a);
    	return 0; 
    }
    ```

  - ```c++
    #include<stdio.h>//以保证a不等于0，且有两个不同的根，求ax^2+bx+c=0的根
    #include<math.h>
    int main()
    {
    	double x1, x2, a, b, c, d;
    	printf("请分别输入三个系数a,b,c的值");
    	scanf("%lf%lf%lf", &a, &b, &c);
    	d = b * b - 4 * a * c;
    	x1 = (-b + sqrt(d)) / (2 * a);
    	x2 = (-b - sqrt(d)) / (2 * a);
    	printf("x1 = %.2lf\nx2 = %.2lf", x1, x2);
    	return 0; 
    }
    ```

#### 3、==选择结构==

- **条件选择语句：if语句**

  - if语句用于实现选择结构，他有三种基本格式；**单分支if、双分支if-else、多分支if-else if**

  - **单分支if**

    - 格式为：if（表达式）  换行  语句。该语句只有一个分支，如果真则执行，否则不执行。

    - 作为条件的表达式应**具有一定意义、有实用价值**，因此最常用关系表达式和逻辑表达式。

    - ```c++
      #include<stdio.h>//输入大写字母，输出小写字母
      int main()
      {
      	char c;
      	printf("输入一个大写字母: ");
      	c = getchar();
      	if ('A' <= c && c <= 'Z')
      		c = c + 32;//小写字母的ASCII值比大写的大32
      	printf("%c\n", c);
      	return 0; 
      }
      ```

    - ```c++
      #include<stdio.h>//输入两个数，按升序输出这两个数
      int main()
      {
      	double a, b, t;
      	printf("输入两个数：");
      	scanf("%lf%lf", &a, &b);
      	if (a > b)
      	{
      		t = a;
      		a = b;
      		b = t;//交换a和b
      	}
      	printf("%.2lf  %.2lf", a, b);
      	return 0; 
      }
      ```

  - **双分支if-else**

    - 格式为：if（表达式） 换行 语句1 换行 else 换行 语句2。该语句有两个分支，**如果真，则执行语句1，否则执行语句2**。

    - ```c++
      #include<stdio.h>//输入两个数，按升序输出这两个数
      int main()
      {
      	double a, b, t;
      	printf("输入两个数：");
      	scanf("%lf%lf", &a, &b);
      	if (a > b)
      		printf("%.2lf %.2lf", b, a);
      	else
      		printf("%.2lf %.2lf", a, b);
      	return 0; 
      }
      ```

  - **多分支if-else if**

    - 前两种格式用于单个分支和双个分支的情况。当有多个分支供选择时，可采用此语句。格式为：if()    ;    else if()    ;     else if()     ;……  else     ；

    - 各分支内嵌的语句均可以是单个语句或者复合语句1。并且可以没有else分支。

    - 功能：依次判断括号内各表达式的值，若其中一个值为真，则执行该语句；若全都为假，则执行else内的值。

    - ```c++
      #include<stdio.h>//判断输入的百分制成绩属于哪个分数段，进而输出相应的五级制成绩
      int main()
      {
      	int score;
      	printf("请输入你的分数：");
      	scanf("%d", &score);
      	if (score >= 90)
      		printf("A\n");
      	else if (score >= 80)
      		printf("B\n");
      	else if (score >= 70)
      		printf("C\n");
      	else if (score >= 60)
      		printf("D\n");
      	else
      		printf("E\n");
      	return 0; 
      }
      ```

    - ```c++
      #include<stdio.h>//计算分段函数
      int main()
      {
      	double x, y;
      	scanf("%lf", &x);
      	if (x < 0)
      		y = 0;
      	else if (x > 50)
      		y = x * x;
      	else
      		y = x;
      	printf("%lf", y);
      	return 0; 
      }
      ```

  - **if语句的嵌套**

    - 一个if语句中的某个分支又完整的包含了另一个if语句，叫做**if语句的嵌套**。

    - 书写if语句的嵌套时，要特别注意if和else的配对关系，因为**else总是与它前面最近未配对的if配对**。

    - ```c++
      #include<stdio.h>//在if分支中内嵌带else的if语句
      int main()
      {
      	double x, y;
      	scanf("%lf", &x);
      	if (x > 0)
      		if (x <= 50)
      			y = x;
      		else
      			y = x * x;
      	else
      		y = 0;
      	printf("x = %lf,y = %lf\n", x, y);
      	return 0;
      }
      ```

    - ```c++
      #include<stdio.h>//在if分支中内嵌不带else的if语句
      int main()
      {
      	double x, y;
      	scanf("%lf", &x);
      	if (x > 0)
      	{//这里打上大括号是为了防止嵌套的if与else配对
      		if (x >= 50)
      			y = x;
      	}
      	else
      		y = 0;
      	printf("x = %lf,y = %lf\n", x, y);
      	return 0;
      }
      ```

- **swich语句**

  - switch语句可以根据一个表达式的不同取值来实现对分支的选择。废话不多说，直接看实例。

  - ```c++
    #include<stdio.h>//switch语句：输入五级制语句，输出相应的百分制成绩段
    int main()
    {
    	char grade;
    	grade = getchar();
    	grade = (grade >='a' && grade <= 'z' ? grade - 32 : grade);
    	switch (grade)//switch语句，括号内写一个表达式
    	{
    	case'A':
    		printf("90~100\n");//如果grade是A，则打印这个。后面同理
    		break;//结束语句，如果有break就停止switch的执行。
    	case'B':
    		printf("80~89\n");
    		break;
    	case'C':
    		printf("70~79");
    		break;
    	case'D':
    		printf("60~69\n");
    	case'E':
    		printf("<60\n");
    	default://结束语句，如果case都没用就执行此语句
    		printf("error\n");
    	}
    	return 0;
    }
    ```

  - **说明：**

    - 各个case分支的常量表达式的类型都要与switch括号内的表达式**类型一致**。
    - 各个分支内的语句**允许内嵌语句，而且可以不用{}括起来**。
    - 如果没有break语句，那么执行完这个case语句后，就会继续执行下一个case语句。
    - 可以没有defaul分支，这样如果case分支都不对，则不执行switch内任何语句。
    - 如果一个case语句为空，则代表它和后续分支公用同一组内嵌语句。

  - ```c++
    #include<stdio.h>//switch语句：输入百分制语句，输出相应的五级制成绩段
    int main()
    {
    	int score;
    	printf("输入您的分数：");
    	scanf("%d", &score);
    	switch (score / 10)
    	{
    	case 10:case 9:
    		printf("A\n");
    		break;
    	case 8:
    		printf("B\n");
    		break;
    	case 7:
    		printf("C\n");
    		break;
    	case 6:
    		printf("D\n");
    		break;
    	default:
    		printf("E\n");
    	}
    	return 0;
    }
    ```

- **选择结构的嵌套**

  - ```c++
    #include<stdio.h>//编写一个计算器程序
    int main()
    {
    	double a, b;
    	char c;
    	printf("请输入计算式: ");
    	scanf("%lf%c%lf", &a, &c, &b);
    	switch (c)
    	{
    	case '+':
    		printf("%lf", a + b);
    		break;
    	case'-':
    		printf("%lf", a - b);
    		break;
    	case'*':
    		printf("%lf", a * b);
    		break;
    	case'/':
    		if (b == 0)
    			printf("你不能这么写");
    		else
    			printf("%lf", a / b);
    	default:
    		printf("你写的啥");
    	}
    	return 0;
    }
    ```

- **选择结构程序的举例**

  - ```c++
    #include<stdio.h>//判断输入的字符类型
    int main()
    {
    	char a;
    	printf("请输入一个字符：");
    	a = getchar();
    	if (a >= '0' && a <= '9')
    		printf("这是数字类型字符。\n");
    	else if (a >= 'A' && a <= 'Z')
    		printf("这是大写字母。\n");
    	else if (a >= 'a' && a <= 'z')
    		printf("这是小写字母");
    	else
    		printf("程序错误，请重新输入。\n");
    	return 0;
    }
    ```

  - ```c++
    #include<stdio.h>//输入三边长，求三角形面积
    #include<math.h>
    int main()
    {
    	double a, b, c, area, s;
    	scanf("%lf%lf%lf", &a, &b, &c);
    	if (a + b > c && b + c > a && a + c > b)
    	{
    		s = (a + b + c) / 2;
    		area = sqrt(s * (s - a) * (s - b) * (s - c));
    		printf("area = %7.2lf\n", area);
    	}
    	else
    		printf("格式错误\n");
    	return 0;
    }
    ```

  - ```c++
    #include<stdio.h>//输入三个整数，输出最大的数和最小的数
    #include<math.h>
    int main()
    {
    	int a, b, c, max, min;
    	scanf("%d%d%d", &a, &b, &c);
    	max = a > b ? a : b;
    	min = a < b ? a : b;
    	if (max < c)
    		max = c;
    	else if (min > c)
    		min = c;
    	printf("max = %d,min = %d", max, min);
    	return 0;
    }
    ```

  - ```c++
    #include<stdio.h>//计算a*x*2+b*x+c=0的实数根
    #include<math.h>
    int main()
    {
    	double a, b, c, d, x1, x2,x;
    	scanf("%lf%lf%lf", &a, &b, &c);
    	d = b * 2 - 4 * a * c;
    	if (a == 0)
    		if (b == 0)
    			if (c == 0)
    				printf("此方程有无穷实数根。\n");
    			else
    				printf("此方程无解。\n");
    		else
    		{
    			x = -c / b;
    			printf("x = %.2lf", x);
    		}
    	else
    		if (d >= 0)
    		{
    			x1 = (-b + sqrt(d)) / (2 * a);
    			x2 = (-b - sqrt(d)) / (2 * a);
    			printf("x1 = %.2lf,x2 = %.2lf", x1, x2);
    		}
    		else
    			printf("此公式无实数根。\n");
    	return 0;
    }
    ```

#### 4、==循环结构==

- 循环结构的特点是，**在给定条件成立时，反复执行某程序段，直到条件不成立为止**。

- **while语句**：他的格式是什么？看实例就完了！

  - ```c++
    #include<stdio.h>//while实例:计算1+2+3……+100的和
    int main()
    {
    	int i = 1, sum = 0;//设置循环变量i和迭代变量sum
    	while (i <= 100)//循环条件，决定了循环是否进行
    	{//循环体语句，既可以是单个语句，也可以是复合语句
    		sum = sum + i;
    		i++;
    	}
    	printf("sum = %d", sum);
    	return 0;
    }
    ```

    - 计算表达式的值，**若值为真，则执行循环语句，为假则退出循环**。
    - 在循环语句中一定要有循环变量，不然执行程序的时候会陷入死循环。

  - ```c++
    #include<stdio.h>//计算n的阶乘
    int main()
    {
    	int i = 1, p = 1, n;
    	scanf("%d", &n);
    	while (i <= n)
    	{
    		p *= i;
    		i++;
    	}
    	printf("n! = %d", p);
    	return 0;
    }
    ```

    - 本题使用了**递推算法**：后一项的值对前一个或前几个值有某种依赖关系。一般**先确定初始条件或边界条件**，**再找出递推公式**。
    - 在每次循环中，p的值都会被刷新为别的值，这叫**迭代**。利用循环通过多次迭代，递推出所需的结果，将复杂的数学问题简单化。

  - ```c++
    #include<stdio.h>//猴子吃桃问题
    int main()
    {
    	int i = 9, p = 1;
    	while (i >= 1)
    	{
    		p = 2 * (p + 1);
    		i--;
    	}
    	printf("%d", p);
    	return 0;
    }
    ```

- **用do-while语句实现循环**

  - 此循环结构与while语句的不同的在于：while如果第一次判断为假，则不执行循环语句。而do-while会先执行一次循环语句再判断真假。废话不多说，直接看实例。

  - ```c++
    #include<stdio.h>//利用格高里公式求Π，直到最后一项小于10^-6
    int main()
    {
    	int s = -1, i = 2;
    	double p = 1.0, pi;
    	do
    	{//先执行下列语句
    		p += s / (i + 1.0);
    		i+=2;
    		s = -s;
    		pi = 1.0/ (i + 1);
    	} while (pi >= 1E-6);//再判断真假
    	p *= 4;
    	printf("%lf", p);
    	return 0;
    }
    ```

  - **不管是while语句还是这个语句，如果没有循环变量，将会形成死循环**

  - while和此语句如果循环体包含了一个以上的语句，都应与复合函数的形式出现。

- **用for语句实现循环**

  - 前面两种语句适用于循环次数无法预知的情况，而for语句则适用于知道循环次数的情况。

  - for语句的格式：**for（表达式1；表达式2；表达式3）  语句；**其中表达式1为循环变量指定初值，只执行一次；表达式2为判断条件，真就执行，假就退出；表达式3用于改变循环变量，在执行循环语句后再执行表达式3。

  - ```c++
    #include<stdio.h>//求1！+2！+3！+……+n！的值
    int main()
    {
    	int i;
    	double p, sum;
    	for (i = 2, p = 1, sum = 1;i <= 10;i++)
    	{
    		p *= i;
    		sum += p;
    	}
    	printf("%lf", sum);
    	return 0;
    }
    ```

  - for语句中三个表达式都可以省，但“；”不能省。其中

    - 省略表达式1，可以在for语句前就设定初始变量。

    - 省略表达式2整个语句就会陷入死循环。

    - 省略表达式3，可以在循环语句末改变循环变量。

    - 照理来说，按照for的执行顺序，可以把所有循环语句都放进括号内，但是为了简洁和可读性，一般不建议这么做。

    - 一般来说，只要表达式2的值不为零，那么就执行循环体。

    - ```c++
      #include<stdio.h>//统计从键盘输入一行字符的个数，以回车结束
      int main()
      {
      	int n;
      	char c;
      	printf("请输入一段字符：");
      	for(n = 0;(c=getchar())!='\n';n++);
      	printf("%d", n);
      	return 0;
      }
      ```

    - **斐波那契数列**：前面相邻两项之和，构成了后一项，“1，1，2，3，5，8，13，……”下面是实例

    - ```c++
      #include<stdio.h>//统计从键盘输入一行字符的个数，以回车结束
      int main()
      {
      	int i, x1, x2;
      	for (i = 1, x1 = 1, x2 = 1;i <= 10;i++)
      	{
      		printf("%d	%d	", x1, x2);
      		if (i % 2 == 0)
      			printf("\n");
      		x1 = x1 + x2;
      		x2 = x1 + x2;
      	}
      	return 0;
      }
      ```

- **continue语句和break语句**

  - **break语句**

    - 通常break语句可以用在**循环语句和开关语句中**，开关语句讲过了就不重复了。

    - break用于循环语句中时，可使程序跳出循环，通常与if语句连在一起。

    - ```c++
      #include<stdio.h>//将数字512表示为两个数之和，这两个数分别是15和13的倍数
      int main()
      {
      	int i, a, b;
      	for (i = 1;;i++)
      		if ((512 - i * 15) % 13 == 0)
      			break;
      	a = i * 15;
      	b = 512 - i * 15;
      	printf("%d	%d", a, b);
      	return 0;
      }
      ```

    - break语句不能用于除循环语句和开关语句之外的语句，所以它不能对条件语句起作用。

  - **continue语句**

    - 这个语句的作用是跳过循环体剩余的语句，返回循环语句开头，继续执行循环。

    - ```c++
      #include<stdio.h>//输出100~200之间能够被7或九整除的数
      int main()
      {
      	int i, n = 0;
      	for (i = 100;i <= 200;i++)
      	{
      		if (!(i % 7==0 || i % 9==0))
      			continue;
      		printf("%5d	", i);
      		n++;
      		if (n % 5 == 0)
      			printf("\n");
      	}
      	return 0;
      }
      ```
      
    - 上题显示，如果if为真，那么就返回到for语句再次执行，if为假就向下执行循环语句。

  - **这两个语句的比较**

    - 这两个语句都是用来终止循环的，但是continue只终止部分循环，而break则终止包括它自己的整个循环。  
    - break语句不但可以用于终止循环结构，也可以用于终止switch结构。而continue语句只能用于循环语句中，如果switch中出现continue语句，那么它只会对控制它的循环语句起作用。
    - break语句和continue语句都会使循环结构从一个非正常出口结束，与程序化一个入口一个出口的原则相违背了。所以要适当减少这两个语句的使用。

- **循环的嵌套**

  - 当一个循环体中又包含循环结构时，称为**循环嵌套**。处于外部的循环为外循环，内部的语句为内循环，**整个内循环仅仅是外循环的一条语句而已**。

  - ```c++
    #include<stdio.h>//生成一个三角图像
    #include<math.h>
    int main()
    {
    	int i, j, k;
    	for (i = 8;i >= 1;i--)//控制行数
    	{
    		for (j = 1;j <= 8 - i;j++)//控制输出的空格
    			printf(" ");
    		for (k = 1;k <= 2 * i - 1;k++)//控制输出的星星
    			printf("*");
    		printf("\n");
    	}
    	return 0;
    }
    ```

  - 从算法上分析，多重嵌套的循环比不嵌套的循环效率低很多，所以在编程中，能不使用循环嵌套就不要使用。

- **程序举例**

  - **穷举**

    - 穷举法类似于数学的**完全归纳法**，又称**暴力破解法**。比如一个密码有100000种组合，那么最多尝试100000次才能找到密码。

    - ```c++
      #include<stdio.h>//生成所有三位自方次幂
      #include<math.h>
      int main()
      {
      	int i, j, k,m1,m2;
      	printf("三位自方次幂");
      	for(i=1;i<=9;i++)//i不能为0，不然不是三位数
      		for(j=0;j<=9;j++)
      			for (k = 0;k <= 9;k++)
      			{
      				m1 = i * 100 + j * 10 + k;
      				m2 = i * i * i + j * j * j + k * k * k;
      				if (m1 == m2)
      					printf("%4d", m1);
      			}
      	return 0;
      }
      ```

  - **数的分离**

    - ```c++
      #include<stdio.h>//将数分离
      #include<math.h>
      int main()
      {
      	int m;
      	scanf("%d", &m);
      	int i, j, k, t, s;
      	i = 1;
      	s = m;
      	while (s / 10)//设定计数器，计算数的位数
      	{
      		s = s / 10;
      		i++;
      	}
      	for (j = i;j>=1;j--)//主要循环
      	{
      		k = m / pow(10, j - 1);
      		m = m - k*pow(10,j-1);
      		printf("%d ", k);
      	}
      	return 0;
      }
      ```

  - **二分法方程求根**

    - ```c++
      #include<stdio.h>//用二分法求方程的根
      #include<math.h>
      int main()
      {
      	double c, a, b, fa, fb, fc;
      	do
      	{//验证fa*fb<0,是则跳出循环，否则重新输入
      		printf("请输入两个值：");
      		scanf("%lf%lf", &a, &b);
      		fa = ((a + 1.1) * a + 0.9) * a - 1.4;
      		fb = ((b + 1.1) * b + 0.9) * b - 1.4;
      	} while (fa * fb >= 0);
      	do//
      	{
      		c = (a + b) / 2;//找到ab的中点
      		fc= ((c + 1.1) * c + 0.9) * c - 1.4;//计算c的函数值
      		if (fc * fa > 0)//判断fc和fa之间是否有实根
      			a = c;//是则让a=c
      		else
      			b = c;//否则让b=c
      	} while (fabs(fc) >= 1e-6);//直到fc接近临界值
      	printf("一个实根为：%8.2lf\n", c);
      	return 0;
      }
      ```

  - **多项式计算**

    - ```c++
      #include<stdio.h>//求多项式
      #include<math.h>
      int main()
      {
      	double sum, p, x;
      	int n, i, s;
      	printf("请输入多项式的第n项，和x的值：");
      	scanf("%d%lf", &n, &x);
      	sum = x;
      	p = x;
      	s = 1;
      	for (i = 2;i <= n;i++)//用迭代法
      	{
      		p *= x * x / (2 * i - 2) / (2 * i - 1);
      		s = -s;
      		sum += s * p;
      	}
      	printf("sum = %lf\n", sum);
      	return 0;
      }
      ```

  - **数的判别**

    - ```c++
      #include<stdio.h>//判断一个数是不是素数
      #include<math.h>
      int main()
      {
      	int a;
      	printf("输入一个大于1的整数：");
      	scanf("%d", &a);
      	int i,j;
      	for (i = 2;i <  a;i++)
      		if (a % i == 0)
      		{
      			printf("不是素数");
      			break;
      		}
      	if (i / a == 1)
      		printf("是素数");
      	return 0;
      }
      ```

  - **辗转相除法**

    - 辗转相除法又称**欧几里得算法**，是求两个正整数的最大公约数的算法。用大的数除小的数，然后用小的数除得到的除数，一直执行下去，直到得到的余数为零，那么上一步得到的除数就是最大公约数。	

    - ```c++
      #include<stdio.h>//使用欧几里得算法计算两个数的最大公约数
      #include<math.h>
      int main()
      {
      	int a, b, t,m;
      	printf("输入两个正整数：");
      	scanf("%d%d", &a, &b);
      	if (a < b)//判断两个数的大小
      	{
      		t = b;
      		b = a;
      		a = t;
      	}
      	do
      	{
      		m=a%b;
      		a = b;
      		b = m;
      	} while (m != 0);
      	printf("%d", a);
      	return 0;
      }
      ```

## 二、学系心得

从这一章感受到了难度，tmd定积分怎么求啊啊啊啊啊


​										