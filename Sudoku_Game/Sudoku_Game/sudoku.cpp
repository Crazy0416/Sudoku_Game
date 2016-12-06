#include "sudoku.h"

sudoku::sudoku(void)
{
	for(int i =0; i <9; i++)          // sudoku�� �� arr�� 0���� �ʱ�ȭ
		for(int j = 0; j < 9; j++)
		{
			sudoku_arr[i][j] = 0;
		}

	for(int i = 0; i < 9; i++)            // can_save_arr[x��ǥ][y��ǥ][1~9���� ����]
		for(int j = 0; j < 9; j++)
			for(int k = 0; k < 9; k++)
				can_save_arr[i][j][k] = k + 1;
}

sudoku::~sudoku(void) // �׳� �ʱ�ȭvoid user_sudoku_solve(); // ����ڰ� ���� Ǫ�� �Լ�
{	
	for(int i =0; i <9; i++)          // sudoku�� �� arr�� 0���� �ʱ�ȭ
		for(int j = 0; j < 9; j++)
		{
			sudoku_arr[i][j] = 0;
		}

	for(int i = 0; i < 9; i++)            // can_save_arr[x��ǥ][y��ǥ][1~9���� ����]
		for(int j = 0; j < 9; j++)
			for(int k = 0; k < 9; k++)
				can_save_arr[i][j][k] = k + 1;
}

void sudoku::just_print_sudoku()                  // ���� ������ �׸��� �����ش�.
{
	SKY;
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				if(j == 3 || j == 6 || j ==9)
				{
					YEL;
					printf("       ��");
				}
				if(sudoku_arr[i][j] != 0)
				{
					SKY;
					printf("\t%d",sudoku_arr[i][j]);
				}
				else
				{
					YEL;
					printf("\t%d",sudoku_arr[i][j]);
				}
			}
			if(i == 2 || i == 5)
			{
				printf("\n");
				YEL;
				printf("\t����������������������������������������������������������������������������������");
				printf("\n");
			}
			else
				printf("\n");
		}
}

