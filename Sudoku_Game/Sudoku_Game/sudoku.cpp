#include "sudoku.h"

sudoku::sudoku(void)
{
	for(int i =0; i <9; i++)          // sudoku에 들어갈 arr를 0으로 초기화
		for(int j = 0; j < 9; j++)
		{
			sudoku_arr[i][j] = 0;
		}

	for(int i = 0; i < 9; i++)            // can_save_arr[x좌표][y좌표][1~9까지 저장]
		for(int j = 0; j < 9; j++)
			for(int k = 0; k < 9; k++)
				can_save_arr[i][j][k] = k + 1;
}

sudoku::~sudoku(void) // 그냥 초기화void user_sudoku_solve(); // 사용자가 직접 푸는 함수
{	
	for(int i =0; i <9; i++)          // sudoku에 들어갈 arr를 0으로 초기화
		for(int j = 0; j < 9; j++)
		{
			sudoku_arr[i][j] = 0;
		}

	for(int i = 0; i < 9; i++)            // can_save_arr[x좌표][y좌표][1~9까지 저장]
		for(int j = 0; j < 9; j++)
			for(int k = 0; k < 9; k++)
				can_save_arr[i][j][k] = k + 1;
}

void sudoku::just_print_sudoku()                  // 단지 스도쿠 그림만 보여준다.
{
	SKY;
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				if(j == 3 || j == 6 || j ==9)
				{
					YEL;
					printf("       ┃");
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
				printf("\t━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
				printf("\n");
			}
			else
				printf("\n");
		}
}

void sudoku::make_sudoku()    // 스도쿠 만듬
{
	int x = 0;/*열좌표*/
	int y = 0;/*행좌표*/
	int swt = 1;                      // 스위치 print_sudoku에서 사용
	while(true)
	{

		print_sudoku(x,y,swt);          // 스도쿠를 그려준 후에 방향키와 스페이스바 'e' 'l' 키를 사용한다.
		int put_in_result;     // 스도쿠 배열 자리에 넣을 값

		if(x == -1 && y == -1) // 만드는걸 저장 후 종료.
		{	
			char C_sudoku_num[2]= "0";
			char name[12] = "quest";
			while (true)
			{
				system("cls");
				cout << "저장할 곳의 위치를 숫자로 적으세요.(1~9) : ";
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
					cout << "잘못 입력하셨습니다.";
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

		if(x == -2 && y == -2)             // 다시 초기화. 잘못 만들었을때 다시 초기화 하는것
		{


			for(int i =0; i <9; i++)          // sudoku에 들어갈 arr를 0으로 초기화
				for(int j = 0; j < 9; j++)
				{
					sudoku_arr[i][j] = 0;
				}

			for(int i = 0; i < 9; i++)            // can_save_arr[x좌표][y좌표][1~9까지 저장]
				for(int j = 0; j < 9; j++)
					for(int k = 0; k < 9; k++)
						can_save_arr[i][j][k] = k + 1;
			x=0;
			y=0;

			
			continue;
		}

		cin >> put_in_result;        // 스도쿠 배열 자리에 넣을 값
		system("cls");
		if(sudoku_arr[y][x] != 0) // 이미 값이 존재할 경우
		{
			printf("\n\t값이 있으므로 들어갈 수 없습니다.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // 스도쿠 검사
			sudoku_arr[y][x] = put_in_result;     // x는 열좌표 y는 행좌표이기 때문
		else
		{
			printf("\n\t값이 겹치므로 들어갈 수 없습니다.\n");
			Sleep(2000);
		}
	}


}

void sudoku::print_sudoku(int &x/*열좌표*/, int &y/*행좌표*/, int swt /*이 변수는 print_sudoku가 다른함수에서 살짝 다른 용도로 쓰이므로 구분하기 위한 변수*/)
{


	while(true)      // 스도쿠 그려줌
	{
		YEL;
		if(swt == 1)
			printf("\t스페이스 바 누른 후에 넣을 값을 입력하세요. 'e'를 누르면 저장, 'l'을 누르면 로드 됩니다~~\n\n\n");
		else
			printf("\t스페이스 바 누른 후에 넣을 값을 입력하세요. 'e'를 누르면 저장, 'l'을 누르면 메인으로 나가게 됩니다~~\n\n\n");
		SKY;
		for(int i = 0; i < 9; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				if(j == 3 || j == 6 || j ==9)
				{
					YEL;
					printf("       ┃");
				}
				if(y == i && x == j)               // i는 열 좌표 j는 행 좌표이다.
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
				printf("\t━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
				printf("\n");
			}
			else
				printf("\n");
		}

		char ch;
		ch = _getch();// 방향키 입력 받음

		if(ch == DownKey)  // 방향키 아래 입력
		{
			if(y == 8)
				y = 8;
			else
				y++;
		}
		else if(ch == UpKey)  // 방향키 위 입력
		{
			if(y == 0)
				y = 0;
			else
				y--;
		}
		else if(ch == RightKey)  // 방향키 오른쪽 입력
		{
			if(x == 8)
				x = 8;
			else
				x++;
		}
		else if(ch == LeftKey)  // 방향키 왼쪽 입력
		{
			if(x == 0)
				x = 0;
			else
				x--;
		}
		else if(ch == ' '/*스페이스바 입력했을때*/)
		{
			printf("\n\n\t 넣을 값 입력 : ");
			return; // 함수 종료
		}
		else if(ch == 101/* 'e' */)  /*만드는걸 종료하고 싶을때*/
		{
			x = -1;
			y = -1;
			system("cls");
			return;
		}
		else if(ch == 108 /* 'l'*/) /* 다 지우고 로드 하고 싶을때 */
		{
			x = -2;
			y = -2;
			system("cls");
			return;
		}
		else    // 디폴트 값일때
		{
			x = x;
			y = y;
		}
		
		system("cls");
		
	}
}

bool sudoku::row_det(int x, int y, int num) // 행 검사
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[i][j] != 0) // 만약 sudoku_arr[i][j]가 빈칸이 아니라면
			{
				int a = sudoku_arr[i][j]; // int a 는 arr[i][j] 
				for(int k = 0; k < 9; k++)
					 can_save_arr[i][k][a-1] = 0; // can_arr[x좌표][y좌표][a-1] 값을 없앤다. 0으로 만든다.
			}
		}
	}

	if(can_save_arr[y][x][num-1] == 0)             // 넣을수 있다면 true 아니면 false
		return false;
	else
		return true;
}

