#include <iostream>
#include <string.h>
#pragma warning(disable:4996) 
using namespace std;

char a[121] , b[121] ;
char cInt1[121] = "", cInt2[121] = "";
char cDec1[121] = "", cDec2[121] = "";
int int1[120] = { 0 }, int2[120] = { 0 }, int3[120] = { 0 };
int dec1[120] = { 0 }, dec2[120] = { 0 }, dec3[120] = { 0 };
int i1, i2, i3, d1, d2, d3, i, j, flag = 0;

void number(int p, int q)
{
	//第一个数取整数部分
	for (i = 0; a[p] != '.'; i++, p++)
		cInt1[i] = a[p];
	p++;
	//第一个数取小数部分
	for (j = 0; a[p] != '\0'; j++,p++)
		cDec1[j] = a[p];
	//第二个数取整数部分
	for (i = 0; b[q] != '.'; i++,q++)
		cInt2[i] = b[q];
	q++;
	//第二个数取小数部分
	for (j = 0; b[q] != '\0'; j++,q++)
		cDec2[j] = b[q];
	//获取长度
	i1 = strlen(cInt1);
	d1 = strlen(cDec1);
	i2 = strlen(cInt2);
	d2 = strlen(cDec2);
	i3 = i1 > i2 ? i1 : i2;
	d3 = d1 > d2 ? d1 : d2;
}
void change()
{
//字符数组转化为整型数组
	for (int i = 0; i < i1; i++)
		int1[i1 - 1 - i] = cInt1[i] - '0';
	for (int i = 0; i < d1; i++)
		dec1[i] = cDec1[i] - '0';

	for (int i = 0; i < i2; i++)
		int2[i2 - 1 - i] = cInt2[i] - '0';
	for (int i = 0; i < d2; i++)
		dec2[i] = cDec2[i] - '0';
}
void sub(int k)
{
	//交换从而实现大数是a1.a2，小数是b1.b2，从而大数减小数
	if (i1 < i2 || (i1 == i2 && (strcmp(cInt1, cInt2) < 0 || strcmp(cInt1, cInt2) && strcmp(cDec1, cDec2) < 0)))
	{
		int temp;
		char n[121];
		strcpy(n, cInt1);
		strcpy(cInt1, cInt2);
		strcpy(cInt2, n);
		temp = i1;
		i1 = i2;
		i2 = temp;
		strcpy(n, cDec1);
		strcpy(cDec1, cDec2);
		strcpy(cDec2, n);
		temp = d1;
		d1 = d2;
		d2 = temp;
		flag = 1;
	}
	change();
	//运算
	for (i = 0; i < i3; i++)
		int3[i] = int1[i] - int2[i];
	for (i = 0; i < d3; i++)
		dec3[i] = dec1[i] - dec2[i];
	//负化正
	//小数部分 最后一位到百分位（若存在的话）
	for (i = d3 - 1; i > 0; i--)
		if (dec3[i] < 0)
		{
			dec3[i] += 10;
			dec3[i - 1]--;
		}
	//十分位
	if (dec3[0] < 0)
	{
		dec3[0] += 10;
		int3[0]--;
	}
	//整数部分
	for (i = 0; i < i3 - 1; i++)
		if (int3[i] < 0)
		{
			int3[i] += 10;
			int3[i + 1]--;
		}
	//减小lc1从而不输出整数高位的0
	for (i = i3 - 1; int3[i] == 0 && i > 0; i--);
	i3 = i + 1;
	//减小lc1从而不输出小数末尾的0
	for (i = d3 - 1; dec3[i] == 0 && i > 0; i--);
	d3 = i + 1;
	//输出
	if ((!k && flag) || (k && !flag))
		if (!k || (k && i3 > 1 && d3 > 1))
		//保证-xx.xx-(-xx.xx)的结果为0.0，而不是-0.0	
			cout << '-';
	for (i = i3 - 1; i >= 0; i--)
		cout << int3[i];
	cout << '.';
	for (i = 0; i < d3; i++)
		cout << dec3[i];
	cout << endl;
}
void add(int k)
{
	change();
	//运算
	for (i = 0; i < i3; i++)
		int3[i] = int1[i] + int2[i];
	for (i = 0; i < d3; i++)
		dec3[i] = dec1[i] + dec2[i];
	//进位
	//小数部分 从最后一位到百分位（若存在的话）
	for (i = d3 - 1; i > 0; i--)
		if (dec3[i] > 9)
		{
			dec3[i] -= 10;
			dec3[i - 1]++;
		}
	//十分位
	if (dec3[0] > 9)
	{
		dec3[0] -= 10;
		int3[0]++;
	}
	//整数部分
	for (i = 0; i < i3 - 1; i++)
		if (int3[i] > 9)
		{
			int3[i] -= 10;
			int3[i + 1]++;
		}
	//减小lc1从而不输出小数末尾的0
	for (i = d3 - 1; dec3[i] == 0 && i > 0; i--);
	d3 = i + 1;
	//输出
	if (k)
		cout << '-';
	for (i = i3 - 1; i >= 0; i--)
		cout << int3[i];
	cout << '.';
	for (i = 0; i < d3; i++)
		cout << dec3[i];
	cout << endl;
}

int main()
{
	cout << "请输入两个高精度实数（格式为xxx.xxx)：" << endl;
	cin >> a;
	cin >> b;
	if (a[0] == '-')
		if (b[0] == '-')
		{number(1, 1); sub(1);}
		else
		{number(1, 0); add(1);}
	else
		if (b[0] == '-') 
		{number(0, 1); add(0);}
		else 
		{number(0, 0); sub(0);}
	return 0;
}
