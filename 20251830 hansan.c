// hansan.c (이순신의 한산 전쟁)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


#define CMD_RELOAD      0x01 // Bit 0 - 장전 준비
#define CMD_FIRE        0x02 // Bit 1 - 발포 명령
#define CMD_CHARGE      0x04 // Bit 2 - 돌격 전진
#define CMD_HOLD        0x08 // Bit 3 - 후퇴 준비
#define CMD_CRANE_FORM  0x10 // Bit 4 - 학익진 유지
#define CMD_EVAC        0x20 // Bit 5 - 부상병 후송
#define CMD_DAMAGE      0x40 // Bit 6 - 피해 경고
#define CMD_REPAIR      0x80 // Bit 7 - 함선 수리 명령

unsigned char CommandOn(unsigned char fleet, unsigned char bit) {
    if (bit < 8)
        fleet |= (0x01 << bit);
    return fleet;
}

unsigned char CommandOff(unsigned char fleet, unsigned char bit) {
    if (bit < 8)
        fleet &= ~(0x01 << bit);
    return fleet;
}

void showStatus(unsigned char fleet, int hp) {
    printf("\n[현재 함선 상태] HEX: %02X | BIN: ", fleet);
    for (int i = 7; i >= 0; i--) printf("%d", (fleet >> i) & 1);
    printf("\n");

    if (fleet & CMD_RELOAD)     printf("장전 준비 완료\n");
    if (fleet & CMD_FIRE)       printf("발포 명령 활성\n");
    if (fleet & CMD_CHARGE)     printf("돌격 전진 개시\n");
    if (fleet & CMD_HOLD)       printf("후퇴 준비 중\n");
    if (fleet & CMD_CRANE_FORM) printf("학익진 진형 유지\n");
    if (fleet & CMD_EVAC)       printf("부상병 후송 중 (HP +5)\n");
    if (fleet & CMD_DAMAGE)     printf("함선 피해 발생! (HP -10)\n");
    if (fleet & CMD_REPAIR)     printf("함선 수리 중... 조선공이 분주합니다!\n");
    if (fleet == 0)             printf("모든 함선 대기 상태\n");

    printf("현재 함대 생명력 (HP): %d\n", hp);
}


void printMenu(void) {
    printf("\n===  이순신의 한산 전쟁!  ===\n");
    printf("1. Toggle 장전 준비\n");
    printf("2. Toggle 발포 명령\n");
    printf("3. Toggle 돌격 전진\n");
    printf("4. Toggle 후퇴 준비\n");
    printf("5. Toggle 학익진 유지\n");
    printf("6. Toggle 부상병 후송\n");
    printf("7. Toggle 피해 경고\n");
    printf("8. Reset ALL (초기화)\n");
    printf("9. Inspection (총무공 점검)\n");
    printf("10. Full Attack Mode (전면 돌격)\n");
    printf("11. Toggle 함선 수리 명령\n");
    printf("12. Exit\n");
    printf("명령 선택 (1~12): ");
}


int main(void) {
    unsigned char fleet = 0;
    int choice;
    int hp = 100; 

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            fleet = (fleet & CMD_RELOAD) ? CommandOff(fleet, 0) : CommandOn(fleet, 0);
            printf((fleet & CMD_RELOAD) ? "전 함선, 표를 장전하라!\n" : "장전 중지!\n");
            break;

        case 2:
            fleet = (fleet & CMD_FIRE) ? CommandOff(fleet, 1) : CommandOn(fleet, 1);
            printf((fleet & CMD_FIRE) ? "발포 하라! 적을 향해 쏴라!\n" : "발포 중지! 포신 내린다!\n");
            break;

        case 3:
            fleet = (fleet & CMD_CHARGE) ? CommandOff(fleet, 2) : CommandOn(fleet, 2);
            printf((fleet & CMD_CHARGE) ? "전 함선 돌격 전진 개시!\n" : "돌격 중지!\n");
            break;

        case 4:
            fleet = (fleet & CMD_HOLD) ? CommandOff(fleet, 3) : CommandOn(fleet, 3);
            printf((fleet & CMD_HOLD) ? "후퇴 준비, 적 움직임 감시!\n" : "후퇴 명령 해제!\n");
            break;

        case 5:
            fleet = (fleet & CMD_CRANE_FORM) ? CommandOff(fleet, 4) : CommandOn(fleet, 4);
            printf((fleet & CMD_CRANE_FORM) ? "학익진 진형 유지!\n" : "학익진 진형 해제!\n");
            break;

        case 6: 
            fleet = (fleet & CMD_EVAC) ? CommandOff(fleet, 5) : CommandOn(fleet, 5);
            if (fleet & CMD_EVAC) {
                printf("부상병 후송 시작! HP +5\n");
                hp += 5; 
            }
            else {
                printf("부상병 후송 중지!\n");
            }
            break;

        case 7:
            fleet = (fleet & CMD_DAMAGE) ? CommandOff(fleet, 6) : CommandOn(fleet, 6);
            if (fleet & CMD_DAMAGE) {
                printf("함선 피해 발생! HP -10\n");
                hp -= 10; 
            }
            else {
                printf("피해 경고 해제!\n");
            }
            break;

        case 8:
            fleet = 0;
            printf("모든 함선 상태 초기화 완료!\n");
            break;

        case 9:
            printf("총무공 점검: 현재 모든 함선 상태 확인!\n");
            showStatus(fleet, hp);
            continue;

        case 10:
            fleet = 0xFF;
            printf("전면 돌격 모드! 모든 명령 활성!\n");
            break;

        case 11: 
            fleet = (fleet & CMD_REPAIR) ? CommandOff(fleet, 7) : CommandOn(fleet, 7);
            printf((fleet & CMD_REPAIR) ? "함선 수리 개시! 조선공 투입!\n" : "수리 작업 중지!\n");
            break;

        case 12:
            printf("프로그램을 종료합니다.\n");
            return 0;

        default:
            printf("잘못된 입력입니다! (1~12)을 선택하세요.\n");
        }

        if (hp <= 0) {
            printf("\n You are dead. Game Over \n");
            return 0;
        }

        showStatus(fleet, hp);
    }

    return 0;
}