void sudoku::make_sudoku()    // ������ ����
{
	int x = 0;/*����ǥ*/
	int y = 0;/*����ǥ*/
	int swt = 1;                      // ����ġ print_sudoku���� ���
	while(true)
	{

		print_sudoku(x,y,swt);          // ������ �׷��� �Ŀ� ����Ű�� �����̽��� 'e' 'l' Ű�� ����Ѵ�.
		int put_in_result;     // ������ �迭 �ڸ��� ���� ��

		if(x == -1 && y == -1) // ����°� ���� �� ����.
		{	
			char C_sudoku_num[2]= "0";
			char name[12] = "quest";
			while (true)
			{
				system("cls");
				cout << "������ ���� ��ġ�� ���ڷ� ��������.(1~9) : ";
				cin >> C_sudoku_num[0];
				cout << C_sudoku_num[0] << C_sudoku_num[1];
				Sleep(1000);
				if (C_sudoku_num[0] <= 9 || C_sudoku_num[0] >= 1)
				{
					break;
				}
				else
				{
					system("cls");
					cout << "�߸� �Է��ϼ̽��ϴ�.";
					Sleep(1000);
				}
			}

			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");

			ofstream fout1;
			fout1.open(name);

			for(int i = 0; i < 9; i++)
			{
				for(int j = 0; j < 9; j++)
				{
					fout1 << "\t";
					fout1 << sudoku_arr[i][j];
				}
				fout1 << endl;
			}
		
			fout1.close();

			return;
		}

		if(x == -2 && y == -2)             // �ٽ� �ʱ�ȭ. �߸� ��������� �ٽ� �ʱ�ȭ �ϴ°�
		{


			for(int i =0; i <9; i++)          // sudoku�� �� arr�� 0���� �ʱ�ȭ
				for(int j = 0; j < 9; j++)
				{
					sudoku_arr[i][j] = 0;
				}

			for(int i = 0; i < 9; i++)            // can_save_arr[x��ǥ][y��ǥ][1~9���� ����]
				for(int j = 0; j < 9; j++)
					for(int k = 0; k < 9; k++)
						can_save_arr[i][j][k] = k + 1;
			x=0;
			y=0;

			
			continue;
		}

		cin >> put_in_result;        // ������ �迭 �ڸ��� ���� ��
		system("cls");
		if(sudoku_arr[y][x] != 0) // �̹� ���� ������ ���
		{
			printf("\n\t���� �����Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // ������ �˻�
			sudoku_arr[y][x] = put_in_result;     // x�� ����ǥ y�� ����ǥ�̱� ����
		else
		{
			printf("\n\t���� ��ġ�Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
		}
	}


}

void sudoku::print_sudoku(int &x/*����ǥ*/, int &y/*����ǥ*/, int swt /*�� ������ print_sudoku�� �ٸ��Լ����� ��¦ �ٸ� �뵵�� ���̹Ƿ� �����ϱ� ���� ����*/)
{


	while(true)      // ������ �׷���
	{
		YEL;
		if(swt == 1)
			printf("\t�����̽� �� ���� �Ŀ� ���� ���� �Է��ϼ���. 'e'�� ������ ����, 'l'�� ������ �ε� �˴ϴ�~~\n\n\n");
		else
			printf("\t�����̽� �� ���� �Ŀ� ���� ���� �Է��ϼ���. 'e'�� ������ ����, 'l'�� ������ �������� ������ �˴ϴ�~~\n\n\n");
		SKY;
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				if(j == 3 || j == 6 || j ==9)
				{
					YEL;
					printf("       ��");
				}
				if(y == i && x == j)               // i�� �� ��ǥ j�� �� ��ǥ�̴�.
				{
					RED;
					printf("\t%d",sudoku_arr[i][j]);
				}
				else if(sudoku_arr[i][j] != 0)
				{
					SKY;
					printf("\t%d",sudoku_arr[i][j]);
				}
				else
				{
					YEL;
					printf("\t%d",sudoku_arr[i][j]);
				}
			}
			if(i == 2 || i == 5)
			{
				printf("\n");
				YEL;
				printf("\t����������������������������������������������������������������������������������");
				printf("\n");
			}
			else
				printf("\n");
		}

		char ch;
		ch = _getch();// ����Ű �Է� ����

		if(ch == DownKey)  // ����Ű �Ʒ� �Է�
		{
			if(y == 8)
				y = 8;
			else
				y++;
		}
		else if(ch == UpKey)  // ����Ű �� �Է�
		{
			if(y == 0)
				y = 0;
			else
				y--;
		}
		else if(ch == RightKey)  // ����Ű ������ �Է�
		{
			if(x == 8)
				x = 8;
			else
				x++;
		}
		else if(ch == LeftKey)  // ����Ű ���� �Է�
		{
			if(x == 0)
				x = 0;
			else
				x--;
		}
		else if(ch == ' '/*�����̽��� �Է�������*/)
		{
			printf("\n\n\t ���� �� �Է� : ");
			return; // �Լ� ����
		}
		else if(ch == 101/* 'e' */)  /*����°� �����ϰ� ������*/
		{
			x = -1;
			y = -1;
			system("cls");
			return;
		}
		else if(ch == 108 /* 'l'*/) /* �� ����� �ε� �ϰ� ������ */
		{
			x = -2;
			y = -2;
			system("cls");
			return;
		}
		else    // ����Ʈ ���϶�
		{
			x = x;
			y = y;
		}
		
		system("cls");
		
	}
}

bool sudoku::row_det(int x, int y, int num) // �� �˻�
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[i][j] != 0) // ���� sudoku_arr[i][j]�� ��ĭ�� �ƴ϶��
			{
				int a = sudoku_arr[i][j]; // int a �� arr[i][j] 
				for(int k = 0; k < 9; k++)
					 can_save_arr[i][k][a-1] = 0; // can_arr[x��ǥ][y��ǥ][a-1] ���� ���ش�. 0���� �����.
			}
		}
	}

	if(can_save_arr[y][x][num-1] == 0)             // ������ �ִٸ� true �ƴϸ� false
		return false;
	else
		return true;
}

