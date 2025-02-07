# C语言学习记录（七）

## 一、知识要点（函数）

### 一、函数的作用

- 在一个应用程序中的若干个**功能相互独立，可单独操作**的程序单元叫做**模块**。在C语言中**用函数实现模块的功能**，将这些模块构成完整的程序来完成问题的解决。

- 在C语言中，除了主函数，其他的函数称之为**子函数**。一个C语言程序**由一个主函数和若干个子函数构成**，主函数可以调用子函数，子函数之间也可以互相调用（包括自己），**但是主函数不能被调用**。

- 从使用角度看，C函数包括两种：**库函数和自定义函数**。库函数是编译系统提供的，而自定义函数需要自己构造。

- 从函数的形式看，C函数有两类：**无参函数和有参函数**。无参函数被调用时，主函数不用向子函数传递数据，而有参函数则需要。
  ```c++
  #include <stdio.h>              
  #include <string.h>
  
  // 定义无参函数myprint，输出18个星号
  void myprint()
  {
      int i = 0;
  
      for (i = 1; i <= 18; i++)
          printf("*");
          
      printf("\n");
  }
  
  // 定义有参函数myprint_n，输出n个星号
  void myprint_n(int n)
  {
      int i = 0;
  
      for (i = 1; i <= n; i++)
          printf("*")
  
      printf("\n");
  }
  
  // 主函数
  int main()
  {
      // 调用函数myprint，输出18个星号
      myprint();
  
      // 调用函数myprint_n，输出6个星号
      myprint_n(6);
  
      // 调用函数myprint_n，输出12个星号
      myprint_n(12);
  
      // 调用函数myprint，输出18个星号
      myprint();
  
      return 0;
  }
  ```

  ```c++
  #include <stdio.h>              
  #include <string.h>
  
  // 自定义函数mypow，实现计算x的y次方
  double mypow(double x, int y)
  {
      int i;
      double z = 1.0;
  
      // 循环计算x的y次方
      for (i = 1; i <= y; i++)
          z = z * x;
  
      return z;
  }
  
  // 主函数
  int main()
  {
      double x, z;
      int y;
  
      // 提示用户输入x和y
      printf("输入x，y：");
      scanf("%lf%d", &x, &y);
  
      // 调用mypow函数，计算x的y次方
      z = mypow(x, y);
  
      // 输出结果
      printf("%.2lf, %d, %.2lf", x, y, z);
  
      return 0;
  }
  ```

- 总结
  - 一个C语言程序中，只能有一个main函数，并且程序的执行都是从main函数开始，然后调用其他函数，最后回到main函数直到结束。
  - 在C语言中函数之间**是相互独立的**，不允许函数嵌套定义。

### 二、函数定义和函数调用

#### 1、==函数定义==

- **函数定义的一般形式**

  - 函数定义的一般形式如下：
    `[类型名] 函数名([形式参数表])`
    `{`
    		`声明部分;`
    		`执行部分;`
    `}`

  - 第一行称为**函数首部**，花括号内的部分称为**函数体**。

  - 类型名指定函数的类型，若返回值为int型，则可省略int。如果函数无返回值，则为**void型**。
    形式参数表**指定函数参数的名字和类型**。有参数的形参表可以由多个形参，而且**必须单独定义，各形参直接用逗号隔开**。无参函数无形参表，但不能省略空括号。

  - ```c++
    #include <stdio.h>
    
    // 自定义函数my_max，返回三个整数中的最大值
    int my_max(int a, int b, int c)
    {
        int max;
    
        // 比较a和b的大小，取较大值
        if (a > b)
            max = a;
        else
            max = b;
    
        // 再比较之前的较大值和c的大小，取最大值
        if (max < c)
            max = c;
    
        return max;
    }
    
    // 主函数
    int main()
    {
        int x, y, z, m;
    
        // 提示用户输入三个整数
        printf("输入三个整数：");
        scanf("%d %d %d", &x, &y, &z);
    
        // 调用my_max函数，求出最大值
        m = my_max(x, y, z);
    
        // 输出最大值到控制台
        printf("最大值为%d", m);
    
        return 0;
    }
    ```

