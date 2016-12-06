#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define col GetStdHandle(STD_OUTPUT_HANDLE) //  �ܼ�â�� �ڵ����� �ޱ� 

///////////////////////////////////////////////////////////////////////////////////////////////// ��������  
#define RED SetConsoleTextAttribute( col,0x000c ); //������ 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008); //�Ķ��� 
#define HIGH SetConsoleTextAttribute( col,0x00a); // ����
#define WHITE SetConsoleTextAttribute( col,0x000f); // ���
#define SKY SetConsoleTextAttribute( col, 0x000b); //�ϴû�
#define YEL SetConsoleTextAttribute( col, 0x000e); //�����
#define HIG SetConsoleTextAttribute( col, 0x000d); //����
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c); //���� 
///////////////////////////////////////////////////////////////////////////////////////////////// Ű���� ����Ű
#define DownKey 80
#define RightKey 77
#define LeftKey 75
#define UpKey 72
////////////////////////////////////////////


class sudoku
{
private:
	int sudoku_arr[9][9];                    // ������
	int can_save_arr[9][9][9];               // ������ �� ������ � ���ڰ� �� �� �ִ��� �����ϴ� �迭 can_save_arr[��][��][1~9���� �� �� �ִ� ��]
public:
	sudoku(void);                      // �迭�� can_save_arr[][][1~9] = 1~9�� �ʱ�ȭ
	~sudoku(void);                     // �����ϸ� �ʱ�ȭ
	void make_sudoku();     // ������ ����� �Լ�
	void print_sudoku(int &x, int &y, int swt);    // ������ �׸��� ���� �����̰� �� ���� ��ǥ�� �����Ѵ�.
	bool row_det(int x, int y, int num); // �� �˻�, can_save_arr�� ���� �ִٸ� ����� ������ sudoku_arr�� ������� �� �����Ƿ� false ��ȯ
	bool col_det(int x, int y, int num); // �� �˻�, can_save_arr�� ���� �ִٸ� ����� ������ sudoku_arr�� ������� �� �����Ƿ� false ��ȯ
	bool box_det(int x, int y, int num); // 3x3 ��� �˻� �κ�, can_save_arr�� ���� �ִٸ� ����� ������ sudoku_arr�� ������� �� �����Ƿ� false ��ȯ
	void user_sudoku_solve(); // ����ڰ� ���� Ǫ�� �Լ�
	void rand_solve_sudo_arr();            // ������ Ǯ���ִ� �Լ�
	void sudoku_detect();          // ������ Ǯ����
	void detect();                   // can_save_arr�� ���� �Ѱ� �ۿ� ���ٸ� sudoku_arr�� ���� �����Ѵ�.
	void row_det();                  // bool row_det�ʹ� �ٸ��� �˻��ؼ� can_save_arr�� �����.
	void col_det();                  // ���� ����
	void box_det();                  // ���� ����
	void just_print_sudoku();        // ���� �������� �׸��� �����ش�
	bool is_all_correct();           // ĭ�� �� ä������ �� �´ٸ� true
	void win_image();                // �� Ǯ���� �� �̹���
	void color(int i);                    // ����
};

