#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define LAN sizeof (struct list)
#define LEN sizeof (struct list2)
#define LIN sizeof (struct queue)

typedef struct queue
{
	int data;
	queue *next;
};

typedef struct date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

typedef struct data
{
	int type;
	double money;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

typedef struct list2
{
	data data1;
	list2 *next;
};

typedef struct list
{
	char name[10];
	char number[20];
	int password;
	char ID[20];
	char mobile[20];
	int credit_rating;
	date start_date;
	list2 *next1;
	list *next2;
	int n;
};

list *h;
void deposit(list *h);
void withdrawal(list *h);
void business_handling(list *h);
void balance(list2 *h);
void printmessage(list *h);
int main();
double reserve = 0;
double total = 0;
double money = 0;
int windows[5] = { 0 };
int qn, sn;

int limit()
{
	if (reserve - total < 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

list2 *createlist2(list2 *h,data data1)
{
	if (h == NULL)
	{
		h = (list2 *)malloc(LEN);
		h->data1.type = data1.type;
		h->data1.money = data1.money;
		h->data1.year = data1.year;
		h->data1.month = data1.month;
		h->data1.day = data1.day;
		h->data1.hour = data1.hour;
		h->data1.minute = data1.minute;
		h->data1.second = data1.second;
		h->next = NULL;
	}
	return h;
}

void findlist2(list2 *h,data data1,int type)
{
	if (h != NULL&& 
		h->data1.year == data1.year&&h->data1.month == data1.month&&h->data1.day == data1.day&&
		h->data1.hour == data1.hour, h->data1.minute == data1.minute, h->data1.second == data1.second)
	{
		
		findlist2(h, data1, type);
	}
	else if (h == NULL)
	{
		h = createlist2(h, data1);
	}
	else
	{
		findlist2(h->next, data1, type);
	}
}

void printlist2(list2 *h)
{
	double money;
	if (h != NULL)
	{
		if (h->data1.type == 0)
		{
			money = -h->data1.money;
			printf("%lf    %d.%d.%d  %d:%d:%d\n", money, h->data1.year, h->data1.month, h->data1.day, h->data1.hour, h->data1.minute, h->data1.second);
		}
		else
		{
			printf("%lf    %d.%d.%d  %d:%d:%d\n", h->data1.money, h->data1.year, h->data1.month, h->data1.day, h->data1.hour, h->data1.minute, h->data1.second);
		}
		printlist2(h->next);
	}
}

void deletelist2(list2 *h)
{
	if (h->next != NULL)
	{
		free(h->next);
	}
}

list *createlist(list *h, char name[10], char number[20], char mobile[20], int password, char ID[20], int credit_rating, date start_date)
{
	list *q;
	q = (list *)malloc(LAN);
	strcpy(q->name, name);
	strcpy(q->number, number);
	strcpy(q->mobile, mobile);
	q->password = password;
	strcpy(q->ID, ID);
	q->credit_rating = credit_rating;
	q->start_date = start_date;
	q->next1 = NULL;
	q->n = 0;
	q->next2 = h->next2;
	h->next2 = q;
	return h;
}

int nlist(list *h,int n)
{
	if (h != NULL)
	{
		n++;
		n = nlist(h->next2, n);
	}
	return n;
}

void findlist(list *h1, char number[20],data data1, int flag, int password)
{
	if (flag == 1 && h1->next2 != NULL && strcmp(h1->next2->number, number) == 0)
	{
		date x = h1->next2->start_date;
		printf("姓名：%s\n", h1->next2->name);
		printf("身份证号：%s\n", h1->next2->ID);
		printf("银行卡号：%s\n", h1->next2->number);
		printf("密码：%d\n", h1->next2->password);
		printf("开户日期：%d.%d.%d %d:%d:%d\n", x.year, x.month, x.day, x.hour, x.minute, x.second);
	}
	else if (flag == 4 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		if (h1->password == password)
		{
			printmessage(h1);
		}
		else
		{
			printf("密码输入错误！\n");
			business_handling(h);
		}
	}
	else if (flag == 3 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		money = 0;
		balance(h1->next1);
		printf("您的余额为：%lf\n", money);
		if (data1.money > money)
		{
			printf("取款失败！\n");
			system("pause");
			exit(0);
		}
	}
	else if (flag == 2 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		if (data1.type == 0 && h1->password == password)
		{
			list2 *h2 = NULL;
			h2 = (list2 *)malloc(LEN);
			h2->data1 = data1;
			h2->next = h1->next1;
			h1->next1 = h2;
			h1->n++;
		}
		if (data1.type == 1)
		{
			list2 *h2 = NULL;
			h2 = (list2 *)malloc(LEN);
			h2->data1 = data1;
			h2->next = h1->next1;
			h1->next1 = h2;
			h1->n++;
		}
		if (data1.type == 0 && h1->password != password)
		{
			printf("密码输入错误！\n");
			business_handling(h);
		}
	}
	else if (flag == 0 && h1->next2 != NULL && strcmp(h1->next2->number, number) == 0)
	{
		if (h1->next2->password == password)
		{
			free(h1->next2);
			h1->next2 = NULL;
		}
		else
		{
			printf("密码输入错误！\n");
		}
	}
	else
	{
		findlist(h1->next2, number, data1, flag, password);
	}
}

void deletelist(list *h)
{
	if (h->next2 != NULL)
	{
		free(h->next2);
	}
}

int business_window(queue *q)
{
	int i;
	queue *temp;
	int flag = 0;
	for (i = 0; i < 5; i++)
	{
		if (windows[i] == 0)
		{
			temp = q->next;
			q->next = temp->next;
			windows[i] = temp->data;
			printf("请到%d号窗口办理业务\n", i);
			flag = 1;
			break;
		}
	}
	FILE *fp1;
	fp1 = fopen("queue.txt", "r+");
	int n = 2;
	for (i = 0; i < 5; i++)
	{
		fseek(fp1, n, SEEK_SET);
		n = n + 2;
		fprintf(fp1, "%d ", windows[i]);
	}
	fclose(fp1);
	return flag;
}

queue *line_up(queue *q)
{
	int y, z;
	queue *p, *r;
	FILE *fp1;
	fp1 = fopen("queue.txt", "r+");
	fscanf(fp1, "%d", &sn);
	int i;
	for (i = 0; i < 5; i++)
	{
		fscanf(fp1, "%d", &windows[i]);
	}
	printf("请输入1以生成您的排队号\n");
	scanf("%d", &y);
	if (y == 1)
	{
		sn++;
	}
	for (p = q; p != NULL; p = p->next)
	{
		if (p->next == NULL)
		{
			r = (queue *)malloc(LIN);
			r->data = sn;
			r->next = p->next;
			p->next = r;
			break;
		}
	}
	fseek(fp1, 0, SEEK_SET);
	fprintf(fp1, "%d", sn);
	printf("您的排队号为：%d号\n", sn);
	z = business_window(q);
	fclose(fp1);
	if (z == 1)
	{
		business_handling(h);
	}
	else
	{
		return q;
	}
}

//用户开户函数：
/*用户通过交互见面手动将个人信息输入到变量之中，由程序自动生成用户的信用度和开户时间两项内容，
通过findlist函数找到新建的用户信息并输出给用户，用户可以检查并确认信息，
如果信息正确将反馈给用户"开户完成！",如果信息不正确将通过findlist函数删除此用户信息并将返回用户开户函数account_opening*/
list *account_opening()
{
	char name[10];
	char number[20];
	char ID[20];
	char mobile[20];
	int credit_rating;
	int password;
	date start_date;
	printf("请输入您的姓名：\n");
	scanf("%s", name);
	printf("请输入您的身份证号：\n");
	scanf("%s", ID);
	printf("请输入您的银行卡号：\n");
	scanf("%s", number);
	printf("请输入您的手机号：\n");
	scanf("%s", mobile);
	printf("请输入六位数字密码：\n");
	scanf("%d", &password);
	//用户输入个人信息
	credit_rating = 10;
	time_t now;
	struct tm *tm_now;
	time(&now);
	tm_now = localtime(&now);
	start_date.year = tm_now->tm_year + 1900;
	start_date.month = tm_now->tm_mon + 1;
	start_date.day = tm_now->tm_mday;
	start_date.hour = tm_now->tm_hour;
	start_date.minute = tm_now->tm_min;
	start_date.second = tm_now->tm_sec;
	//系统生成用户信用度和开户时间
	h = createlist(h, name, number, mobile, password, ID, credit_rating, start_date);
	//在邻接表里创建用户个人节点
	data data1;
	data1.type = 0; data1.money = 0; 
	data1.year = 0; data1.month = 0; data1.day = 0; 
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	printf("请核对您的信息：\n");
	findlist(h, number, data1, 1, password);
	//反馈用户的个人信息帮助用户确定个人信息
	printf("如果没有出错，请按1\n");
	printf("如果有错误，请按2\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		printf("开户完成！\n");
		return h;
	}
	else
	{
		findlist(h, number, data1, 2, password);//找到输入错误的个人信息并删除
		h = account_opening();//返回用户开户函数
	}
}

void balance(list2 *h)
{
	if (h != NULL)
	{
		if (h->data1.type == 1)
		{
			money = money + h->data1.money;
		}
		if (h->data1.type == 0)
		{
			money = money - h->data1.money;
		}
		balance(h->next);
	}
}

void print(list *h)
{
	char number[20];
	int password;
	printf("请输入账号：");
	scanf("%s", number);
	printf("请输入六位数字密码：");
	scanf("%d", &password);
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 4, password);
}

void printmessage(list *h)
{
	printf("姓名：%s\n银行卡号：%s\n身份证号：%s\n", h->name, h->number, h->ID);
	printf("收支清单：\n");
	printlist2(h->next1);
}

//用户存款函数：
/*用户通过交互界面手动将存款信息(银行卡账号、密码)和存款金额输入到系统中，
系统将反馈输入的账户号和存款金额，用于用户检查确定，如果出错将返回功能函数界面，
系统生成存款信息(存款类、金额、存款时间)并通过findlist函数将其新建插入到用户存取款链表中,返回功能函数*/
void deposit(list *h)
{
	double money;
	char number[20];
	int x = 0;
	printf("您选择的是存款业务\n");
	printf("请输入银行卡号：");
	scanf("%s", number);
	printf("请输入存款金额：");
	scanf("%lf", &money);
	//用户输入存款信息
	printf("您确认存入\n");
	printf("账号：%s\n金额：%lf\n", number, money);
	//系统反馈存款信息
	printf("请输入序号以确定存款：\n");
	printf("1.确认    2.取消\n");
	scanf("%d", &x);
	if (x == 1)
	{
		data data1;
		data1.type = 1;
		data1.money = money;
		time_t now;
		struct tm *tm_now;
		time(&now);
		tm_now = localtime(&now);
		data1.year = tm_now->tm_year + 1900;
		data1.month = tm_now->tm_mon + 1;
		data1.day = tm_now->tm_mday;
		data1.hour = tm_now->tm_hour;
		data1.minute = tm_now->tm_min;
		data1.second = tm_now->tm_sec;
		findlist(h, number, data1, 2, 0);
		printf("存款成功！\n");
		//系统生成并保存存款信息
		business_handling(h);
	}
	else
	{
		business_handling(h);
		//如果出错，返回功能函数界面
	}
}

//用户取款函数
/*用户通过交互界面输入取款信息(银行卡号、密码)，通过findlist函数查询账户余额，
并验证密码，如果密码错误则返回功能函数界面，
用户输入取款金额，通过findlist函数验证取款金额是否小于余额，如果不是则提示取款失败并关闭程序，
验证取款金额后，输出取款数据，如果用户同意取款数据则将取款信息新建节点并插入到用户的存取款信息链表中，
否则返回功能函数界面*/
void withdrawal(list *h)
{
	double money;
	char number[20];
	int password;
	printf("您选择的是取款业务\n");
	printf("请输入银行卡号：");
	scanf("%s", number);
	printf("请输入密码：");
	scanf("%d", &password);
	//用户输入取款信息
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 3, password);
	//查询账户余额并验证密码
	printf("请输入取款金额：\n");
	scanf("%lf", &money);//用户输入取款金额
	printf("您确认取出\n");
	printf("账号：%s\n金额：%lf\n", number, money);
	data1.money = money;
	findlist(h, number, data1, 3, password);
	//验证取款金额
	printf("请输入序号以确定取款：\n");
	printf("1.确认    2.取消\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		data1.type = 0;
		data1.money = money;
		time_t now;
		struct tm *tm_now;
		time(&now);
		tm_now = localtime(&now);
		data1.year = tm_now->tm_year + 1900;
		data1.month = tm_now->tm_mon + 1;
		data1.day = tm_now->tm_mday;
		data1.hour = tm_now->tm_hour;
		data1.minute = tm_now->tm_min;
		data1.second = tm_now->tm_sec;
		findlist(h, number, data1, 2, password);
		printf("取款成功！\n");
		business_handling(h);
		//取款信息存入用户存取款信息链表并返回功能函数界面
	}
	else
	{
		business_handling(h);
		//用户返回功能函数界面
	}
}

//用户注销账户功能函数
/*用户通过交互界面输入账户信息(银行卡号、密码)，通过findlist函数验证密码和查询账户余额，
密码错误则返回功能函数界面，用户确认信息后通过findlist函数删除账户信息并返回功能函数界面，否则直接返回功能函数界面*/
void logout_account(list *h)
{
	char number[20];
	int password;
	printf("请输入银行卡号：");
	scanf("%s", number);
	printf("请输入六位数字密码：");
	scanf("%d", &password);
	//用户输入账户信息
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 3, password);
	//验证密码，查询余额
	printf("请输入序号以确定注销账户%s：\n", number);
	printf("1.确认    2.取消\n");
	int x = 0;
	scanf("%d", &x);
	if (x == 1)
	{
		findlist(h, number, data1, 0, password);
		printf("注销成功！");
		business_handling(h);
		//删除用户信息，返回功能函数界面
	}
	if (x == 2)
	{
		business_handling(h);
		//返回功能函数界面
	}
}