- **空函数的定义形式**
  函数体中没有任何内容的函数称为空函数，空函数的定义形式如下：
  `[类型名] 函数名()`
  `{}`
  **程序设计时常在准备扩充功能的地方写上一个空函数**，用空函数占个位置。

#### 2、==函数调用==

- **函数调用的一般形式**

  - 形式为：
    `函数名([实际参数表])`

  - 函数名为被调用的函数的名字，在一个函数中**允许多次调用其他函数**。

  - 如果被调用的是有参函数，括号内的实参之间要用括号隔开，并且要与形参形式一致。

  - 如果调用的是无参函数，则实参表为空。

  - **执行过程**：先将实参的值赋给形参，然后执行被调函数的函数体语句，执行完之后将结果返回到主调函数。

  - ```c++
    #include <stdio.h>
    #include <math.h>
    
    // 自定义函数my_fac，用于计算n的阶乘
    double my_fac(int n)
    {
        int i;
        double p = 1;
    
        // 计算n的阶乘
        for (i = 1; i <= n; i++)
        {
            p *= i;
        }
    
        return p;
    }
    
    // 主函数
    int main()
    {
        int n;
        double sq, m;
    
        // 提示用户输入一个整数n
        printf("请输入一个整数：");
        scanf("%d", &n);
    
        // 调用内置函数sqrt求出n的平方根
        sq = sqrt(n);
    
        // 调用my_fac函数计算n的阶乘
        m = my_fac(n);
    
        // 输出n的平方根和阶乘到控制台
        printf("%.2lf %.2lf", sq, m);
    
        return 0;
    }
    ```

- **函数调用方式**

  - **函数语句方式**
    这种调用方式是把函数用作一个独立的语句。如例题中：
    `my_print();`
    `my_print_n(6);`
    这种不要求被调函数返回值，只要求被调函数完成一系列操作。
  - **函数表达式方式**
    这种调用方式是把函数调用用在表达式的组成部分中，要求被调函数返回一个确定的值来参加表达式运算。如：
    `z = 2 * my_fac(n);`
  - **函数参数方式**
    这种调用方式是将一个函数作为一个函数的实参。例如：
    `m = min(a, min(b, c));`,又如：
    `printf(" %f", min(a, b));`
    这种方式实质上也是一种函数表达式方式的调用。

- **形式参数与实际参数**

  - 在函数定义时形式参数表中的变量时形式参数，简称**形参**；在函数调用中的实际参数表中的参数称为实际参数，简称**实参**。

  - ```c++
    #include <stdio.h>
    #include <math.h>
    
    // 自定义函数my_max，返回两个整数中的最大值
    int my_max(int x, int y)
    {
        int max;
    
        // 使用条件运算符（三目运算符）比较x和y的大小，取最大值
        max = x > y ? x : y;
    
        return max;
    }
    
    // 主函数
    int main()
    {
        int a, b, max;
    
        // 提示用户输入两个整数
        printf("输入两个整数:");
        scanf("%d %d", &a, &b);
    
        // 调用my_max函数，求出两个整数中的最大值
        max = my_max(a, b);
    
        // 输出最大值到控制台
        printf("max = %d", max);
    
        return 0;
    }
    ```

  - **关于形参和实参的说明**

    - 在函数未被调用时，形参不占用内存中储存单元。而当调用时，才分配储存单元（与实参的储存单元类型不同）。函数调用结束后，形参单元被系统释放，实参的数值不变，这就是C语言所采用的单项的**值传递**方式。
    - 实参可以是常量、变量或表达式。但是他们在调用前必须有确定的值。

