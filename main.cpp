// ****** team15_main.cpp ******
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "cPlayList.h"

using namespace std;

int main() {

	cPlayList a15;

	a15.playList();


	return 0;
}

/*
***** 특이케이스 1번 일정 편집&삭제 *****

=> 삭제할 일정 이름을 입력하세요 : 축구

1. 축구 ( 단발 2022 06 22 )
2. 축구 ( 반복 2022 08 20 , 15 00 00 )
3. 축구 ( 기간제 2022 10 08 ~ 2022 10 10 )

삭제할 번호를 선택하세요 :

*/




/*
<문제점>

1. 년수가 긴 일정의 경우, 따로따로 isLeafYear를 구하는 걸 만들어야 하나?


*/