bool sudoku::col_det(int x, int y, int num) // �� �˻�
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[j][i] != 0) //����!!! arr[��][��] �� �ƴ� arr[��][��]�̴�. (�� �˻��̱� ������ �ؿ��� �Ʒ��� �� �˻� �� �� ���� �Ѿ��.)
							   // arr[][] �� ��ĭ�� �ƴ϶��
			{
				int a = sudoku_arr[j][i]; 
				for(int k = 0; k < 9; k++) 
					can_save_arr[k][i][a-1] = 0; // can_arr[x��ǥ][y��ǥ][a-1] ���� ���ش�. 0���� �����.
			}
		}
	}
	
	if(can_save_arr[y][x][num-1] == 0)
		return false;
	else
		return true;
}

bool sudoku::box_det(int x, int y, int num) // 3x3 ��� �˻� �κ�, can_save_arr�� ���� �ִٸ� ����� ������ sudoku_arr�� ������� �� �����Ƿ� false ��ȯ
{
	for(int a = 1; a != 7; a += 3) // a,b �� 3x3 ����� ��� �κ� for ���� ������ 3�� ���ذ���.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j �� ���� �� 3x3 ����� ���� ����.
			{
				for(int j = -1; j < 2; j++)
				{
					if(sudoku_arr[a+i][b+j] != 0) 
					{	
						for(int m = -1; m < 2; m++)
						{
							for(int n = -1; n < 2; n++)
							{
								int same = sudoku_arr[a+i][b+j];
								can_save_arr[a+m][b+n][same-1] = 0;
							}
						}
					}
				}
			}
		}
	}

	if(can_save_arr[y][x][num-1] == 0)
		return false;
	else
		return true;
}

void sudoku::detect()
{
	int total = 0; // total �� ���� can_arr[][][] ���� �ϳ� �ۿ� ���� ��츦 ã�� ���� ����
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			for(int k = 0; k < 9; k++)
			{
				if(can_save_arr[i][j][k] == 0) // can_arr[][][] �� 0�̶�� 
				{
					total++; // total ���� �ϳ� �ø���,
				}
				if(total == 8 && sudoku_arr[i][j] == 0) // total ���� 8, �׸��� arr[][]�� ��ĭ, Ȥ�� 0�̶��
				{
					for(int m = 0; m < 9; m++)
					{
						int a;
						if(can_save_arr[i][j][m] != 0)
						{
							a = can_save_arr[i][j][m];
							sudoku_arr[i][j] = a; // �׶� arr[][]�� ���� �־� ���� �Է��Ѵ�.
						}
					}
				}
			}
		total = 0; // total �� �ʱ�ȭ
		}
	}
	
}
void sudoku::row_det() // �� �˻�
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[i][j] != 0) // ���� arr[i][j]�� �ƴ϶�� ��, ��ĭ
			{
				int a = sudoku_arr[i][j]; // int a �� arr[i][j] 
				for(int k = 0; k < 9; k++)
					 can_save_arr[i][k][a-1] = 0; // can_arr[x��ǥ][y��ǥ][a-1] ���� ���ش�. 0���� �����.
			}
		}
	}
}



void sudoku::col_det() // �� �˻�
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[j][i] != 0) //����!!! arr[��][��] �� �ƴ� arr[��][��]�̴�. (�� �˻��̱� ������ �ؿ��� �Ʒ��� �� �˻� �� �� ���� �Ѿ��.)
							   // arr[][] �� ��ĭ�� �ƴ϶��
			{
				int a = sudoku_arr[j][i]; 
				for(int k = 0; k < 9; k++) 
					can_save_arr[k][i][a-1] = 0; // can_arr[x��ǥ][y��ǥ][a-1] ���� ���ش�. 0���� �����.
			}
		}
	}
}