- **函数的返回值**

  - **return语句的语法格式**
    `return [(表达式)]`

    - **return语句的两个功能**

      - 如果函数有返回值，则计算return后面的表达式的值，并把值传回主函数。
      - 终止被调函数的执行，使流程返回主函数。

    - **return语句的使用形式**

      - return后面的表达式可以不用圆括号圈起来。

      - 一个函数若没有返回值，则return后面可以不跟表达式，只是用来使流程转向主函数。

      - 若不需要被调函数的返回值，则可以不写return语句。

      - 一个函数可以有多个return语句，如：
        ```c++
        #include <stdio.h>
        
        int sign(double x)
        {
            if (x > 0)
                return 1;
            else if (x == 0)
                return 0;
            else    
                return -1;
        }
        
        int main()
        {
            double x;
        
            printf("输入一个整数：");
            scanf("%lf", &x);
        
            printf("%d", sign(x));
        
            return 0;
        }
        ```

  - **函数的返回值类型**
    函数的类型决定了函数返回值的类型。

    - 在定义函数时，应指定函数的类型，从而确定返回值类型。
    - 若return语句的类型与被调函数返回值类型不一致，系统则会强行改为返回值类型。
    - 对于无返回值类型函数，函数的类型名应该说明为void型，表示无类型。

- **被调函数声明与函数原型**

  - 当采用自顶向下的格式（先写main函数）编写程序时，需要先声明要使用的子函数。

  - 函数说明有两种格式：
    `类型名 函数名(参数类型1 参数名1, 参数类型2 参数名2,..., 参数类型n 参数名n);`
    `类型名 函数名(参数类型1, 参数类型2,..., 参数类型n)`

  - 若被调函数在主调函数之前定义，则可不必对被调函数加以声明。

  - 若被调函数在主调函数之后定义，则需要在主调函数内对被调函数作声明。
    ```c++
    #include <stdio.h>
    
    double sub(double x, double y); // 声明函数sub
    
    int main() 
    { 
        double a, b, c;
    
    	scanf("%lf%lf", &a, &b);     // 输入两个双精度浮点数
    
    	c = sub(a, b);               // 调用函数sub，将其返回值赋给变量c
    
    	printf("%lf", c);            // 输出变量c的值
    
    	return 0;
    }
    
    double sub(double x, double y) // 定义函数sub 
    { 
        double z;
    
    	z = x - y;
    
    	return z;                    // 返回值为z
    }
    ```

  - 如果在文件的开头已对本程序中要调用的所有函数进行了声明，那么之后就不用再声明了。


### 三、函数调用中的参数传递

#### 1、==**简单变量作函数参数**==

- 当形参是简单变量时，实参和形参之间采用**数值传递**方式。形参和实参的储存单元类型不同，所以**形参的改变不影响实参单元**，因此**只能由实参向形参单向传递**。

- ```c++
  #include <stdio.h>
  
  	// 函数声明：定义函数mult，其返回值为int类型，参数为n。 
  int mult(int n);
  
  int main() 
  {	 // 定义并初始化变量num和res int num = 668; int res = mult(num);
  
  	// 输出变量num和res的值
  	printf("num = %d\n", num);
  	printf("res = %d\n", res);
  
  	return 0;
  }
  
  	// 函数定义：定义函数mult，其返回值为int类型，参数为n。 
  int mult(int n) 
  { 	// 将参数n乘以
      10 n *= 10;
  
  	// 返回乘以10后的结果
  	return n;
  }
  ```

#### 2、==**指针变量作函数参数**==

- 当形参为指针变量时，对应实参一定是一个指针，其类型相同，值为地址，所以采用**地址传递**方式。

- 由于形参和实参**指向**同一个储存单元，被调函数对形参的改变**能实现实参所指的单元的改变**，所以他们的**数据是双向传递的**，但是**地址传递是单向的**。

