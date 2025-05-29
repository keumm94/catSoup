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
void drawRoom(int cat_position, int prev_position, int scratcher_position, int cattower_position) {
	printf("##########\n");
	printf("#");
	for (int i = 1; i < ROOM_WIDTH - 1; i++) {
		if (i == HME_POS) { printf("H"); }
		else if (i == BWL_POS) { printf("B"); }
		else if (i == scratcher_position) { printf("S"); }
		else if (i == cattower_position) { printf("T"); }
		else { printf(" "); }
	}
	printf("#\n");

	printf("#");
	for (int i = 1; i < ROOM_WIDTH - 1; i++) {
		if (i == cat_position) { printf("C"); }
		else if (i == prev_position) { printf("."); }
		else { printf(" "); }
	}
	printf("#");

	printf("\n##########\n\n");
}

//돌발퀘스트
void quest() {
	int choice_box, hide_box; //choice_box: 유저 선택, hide_box: 고양이가 숨은 박스
	hide_box = rand() % 4 + 1;
	printf("▶ 돌발 퀘스트 발생!\n");
	printf("  쫀떡이 버려져있는 박스 안에 숨었습니다.\n");
	printf("  당신이 찾아낸다면 관계가 좋아질 수도...\n");
	printf("  ■ ■ ■ ■\n");
	printf("  어디에 숨었을까요? (1 ~ 4)\n");
	printf("▷ ");
	scanf_s("%d", &choice_box);
	printf("\n");
	if (choice_box == hide_box) {
		printf("▶ 쫀떡을 찾았습니다. 대단해요!\n");
		rel++;
		printf("  친밀도가 높아집니다.\n");
		printf("  현재 친밀도: %d\n", rel);
	}
	else {
		printf("▶ 쫀떡을 찾지 못했습니다. 실망이에요...\n");
		rel--;
		printf("  친밀도가 낮아집니다.\n");
		printf("  현재 친밀도: %d\n", rel);
	}
}