void sudoku::box_det() // 3x3 ��� �˻� �κ�
{
	for(int a = 1; a != 7; a += 3) // a,b �� 3x3 ����� ��� �κ� for ���� ������ 2�� ���ذ���.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j �� ���� �� 3x3 ����� ���� ����.
			{
				for(int j = -1; j < 2; j++)
				{
					if(sudoku_arr[a+i][b+j] != 0) 
					{	
						for(int x = -1; x < 2; x++)
						{
							for(int y = -1; y < 2; y++)
							{
								int val = sudoku_arr[a+i][b+j];
								can_save_arr[a+x][b+y][val-1] = 0;
							}
						}
					}
				}
			}
		}
	}
}

void sudoku::sudoku_detect()            // �� �˻� �� �� �� �ִ��� Ȯ��, �ڽ� �˻��� �� �� �ִ��� Ȯ��, �� �˻� �� �� �� �ִ��� Ȯ��
{
	for(int i = 0; i < 100000; i++)
	{
		row_det();
		detect();
		box_det();
		detect();
		col_det();
		detect();
	}
}

void sudoku::user_sudoku_solve() // ����ڰ� ���� Ǫ�� �Լ�
{
	int choose_second_menu_num = 1;
	int swt = 1;
	while(true)                                   // ������ ����
	{
		switch(choose_second_menu_num)
		{
		case 1:
			system("cls");
			printf("\n\n\t->quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 2:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t->quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 3:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t->quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 4:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t->quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 5:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t->quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 6:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t->quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 7:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t->quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 8:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t->quest8");
			printf("\n\n\t  quest9");
			break;
		case 9:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t->quest9");
			break;
		}
		
		char ch = _getch();                       // ����Ű �����ϴ� ����

		if(ch == DownKey)
		{
			if(choose_second_menu_num >= 9)
				choose_second_menu_num =  9;
			else
				choose_second_menu_num += 1;
		}
		else if(ch == UpKey)
		{
			if(choose_second_menu_num == 1)
				choose_second_menu_num = 1;
			else
				choose_second_menu_num -= 1;
		}
		else if(ch == ' ')
		{
			system("cls");
			break;
		}
		else
		{
			choose_second_menu_num = choose_second_menu_num;
		}
	}

	char C_sudoku_num[3] = "";

	C_sudoku_num[0] = choose_second_menu_num + 48; /* 48�� '0'�� �ƽ�Ű�ڵ�*/ 

	char name[12] = "quest";
	strcat_s(name,C_sudoku_num);
	strcat_s(name,".txt");

	ifstream fin1;
	fin1.open(name);

	for(int i = 0; i < 9; i++)           // ���Ͽ� �ִ� ���� �޾ƿ���
	{
		for(int j = 0; j < 9; j++)
		{
			fin1 >> sudoku_arr[i][j];
		}
	}

	fin1.close();

	int x = 0;/*����ǥ*/
	int y = 0;/*����ǥ*/
	////////////////////////////////////////////////////////////////////
	while(true)        // make_sudoku()�� ������ ���� �������� �ʴ´�.
	{
		system("cls");
		print_sudoku(x,y,swt);
		int put_in_result;     // ������ �迭 �ڸ��� ���� ��

		
		if(x == -1 && y == -1) // ����°� ���� �� ����.
		{
			
			char name[12] = "quest";
			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");
			
			ofstream fout2;
			fout2.open(name);

			for(int i =0; i <9; i++)          // sudoku�� �� arr�� �ʱ�ȭ
			{
				for(int j = 0; j < 9; j++)
				{
					fout2 << "\t" << sudoku_arr[i][j];
				}
				fout2 << endl;
			}

			fout2.close();

			return;

		}
		if(x == -2 && y == -2)           // ������
		{
			char name[12] = "quest";
			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");
		
			ifstream fin1;
			fin1.open(name);
		
			for(int i = 0; i < 9; i++)
			{
				for(int j = 0; j < 9; j++)
				{
					fin1 >> sudoku_arr[i][j];
				}
			}

			for(int i = 0; i < 9; i++)            // can_save_arr[x��ǥ][y��ǥ][1~9���� ����]
				for(int j = 0; j < 9; j++)
					for(int k = 0; k < 9; k++)
						can_save_arr[i][j][k] = k + 1;
			x=0;
			y=0;
			continue;
		}

		cin >> put_in_result;        // ������ �迭 �ڸ��� ���� ��
		if(sudoku_arr[y][x] != 0) // �̹� ���� ������ ���
		{
			printf("\n\t���� �����Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // ������ �˻�
			sudoku_arr[y][x] = put_in_result;     // x�� ����ǥ y�� ����ǥ�̱� ����
		else
		{
			printf("\n\t���� ��ġ�Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
		}

		if(is_all_correct() == true)
		{
			win_image();
		}
	}
	//////////////////////////////////////////////////////////////////


}


void sudoku::rand_solve_sudo_arr()
{
	int choose_second_menu_num = 1;
	int swt = 0;

	while(true)                                   // ������ ����
	{
		switch(choose_second_menu_num)
		{
		case 1:
			system("cls");
			printf("\n\n\t->quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 2:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t->quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 3:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t->quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 4:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t->quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 5:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t->quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 6:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t->quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 7:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t->quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t  quest9");
			break;
		case 8:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t->quest8");
			printf("\n\n\t  quest9");
			break;
		case 9:
			system("cls");
			printf("\n\n\t  quest1");
			printf("\n\n\t  quest2");
			printf("\n\n\t  quest3");
			printf("\n\n\t  quest4");
			printf("\n\n\t  quest5");
			printf("\n\n\t  quest6");
			printf("\n\n\t  quest7");
			printf("\n\n\t  quest8");
			printf("\n\n\t->quest9");
			break;
		}
		
		char ch = _getch();                       // ����Ű �����ϴ� ����

		if(ch == DownKey)
		{
			if(choose_second_menu_num >= 9)
				choose_second_menu_num =  9;
			else
				choose_second_menu_num += 1;
		}
		else if(ch == UpKey)
		{
			if(choose_second_menu_num == 1)
				choose_second_menu_num = 1;
			else
				choose_second_menu_num -= 1;
		}
		else if(ch == ' ')
		{
			system("cls");
			break;
		}
		else
		{
			choose_second_menu_num = choose_second_menu_num;
		}
	}

	char C_sudoku_num[3] = "";

	C_sudoku_num[0] = choose_second_menu_num + 48; /* 48�� '0'�� �ƽ�Ű�ڵ�*/ 

	char name[12] = "quest";
	strcat_s(name,C_sudoku_num);
	strcat_s(name,".txt");

	ifstream fin1;
	fin1.open(name);

	for(int i = 0; i < 9; i++)           // ���Ͽ� �ִ� ���� �޾ƿ���
	{
		for(int j = 0; j < 9; j++)
		{
			fin1 >> sudoku_arr[i][j];
		}
	}

	fin1.close();

	printf("\n\n\n\tǮ�� �� ������ : \n\n");

	just_print_sudoku();
	
	printf("\n\n\n");
	sudoku_detect();

	if(is_all_correct() == true)
	{
		win_image();
	}
	YEL;
	printf("\t��� ���� Ǭ ���� ������ : \n\n\n");
	int x = 0;/*����ǥ*/
	int y = 0;/*����ǥ*/
	////////////////////////////////////////////////////////////////////
	while(true)        // make_sudoku()�� ������ ���� �������� �ʴ´�.
	{
		
		print_sudoku(x,y,swt);
		int put_in_result;     // ������ �迭 �ڸ��� ���� ��

		if(x == -1 && y == -1) // ����°� ���� �� ����.
		{
			char name[12] = "quest";
			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");
			
			ofstream fout2;
			fout2.open(name);

			for(int i =0; i <9; i++)          // sudoku�� �� arr�� �ʱ�ȭ
			{
				for(int j = 0; j < 9; j++)
				{
					fout2 << "\t" << sudoku_arr[i][j];
				}
				fout2 << endl;
			}

			fout2.close();

			return;

		}
		if(x == -2 && y == -2)           // ������
		{
			return;
		}

		cin >> put_in_result;        // ������ �迭 �ڸ��� ���� ��
		system("cls");
		if(sudoku_arr[y][x] != 0) // �̹� ���� ������ ���
		{
			printf("\n\t���� �����Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // ������ �˻�
			sudoku_arr[y][x] = put_in_result;     // x�� ����ǥ y�� ����ǥ�̱� ����
		else
		{
			printf("\n\t���� ��ġ�Ƿ� �� �� �����ϴ�.\n");
			Sleep(2000);
		}
	}
	//////////////////////////////////////////////////////////////////

}

bool sudoku::is_all_correct()
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[i][j] == 0)
				return false;
		}
	}
	
	int total = 0;

	for(int a = 1; a != 7; a += 3) // a,b �� 3x3 ����� ��� �κ� for ���� ������ 3�� ���ذ���.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j �� ���� �� 3x3 ����� ���� ����.
			{
				for(int j = -1; j < 2; j++)
				{
					total += sudoku_arr[a+i][b+j];
				}
			}

			if(total != 45)
				return false;

			total = 0;
		}
	}

	total = 0;

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			total += sudoku_arr[i][j];
		}
		if(total != 45)
			return false;

		total = 0;
	}

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			total += sudoku_arr[j][i];
		}
		if(total != 45)
			return false;

		total = 0;
	}

	return true;
}

