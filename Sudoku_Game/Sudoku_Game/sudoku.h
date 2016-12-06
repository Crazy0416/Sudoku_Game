#pragma once
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define col GetStdHandle(STD_OUTPUT_HANDLE) //  콘솔창의 핸들정보 받기 

///////////////////////////////////////////////////////////////////////////////////////////////// 색깔정의  
#define RED SetConsoleTextAttribute( col,0x000c ); //빨간색 
#define BLUE SetConsoleTextAttribute( col,0x0001 | 0x0008); //파란색 
#define HIGH SetConsoleTextAttribute( col,0x00a); // 연두
#define WHITE SetConsoleTextAttribute( col,0x000f); // 흰색
#define SKY SetConsoleTextAttribute( col, 0x000b); //하늘색
#define YEL SetConsoleTextAttribute( col, 0x000e); //노란색
#define HIG SetConsoleTextAttribute( col, 0x000d); //형광
#define VIO SetConsoleTextAttribute( col,0x0001 | 0x0008 |0x000c); //보라 
///////////////////////////////////////////////////////////////////////////////////////////////// 키보드 방향키
#define DownKey 80
#define RightKey 77
#define LeftKey 75
#define UpKey 72
////////////////////////////////////////////


class sudoku
{
private:
	int sudoku_arr[9][9];                    // 스도쿠
	int can_save_arr[9][9][9];               // 스도쿠 빈 공간에 어떤 숫자가 들어갈 수 있는지 저장하는 배열 can_save_arr[행][열][1~9까지 들어갈 수 있는 수]
public:
	sudoku(void);                      // 배열과 can_save_arr[][][1~9] = 1~9로 초기화
	~sudoku(void);                     // 종료하면 초기화
	void make_sudoku();     // 스도쿠 만드는 함수
	void print_sudoku(int &x, int &y, int swt);    // 스도쿠 그리고 내가 움직이고 난 후의 좌표를 저장한다.
	bool row_det(int x, int y, int num); // 행 검사, can_save_arr에 값이 있다면 지우고 없으면 sudoku_arr에 집어넣을 수 없으므로 false 반환
	bool col_det(int x, int y, int num); // 열 검사, can_save_arr에 값이 있다면 지우고 없으면 sudoku_arr에 집어넣을 수 없으므로 false 반환
	bool box_det(int x, int y, int num); // 3x3 행렬 검사 부분, can_save_arr에 값이 있다면 지우고 없으면 sudoku_arr에 집어넣을 수 없으므로 false 반환
	void user_sudoku_solve(); // 사용자가 직접 푸는 함수
	void rand_solve_sudo_arr();            // 스도쿠 풀어주는 함수
	void sudoku_detect();          // 스도쿠 풀어줌
	void detect();                   // can_save_arr에 값이 한개 밖에 없다면 sudoku_arr에 값을 저장한다.
	void row_det();                  // bool row_det와는 다르게 검사해서 can_save_arr만 지운다.
	void col_det();                  // 위와 같다
	void box_det();                  // 위와 같다
	void just_print_sudoku();        // 단지 스도쿠의 그림만 보여준다
	bool is_all_correct();           // 칸이 다 채워지고 다 맞다면 true
	void win_image();                // 다 풀었을 때 이미지
	void color(int i);                    // 색깔
};

