\
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>

PSP_MODULE_INFO("NarutoRoadToWorldPeace_Text", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

#define MAX_CHAR 24
#define SAVE_PATH "ms0:/PSP/SAVEDATA/NarutoRoadToWorldPeace/unlocked.dat"

const char *roster[MAX_CHAR] = {
    "Naruto Uzumaki",
    "Sasuke Uchiha",
    "Sakura Haruno",
    "Kakashi Hatake",
    "Itachi Uchiha",
    "Kisame Hoshigaki",
    "Pain (Nagato)",
    "Konan",
    "Deidara",
    "Sasori",
    "Hidan",
    "Kakuzu",
    "Tobi (Obito)",
    "Hashirama Senju (1st)",
    "Tobirama Senju (2nd)",
    "Hiruzen Sarutobi (3rd)",
    "Minato Namikaze (4th)",
    "Tsunade Senju (5th)",
    "Kakashi Hatake (6th)",
    "Naruto Uzumaki (7th)",
    "Jiraiya",
    "Orochimaru",
    "Tsunade (Sannin)",
    "Madara Uchiha"
};

int unlocked[MAX_CHAR];
int hp_player, hp_enemy;

void save_unlocks(){
    FILE *f = fopen(SAVE_PATH, "wb");
    if(!f) return;
    fwrite(unlocked, sizeof(int), MAX_CHAR, f);
    fclose(f);
}

void load_unlocks(){
    FILE *f = fopen(SAVE_PATH, "rb");
    if(!f) return;
    fread(unlocked, sizeof(int), MAX_CHAR, f);
    fclose(f);
}

void init_game(){
    memset(unlocked, 0, sizeof(unlocked));
    unlocked[0] = 1; // Naruto
    unlocked[1] = 1; // Sasuke
    load_unlocks();
}

void show_roster(){
    pspDebugScreenClear();
    pspDebugScreenPrintf("=== ROSTER (locked/unlocked) ===\n\n");
    for(int i=0;i<MAX_CHAR;i++){
        pspDebugScreenPrintf("%2d. %-25s [%s]\n", i, roster[i], unlocked[i] ? "UNLOCKED" : "LOCKED");
    }
    pspDebugScreenPrintf("\nPress CROSS to continue...");
    // wait for X
    SceCtrlData pad;
    while(1){
        sceCtrlReadBufferPositive(&pad, 1);
        if(pad.Buttons & PSP_CTRL_CROSS) break;
        sceKernelDelayThread(100000);
    }
}

int simple_combat(int playerIdx, int oppIdx){
    // Simple combat: each has HP, player does small advantage if lower index (Naruto/Sasuke)
    hp_player = 10 + (playerIdx<=1 ? 5 : 0);
    hp_enemy = 10 + (oppIdx%6);
    pspDebugScreenPrintf("Fight: %s VS %s\n", roster[playerIdx], roster[oppIdx]);
    pspDebugScreenPrintf("Player HP: %d  Enemy HP: %d\n", hp_player, hp_enemy);
    pspDebugScreenPrintf("Press CROSS to perform attack. First to reduce enemy HP to 0 wins.\n\n");
    SceCtrlData pad;
    while(hp_player>0 && hp_enemy>0){
        sceCtrlReadBufferPositive(&pad, 1);
        if(pad.Buttons & PSP_CTRL_CROSS){
            int dmg = 1 + (playerIdx<=1 ? 2 : 0); // starter chars hit stronger
            hp_enemy -= dmg;
            pspDebugScreenPrintf("You hit for %d! Enemy HP: %d\n", dmg, hp_enemy>0?hp_enemy:0);
            if(hp_enemy<=0) break;
            // enemy turn
            int edmg = 1 + (oppIdx%3);
            hp_player -= edmg;
            pspDebugScreenPrintf("Enemy hits for %d! Your HP: %d\n", edmg, hp_player>0?hp_player:0);
        }
        sceKernelDelayThread(100000);
    }
    return hp_player>0;
}

int main_thread(SceSize args, void *argp){
    pspDebugScreenInit();
    init_game();
    pspDebugScreenPrintf("=== Naruto Road to World Peace (Text Demo) ===\n");
    pspDebugScreenPrintf("Naruto & Sasuke unlocked by default.\n\n");
    pspDebugScreenPrintf("Press CROSS to start. Press START to exit any time.\n");

    SceCtrlData pad;
    while(1){
        sceCtrlReadBufferPositive(&pad, 1);
        if(pad.Buttons & PSP_CTRL_START) break;
        if(pad.Buttons & PSP_CTRL_CROSS) break;
        sceKernelDelayThread(100000);
    }

    // Main loop: show roster, select a mission (opponent), fight, unlock if win.
    int running = 1;
    while(running){
        show_roster();
        pspDebugScreenClear();
        pspDebugScreenPrintf("Choose a mission opponent by number (0-%d). Cross to confirm.\n", MAX_CHAR-1);
        int selected = 2; // default pick index 2 (Sakura) for demo
        pspDebugScreenPrintf("Default opponent: %d (%s)\n", selected, roster[selected]);
        pspDebugScreenPrintf("Press CROSS to fight, START to exit.\n");
        while(1){
            sceCtrlReadBufferPositive(&pad, 1);
            if(pad.Buttons & PSP_CTRL_START){ running = 0; break; }
            if(pad.Buttons & PSP_CTRL_CROSS) break;
            // change selection with Left/Right (demo)
            if(pad.Buttons & PSP_CTRL_LEFT){ selected = (selected-1+MAX_CHAR)%MAX_CHAR; pspDebugScreenPrintf("Selected: %d %s\n", selected, roster[selected]); }
            if(pad.Buttons & PSP_CTRL_RIGHT){ selected = (selected+1)%MAX_CHAR; pspDebugScreenPrintf("Selected: %d %s\n", selected, roster[selected]); }
            sceKernelDelayThread(150000);
        }
        if(!running) break;

        // Choose player char (Naruto by default)
        int player = 0; // Naruto
        pspDebugScreenPrintf("\\nStarting mission: Defeat %s\\n", roster[selected]);
        int win = simple_combat(player, selected);
        if(win){
            pspDebugScreenPrintf("\\nYou won! %s unlocked.\\n", roster[selected]);
            unlocked[selected] = 1;
            save_unlocks();
        } else {
            pspDebugScreenPrintf("\\nYou lost. Try again.\\n");
        }
        pspDebugScreenPrintf("Press CROSS to continue, START to exit.\n");
        while(1){
            sceCtrlReadBufferPositive(&pad, 1);
            if(pad.Buttons & PSP_CTRL_START){ running = 0; break; }
            if(pad.Buttons & PSP_CTRL_CROSS) break;
            sceKernelDelayThread(100000);
        }
    }

    sceKernelExitGame();
    return 0;
}

int main(SceSize args, void *argp){
    sceKernelStartModule(sceKernelCreateThread("main_thread", (void*)main_thread, 0x18, 0x10000, 0, NULL), 0, NULL);
    sceKernelSleepThread();
    return 0;
}