void business_handling(list *h)
{
	printf("请输入您的排队号\n");
	scanf("%d", &qn);
	system("CLS");
	printf("1.开户\n");
	printf("2.存款\n");
	printf("3.取款\n");
	printf("4.注销账户\n");
	printf("5.打印清单\n");
	printf("6.返回上一层\n");
	printf("请选择业务序号：");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		h = account_opening();
	}
	else if (x == 2)
	{
		deposit(h);
	}
	else if (x == 3)
	{
		withdrawal(h);
	}
	else if (x == 4)
	{
		logout_account(h);
	}
	else if(x == 5)
	{
		print(h);
	}
	else
	{
		main();
	}
}

//文件读取函数：
/*将data.txt文件内已经按照格式排好的数据通过fscanf读取出来，
先读取银行内储备金reserve，之后读取用户个数n，通过for循环分别读取用户的个人信息和存取款信息，
边读取存取款信息边计算全部用户收支总额，将用于计算判断储备金是否满足用户取款。*/
int read()
{
	FILE *fp;
	int n, m, i, j;
	list *q = NULL;
	fp = fopen("data.txt", "r");
	fscanf(fp, "%lf", &reserve);//读取银行储备金
	fscanf(fp, "%d", &n);//读取用户个数
	h = (list *)malloc(LAN);
	h->next2 = NULL;
	for (i = 0; i < n; i++)
	{
		q = (list *)malloc(LAN);
		fscanf(fp, "%s %d %s %s %d %s %d %d %d %d %d %d %d", q->number, &q->password, q->mobile, q->name, &q->credit_rating, q->ID
			, &q->start_date.year, &q->start_date.month, &q->start_date.day, &q->start_date.hour, &q->start_date.minute, &q->start_date.second, &q->n);
		//读取用户个人信息
		q->next1 = NULL;
		m = q->n;
		list2 *q2 = NULL;
		for (j = 0; j < m; j++)
		{
			q2 = (list2 *)malloc(LEN);
			fscanf(fp, "%d %lf %d %d %d %d %d %d", &q2->data1.type, &q2->data1.money
				, &q2->data1.year, &q2->data1.month, &q2->data1.day
				, &q2->data1.hour, &q2->data1.minute, &q2->data1.second);
			//读取用户存取款信息
			if (q2->data1.type == 1)
			{
				total = total + q2->data1.money;
			}
			if (q2->data1.type == 0)
			{
				total = total - q2->data1.money;
			}//计算全部用户的收支总额
			q2->next = q->next1;
			q->next1 = q2;
		}
		q->next2 = h->next2;
		h->next2 = q;
	}
	return n;//返回用户个数
}