bool sudoku::col_det(int x, int y, int num) // 열 검사
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[j][i] != 0) //조심!!! arr[행][열] 이 아닌 arr[열][행]이다. (열 검사이기 때문에 밑에서 아래로 쭉 검사 후 옆 열로 넘어간다.)
							   // arr[][] 이 빈칸이 아니라면
			{
				int a = sudoku_arr[j][i]; 
				for(int k = 0; k < 9; k++) 
					can_save_arr[k][i][a-1] = 0; // can_arr[x좌표][y좌표][a-1] 값을 없앤다. 0으로 만든다.
			}
		}
	}
	
	if(can_save_arr[y][x][num-1] == 0)
		return false;
	else
		return true;
}

bool sudoku::box_det(int x, int y, int num) // 3x3 행렬 검사 부분, can_save_arr에 값이 있다면 지우고 없으면 sudoku_arr에 집어넣을 수 없으므로 false 반환
{
	for(int a = 1; a != 7; a += 3) // a,b 는 3x3 행렬의 가운데 부분 for 문이 끝나고 3씩 더해간다.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j 가 돌면 서 3x3 행렬을 전부 돈다.
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
	int total = 0; // total 은 만약 can_arr[][][] 값이 하나 밖에 없는 경우를 찾기 위한 변수
	
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			for(int k = 0; k < 9; k++)
			{
				if(can_save_arr[i][j][k] == 0) // can_arr[][][] 가 0이라면 
				{
					total++; // total 값을 하나 올리고,
				}
				if(total == 8 && sudoku_arr[i][j] == 0) // total 값이 8, 그리고 arr[][]이 빈칸, 혹은 0이라면
				{
					for(int m = 0; m < 9; m++)
					{
						int a;
						if(can_save_arr[i][j][m] != 0)
						{
							a = can_save_arr[i][j][m];
							sudoku_arr[i][j] = a; // 그때 arr[][]에 값을 넣어 답을 입력한다.
						}
					}
				}
			}
		total = 0; // total 값 초기화
		}
	}
	
}
void sudoku::row_det() // 행 검사
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[i][j] != 0) // 만약 arr[i][j]가 아니라면 즉, 빈칸
			{
				int a = sudoku_arr[i][j]; // int a 는 arr[i][j] 
				for(int k = 0; k < 9; k++)
					 can_save_arr[i][k][a-1] = 0; // can_arr[x좌표][y좌표][a-1] 값을 없앤다. 0으로 만든다.
			}
		}
	}
}



