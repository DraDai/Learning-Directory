# C语言学习记录（终）

## 一、知识要点（文件）

### 一、文件和文件类型指针

#### 1、==流和文件的概念==

- **流的概念**
  - 我们不管什么物理设备硬件什么的，就把**数据的输入输出抽象化为一种流**，这样就可以方便编程，具有通用性。
  - 流分为**文本流和二进制流**
    - 文本流中的数据以**字符形式存放，每个字符用ASCII码表示，占一个字节**。
    - 二进制流中的数据**以内存存储形式存放， 即根据数据类型分配大小，用二进制码表示**。
- **文件的概念**
  - 从用户角度上来看，文件分为**普通文件和设备文件**
    - 普通文件是**驻留在外部介质中的有序数据集**。普通文件有**程序文件和数据文件**，源文件、目标文件、可执行文件就是程序文件，输入输出数据文件就是数据文件。
    - 设备文件就是**与主机相连的各种外部设备**，在操作系统中把外部设备当作文件来进行管理。
  - 从文件编码来看，文件分为**ASCII码文件和二进制码文件**
    - ASCII码文件又称**文本文件**，其内容**是由一个个字符组成，每个字符对应一个字节，用于存放对应的ASCII码**。如10000按ASCII码输出：`00110001 00110000 00110000 00110000 00110000`,占五个字节。
    - 二进制码文件的数据存储方式和在内存中的一样，如10000是整形，那么`00000000 00000000 00100111 00010000`,占四个字节。
    - 二进制文件输入输出速度较快，适合作中间结果，待后续处理；而ASCII码文件适合让人方便阅读。
- **流和文件**
  - 输入输出数据流的开始和结束**仅受程序控制而不受物理符号控制**的文件，叫做**流式文件**。
  - 执行程序时会自动打开**三种文件及其并联的流**：**标准输入流、标准输出流和标准错误流**，是用文件指针**`stdin、stdout、stderr`**操作的。
  - C语言中对文件的处理方法有**缓冲文件系统和非缓冲文件系统**
    - 缓冲系统文件就是系统自动在内存区**为每个正在使用的文件开辟一个缓冲区**，内存和磁盘输入输出**数据必须先送到缓冲区，等缓冲区装满后在送出去，相当于仓库**。
    - 非缓冲文件系统的缓冲区要用户自己创建。

#### 2、==文件类型的指针==

- **文件类型**

  - 系统给每个打开的文件分别在内存中开辟一个区域，将文件的有关信息**存在一个结构变量中**。该结构类型由系统定义，取名为**FILE**，称为文件类型，他是在头文件**stdio.h**中定义的。

  - ```c
    typedef struct
    {
        short lever;			//缓冲区满或空的状态
        unsigned flags;			//文件状态标志
        char fd;				//文件描述符
        unsigned char hold;		//如无缓冲区不读取字符
        short size;				//缓冲区的大小
        unsigned char *buffer;	//数据缓冲区的位置
        unsigned char *curp;	//当前活动指针
        unsigned istemp;		//文件临时指示器
        short token;			//用与有效性检查
    }FILE;
    ```

- **文件指针**

  - 在C语言中用一个指针变量指向一个文件，这个指针叫**文件指针**。通过文件指针可以对所指的文件进行各种操作。
  - 定义文件指针的语法格式：`FILE *指针变量名;`

### 二、文件的打开和关闭

#### 1、==文件的打开==

- 在对文件进行读写之前，**必须先执行打开文件的操作**。文件的打开操作表示给文件分配一个FILE结构区，并将结构的指针返回给用户，**用户就可以用FILE指针来操作文件了**。

- 打开文件要调用`fopen()`函数完成，其原型为`FILE *fopen(char *filename, char *type);`。其中`filename`是要打开文件的文件名，`type`表示对文件的操作方式。

- 当`fopen()`成功打开文件时，该函数会返回一个**FILE指针**，打开失败则返回**NULL指针**。

- **文件的使用方式说明**

  - 文件使用方式由**`r,w,a,t,b,+`**这六个字符拼成，其含义为：
    `r(read)`				读
    `w(write)`			  写
    `a(append)`			追加
    `t(text)`				文本文件，可省略不写
    `b(binary)`			二进制文件
    `+`							 读和写

  - 用r打开文件时，该文件必须存在，且只能从该文件读出。

  - 用w打开的文件只能向该文件写入。若打开的文件不存在，则以指定的文件名建立该文件；若打开的文件已存在，则**删去该文件，并以此文件名重建一个文件**。

  - 用a打开文件时，可以在已存在的文件中追加新的信息。如果文件不存在，则会出错。

  - 文件打开失败时会返回NULL指针，因此可以用下面的程序段打开文件。

    ```c
    FILE *fp;
    
    if ((fp = fopen("c:\\hzk16", "rb")) == NULL)		//如果文件打开失败返回NULL指针，则提示无法打开
    {
        printf("\nerror on open c:\\hzk16 file!");
        
        exit(1);		//终止程序
    }
    ```

  - 标准输入文件、标准输出文件和标准错误文件的打开可以直接使用。