- ```c++
  #include <stdio.h>
  void swap(int *p1, int *p2);     //指针函数声明
  
  int main()  //主函数,把两个整数按降序排列
  {
      int a, b;
      int *p1, *p2;
  
      printf("请输入两个整数a, b:");
      scanf("%d%d", &a, &b);
  
      p1 = &a;
      p2 = &b;
  
      if (a < b)
          swap(p1, p2);
  
      printf("max = %d, min = %d\n", a, b);
  
      return 0;
  }
  
  void swap(int *p1, int *p2)     //定义一个函数，可将两个指针里的值交换
  {
      int temp;
  
      temp = *p1;
      *p1 = *p2;
      *p2 = temp;
  }
  ```

- ```c++
  #include <stdio.h>
  void swap(int *p1, int *p2);        //交换指针地址函数声明
  
  int main()          //主函数
  {
      int a, b;
      int *p1, *p2;
  
      printf("输入两个整数：");
      scanf("%d%d", &a, &b);
  
      p1 = &a;        //赋指针变量a，b地址
      p2 = &b;
  
      if (a < b)      //判断a，b的大小
          swap(p1, p2);
      
      printf("max = %d, min = %d", a, b);
  
      return 0;
  }
  
  void swap(int *p1, int *p2)     //子函数调换指针地址
  {
      int *temp;
  
      temp = p1;
      p1 = p2;
      p2 = temp;
  }
  
  //运行结果为：max = 1, min = 2
  //此程序说明了地址传递是单向的。。。。
  ```

#### 3、==**数组作参数函数**==

- **数组元素做函数参数**

  - 同简单变量做函数参数一样，单个数组元素做参数也是单向的**数值传递**方式。

  - ```c++
    #include <stdio.h>
    int large(int x, int y);        //声明子函数
    
    int main()
    {
        int i, n = 0, m = 0, k = 0;
        int a[10], b[10];
    
        printf("输入a数组：");
        
        for (i = 0; i < 10; i++)        //输入a数组各元素
        {
            scanf("%d", &a[i]);
        }
    
        printf("\n输入数组b：");        //输入b数组各元素
    
        for (i = 0; i < 10; i++)
        {
            scanf("%d", &b[10]);
        }
    
        for (i = 0; i < 10; i++)        //比较各元素大小，记录次数
        {
            if (large(a[i], b[i]) == 1)
                n++;
            else if(large(a[i], b[i]) == 0)
                m++;
            else
                k++;
        }
    
        if (n > k)
            printf("数组a大于数组b。");
        else if(n < k)
            printf("数组a小于数组b。");
        else
            printf("数组a等于数组b");
    
        return 0;
    }
    
    int large(int x, int y)     //比大小子函数
    {
        int flag;
    
        if (x > y)
            flag = 1;
        else if (x == y)
            flag = 0;
        else
            flag = -1;
    
        return flag;
    }
    ```

