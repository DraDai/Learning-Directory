# C语言学习记录（八）

## 一、结构类型及其变量的定义

#### 1、==结构类型的定义==

- 结构类型是聚合类型对象的抽象，通常要由程序员自行定义。因此结构类型是用户自定义类型。

- **定义结构类型的一般格式**

  - 其定义语法格式为：`struct 结构类型名 { 成员列表；}；`

  - struct是关键字，表示**声明要定义一个结构类型**，结构类型名**用标识符命名**。

  - 成员列表给出n个成员的声明，成员**可以是基本类型变量、数组，也可以是另一结构类型变量**，成员之间用分号间隔。如：
    类型名    成员名；
    ……
    类型名    成员名；

  - 要注意，**}后面一定要加分号”；“**。

  - ```c++
    //定义一个表述学生数据的结构类型
    struct student
    {
        int number;
        char name[9];
        int age;
        char sex;
    };
    ```

- **结构类型的几点说明**

  - 单单只是定义了结构类型，系统是不会为之分配内存单元的，只有定义了结构变量后，才会分配。

  - 每一个数据项都是和数据结构绑定在一起的，**想要引用某个数据项，就得先通过通过结构变量名**。

  - **结构类型可以嵌套定义**。通常用于某个成员是一个结构变量的场合。

    ```c++
    struct Student
    {
        int number;
        char name[9];
        struct Date     //嵌套结构数据
        {           
            int year;
            int month;
            int day;
        }birthday;
            //成员birthday的类型又是结构类型
        char sex;
    };
    ```

  - 允许省略结构类型名，即允许定义无类型结构名的结构类型，但后面必须要定义结构变量，而且只能在一处使用。常用于内嵌结构。

#### 2、==结构类型数对象的定义及初始化==

- **定义结构变量**

  - **先定义结构类型再定义结构变量**

    - 这是标准方式，其语法格式为：`struct 结构变量类型名 变量名表;`。
    - 其中，结构变量类型名**必须是程序中已定义的**。
    - 变量名表：列出n个同类型的结构数据对象名，中间用逗号分隔。
    - 例`struct Student student1, student2;`

  - **在定义结构类型的同时定义结构变量**

    - ```c++
      struct Student
      {
          int number;
          char name[9];
          struct Date     //嵌套结构数据
          {           
              int year;
              int month;
              int day;
          }birthday;
              //成员birthday的类型又是结构类型
          char sex;
      }student1, student2;
      
      struct Student student3;        //正确，此处还是Student的作用域
      struct Date birthday1;           //错误的，此处已出Date的作用域
      ```

  - **直接定义结构变量**

    - 语法格式为：
      `struct`
      `{`
      `成员列表;`
      `}变量名列表;`
    - 该定义方法的变量只能用一次。

- **结构变量的初始化**

  - 可以在定义结构变量名的同时进行初始化，其语法格式为：`struct 结构类型名 结构变量名 = {成员初始化值表};`

  - ```c++
    struct Student
    {
        int number;
        char name[9];
        struct Date     //嵌套结构数据
        {           
            int year;
            int month;
            int day;
        }birthday;
            //成员birthday的类型又是结构类型
        char sex;
    }student = {1001, "LiMing", 1985, 2, 20, 'M'}		//可以看出，其内部嵌套结构变量仍是赋初值
    ```

#### 3、==结构成员的引用==

- **结构成员的表示**

  - 结构变量是由n个成员聚合而成的一个整体，要访问一个成员，必须给出**整体名称和成员名称**。如`student1.name`，"."称为点运算符，表示name从属于student1。
  - 假设有以下定义：`struct Student s1, s2[100], *s3 = &s1;`
    - **结构变量成员的表示**：其成员number、age分别表示为`s1.number、s1.age`
    - **结构数组元素成员的表示**：`s2[5].name`表示s2中第六个元素name成员。
    - **结构指针成员的表示**：`s3->name`表示结构指针s3指向的结构变量s1的name成员。

- **嵌套结构的结构成员的表示**

  - 结构成员本身又是结构变量，称为嵌套结构。
  - 必须使用若干个成员运算符来连接多个结构变量及其对应的分量，逐级表示到最低的成员。比如：`student.birthday.year`(year表示最低的成员，也是基本数据对象)。

- **结构成员变量的引用**

  - 结构变量的成员和普通变量一样可以进行各种运算,例如：
    `student.birthday.year++;`
    `student1.number = 11001;`
    `scanf("%d", &student.sex);`