#### 2、==文件的关闭==

- 文件操作完成后，必须要将文件关闭，**使缓冲区的数据能够全部存入文件**。
- 关闭文件函数为`fclose()`，其函数原型为：`int fclose(FILE *stream);`，若其成功关闭了文件，**则返回0值，否则返回非0值**。

### 三、读写函数

#### 1、==fputc函数和fgetc函数==

- **fputc函数**

  - 该函数**将一个字符写到指定的文件中**，其函数原型为：`int fputc(char ch, FILE *fp)`，调用格式为`fputc(ch, fp);`
    其中ch是待输入的字符变量，fp是文件指针，**将字符ch写入fp所指的文件中去**，成功就返回写入字符的ASCII代码值，失败时返回EOF，即-1。
  - 被写入的文件必须是**写、读写或追加方式打开的**。
  - 在文件内部有个位置指针，用来指向文件当前读写字节。每读写一次，该指针向后移动。
    ```c++
    #include <stdio.h>
    
    int main()
    {
        FILE *fp;
        char ch, file_name[10];
    
        gets(file_name);
    
        if ((fp = fopen(file_name, "w")) == NULL)		//打开文件
        {
            printf("can not open this file\n");
            return 0;										//终止程序
        }
    
        for (; (ch = getchar()) != '@'; )
            fputc(ch, fp);								//输入字符到fp
    
        fclose(fp);										//关闭文件
    
        return 0;
    }
    ```

- **fgetc函数**

  - 从指定文件每次读取一个字符，其函数原型为：`int fgetc(FILE *fp);`，其调用格式为：` c = fgetc(fp);`如果调用成功，就把字符的ASICC码赋予c，c为int型，错误则返回EOF。

  - 使用fgetc函数读取一个字符后，文件内部指针向后移动一字节。
    ```c++
    #include <stdio.h>
    
    int main()
    {
        FILE *fp;
        char ch;
        fp = fopen("C:\\Users\\di\\text.txt", "r");			//打开文件
    
        if (fp == NULL)
        {
            printf("无法打开文件");
    
            return 0;
        } 
        
    
        while ((ch = fgetc(fp)) != EOF)
        {
            putchar(ch);					//顺序读入并显示
        }
    
        fclose(fp);
        return 0;
    }
    ```


#### 2、==fputs函数和fgets函数==

- **fputs函数**

  - 将一个字符串写到文件中，其函数原型为：`int fputs(char *str, FILE *fp);`，调用格式为：`fputs(str, fp);`
  - 正常时返回字符串，否则返回EOF。

- **fgets函数**

  - 从文件中读取一个字符串，并存在字符指针所指的内存中，其函数原型为：`char *fgets(char *str, int n, FILE *fp);`其调用格式为：`fgets(str, n, fp)`
  - fp是文件指针，str是一个字符指针或者字符数组，n是字符的个数。
  - 从fp所指的文件中，每次读取n-1个字符，因为最后一个是'\0'。此函数**调用出错时返回NULL**。

- ```c
  #include <stdio.h>
  #include <string.h>
  
  int main()\
  {
      FILE *fp;
      char file_name[30], str[81];
  
      printf("输入文件名：");
  
      gets(file_name);		//从键盘输入文件名
  
      fp = fopen(file_name, "a");			
  
      if (fp == NULL)
      {
          printf("该文件不存在。");
          return 0;
      }
  
      printf("请输入一个字符串：");
      
      gets(str);			//从键盘输入字符串
      fputs(str, fp);		//存入指定文件
      fclose(fp);
  
      fp = fopen(file_name, "r");		
  
      if (fp == NULL)
      {
          printf("该文件不存在。");
          return 0;
      }
  
      fgets(str, 81, fp);		//读取文本
      puts(str);			//输出屏幕
      fclose(fp);
  
      return 0;
  }
  ```

#### 3、==fread函数和fwrite函数==

- **fread函数**

  - 从文件中读取一段数据，函数原型为：`int fread(char *buf, int size, int n, FILE *fp);`调用格式为：`fread(buf, size, n, fp);`
  - buf是一个**用来指向数据块在内存中的起始地址**，size表示一个数据项的字节数，n表示读取n个数据项，fp则是文件指针。
  - 调用不成功则返回0，成功则返回数据项个数。

- **fwrite函数**

  - 将一组数据写入文件，其函数原型为：`int fwrite(char *buf, int size, int n, FILE *fp);`,调用格式为：`fwrite(buf, size, n, fp);`
  - 和fread一样。。。。

