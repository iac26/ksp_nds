
#include "sound.h"


void sound_init() {
	//Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_AMBIANCE);
}


void sound_rocket() {
	//Declare a sound effect
	mm_sound_effect sound;
	//Set the id of the sound effect with the input parameter
	sound.id = 0;
	//Set the rate to the default one (1024)
	sound.rate = 1024;
	//Set the volume to the maximum (range 0...255)
	sound.volume = 255;
	//Set the panning depending on the effect (0-left....255-right)

	//Play the effect using the sound structure
	mmEffectEx(&sound);
}