//文件写入函数：
/*将邻接表中的数据按照格式用fprintf写入文件data.txt中，
先遍历每个用户的存取款信息并求和赋值到total中，将储备金reserve和total求和以更新储备金，
之后通过for循环将用户个人信息及其对应的存取款信息写入文件data.txt之中。*/
void write(list *h,int n)
{
	FILE *fp;
	int m, i, j;
	list *q = h;
	fp = fopen("data.txt", "w");
	total = 0;
	for (i = 0; i < n; i++)
	{
		m = q->n;
		list2 *q1 = q->next1;
		for (j = 0; j < m; j++)
		{
			if (q1->data1.type == 1)
			{
				total = total + q1->data1.money;
			}
			if (q1->data1.type == 0)
			{
				total = total - q1->data1.money;
			}
			q1 = q1->next;
		}
		q = q->next2;
	}//遍历用户的存取款信息并求和赋值给total
	reserve = reserve + total;//计算储备金reserve
	fprintf(fp, "%lf ", reserve);
	fprintf(fp, "%d ", n);
	q = h;
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s %d %s %s %d %s %d %d %d %d %d %d %d ", q->number, q->password, q->mobile, q->name, q->credit_rating, q->ID
			, q->start_date.year, q->start_date.month, q->start_date.day, q->start_date.hour, q->start_date.minute, q->start_date.second, q->n);
		//将用户个人信息写入
		m = q->n;
		list2 *q2 = q->next1;
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%d %lf %d %d %d %d %d %d ", q2->data1.type, q2->data1.money
				, q2->data1.year, q2->data1.month, q2->data1.day
				, q2->data1.hour, q2->data1.minute, q2->data1.second);
			//将用户存取款信息写入
			q2 = q2->next;
		}
		q = q->next2;
	}
	fclose(fp);
	printf("请确认业务办理完成\n");
	printf("1.确定    2.取消\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		FILE *fp1;
		int n = 0;
		fp1 = fopen("queue.txt", "r+");
		fseek(fp1, n, SEEK_SET);
		fprintf(fp1, "%d ", sn);
		for (i = 0; i < 5; i++)
		{;
			if (windows[i] == qn)
			{
				windows[i] = 0;
				n = n + 2;
				fseek(fp1, n, SEEK_SET);
				fprintf(fp1, "%d ", windows[i]);
			}
			else
			{
				n = n + 2;
				fseek(fp1, n, SEEK_SET);
				fprintf(fp1, "%d ", windows[i]);
			}
		}
		fclose(fp1);
	}
	else
	{
		system("CLS");
		main();
	}
}

int main()
{
	int n;
	queue *q = NULL;
	q = (queue *)malloc(LIN);
	q->next = NULL;
	n = read();
	int y = 0;
	y = limit();
	if (y == 1)
	{
		printf("暂时无法办理业务！\n");
		system("pause");
		return 0;
	}
	reserve = reserve - total;
	printf("银行业务系统\n");
	printf("1.排队取号\n");
	printf("2.办理业务\n");
	printf("3.退出系统\n");
	printf("请选择序号：");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		q = line_up(q);
		system("pause");
		return 0;
	}
	if (x == 2)
	{
		business_handling(h);
	}
	if (x == 3)
	{
		n = 0;
		n = nlist(h, n) - 1;
		write(h->next2, n);
		system("pause");
		return 0;
	}
	n = 0;
	n = nlist(h, n) - 1;
	write(h->next2, n);
	system("pause");
	return 0;
}
