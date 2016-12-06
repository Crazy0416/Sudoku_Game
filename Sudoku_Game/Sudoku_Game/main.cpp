#include "sudoku.h" 


void gotoxy(int x, int y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void visual_sudoku_game();

void first_menu(int &choose_menu_num)
{
	///////////////////////////////////////////////////////////
	SKY;
	gotoxy(8,2);
	printf("t");
	for(int i = 0; i < 5; i++)             // '��' �κ�  (�ﰢ���׸���)
	{
		for(int j = 0; j < 10; j++)
		{
			if(5-i == j || 5+i == j)
				printf("��");
			else
				printf(" ");
		}
		Sleep(100);
		gotoxy(8,2+i);
	}
	printf("\n");
	printf("       ");
	for(int i = 0; i < 8; i++)
	{
		printf("��");
		Sleep(50);
	}
	/////////////////////////////////////////////////////////// '��' �κ�
	WHITE;
	gotoxy(27,2);
	for(int i = 0; i < 5; i++)
	{
		Sleep(13);
		printf("��");
	}
	
	for(int i = 0; i < 3; i++)
	{
		gotoxy(27,2+i);
		Sleep(13);
		printf("��");
	}

	gotoxy(27,5);
	for(int i = 0; i < 5; i++)
	{
		Sleep(13);
		printf("��");
	}

	gotoxy(31,6);
	printf("��");


	gotoxy(25,7);
	for(int i = 0; i < 7; i++)
	{
		Sleep(13);
		printf("��");
	}
	///////////////////////////////////////////////////////////// '��' �κ�

	VIO;

	gotoxy(43,0);
	for(int i = 0; i < 10; i++)
	{
		Sleep(13);
		printf("��");
	}

	for(int i = 0; i< 5; i++)
	{
		Sleep(13);
		gotoxy(61,1+i);
		printf("��");
	}

	for(int i = 0; i< 8; i++)
	{
		Sleep(13);
		gotoxy(45+2*i,3);
		printf("��");
	}
	
	for(int i = 0; i < 11; i++)
	{
		Sleep(13);
		gotoxy(43+2*i,7);
		printf("��");
	}

	for(int i = 0; i< 3; i++)
	{
		Sleep(13);
		gotoxy(53,8+i);
		printf("��");
	}
	/////////////////////////////////////////////////////////// '��' �κ�
	YEL;
	gotoxy(30,15);
	for(int i = 0; i < 20; i++)
	{
		Sleep(20);
		gotoxy(40+i, 12);
		printf("����\r");
	}
	for(int i = 0; i < 10; i++)
	{
		Sleep(20);
		gotoxy(60-i, 12);
		printf("����\r");
	}
	for(int i = 0; i < 10; i++)
	{
		Sleep(20);
		gotoxy(50+i, 12);
		printf("����\r");
	}

	printf("\n\n\n\n\n");

	while(true)
	{
		gotoxy(10,14);
		switch(choose_menu_num)
		{
		case 1:
			printf("\n\n\n\n\t-> �� ��  ��  ��      ��  ��  ��");
			printf("\n\t   �� �� �� ��    �� ��    Ǯ ��");
			printf("\n\t   �� ��  ��  ��          Ǯ  ��\n");
			gotoxy(10,14);
			break;
		case 2:
			printf("\n\n\n\n\t   �� ��  ��  ��      ��  ��  ��");
			printf("\n\t-> �� �� �� ��    �� ��    Ǯ ��");
			printf("\n\t   �� ��  ��  ��          Ǯ  ��\n");
			gotoxy(10,14);
			break;
		case 3:
			printf("\n\n\n\n\t   �� ��  ��  ��      ��  ��  ��");
			printf("\n\t   �� �� �� ��    �� ��    Ǯ ��");
			printf("\n\t-> �� ��  ��  ��          Ǯ  ��\n");
			gotoxy(10,14);
			break;
		}

		char ch = _getch();                       // ����Ű �����ϴ� ����

 		if(ch == DownKey)
		{
			if(choose_menu_num == 3)
				choose_menu_num = 3;
			else
				choose_menu_num += 1;
		}
		else if(ch == UpKey)
		{
			if(choose_menu_num == 1)
				choose_menu_num = 1;
			else
				choose_menu_num -= 1;
		}
		else if(ch == ' ')
		{
			system("cls");
			return;
		}
		else
		{
			choose_menu_num = choose_menu_num;
		}

	}

}



int main()
{
	int choose_menu_num = 1;                  // �� ó�� �޴� 1�� 2�� 3�� �� �����ϴ� ����
		

	while(true)
	{
		first_menu(choose_menu_num);
		sudoku A;

		switch(choose_menu_num)
		{
		case 1:
			A.make_sudoku();
			A.~sudoku();
			system("cls");
			break;
		case 2:
			system("cls");
			A.rand_solve_sudo_arr();
			A.~sudoku();
			break;
		case 3:
			A.user_sudoku_solve();
			A.~sudoku();
			break;
		}
	}


}

void visual_sudoku_game()                   // "������ ����"�̶�� �ܼ�â�� �׸���.
{
	//////////////////////////////////////////////////// "������ ����"
	VIO;
	system("cls");
	printf("\t\t\t\t\t   �����������\n");
	printf("\t\t\t\t\t\t\t     ��\n");
	SKY;
	printf("            �� ��");
	WHITE;
	printf("          ������");
	VIO;
	printf("                        ��\n");
	SKY;
	printf("           ��   ��");
	WHITE;
	printf("         ��");
	VIO;
	printf("                ����������\n");
	SKY;
	printf("          ��     ��");
	WHITE;
	printf("        ��");
	VIO;
	printf("                                ��\n");
	SKY;
	printf("         ��       ��");
	WHITE;
	printf("       ������");
	VIO;
	printf("                        ��\n");
	WHITE;
	printf("\t\t\t       ��\n");
	SKY;
	printf("       ���������");
	WHITE;
	printf("  ��������");
	VIO;
	printf("    ������������\n");
	printf("\t\t\t\t\t\t     ��\n");
	printf("\t\t\t\t\t\t     ��\n");
	printf("\t\t\t\t\t\t     ��\n");
	YEL;
	gotoxy(60, 12);
	printf("����");
	//////////////////////////////////////////////////// "������ ����"
}

