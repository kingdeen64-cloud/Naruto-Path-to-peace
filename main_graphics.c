/*
  Stub for the graphics-based build.
  When you are ready to enable graphics, this file will include menu rendering,
  loading BMP sprites from assets/, and simple HUD drawing (HP bars, cooldowns).
  It is intentionally left as a placeholder in the text build.
*/
#include <pspkernel.h>
#include <pspdebug.h>

PSP_MODULE_INFO("NarutoRoadToWorldPeace_Graphics", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(0);

int main(SceSize args, void *argp){
    pspDebugScreenInit();
    pspDebugScreenPrintf("Graphics build stub. Replace with GUI code when ready.\n");
    sceKernelSleepThread();
    return 0;
}