- **结构成员表示和引用的注意事项**

  - 如果成员是基本类型数据可直接引用。

    - 在绝大多数场合（赋值运算除外），只能访问成员而不能直接访问结构本身。例如：
      ```c++
      struct Student student1, student2;
      Student1 = Student1 + Student3;		//错误，不能将整个结构变量做运算
      printf("%d, %s, %d, %c\n", student1);		//错误，不能将整个结构变量输出
      printf("%d, %s, %d, %c\n", stdent1.number, student1.name, student1.age, stdent1.sex);
      //正确，对每个成员分别输出
      ```

  - 可以**将一个结构变量作为整体赋给另一个相同类型的结构变量**，如`student2 = student1;`
    ```c++
    #include <stdio.h>
    
    struct Date     //定义日期数据结构
    {
        int month;
        int day;
        int year;
    };
    
    struct Student      //定义学生信息数据结构
    {
        int number;
        char name[9];
        int age;
        char sex;
    
        struct Date birthday1;
    };
    
    int main()
    {
        struct Student student1 = {1001, "lili", 18, 'M', 12, 15, 1982}, student2;
        student2 = student1;        //将s1的值整体赋给s2
    
        printf("student1 : %d %s %d %c %d/%d/%d\n", student1.number, student1.name, student1.age, student1.sex, student1.birthday1.month, student1.birthday1.day, student1.birthday1.year);
        printf("student2 : %d %s %d %c %d/%d/%d\n", student2.number, student2.name, student2.age, student2.sex, student2.birthday1.month, student2.birthday1.day, student2.birthday1.year);
    
        return 0;
    }
    ```

    也可以将一个结构变量中的内嵌结构类型成员赋给另一个，比如：`student2.birthday = student1.birthday;`

  - **不能将一组数据常量直接赋给结构变量**。

## 二、结构数组

#### 1、==结构数组的定义及其应用==

- **结构数组的定义**
  - **什么是结构数组**：结构数组是类型为结构类型的数组，它既有结构变量的属性，也有数组的属性。
  - **定义结构数组的语法格式**：
    - 格式1：`struct 结构类型名 数组名[常量表达式];`
    - 格式2：
      `struct 结构类型名`
      `{`
      `成员表;`
      `}数组名[常量表达式];`
- **结构数组的初始化**
  - 与一般数组一样，在定义结构数组的同时，对其全部或部分元素进行赋值，例如：`struct Student student[2] = {{1101, "lilin", 1985, 8, 1, 'M'}, {1102, "LongXing", 1985, 7, 1, 'F'}};`
  - 初值包含在初始化表中，它包含N个子表，即包含N个结构常量。**当初始化结构数组时，可以省略下标**。

#### 2、==对数组结构的操作==

- **引用数组结构元素**
  - 其格式为：`数组名[下表表达式]或 *(数组名 + i)`
  - 如`employee[2]、*(employee + 3)`
- **引用结构数组元素的成员**
  - 相当于结构变量的成员，其引用方式是一样的：`数组名[常量表达式].成员`例如：`employee[5].name`

#### 3、==应用举例==

- ```c++
  #include <stdio.h>
  
  struct Student      //定义学生数据并赋值
  {
      int number;
      char name[20];
      int age;
  }student[4] = {{1011, "ShaBi", 18}, {1012, "DaShaBi", 19}, {1013, "YeShouXianBei", 24}, {1014, "ZhouZhiYang", 17}};
  
  int main()
  {
      int i = 0;
      double aver, sum = 0;
  
      for (i = 0; i < 4; i++)     //计算总年龄和平均年龄
      {
          sum += student[i].age;
      }
  
      printf("%lf\n", sum);
  
      aver = sum / 4.0;
  
      printf("%lf", aver);
  
      return 0;
  }
  ```


## 三、结构和指针

#### 1、==指向结构变量的指针==

- **定义指向结构变量的指针**

  - 语法格式：`struct 结构类型名 *结构指针名;`
  - 例如：`struct Employee employee, *EmpPtr;   EmpPtr = &employee;`表示将employee的起始地址赋予EmpPtr。
    employee.name与EmpPtr->name是等价的。

- **结构指针的初始化**

  - 与普通的指针类似，**既可以赋予一个已存在的、类型相同的结构变量的地址，也可以赋予空地址（NULL）**

  - ```c++
    struct Student
    {
        int number;
        char name[9];
        int age;
    }student1, *p1;
    
    struct Device
    {
        int number;
        char name[20];
        char type[10];
        char address[30];
        double price;
        int quantity;
    }device1, *p2, *p3;
    
    p1 = &device1;      //错误的，因为p1和device1的数据类型不同
    p2 = &student1;     //错误的，因为p2和student1的数据类型不同
    p3 = NULL;          //正确的，可以赋予空指针
    ```

