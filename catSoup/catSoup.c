#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_POS (ROOM_WIDTH - 2)

//수프: soup, 관계도: rel, cp: cp_point, 기분: cat_feeling
int soup = 0, rel = 2;
int cp = 0;
int feeling = 3;
int prev_feeling;

// 방 그리기  
//cat_position: 고양이 위치, prev_position: 이전 위치
void drawRoom(int cat_position, int prev_position) {
	printf("##########\n");
	printf("#H      B#\n");
	printf("#");
	for (int i = 1; i < ROOM_WIDTH - 1; i++) {
		if (i == cat_position) { printf("C"); }
		else if (i == prev_position) { printf("."); }
		else { printf(" "); }
	}
	printf("#");
	printf("\n##########\n\n");
}


int main(void) {
	//인트로
	printf("〓〓〓 야옹이와 수프 〓〓〓 \n\n");
	printf("(^. .^  )/ \n");
	printf("▶ 야옹이의 이름은 쫀떡 입니다.\n\n\n");

	int cat_position = HME_POS; //초기 위치
	int prev_position = cat_position - 1; // 이전 위치

	while (1) {
		//상태 출력
		printf("====================현재 상태 ====================\n");
		printf("현재까지 만든 수프: %d개\n", soup);
		printf("집사와의 관계 (0~4): %d\n", rel);
		switch (rel) {
		case 0: printf("→ 곁에 오는 것조차 싫어합니다.\n"); break;
		case 1: printf("→ 간식 자판기 취급입니다.\n"); break;
		case 2: printf("→ 그럭저럭 쓸 만한 집사입니다.\n"); break;
		case 3: printf("→ 훌륭한 집사로 인정 받고 있습니다.\n"); break;
		case 4: printf("→ 집사 껌딱지 입니다.\n"); break;
		}
		printf("==================================================\n\n");

		//이동
		printf("▶ 쫀떡 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n");
		printf("  주사위 눈이 \'%d\' 이상이면 냄비 쪽으로 이동합니다.\n", 6 - rel);
		printf("  주사위가 굴러갑니다. 또르르륵...\n");
		int position;
		for (int i = 0; i < 1; i++) {
			int r = rand() % 6 + 1;
			printf("  %d이(가) 나왔습니다!\n", r);
			if ((r >= 6 - rel) && (cat_position < BWL_POS)) {
				prev_position = cat_position;
				position = cat_position++;
				printf("  냄비 쪽으로 이동합니다.\n\n");
			}
			else if ((r < 6 - rel) && (cat_position > HME_POS)) {
				prev_position = cat_position;
				position = cat_position--;
				printf("  집 쪽으로 이동합니다.\n\n");
			}
		}

		//수프 제작
		switch (cat_position) {
		case BWL_POS:
			for (int i = 0; i < 1; i++) {
				int soup_r = rand() % 2;
				if (soup_r == 0) {
					printf("▶ 쫀떡이가 감자 스프를 만들었습니다!\n");
				}
				else if (soup_r == 1) {
					printf("▶ 쫀떡이가 양송이 스프를 만들었습니다!\n");
				}
				else {
					printf("▶ 쫀떡이가 브로콜리 스프를 만들었습니다!\n");
				}
			}
			soup++;
			printf("  현재까지 만든 스프: %d\n\n", soup);
			break;
		case HME_POS:
			printf("▶ 쫀떡은 자신의 집에서 편안함을 느낍니다.\n\n");
			break;
		}

		//방
		drawRoom(cat_position, prev_position);

		//상호작용
		int interaction;
		printf("▶ 어떤 상호작용을 하시겠습니까?\n");
		printf("  0. 아무것도 하지 않음  1. 긁어 주기\n");
		while (1) {
			printf("▷ ");
			scanf_s("%d", &interaction);
			if (interaction == 0) {
				printf("\n▶ 아무것도 하지 않았습니다.\n");
				printf("  4/6확률로 친밀도가 떨어집니다.\n");
				printf("  주사위가 굴러갑니다. 또르르륵...\n");
				for (int i = 0; i < 1; i++) {
					int r = rand() % 6 + 1;
					printf("  %d이(가) 나왔습니다!\n", r);
					if (r <= 4 && rel == 0) {
						printf("  친밀도가 떨어집니다.\n");
						printf("  현재 친밀도: %d\n\n", rel);
					}
					else if (r <= 4 && rel != 0) {
						rel -= 1;
						printf("  친밀도가 떨어집니다.\n");
						printf("  현재 친밀도: %d\n\n", rel);
					}
					else if (r > 4) {
						printf("  다행히 친밀도가 떨어지지 않았습니다.\n");
						printf("  현재 친밀도: %d\n", rel);
					}
					break;
				}
				break;
			}
			if (interaction == 1) {
				printf("\n▶ 쫀떡의 턱을 긁어주었습니다.\n");
				printf("  2/6확률로 친밀도가 높아집니다.\n");
				printf("  주사위를 굴립니다. 또르륵...\n");
				for (int i = 0; i < 1; i++) {
					int r = rand() % 6 + 1;
					printf("  %d이(가) 나왔습니다!\n", r);
					if (r >= 5 && rel == 4) {
						printf("  친밀도가 높아집니다.\n");
						printf("  현재 친밀도: %d\n\n", rel);
					}
					else if (r >= 5 && rel != 4) {
						rel += 1;
						printf("  친밀도가 높아집니다.\n");
						printf("  현재 친밀도: %d\n\n", rel);
					}
					else if (r < 5) {
						printf("  친밀도는 그대로입니다.\n");
						printf("  현재 친밀도: %d\n", rel);
					}
					break;
				}
				break;
			}
		}

		Sleep(2500);
		system("cls");
	}
	return 0;
}