- **数组名做函数参数**

  - 数组名代表数组的首元素的地址，数组名做函数参数时，实参与形参采用**地址传递**方式。对形参数组元素的改变就是对其对应的实参数组元素的改变。

  - **一维数组名做函数参数**

    - 形参数组实质上是一个指针变量，指定其大小不起任何作用，因此不在数组内设定大小，但可以另立参数来传递大小。

    - **实参和形参都是数组名**

      ```c++
      #include <stdio.h>
      #define N 9                         //定义全局变量
      void output(int a[], int n);        //声明函数
      
      int main()
      {
          int x[N], i;		//实参为数组
      
          for (i = 0; i < N; i++)     //输入数组
          {
              x[i] = 2 * i;
          }
      
          output(x, N);       //输出数组
      
          return 0;
      }
      
      void output(int a[], int n)     //输出数组子函数
      {
          int i;
      
          for (i = 0; i < n; i++)
              printf("%d ", a[i]);	
      }
      ```

    - **实参为指向数组的指针变量，形参为数组名**

      ```c++
      #include <stdio.h>
      #define N 9                         //定义全局变量
      void output(int a[], int n);        //声明函数
      
      int main()
      {
          int x[N], i;
          int *q;
      
          for (i = 0; i < N; i++)     //输入数组
          {
              x[i] = 2 * i;
          }
      
          q = x;
      
          output(q, N);       //输出数组,实参为指针变量
      
          return 0;
      }
      
      void output(int a[], int n)     //输出数组子函数
      {
          int i;
      
          for (i = 0; i < n; i++)
              printf("%d ", *a++);
      }
      
      ```

    - **实参为数组名，形参为指针变量**

      ```c++
      #include <stdio.h>
      #define N 9                         //定义全局变量
      void output(int *p, int n);        //声明函数
      
      int main()
      {
          int x[N], i;
      
          for (i = 0; i < N; i++)     //输入数组
          {
              x[i] = 2 * i;
          }
      
          output(x, N);       //输出数组,实参为数组名
      
          return 0;
      }
      
      void output(int *p, int n)     //输出数组子函数，形参为指针变量
      {
          int i;
      
          for (i = 0; i < n; i++)
              printf("%d ", *p++);
      }
      
      ```

    - **实参和形参都是指针变量**

      ```c++
      #include <stdio.h>
      #define N 9                         //定义全局变量
      void output(int *p, int n);        //声明函数
      
      int main()
      {
          int x[N], i;
          int *p;
      
          for (i = 0; i < N; i++)     //输入数组
          {
              x[i] = 2 * i;
          }
      
          p = x;
      
          output(x, N);       //输出数组,实参为指针变量
      
          return 0;
      }
      
      void output(int *p, int n)     //输出数组子函数，形参为指针变量
      {
          int i;
      
          for (i = 0; i < n; i++)
              printf("%d ", *p++);
      }
      ```

  - **多维数组名做函数参数**

    - 大概都和一维数组相同，但用数组名做参数时，对形参的定义中，**可以指定每一维的长度，也可以不指定，但是其余各维的都必须指定**。
      像`int a[][]和int a[10][]`都是不允许的。

    - ```c++
      #include <stdio.h>
      #include <math.h>
      int small(int a[5][5]);         //声明子函数
      
      int main()
      {
          int arr[5][5], i, j, vmin;
      
          printf("输入25个整数：");
          
          for (i = 0; i < 5; i++)         //输入数组
              for (j = 0; j < 5; j++)
                  scanf("%d", &arr[i][j]);
      
          vmin = small(arr);          //找出数组对角线最小值
      
          printf("%d", vmin);
      
          return 0;
      }
      
      int small(int a[5][5])      //找出对角线最小值
      {
          int i, vm;
      
          vm = a[0][0];
      
          for (i = 0; i < 5; i++)
          {
              if (vm > a[i][i])
                  vm = a[i][i];
      
              return vm;
          }
      }
      
      ```

  - **字符数组作函数参数**

    - 和一维数组一样

    - ```c++
      #include <stdio.h>
      #include <math.h>
      #include <string.h>
      void my_copy(char str[], char *t);      //声明字符复制函数
      
      int main()
      {
          char str1[] = "I Love Beijing!";
          char str2[] = "I Love Chine!";
      
          my_copy(str1, str2);        //字符复制
      
          printf("%s", str1);
      
          return 0;
      }
      
      void my_copy(char str[], char *t)       //自定义函数
      {
          int i = 0;
      
          while (*t != '\0')
          {
              str[i] = *t;
              i++;
              t++;
          }
      
          str[i] = '\0';
      }
      
      ```

### 四、函数的嵌套调用和递归调用

#### 1、==函数的嵌套调用==

- C语言的函数定义**是相互独立的**，函数与函数之间没有从属关系。**在一个函数内不能定义另一个函数**。但是运行嵌套调用，即**允许在调用一个函数的过程中，又调用另一个函数。**