- **通过指针来引用结构变量成员**

  - 如果有`struct employee, *EmpPtr = employee;`则`EmpPtr->name与employee.name`等价，都表示访问employee的成员name。
  - 用**(指针结构名).成员名**也可以表示结构指针成员，比如`(*EmpPtr).name`。

#### 2、==指针变量作为结构成员==

- ```c++
  #include <stdio.h>
  
  struct Student
  {
      int number;
      char *name;     //定义结构成员指针变量
  };
  
  int main()
  {
      struct Student stu;
  
      printf("输入你的学号：");
      scanf("%d", &stu.number);
  
      printf("输入你的名字：");
      stu.name = (char*)calloc(21, sizeof(char));     //申请字符数组所需的内存空间，并将首地址保存在name指针中
      scanf("%s", stu.name);
      printf("%s", stu.name);
  
      return 0;
  }
  ```

#### 3、==指向结构数组的指针==

- 可以定义结构指针**指向结构数组**，利用该指针就可以访问结构数组的元素。如：
  ```c++
  struct A
  {
      int a;
      double b;
  }arr[3], *p;
  
  p = arr;
  ```

  - 这样p就指向了arr[0]的第一个元素，当p = p + 1时，p就指向了arr[1]的第一个元素。
  - `p -> a;`表示指针p得到了起始数组第a个元素；
    `(p++) -> a;`表示指针p先得到起始数组第a个元素，然后自增；
    `(++p) -> a;`表示指针p先自增，再得到自增后的数组第a个元素；
    `(p -> a)++`表示指针p先得到a的值，然后对得到的值加一；

- ```c++
  #include <stdio.h>
  
  struct Student          //定义Student结构类型
  {
      int number;
      char name[9];
      int age;
      char sex;
  };
  
  struct Student stu[2] = {{10101, "lilin", 18, 'M'}, {10102, "zhangfan", 19, 'M'}};      //输入两个学生的信息
  
  int main()
  {
      struct Student *p;
  
      printf("No.     Name    sex     age\n");
  
      for (p = stu; p < stu + 2; p++)
          printf("%-11d%-12s%2c%10d\n", p -> number, (*p).name, p -> sex, p ->age);
  
      return 0;
  }
  ```

#### 4、==结构指针作为函数参数==

- **结构变量和结构和指针**可作函数形参；函数返回值的类型为结构类型，可返回结构常量；

  ```c++
  #include <stdio.h>
  
  struct Student		//定义学生数据类型
  {
      int number;
      char name[9];
      int age;
  };
  
  void age(struct Student *p);
  
  int main()		
  {
      struct Student stu[3] = {{1101, "devid", 18}, {1102, "star", 19}, {1103, "bageyalu", 17}};
      struct Student *p;
      p = stu;
  
      age(p + 1);
  
      return 0;
  }
  
  void age(struct Student *p)
  {
      printf("%s\n", p -> name);
      printf("%d", (*p).age);
  }
  ```

- ```c++
  #include <stdio.h>
  //定义员工结构类型
  struct Employee
  {
      char name[9];
      char sex;
      char birthday[12];
      char dept[11];      //部门
      char ProTitle[9];   //职称
      double salary;      //工资
      double bonus;       //奖金
      char health;
  };
  //定义工资和奖金的统计结果
  struct Total
  {
      char title1[10];
      double sum1;
  
      char title2[10];
      double sum2;
  };
  
  #define NUM 5        //定义职工人数
  void ReadEmplo(struct Employee employee[]);     //声明自定义函数
  void WriteEmplo(struct Employee employee);
  struct Total sum(struct Employee employee[], struct Total temp);
  
  int main()
  {
      struct Employee employee[NUM];      //定义员工数据表
      struct Total t1 = {"基本工资：", 0, "奖金总和", 0};     //赋初值
      int i;
  
      ReadEmplo(employee);        //输入各员工数据
  
      for (i = 0; i < NUM; i++)
      {
          WriteEmplo(employee);       //输出各员工的数据
      }
  
      t1 = sum(employee, t1);         //将员工工资总和，，奖金总和
  
      printf("%s%7.2lf\n", t1.title1, t1.sum1);        //输出员工总工资
      printf("%s%7.2lf\n", t1.title2, t1.sum2);           //输出员工奖金之和
  
      return 0;
  }
  
  void ReadEmplo(struct Employee employee[])      //自定义员工数据输入函数
  {
      int i;
  
      for (i = 0; i < NUM; i++)
      {
          scanf("%s", employee[i].name);
          scanf(" %c", &employee[i].sex);
          scanf("%s", employee[i].birthday);
          scanf("%s", employee[i].dept);
          scanf("%s", employee[i].ProTitle);
          scanf("%lf", &employee[i].salary);
          scanf("%lf", &employee[i].bonus);
          scanf(" %c", &employee[i].health);
      }
  }
  
  void WriteEmplo(struct Employee employee)     //自定义员工数据输出函数
  {
      printf("性名    性别    出生年月    部门    职称    工资    奖金    健康状况\n");
      printf("%s%c%s%s%s%6.2lf%6.2lf%c", employee.name, employee.sex, employee.birthday, employee.dept, employee.ProTitle, employee.salary, employee.bonus, employee.health);
  }
  
  struct Total sum(struct Employee employee[], struct Total temp)     //自定义员工工资和奖金的总和函数
  {
      int i;
  
      for (i = 0; i < NUM; i++)
      {
          temp.sum1 = temp.sum1 + employee[i].salary;
          temp.sum2 = temp.sum2 + employee[i].bonus;
      }
  
      return temp;
  }
  ```


