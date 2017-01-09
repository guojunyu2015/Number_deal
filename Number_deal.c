#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int Get_prime_num(int n);
int get_common_divisor(int a,int b);
int get_max_common(int a,int b);
int GetMostAccur_num(char *str);
int my_atoi(const char *str);
double my_atof(const char *str);

int main(int argc,char **argv)
{
	double i = 0;
	int a[10] = {1,11,222,33,11,444,1,1,5,10};
	char b[] = "-1121000.111110e-10";
	double c = 0.00;
	GetMostAccur_num(b);
	return 0;
}


/*
	获取num数组中出现次数最多的数字以及出现的次数
	输入参数 iNum:iNum数组地址，iCount:数组中的元素个数
*/
int GetMostAccur_num(char *str)
{
	int i = 0;
	int fre[255];
	char max_val;
	int max_count = 0;
	
	max_val = '\0';
	for(i = 0;i < 255;i++)
		fre[i] = 0;
	
	for(i = 0;i < strlen(str);i++)
		fre[str[i]]++;
	
	for(i = 0;i < 255;i++)
	{
		if(fre[i] > max_count)
		{
			max_val = i;
			max_count = fre[i];
		}
	}
	
	printf("字符串中出现次数最多的字符为:[%c],出现次数为:[%d]\n",max_val,max_count);
	return 0;
}


double my_atof(const char *str)
{
	double val = 0.0;		/*返回值*/
	double dec = 1;			/*小数部分数值*/
	double dec_count = 0.1;	/*小数部分进位计数*/
	int sign = 1;			/*返回值的正负值*/
	int iee754_count = 0;
	int iee754_sign = 1;
	int i;
	
	while(*str == ' ')
		str++;
	
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	else if(*str == '+')
		str++;
	
	/*获取整数部分*/
	while(*str)
	{
		if(*str == '.' || *str == 'e' || *str == 'E')
			break;
		else if(*str < '0' || *str > '9')
		{
			str++;
			continue;
		}
		val *= 10;
		val += *str - '0';
		str++;
	}
	
	/*判断是否存在小数部分*/
	if(*str == '.')
	{
		str++;
		while(*str)
		{
			if(*str == 'e' || *str == 'E')
				break;
			else if (*str < '0' || *str > '9')
			{
				str++;
				continue;
			}
			dec += dec_count * (*str - '0');
			dec_count *= 0.1;
			str++; 
		}
	}
	
	/*计算科学计数值部分*/
	if(*str == 'e' || *str == 'E')
	{
		str++;
		
		/*获取科学计数部分正负值*/
		if(*str == '-')
		{
			iee754_sign = -1;
			str++;
		}
		else if (*str == '+')
			str++;
		
		while(*str)
		{
			if (*str < '0' || *str > '9')
			{
				str++;
				continue;
			}
			iee754_count *= 10;
			iee754_count += *str - '0';
			str++;
		}
	}
	
	/*计算最终值*/
	val += dec;
	for(i = 0;i < iee754_count;i++)
	{
		if(iee754_sign == 1)
			val *= 10;
		else 
			val *= 0.1;
	}
	val *= sign;
	
	return val;
}


/*获取数值n以内的所有质数并打印出来*/
int Get_prime_num(int n)
{
	/*如果数值小于等于1,则不是质数*/
	if(n <= 1)
	{
		printf("数值[%d]内不包含质数\n",n);
		return -1;
	}
	
	int i = 0,j = 0;
	bool *prime_str = (bool *)malloc(sizeof(bool) * (n+2));
	if(prime_str == NULL)
	{
		printf("malloc space fail\n");
		return -1;
	}
	
	/*初始化bool数组,将奇数位初始化为true,将偶数位初始化为false,最后一位(n+1)为缓存位*/
	for(i = 1;i <= n;i+=2)
	{
		prime_str[i] = true;
		prime_str[i+1] = false;
	}
	
	/*遍历数组中的值*/
	for(i = 3;i <= (int)(sqrt(n)-1);i+=2)
	{
		if(prime_str[i] == true)
		{
			for(j=i+i;j<=n;j+=i)
			{
				prime_str[j] = false;
			}
		}
	}
	
	/*打印数组中所有的质数*/
	for(i = 0;i <= n;i++)
	{
		if(prime_str[i] == true)
			printf("[%d]为质数\n",i);
	}
	
	free(prime_str);
	return 0;
}

/*求两个数值a和b的最大公约数(a>b)*/
int get_common_divisor(int a,int b)
{
	int c = a%b;
	int tmp_b,tmp;
	tmp_b = b;
	while(c != 0)
	{
		tmp = tmp_b;
		tmp_b = c;
		c = tmp%c;
	}
	printf("%d和%d的最大公约数是:[%d]\n",a,b,tmp_b);
	return tmp_b;
}

/*最大公倍数*/
int get_max_common(int a,int b)
{
	int least_common = get_common_divisor(a,b);
	printf("%d和%d的最大公倍数为:[%d]\n",a,b,((a*b)/least_common));
	return 0;
}

int my_atoi(const char *str)
{
	int sign = 1;
	int value = 0;
	char tmp;
	while(*str == ' ')
		str++;
	
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	
	while(tmp = *str)
	{
		if(tmp < '0' || tmp > '9')
		{
			str++;
			continue;
		}
		value *= 10;
		value += tmp - '0';
		str++;
		
		if(value < 0)	/*如果值越界,直接返回0值*/
			return 0;
	}
	
	return value * sign;
}

