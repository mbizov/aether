#include "battle.h"

entity_t *make_enemy() {
    entity_t *e = (entity_t*)malloc(sizeof(entity_t));
    e->dmg = 3 + rand_int(0, 3);
    e->dmg_vary = 3;
    e->max_hp = 20 + rand_int(0, 10);
    e->hp = e->max_hp;
    e->coins = rand_int(5, 10);
    return e;
}

int enemy_turn(HANDLE con, entity_t *player, entity_t *enemy){
    int dmg_final = enemy->dmg + rand_int(0, enemy->dmg_vary) - player->armour;
    if(player->defending){
        dmg_final /= 2;
        player->defending = 0;
    }
    if(player->armour > dmg_final)
        dmg_final = 0;
    player->hp -= dmg_final;
    return dmg_final;
}

void victory(HANDLE con, entity_t *player, entity_t *enemy, inventory_t *inv){
    DWORD written;
	//mciSendStringA(concat("play sound\\", sounds[7]), NULL, 0, NULL);
	//Sleep(2000);
	//mciSendStringA(concat("play sound\\", sounds[3]), NULL, 0, NULL);
	//PlaySound(NULL, NULL, SND_ASYNC);
    player->coins += enemy->coins;
	WriteConsoleA(con, "As the fiend falls, your courage stands tall. You've won the encounter.\n\n", 73, &written, NULL); //could list loot as well when implemented
    drops(con, inv);
    Sleep(2000);
}

void defeat(HANDLE con){
    DWORD written;
	//mciSendStringA(concat("play sound\\", sounds[0]), NULL, 0, NULL);
	//PlaySound(NULL, NULL, SND_ASYNC);
	WriteConsoleA(con, "Before you even get to reflect on your life, you are struck down viciously by your enemy. Humanity is now doomed to fall...\n\n", 125, &written, NULL);
	Sleep(3000);
}

void player_turn(HANDLE con, entity_t *player, entity_t *enemy){
    DWORD written;
    char buffer[CONSOLE_COLS];

    int opt;
    player->escaped = 0;
    int p_dmg;

    sprintf(buffer, "Player: HP: %d/%d ATK: %d - %d\tEnemy: HP: %d/%d ATK: %d - %d \n", player->hp, player_max_hp, player->dmg, player->dmg + player->dmg_vary, enemy->hp, enemy->max_hp, enemy->dmg, enemy->dmg + enemy->dmg_vary);
    WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
    WriteConsoleA(con, "1.Attack\n2.Defend\n3.Run\n4.Item\n", 31, &written, NULL);

    do {
        opt = getch();
        if (opt < '1' || opt > '4') WriteConsoleA(con, "That is not a valid action.\n\n", 29, &written, NULL);
    } while (opt < '1' || opt > '4');

    switch(opt){
        case '1':
            if(rand_int(1, 7) == 1)
                WriteConsoleA(con, "You swing your weapon and whoops! You missed!\n", 48, &written, NULL);
            else{    
                p_dmg = player_attack(player, enemy);
                //mciSendStringA(concat("play sound\\", sounds[13]), NULL, 0, NULL);
                sprintf(buffer, "You swing your weapon and hit the enemy for %d damage\n\n", p_dmg);
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
                //Sleep(1400);
            }
            break;

        case '2':
            //mciSendStringA(concat("play sound\\", sounds[10]), NULL, 0, NULL);
            player->defending = 1;
            WriteConsoleA(con, "You take a defensive stance, expecting your enemy's vicious attack, bolstering your defense for the next turn.\n\n", 112, &written, NULL);
            break;

        case '3':
            //mciSendStringA(concat("play sound\\", sounds[11]), NULL, 0, NULL);
		    WriteConsoleA(con, "You have decided your chances of winning have faltered, and cowardly sprint away from your adversaries...\n\n", 107, &written, NULL);
            if(rand() % 2 == 0){
				//Sleep(3000);
			}
			else{
				WriteConsoleA(con, "...but even that you do sloppily. The enemy could hit you one last time...\n", 75, &written, NULL);
				Sleep(3000);
				//mciSendStringA(concat("play sound\\", sounds[6]), NULL, 0, NULL);
	            sprintf(buffer, "The enemy has hit you for %d damage.\n", enemy_turn(con, player, enemy));
                WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
	            //Sleep(1400);
				}
			player->escaped = 1;	
			break;
        
        case '4':
        WriteConsoleA(con, "...", 3, &written, NULL);
    }

}

void battle(HANDLE con, entity_t *player, inventory_t *inv){
    DWORD written;
    char buffer[CONSOLE_COLS];
    entity_t *enemy = make_enemy();
    player->defending = 0;
    int m_dmg;
    WriteConsoleA(con, "You're under attack!\n\n", 22, &written, NULL);

    while(1){
        player_turn(con, player, enemy);
        if(player->hp <= 0){
            defeat(con);
            //sleep(2000);
            return;
        }

        if(player->escaped == 1){
            //sleep(2000);
            return;
        }

        if(enemy->hp <= 0){
            victory(con, player, enemy, inv);
            return;
        }


        m_dmg = enemy_turn(con, player, enemy);
        //mciSendStringA(concat("play sound\\", sounds[6]), NULL, 0, NULL);
	    sprintf(buffer, "The enemy has hit you for %d damage.\n", m_dmg);
        WriteConsoleA(con, buffer, strlen(buffer), &written, NULL);
	    //Sleep(1400);

        if(player->hp <= 0){
            defeat(con);
            return;
        }
    }
}