## 四、联合类型

#### 1、==联合类型的概念及联合类型定义==

- **联合的概念**

  - 将若干个变量组织在一起，**使它们能在不同的时间占用同一段内存空间**，这种数据类型叫做**联合类型或共同体类型**。
  - 如果将多个不同类型的变量变成联合类型，那么**编译程序分配空间时，会取字节数最大的变量**，并且多个变量在空间起始位置一致，但只能分时使用。

- **定义联合类型**

  - 语法格式：
    ```c
    union 联合类型名
    {
        成员列表；
    }；
    //union是关键字，表示定义一个联合类型
        //联合类型名，是标识符，和int相似
    ```

#### 2、==联合变量的定义及成员的引用==

- **定义联合变量**

  - 和前面一样：`union 联合类型名 变量名;`

  - 联合在一个时间内不能对对多个成员同时起作用，只能最后被赋值的成员才有作用。
    ```c
    datal.b = 'M';		//对联合成员b赋值，'M'放在1000单元
    printf("%c\n", datal.b);		//输出M
    datal.a = 100;		//这时成员b被成员a覆盖，100存放在1000~1003单元
    printf("%d", datal.a);		//输出100
    ```

  - 类型变量长度等于类型最长的成员的长度。

- **联合成员的引用**

  - 和结构类型一样，如：`datal.b	(*p).b	p -> b`

#### 3、==联合类型应用举例==

- ```c++
  //数据处理问题中，可以用一个数据域存放不同类型的对象。
  struct Person
  {
      int number;
      char name[9];
      char sex;
      char job;
      
      union Category
      {
          int class;
          char post[21];
      }category;
      
  }person;
  ```

## 五、枚举类型

#### 1、==枚举类型的定义==

- 枚举类型简称枚举型，是一种特殊的数据类型，**他的值域是某个数据集合**，集合内所有整数均可赋值。
- 定义格式为`enum 枚举类型名{枚举值表};`如果没有指定枚举值表中枚举常量名对应的整数值的话，C语言会默认取值，如
  `enum Week{Sunday, Monday, Tuesday, Wednesday, Friday, Saturday}`,系统就会从Sunday开始到最后对应值分别为0，1，2，3……6，即其值域为{0, 1, 2, 3, 4, 5, 6}。
  如果将`enum Week{Sunday = 7, Monday = 1, ……,Saturday};`,那么就是{7, 1, 2, 3, 4, 5, 6}

#### 2、==枚举类型的定义和使用==

- **用变量定义语句定义枚举类型变量**

  - 和前面一样，如：`enum Week weekdays = Sunday`\

  - 枚举类型变量的取值**只能取一次**，**且一次只能取一个值**

  - ```c
    //合法语句
    weekDay = Monday;
    weekDay = (enum Week)1;		//将整数类型转化为枚举类型
    //不合法语句
    weekday = Mon		//euum Week类型不包含Mon这个值
    weekday = 1;		
    ```

  - 可以进行关系运算
    ```c
    enum Week weekday1 = Monday, weekday2 = Friday;
    if (weekday1 == weekday2)
        printf("ok");
    if (Monday != Friday)
        printf("ok");
    //实际上是1！=5，枚举变量其实是整数符，不是字符串符
    ```

## 六、用typedef定义类型别名

- **简单的名字替换**

  - 语法格式为：`typedef 类型名 类型别名`如：`typedef int Intget`。`int a和Intget a是等价的`

- **定义一个类型名代表一个结构**

  - `typedef struct Student STUDENT;		STUDENT stu2;`

- **定义数组类型**

  - ```c
    typedef int Count[10];
    Count a, b;		//用Count定义整数数组，他们都具有10个元素
    ```

- **定义指针类型**

  - ```c
    typedef int *String;
    String p1, p2;		//用String定义p1,p2为指针变量
    ```