- ```c++
  #include <stdio.h>
  int my_max(int x, int y, int z);
  int my_min(int x, int y, int z);
  int dif(int x, int y, int z);
  
  int main()          //主函数，计算最大值见最小值
  {
      int a, b, c, d;
  
      printf("输入三个整数：");
      scanf("%d%d%d", &a, &b, &c);
  
      d = dif(a, b, c);
  
      printf("max - min = %d", d);
  
      return 0;
  }
  
  int my_max(int x, int y, int z)     //找出最大值
  {
      int max1, max2;
  
      max1 = (x > y) ? x : y;
      max2 = (max1 > z) ? max1 : z;
  
      return max2;
  }
  
  int my_min(int x, int y, int z)     //找出最小值
  {
      int min1, min2;
  
      min1 = (x < y) ? x : y;
      min2 = (min1 < z) ? min1 : z;
  
      return min2;
  }
  
  int dif(int x, int y, int z)        //调用max和min自定义函数，让其相减
  {
      int max, min, d;
  
      max = my_max(x, y, z);
      min = my_min(x, y, z);
      d = max - min;
  
      return d;
  }
  ```

#### 2、==函数的递归调用==

- C语言允许函数递归调用。递归调用有直接调用和间接调用之分

  - **直接递归调用**：在调用某函数时，又调用其函数本身叫做直接递归调用。
  - **间接递归调用**：在调用a函数的过程中调用了b函数，而b函数之中又调用了a函数，这叫**间接递归调用**。
  - 采用递归方法处理问题的关键，就是**一要找出求解的递归公式， 二要确定递归结束条件**

- ```c++
  #include <stdio.h>
  double fac(int x);
  
  int main()      //主函数，计算阶乘
  {
      int n;
      double f;
  
      printf("输入一个整数：");
      scanf("%d", &n);
  
      f = fac(n);
  
      printf("%d! = %lf", n, f);
  
      return 0;
  }
  
  double fac(int x)       //子函数，计算阶乘
  {
      int f;
  
      if (x == 0 || x == 1)       
          f = 1;
      else
          f = x * fac(x - 1);     //直接递归调用
  
      return f;
  }
  ```

- ```c++
  #include <stdio.h>
  int fib(int x);
  
  int main()      //主函数，求斐波那契数列
  {
      int i;
  
      for (i = 1; i <= 20; i++)
      {
          printf("%8d", fib(i));
  
          if (i % 5 == 0)
              printf("\n");
      }
  
      return 0;
  }
  
  int fib(int x)      //子函数求斐波那契数列
  {
      int f;
  
      if (x == 1 || x == 2)
          f = 1;
      else
          f = fib(x - 1) + fib(x - 2);        //递归调用
  
      return f;
  }
  ```

### 五、函数的返回值为指针

- 函数的返回值可以是指针，即可是变量的地址。其函数定义格式为`类型名 *函数名([形参列表])`

- ```c++
  #include <stdio.h>
  int *fun(int *x, int *y, int *z);
  
  int main()              //求三个数的最大值，以及他的地址
  {
      int a, b, c, *p;
  
      printf("输入三个整数：");
      scanf("%d%d%d", &a, &b, &c);
  
      p = fun(&a, &b, &c);
  
      printf("%d %d", p, *p);
  
      return 0;
  }
  
  int *fun(int *x, int *y, int *z)
  {
      if (*x > *y && *x > *z)
          return (x);
      
      if (*y > *x && *y > *z)
          return (y);
  
      return (z);
  }
  ```

### 六、变量的作用域和存储类别

#### 1、==局部变量及其存储类型==

- **在函数内部定义的变量叫做局部变量**，局部变量的作用域仅仅局限于定义它的函数。

  - 就算在主函数内定义的变量也只在主函数内有效，主函数不能使用其他函数内定义的变量。
  - 在不同的函数中可以定义同名的变量。
  - 形参也是局部变量。
  - 在函数中的复合语句定义的局部变量，只在其复合语句中有效。