void sudoku::win_image()
{
	for(int i = 0; i < 20; i++)
	{
		int div_i = i%2;
		switch(div_i)
		{
		case 0:
			color(i);
			printf("                  ����\n");
			printf("                ������\n");
			printf("            ��  ������  \n");
			printf("            ��  ������  \n");
			printf("            ��    ����    \n");
			printf("              ��    ��    \n");
			printf("                ������\n");
			printf("                    ��    ��\n");
			printf("                    ��      ��\n");
			printf("                    ��      ��\n");
			printf("                    ��      ��\n");
			printf("                  ��  ��      \n");
			printf("                ��      ��      \n");
			printf("               ��        ��      \n");
			printf("               ��        ��      \n");
			printf("               ��        ��      \n");
			printf("              ��          ��      \n");
			Sleep(60);
			system("cls");

		case 1:
			color(i);
			printf("                  ����\n");
			printf("                ������\n");
			printf("                ������  ��\n");
			printf("                ������  ��\n");
			printf("                  ����    ��\n");
			printf("                    ��    ��\n");
			printf("                ������\n");
			printf("              ��    ��    \n");
			printf("            ��      ��      \n");
			printf("            ��      ��      \n");
			printf("            ��      ��      \n");
			printf("                  ��  ��      \n");
			printf("                ��      ��      \n");
			printf("               ��        ��      \n");
			printf("               ��        ��      \n");
			printf("               ��        ��      \n");
			printf("              ��          ��      \n");
			Sleep(60);
			system("cls");

		}
	}


	Sleep(2000);
}

void sudoku::color(int i)
{
	int num = i%8;

	if(num == 0)
	{
		RED;
	}
	else if(num == 1)
	{
		BLUE;
	}
	else if(num == 2)
	{
		HIGH;
	}
	else if(num == 3)
	{
		WHITE;
	}
	else if(num == 4)
	{
		SKY;
	}
	else if(num == 5)
	{
		YEL;
	}
	else if(num == 6)
	{
		HIG;
	}
	else if(num == 7)
	{
		VIO;
	}
}