int main(void) {
	//인트로
	printf("〓〓〓 야옹이와 수프 〓〓〓 \n\n");
	printf("(^. .^  )/ \n");
	printf("▶ 야옹이의 이름은 쫀떡 입니다.\n\n\n");

	int cat_position = HME_POS; //초기 위치
	int prev_position = cat_position - 1; // 이전 위치
	int scratcher_position = -1; // 스크래처 위치
	int cattower_position = -1; //캣타워 위치

	//물건 
	int has_mouse = 0, has_laser = 0, has_cattower = 0, has_scratcher = 0;

	//턴
	int turn = 1;

	while (1) {
		//상태 출력
		printf("====================현재 상태 ====================\n");
		printf("현재까지 만든 수프: %d개\n", soup);
		printf("CP: %d 포인트\n", cp);
		printf("쫀떡이의 기분(0~3): %d\n", feeling);
		switch (feeling) {
		case 0: printf("→ 기분이 매우 나쁩니다.\n"); break;
		case 1: printf("→ 심심해합니다.\n"); break;
		case 2: printf("→ 식빵을 굽습니다.\n"); break;
		case 3: printf("→ 골골송을 부릅니다.\n"); break;
		}
		printf("집사와의 관계 (0~4): %d\n", rel);
		switch (rel) {
		case 0: printf("→ 곁에 오는 것조차 싫어합니다.\n"); break;
		case 1: printf("→ 간식 자판기 취급입니다.\n"); break;
		case 2: printf("→ 그럭저럭 쓸 만한 집사입니다.\n"); break;
		case 3: printf("→ 훌륭한 집사로 인정 받고 있습니다.\n"); break;
		case 4: printf("→ 집사 껌딱지 입니다.\n"); break;
		}
		printf("==================================================\n\n");

		//기분
		printf("▶ 6-2: 주사위 눈이  \'%d\' 이하이면 그냥 기분이 나빠집니다.\n", 6 - rel);
		printf("  주사위가 굴러갑니다. 또르르륵...\n");
		for (int i = 0; i < 1; i++) {
			int r = rand() % 6 + 1;
			printf("  %d이(가) 나왔습니다.\n", r);
			if ((r <= 6 - rel)) {
				prev_feeling = feeling;
				feeling = prev_feeling - 1;
				if (feeling == 0) { feeling = 0; }
				printf("  쫀떡의 기분이 나빠집니다: %d → %d\n\n", prev_feeling, feeling);
			}
			else {
				printf("  쫀떡의 기분은 그대로입니다.\n\n");
			}
		}


		//이동
		int position;
		switch (feeling) {
		case 0 : //집 쪽으로 이동
			prev_position = cat_position;
			if (cat_position > HME_POS) {
				cat_position--;
			}
			printf("▶ 기분이 매우 나쁜 쫀떡은 집으로 향합니다.\n\n");
			break;

		case 1: //더 가까운 놀이기구 쪽으로 이동
			printf("▶ 쫀떡은 심심해서 놀이기구 쪽으로 이동합니다.\n\n");
			if (has_scratcher || has_cattower) {
				int target = has_scratcher ? scratcher_position : cattower_position;
				if (cat_position < target) cat_position++;
				else if (cat_position > target) cat_position--;
			}
			else {
				if (feeling == !0) {
					prev_feeling = feeling;
					feeling = prev_feeling - 1;
					printf("  놀 거리가 없어서 기분이 매우 나빠졌습니다.: %d → %d\n\n", prev_feeling, feeling);
				}
			}
			break;

		case 2: //제자리에 대기
			printf("▶ 쫀떡은 기분 좋게 식빵을 굽고 있습니다.\n\n");
			break;

		case 3 : //냄비 쪽으로 이동
			prev_position = cat_position;
			if (cat_position < BWL_POS) {
				position = cat_position++;
			}
			printf("  쫀떡은 골골송을 부르며 수프를 만들러 갑니다.\n\n");
			break;

		}

		//행동
		if (cat_position == BWL_POS) {
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
				soup++;
				printf("  현재까지 만든 스프: %d\n\n", soup);
			}
		}
		if (cat_position == HME_POS) {
			printf("▶ 쫀떡은 자신의 집에서 편안함을 느낍니다.\n\n");
			prev_feeling = feeling;
			feeling = prev_feeling + 1;
			if (feeling > 3) { feeling = 3; }
			printf("  쫀떡의 기분이 꽤 좋아졌습니다: %d → %d\n", prev_feeling, feeling);
		}
		if (cat_position == scratcher_position) {
			prev_feeling = feeling;
			feeling = prev_feeling + 1;
			if (feeling > 3) { feeling = 3; }
			printf("▶ 쫀떡은 스크래처를 긁고 놀았습니다.\n");
			printf("  기분이 조금 좋아졌습니다: %d → %d\n\n", prev_feeling, feeling);
		}
		if (cat_position == cattower_position) {
			prev_feeling = feeling;
			feeling = prev_feeling + 2;
			if (feeling > 3) { feeling = 3; }
			printf("▶ 쫀떡은 캣타워를 뛰어다닙니다.\n");
			printf("  기분이 조금 좋아졌습니다: %d → %d\n\n", prev_feeling, feeling);
		}

		//방
		drawRoom(cat_position, prev_position);

		//상호작용
		int interaction;
		printf("▶ 어떤 상호작용을 하시겠습니까?\n");
		printf("  0. 아무것도 하지 않음\n");
		printf("  1. 긁어 주기\n");
		if (has_laser == 1) {
			printf("  2. 레이저 포인터로 놀아주기\n");
			if (has_mouse == 1) {
				printf("  3. 장난감 쥐로 놀아주기\n");
			}
			while (1) {
				printf("▷ ");
				scanf_s("%d", &interaction);
				if (interaction == 0) {
					prev_feeling = feeling;
					feeling = prev_feeling - 1;
					if (feeling == 0) { feeling = 0; }
					printf("\n▶ 아무것도 하지 않았습니다.\n");
					printf("  쫀떡의 기분이 나빠졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 5 && rel == !0) {
							rel--;
							printf("  집사와의 관계가 나빠집니다. \n");
						}
					}
					break;
				}
				else if (interaction == 1) {
					printf("\n▶ 쫀떡의 턱을 긁어주었습니다.\n");
					printf("  쫀떡의 기분은 그대로입니다: %d\n", feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r <= 5 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else if (interaction == 2) {
					prev_feeling = feeling;
					feeling = prev_feeling + 2;
					if (feeling > 3) { feeling = 3; }
					printf("\n▶ 레이저 포인터로 쫀떡과 놀아주었습니다.\n");
					printf("  쫀떡의 기분이 꽤 좋아졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 4 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else if (interaction == 3) {
					prev_feeling = feeling;
					feeling = prev_feeling + 1;
					if (feeling > 3) { feeling = 3; }
					printf("\n▶ 장난감 쥐로 쫀떡과 놀아주었습니다.\n");
					printf("  쫀떡의 기분이 조금 좋아졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 4 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					printf("\n");
					break;
				}
				else { continue; }
			}

		}
		else if (has_mouse == 1) {
			printf("  2. 장난감 쥐로 놀아주기\n");
			if (has_laser == 1) {
				printf("  3. 레이저 포인터로 놀아주기\n");
			}
			while (1) {
				printf("▷ ");
				scanf_s("%d", &interaction);
				if (interaction == 0) {
					prev_feeling = feeling;
					feeling = prev_feeling - 1;
					if (feeling == 0) { feeling = 0; }
					printf("\n▶ 아무것도 하지 않았습니다.\n");
					printf("  쫀떡의 기분이 나빠졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 5 && rel == !0) {
							rel--;
							printf("  집사와의 관계가 나빠집니다. \n");
						}
					}
					break;
				}
				else if (interaction == 1) {
					printf("\n▶ 쫀떡의 턱을 긁어주었습니다.\n");
					printf("  쫀떡의 기분은 그대로입니다: %d\n", feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r <= 5 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else if (interaction == 2) {
					prev_feeling = feeling;
					feeling = prev_feeling + 1;
					if (feeling > 3) { feeling = 3; }
					printf("\n▶ 장난감 쥐로 쫀떡과 놀아주었습니다.\n");
					printf("  쫀떡의 기분이 조금 좋아졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 4 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else if (interaction == 3) {
					prev_feeling = feeling;
					feeling = prev_feeling + 2;
					if (feeling > 3) { feeling = 3; }
					printf("\n▶ 레이저 포인터로 쫀떡과 놀아주었습니다.\n");
					printf("  쫀떡의 기분이 꽤 좋아졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 4 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else { continue; }
			}
		}
		else if (has_laser == 0 && has_mouse == 0) {
			while (1) {
				printf("▷ ");
				scanf_s("%d", &interaction);
				if (interaction == 0) {
					prev_feeling = feeling;
					feeling = prev_feeling - 1;
					if (feeling == 0) { feeling = 0; }
					printf("\n▶ 아무것도 하지 않았습니다.\n");
					printf("  쫀떡의 기분이 나빠졌습니다: %d → %d\n", prev_feeling, feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r >= 5 && rel == !0) {
							rel--;
							printf("  집사와의 관계가 나빠집니다. \n");
						}
					}
					break;
				}
				else if (interaction == 1) {
					printf("\n▶ 쫀떡의 턱을 긁어주었습니다.\n");
					printf("  쫀떡의 기분은 그대로입니다: %d\n", feeling);
					for (int i = 0; i < 1; i++) {
						int r = rand() % 6 + 1;
						if (r <= 5 && rel == !6) {
							rel++;
							printf("  친밀도가 높아집니다.\n");
							printf("  현재 친밀도: %d\n", rel);
						}
					}
					break;
				}
				else { continue; }
			}
		}
		printf("\n");

		//CP생산
		printf("▶ 쫀떡의 기분(0~3): %d\n", feeling);
		printf("  집사와의 친밀도(0~4): %d\n", rel);
		int get_cp;
		get_cp = 0;
		if (feeling == 0) { get_cp = rel; }
		else { get_cp = (feeling - 1) + rel; }
		cp = cp + get_cp;
		printf("  쫀떡의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", get_cp);
		printf("  보유 CP: %d 포인트\n\n", cp);

		//상점
		int choice_num;
		printf("▶ 상점에서 물건을 살 수 있습니다.\n");
		printf("  어떤 물건을 구매할까요?\n");
		printf("   0. 아무것도 사지 않는다.\n");
		if (has_mouse == 0) { printf("   1. 장난감 쥐: 1 CP\n"); }
		else { printf("   1. 장난감 쥐: 1 CP (품절)\n"); }
		if (has_laser == 0) { printf("   2. 레이저 포인터: 2 CP\n"); }
		else { printf("   2. 레이저 포인터: 2 CP (품절)\n"); }
		if (has_scratcher == 0) { printf("   3. 스크래처: 4 CP\n"); }
		else { printf("   3. 스크래처: 4 CP (품절)\n"); }
		if (has_cattower == 0) { printf("   4. 캣 타워: 6 CP\n"); }
		else { printf("   4. 캣 타워: 6 CP (품절)\n"); }
		while (1) {
			printf("▷ ");
			scanf_s("%d", &choice_num);
			printf("\n");
			switch (choice_num) {
			case 0: printf("▶ 아무것도 사지 않았습니다.\n"); break;
			case 1: //장난감 쥐
				if (has_mouse == !0) {
					printf("▶ 장난감 쥐를 이미 구매했습니다.\n");
					continue;
				}
				else if (cp < 1) {
					printf("▶ CP가 부족합니다.\n");
					continue;
				}
				else {
					has_mouse = 1;
					cp = cp - 1;
					printf("▶ 장난감 쥐를 구매했습니다.\n");
					printf("  보유 CP: %d\n", cp);
					break;
				}
				break;
			case 2: //레이저 포인터
				if (has_laser == !0) {
					printf("▶ 레이저 포인터를 이미 구매했습니다.\n");
					continue;
				}
				else if (cp < 2) {
					printf("▶ CP가 부족합니다.\n");
					continue;
				}
				else {
					has_laser = 1;
					cp = cp - 2;
					printf("▶ 레이저 포인터를 구매했습니다.\n");
					printf("  보유 CP: %d\n", cp);
					break;
				}
				break;
			case 3: //스크래처
				if (has_scratcher == !0) {
					printf("▶ 스크래처를 이미 구매했습니다.\n");
					continue;
				}
				else if (cp < 4) {
					printf("▶ CP가 부족합니다.\n");
					continue;
				}
				else {
					has_scratcher = 1;
					cp = cp - 4;
					printf("▶ 스크래처를 구매했습니다.\n");
					printf("  보유 CP: %d\n", cp);
					break;
				}
				break;
			case 4: //캣타워
				if (has_cattower == !0) {
					printf("▶ 캣 타워를 이미 구매했습니다.\n");
					continue;
				}
				else if (cp < 6) {
					printf("▶ CP가 부족합니다.\n");
					continue;
				}
				else {
					has_cattower = 1;
					cp = cp - 6;
					printf("▶ 캣 타워를 구매했습니다.\n");
					printf("  보유 CP: %d\n", cp);
					break;
				}
				break;
			default: continue;
			}
			break;
		}

		printf("\n");

		//랜덤 배치
		if (has_scratcher == 1) {
			do { scratcher_position = rand() % 6 + 2; } while (cattower_position == scratcher_position);
		}
		if (has_cattower == 1) {
			do { cattower_position = rand() % 6 + 2; } while (cattower_position == scratcher_position);
		}

		//퀘스트
		turn++;
		if (turn == 3) {
			quest();
		}

		Sleep(2500);
		system("cls");
	}
	return 0;
}