void sudoku::col_det() // 열 검사
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(sudoku_arr[j][i] != 0) //조심!!! arr[행][열] 이 아닌 arr[열][행]이다. (열 검사이기 때문에 밑에서 아래로 쭉 검사 후 옆 열로 넘어간다.)
							   // arr[][] 이 빈칸이 아니라면
			{
				int a = sudoku_arr[j][i]; 
				for(int k = 0; k < 9; k++) 
					can_save_arr[k][i][a-1] = 0; // can_arr[x좌표][y좌표][a-1] 값을 없앤다. 0으로 만든다.
			}
		}
	}
}

void sudoku::box_det() // 3x3 행렬 검사 부분
{
	for(int a = 1; a != 7; a += 3) // a,b 는 3x3 행렬의 가운데 부분 for 문이 끝나고 2씩 더해간다.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j 가 돌면 서 3x3 행렬을 전부 돈다.
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

void sudoku::sudoku_detect()            // 행 검사 후 들어갈 수 있는지 확인, 박스 검사후 들어갈 수 있는지 확인, 열 검사 후 들어갈 수 있는지 확인
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

void sudoku::user_sudoku_solve() // 사용자가 직접 푸는 함수
{
	int choose_second_menu_num = 1;
	int swt = 1;
	while(true)                                   // 스도쿠 고르기
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
		
		char ch = _getch();                       // 방향키 저장하는 변수

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

	C_sudoku_num[0] = choose_second_menu_num + 48; /* 48은 '0'의 아스키코드*/ 

	char name[12] = "quest";
	strcat_s(name,C_sudoku_num);
	strcat_s(name,".txt");

	ifstream fin1;
	fin1.open(name);

	for(int i = 0; i < 9; i++)           // 파일에 있는 값들 받아오기
	{
		for(int j = 0; j < 9; j++)
		{
			fin1 >> sudoku_arr[i][j];
		}
	}

	fin1.close();

	int x = 0;/*열좌표*/
	int y = 0;/*행좌표*/
	////////////////////////////////////////////////////////////////////
	while(true)        // make_sudoku()와 같지만 새로 저장하지 않는다.
	{
		system("cls");
		print_sudoku(x,y,swt);
		int put_in_result;     // 스도쿠 배열 자리에 넣을 값

		
		if(x == -1 && y == -1) // 만드는걸 저장 후 종료.
		{
			
			char name[12] = "quest";
			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");
			
			ofstream fout2;
			fout2.open(name);

			for(int i =0; i <9; i++)          // sudoku에 들어갈 arr를 초기화
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
		if(x == -2 && y == -2)           // 나가기
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

			for(int i = 0; i < 9; i++)            // can_save_arr[x좌표][y좌표][1~9까지 저장]
				for(int j = 0; j < 9; j++)
					for(int k = 0; k < 9; k++)
						can_save_arr[i][j][k] = k + 1;
			x=0;
			y=0;
			continue;
		}

		cin >> put_in_result;        // 스도쿠 배열 자리에 넣을 값
		if(sudoku_arr[y][x] != 0) // 이미 값이 존재할 경우
		{
			printf("\n\t값이 있으므로 들어갈 수 없습니다.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // 스도쿠 검사
			sudoku_arr[y][x] = put_in_result;     // x는 열좌표 y는 행좌표이기 때문
		else
		{
			printf("\n\t값이 겹치므로 들어갈 수 없습니다.\n");
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

	while(true)                                   // 스도쿠 고르기
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
		
		char ch = _getch();                       // 방향키 저장하는 변수

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

	C_sudoku_num[0] = choose_second_menu_num + 48; /* 48은 '0'의 아스키코드*/ 

	char name[12] = "quest";
	strcat_s(name,C_sudoku_num);
	strcat_s(name,".txt");

	ifstream fin1;
	fin1.open(name);

	for(int i = 0; i < 9; i++)           // 파일에 있는 값들 받아오기
	{
		for(int j = 0; j < 9; j++)
		{
			fin1 >> sudoku_arr[i][j];
		}
	}

	fin1.close();

	printf("\n\n\n\t풀기 전 스도쿠 : \n\n");

	just_print_sudoku();
	
	printf("\n\n\n");
	sudoku_detect();

	if(is_all_correct() == true)
	{
		win_image();
	}
	YEL;
	printf("\t어느 정도 푼 후의 스도쿠 : \n\n\n");
	int x = 0;/*열좌표*/
	int y = 0;/*행좌표*/
	////////////////////////////////////////////////////////////////////
	while(true)        // make_sudoku()와 같지만 새로 저장하지 않는다.
	{
		
		print_sudoku(x,y,swt);
		int put_in_result;     // 스도쿠 배열 자리에 넣을 값

		if(x == -1 && y == -1) // 만드는걸 저장 후 종료.
		{
			char name[12] = "quest";
			strcat_s(name,C_sudoku_num);
			strcat_s(name,".txt");
			
			ofstream fout2;
			fout2.open(name);

			for(int i =0; i <9; i++)          // sudoku에 들어갈 arr를 초기화
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
		if(x == -2 && y == -2)           // 나가기
		{
			return;
		}

		cin >> put_in_result;        // 스도쿠 배열 자리에 넣을 값
		system("cls");
		if(sudoku_arr[y][x] != 0) // 이미 값이 존재할 경우
		{
			printf("\n\t값이 있으므로 들어갈 수 없습니다.\n");
			Sleep(2000);
			continue;
		}
		if(row_det(x,y,put_in_result) && col_det(x,y,put_in_result) && box_det(x,y,put_in_result))  // 스도쿠 검사
			sudoku_arr[y][x] = put_in_result;     // x는 열좌표 y는 행좌표이기 때문
		else
		{
			printf("\n\t값이 겹치므로 들어갈 수 없습니다.\n");
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

	for(int a = 1; a != 7; a += 3) // a,b 는 3x3 행렬의 가운데 부분 for 문이 끝나고 3씩 더해간다.
	{
		for(int b = 1; b != 7; b += 3)
		{
			for(int i = -1; i < 2; i++) // i j 가 돌면 서 3x3 행렬을 전부 돈다.
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
			printf("                  ■■■\n");
			printf("                ■■■■■\n");
			printf("            ■  ■■■■■  \n");
			printf("            ■  ■■■■■  \n");
			printf("            ■    ■■■    \n");
			printf("              ■    ■    \n");
			printf("                ■■■■■\n");
			printf("                    ■    ■\n");
			printf("                    ■      ■\n");
			printf("                    ■      ■\n");
			printf("                    ■      ■\n");
			printf("                  ■  ■      \n");
			printf("                ■      ■      \n");
			printf("               ■        ■      \n");
			printf("               ■        ■      \n");
			printf("               ■        ■      \n");
			printf("              ■          ■      \n");
			Sleep(60);
			system("cls");

		case 1:
			color(i);
			printf("                  ■■■\n");
			printf("                ■■■■■\n");
			printf("                ■■■■■  ■\n");
			printf("                ■■■■■  ■\n");
			printf("                  ■■■    ■\n");
			printf("                    ■    ■\n");
			printf("                ■■■■■\n");
			printf("              ■    ■    \n");
			printf("            ■      ■      \n");
			printf("            ■      ■      \n");
			printf("            ■      ■      \n");
			printf("                  ■  ■      \n");
			printf("                ■      ■      \n");
			printf("               ■        ■      \n");
			printf("               ■        ■      \n");
			printf("               ■        ■      \n");
			printf("              ■          ■      \n");
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