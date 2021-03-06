
#include "sound.h"


void sound_init() {
	//initialize the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_CRASH);
	mmLoad(MOD_AMBIANCE);
}


void sound_crash() {
	mm_sound_effect sound;
	sound.id = SFX_CRASH;
	sound.rate = 1024;
	sound.volume = 255;
	sound.panning = 127;
	mmEffectEx(&sound);
}

void sound_ambiance() {
	//Start playing music in a loop
	mmStart(MOD_AMBIANCE, MM_PLAY_LOOP);
	mmSetModuleVolume(1024);
}
