#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
char* vir; 
char* check;
int count_letter = 0; //количесиво различных букв в примере
int letter_now = 0; //количество букв, которым нашли значение
int res = 0; int ind_res = 0;

 
double start, diff;
int answer(short int mas[])
{
	int plus = 0; 
	int result = 0; 
	int first_0 = 0;
	int summa = 0;
	int flag = 0;

	


	for (int i = 0; i < strlen(vir); i++)
	{
		if (vir[i] >= 'A' && vir[i] <= 'Z')
		{
			int add = vir[i]-65;//взятие индекса буквы
			
			if (mas[add] == 0 && first_0==1)return 0;//если значение буквы=0, и эта буква первая в слагаемом, то значение выбрано неверно
			if (flag == 0)//если еще не дошли до знака "="
			{
				plus = plus * 10 + mas[add];//преобразование значений букв в число
				first_0 = 0;
			}
			else
			{
				result = result * 10 + mas[add];//нахождение результата для суммы
			}
		}
		else
		{
			if (vir[i] == '+')
			{
				first_0 = 1;
				summa += plus;//сложение всех слагаемых
				plus = 0;
			}
			else
				if (vir[i] == '=')
				{
					ind_res = i;
					summa += plus;
					flag = 1;
				}
				else
					if (vir[i] == ' ')continue;
		}
	}
	
	if (result == summa)
	{
		res = result;
		return 1;
	}
	else return 0;
}

void print(short int mas[])
{
	for (int i = 0; i < ind_res; i++)
	{
		if (vir[i] >= 'A' && vir[i] <= 'Z')
		{
			int add = vir[i] - 65;
			printf("%d",mas[add]);
		}
		else
		{
			if (vir[i] == '+')
			{
				printf("+");
			}
		}
	}
	printf("=%d",res);
}

int solution_of_rebus(short int mas[],short int num[])
{
	int zn = 0;
	int new_letter = 0;
	for(int i=0;i<26;i++)
		if (mas[i] == -1 ) { zn = mas[i]; new_letter = i; break; }//нахождение первой буквы, которой еще не было дано значение

	

	for (int i = 0; i < 10; i++)
	{
		if (num[i] == FALSE)//нахождение цифры, которую еще не присвоили букве
		{

			mas[new_letter] = i;//присваивание букве значения
			num[i] = TRUE;//флаг того, что цифра занята
			letter_now++;//счетчик занятых букв
			if (letter_now == count_letter)//если все буквы получили значения
			{
				 
				if (answer(mas)) { print(mas); return 1; }//проверка результата
			}
			else
				if(solution_of_rebus(mas,num)) return 1;//рекурсивный спуск вниз

			
			num[i] = FALSE;//если ответ был неверным, то флаги с занятых цифр снимаются, значения у букв убираются
			letter_now--;
			mas[new_letter] = zn;
			

		}
	}

	return 0;
}


int main()
{
	int sh = -1;

	char t = 0;
	int index = -1;
	int error = 0;
	short int table[26];
	short int number[10];

	
	int plus = 0; int count = 0;

	
	


	//замена цикла на memset - машинно-независимая оптимизация
	memset(number, FALSE, 10 * sizeof(number[0]));
	//развертка цикла
	for (int i = 0; i < 26; i += 2)
	{
		table[i] = -2;
		table[i + 1] = -2;
	}
	
	int vhod = 0;
	vir = (char*)calloc(20, sizeof(char));
	check = (char*)calloc(8, sizeof(char));
	int check_ind = 0;
	
	while (t != '\n')
	{
		sh++; index++;
		if (sh == 19) { vir = (char*)realloc(vir, sizeof(char) * (index+20)); sh = -1; }//довыделение памяти под выражение
		t = getc(stdin);

		if (t >= 'A' && t <= 'Z')
		{
			int state = t - 65;//получение индекса таблицы, под которым будет храниться буква
			
					if (table[state] == -2)//если такой буквы не было
					{
						table[state] = -1;//ставится флаг, что в примере есть такая буква
						count_letter++;//увеличение счетчика различных букв
					}
		}
		else {
			vhod++;
			if (t == '+' || t == '=')error++;
			else
				if (t != ' ' && t != '\n')
				{
					printf("invalid character"); return 0;
				}
		}
		
		vir[index] = t;
		
		
	}
	check[check_ind] = vir[index - 1];
	check[check_ind+1] = 0;
	vir[index] = 0;

	if (error < 2) { printf("ERROR"); return 0; }
	if (count_letter == 1 && strlen(vir) >= 5)
	{
		printf("0+0=0"); return 1;
	}
	start = clock();
	solution_of_rebus(table, number);

	diff = clock() - start;
	float msec = diff / CLOCKS_PER_SEC;
	printf("\nTime %f\n", msec);
	return 1;
}