- 这俩函数**一般用于二进制文件的读写**
  ```c
  //将两个学生的数据写入磁盘中，在读取，显示在屏幕上
  #include <stdio.h>
  
  struct stu			//定义学生数据
  {
      char name[20];
      int number;
      int age;
      char addr[15];
  }boy1[2], boy2[2], *pp, *qq;
  
  int main()
  {
      FILE *fp;
      int i;
      pp = boy1;
      qq = boy2;
      fp = fopen("C:\\Users\\di\\student", "wb+");		//打开文件并读写追加数据
  
      if (fp == NULL)
      {
          printf("无法打开文件。");
          return 0;
      }
  
      for (i = 0; i < 2; i++, pp++)			//输入学生数据
      {
          scanf("%s%d%d%s", pp -> name, &pp -> number, &pp -> age, pp -> addr);
      }
  
      pp = boy1;			//使pp重新指向开头
  
      fwrite(pp, sizeof(struct stu), 2, fp);		//将数据写入磁盘
      rewind(fp);									//使指针fp返回开头
      fread(qq, sizeof(struct stu), 2, fp);		//从磁盘读取数据到qq上
  
      printf("\n\nname\tnumber        age      addr\n");
  
      for (i = 0; i < 2; i++, qq++)				//打印数据
      {
          printf("%s\t%5d%7d       %s\n", qq -> name, qq -> number, qq -> age, qq -> addr);
      }
  
      fclose(fp);		//关闭文件
  
      return 0;
  }
  ```

#### 4、==fscanf函数和fprintf函数==

- **fscanf函数**：和scanf函数作用类似，从文件中读取数据，然后赋值：`fscanf(fp, "格式控制字符串", 输出列表);`
- **fprintf函数**：和printf函数作用类型，输出列表的值，然后**打印到文件中**：`fprintf(fp, "格式控制字符", 输出列表);`

### 四、文件的定位和随机读写

#### 1、==文件的定位==

- **rewind函数**：将fp指针重新回到文件开头位置，调用格式为：`rewind(fp)`;
- **ftell函数**：用来得到文件当前位置，调用格式为：`i = ftell(fp);`
- **fseek函数**
  - 用来移动文件的位置指针，调用格式为：`feek(fp, offset, origin);`
  - fp是文件指针；offset为偏移量，表示相对起始点向后移动的字节数，一般是长整型数据；origin为起始点，规定的起始点有三种：**文件首，数字表示为0**、**当前位置，数字表示为1**、**文件末尾，数字表示为2**。

#### 2、==文件的随机读写==

- 由于一般是读写一个数据块，因此常用fread和fwrite函数。

- ```c
  //将学生数据随机写入磁盘中
  #include <stdio.h>
  
  struct stu			//设定学生数据
  {
      char name[10];
      int number;
      int age;
      char addr[15];
  }boy;
  
  int main()
  {
      FILE *fp;			
      fp = fopen("c:\\Users\\di\\stu_list.txt", "ab+");		//打开并追加二进制文件
  
      if (fp == NULL)
      {
          printf("无法打开文件：");
          return 0;
      }
  
      printf("请输入学生学号1到5，0结束输入：");		//输入学生学号
      scanf("%d", &boy.number);
  
      while (boy.number != 0)
      {
          printf("请输入名字、年龄、地址：\n");
          scanf("%s%d%s", boy.name, &boy.age, boy.addr);
  
          fseek(fp, (boy.number - 1) * sizeof(struct stu), 0);		//将文件指针移动到相应位置
          fwrite(&boy, sizeof(struct stu), 1, fp);		//把学生数据写入文件
  
          printf("请输入学号：");
          scanf("%d", &boy.number);
      }
  
      fclose(fp);
  
      return 0;
  }
  ```

### 五、文件出错检测

- **ferror函数**：用来检测读写时是否出错，其调用格式为：`ferror(fp);`，返回值为0，表示未出错，非零值表示出错。
  - 每次调用输入输出函数均会产生一个新的ferror()的函数值，因此在每次调用后应立即检查，否则检查信息会丢失。
  - 在执行fopen()函数时，ferror()的值会变成0；
- **feof函数**：判断文件是否处于文件结束位置，调用格式为：`feof(fp);`，如果函数返回值为0，表示没有处于文件结束处；
- **clearerr函数**：清除出错标志和文件结束标志，它将文件错误标志和文件结束标志的值设为0，调用格式为：`clearerra(fp);`

## 二、学习心得

之前学c的时候在想，我写这些程序怎么放到文件里？学到这就大概知道怎么一回事了。。。

历经一个多月，总算把c语言基础的这些东西学完了，之后我就继续学数据结构与算法喽。