- **自动类变量**

  - 在函数内定义的变量，如果不加任何前缀，那么系统默认为自动类变量。定义自动类变量的格式为`auto double a`;

  - 自动类变量**是在动态存储区分配单元的（因而也称动态变量）**，当函数结束调用时，自动类变量不复存在。

  - ```c++
    #include <stdio.h>
    void text_auto();
    
    int main()
    {
        int i;
    
        for (i = 0; i <= 4; i++)
            text_auto();
        
        return 0;
    }
    
    void text_auto()
    {
        int v = 0;
        printf("v = %d\n", v);
        v++;
    }
    
    //结果v全是0
    ```

- **静态类变量**

  - 要在函数调用结束让变量的值保留，那么可将该局部变量定义为**静态局部变量**。定义格式为：`static int x;`

  - 静态局部变量**在静态存储区中分配单元**，在整个程序运行期间都不会释放。

  - ```c++
    #include <stdio.h>
    void text_auto();
    
    int main()
    {
        int i;
    
        for (i = 0; i <= 4; i++)
            text_auto();
        
        return 0;
    }
    
    void text_auto()
    {
        static int v = 0;
        printf("v = %d\n", v);
        v++;
    }
    
    //v = 0 v = 1 v = 2 v = 3
    ```

  - **静态变量若未被赋初值，那么系统会默认其为0**，而动态变量则是随机数。

  - 为提升效率，C程序中大部分都是自动类变量，只有必要的情况下才定义静态变量。

- **寄存器变量**

  - 有的变量用的很频繁，为了加强效率，把这个变量定义为寄存器变量，这样函数只要在寄存器中拿这个变量，就不用到内存中拿了。定义格式为：`register 类型名 变量名;`
  - 只有**局部自定义变量才能被定义为寄存器变量**，其他都不行。
  - 不能定义任意多个寄存器变量，因为寄存器数量有限。
  - **寄存器变量没有地址**，所以不能取它的地址。

#### 2、==全局变量及其存储类型==

- 在函数外部定义的变量叫做**外部变量，又叫全局变量**，他的作用域是从**变量的定义处开始**执行到结束。在此作用域内全局变量**可以被各个函数所使用**。

  - C语言设置全局变量是为了**增加函数间数据联系的渠道**。例如可以利用全局变量，从函数调用中得到一个以上的返回值。
  - 为了区分局部变量和全局变量，一般将全局变量的首字母大写。

- ```c++
  #include <stdio.h>
  double Max = 0, Min = 0;        //定义全局变量并赋初值
  double average(double array[], int n);      //声明函数
  
  int main()
  {
      double aver, score[10];
      int i;
  
      for (i = 0; i < 10; i++)
      {
          scanf("%lf", &score[i]);
      }
  
      aver = average(score, 10);      //函数调用，计算平均值
  
      printf("Max = %lf, Min = %lf, aver = %lf", Max, Min, aver);     //输出平均值和全局变量值
  
      return 0;
  }
  
  double average(double array[], int n)       //定义函数
  {
      int i;
      double aver, sum = array[0];
      Max = Min = array[0];
  
      for (i = 1; i < n; i++)
      {
          if (array[i] > Max)
              Max = array[i];         //全局变量初值被改变
          else if (array[i] < Min)
              Min = array[i];
  
          sum += array[i];
      }
  
      aver = sum / n;
  
      return aver;
  }
  ```

- 尽量少用全局变量，不然容易混乱，，，，**在同一个源文件中，局部变量和全局变量可以同名，在这种情况下，全局变量会被屏蔽，即它对有局部变量的函数内部不起作用**。

### 七、内部函数和外部函数

#### 1、==内部函数==

- 内部函数又称为**静态函数**，只能在定义它的源文件内被调用，定义内部函数的语法格式为：`static double act(int a, int b)`
- 使用内部函数，在外部源文件中可以有同名的内部函数，它们互不干扰。

#### 2、==外部函数==

- 凡是不被说明为内部函数的函数都是外部函数，**外部函数可以被其他源文件调用**。可以不加前缀，也可以加前缀extern。

## 二、学习心得

快学完了。。。🤣🤣