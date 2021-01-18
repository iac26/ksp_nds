# KSP for NDS

### utilisation de la memoire graphique

cet outil permet de designer facilement le placement dans la memoire:
https://mtheall.com/vram.html#SUB=1&T0=1&NT0=320&MB0=11&TB0=0&S0=0&T1=1&NT1=64&MB1=14&TB1=2&S1=0&T2=5&MB2=3&S2=0&T3=5&MB3=4&S3=0







### modification a faire dans GRIT

il faut modifier cette fontion dans grit/libgrit/grit_prep.cpp
pour que l'assemblage des palettes fonctionne!

Une version precompilée pour la machine virtuelle se trouve dans ```media/grit``` 

```C
bool grit_prep_gfx(GritRec *gr)
{
	lprintf(LOG_STATUS, "Graphics preparation.\n");		

	int srcB= dib_get_bpp(gr->_dib);	// should be 8 or 16 by now
	int srcP= dib_get_pitch(gr->_dib);
	int srcS= dib_get_size_img(gr->_dib);
	BYTE *srcD= dib_get_img(gr->_dib);

	int dstB= gr->gfxBpp;
	// # dst bytes, with # src pixels as 'width'
	int dstS= dib_align(srcS*8/srcB, dstB);
	dstS= ALIGN4(dstS);
	BYTE *dstD= (BYTE*)malloc(dstS);
	if(dstD == NULL)
	{
		lprintf(LOG_ERROR, "  Can't allocate graphics data.\n");
		return false;
	}

	// Convert to final bitdepth
	// NOTE: do not use dib_convert here, because of potential
	//   problems with padding
	// NOTE: we're already at 8 or 16 bpp here, with 16 bpp already 
	//   accounted for. Only have to do 8->1,2,4
	// TODO: offset


	if(srcB == 8 && srcB != dstB)
	{
		lprintf(LOG_STATUS, "  Bitpacking: %d -> %d.\n", srcB, dstB);
		data_bit_pack(dstD, srcD, srcS, srcB, dstB, 0);
	}
	else
		memcpy(dstD, srcD, dstS);
	// DEBUT des modifications
	for(int i = 0; i < dstS; i++) {
		if(dstD[i])
			dstD[i] += gr->gfxOffset;
	}
	// FIN des modifications
	RECORD rec= { 1, dstS, dstD};

	if( BYTE_ORDER == BIG_ENDIAN && gr->gfxBpp > 8 )
		data_byte_rev(rec.data, rec.data, rec_size(&rec), gr->gfxBpp/8);		

	// attach and compress graphics
	grit_compress(&rec, &rec, gr->gfxCompression);
	rec_alias(&gr->_gfxRec, &rec);

	lprintf(LOG_STATUS, "Graphics preparation complete.\n");		
	return true;
}

```


### photos

![alt text](https://github.com/iac26/ksp_nds/blob/main/media/ss_01.png "photo")
Splash screen

![alt text](https://github.com/iac26/ksp_nds/blob/main/media/ss_02.png "photo")
Ingame first prototype


## done list
* autopilot
* GUI numbers
* GUI rocket with ajustable flame
* GUI horizon
* GUI buttons for autopilot
* splashscreen
* Game logic
* Crash detection and crash screen

## todo list
* GUI cleanup
* RK4 in fixed point
* Something with the abort button (need to connect to splash screen not done yet)
* use 20.12 fixed point numbers representation for everything!
* BG images for: wall crash, sub crash screen, instruction pannels, pause controls
* exact list of buttons that lead from one screen to another
* sprite rotation?
* sound in the game




## problems list
* start screen for some reason is slightly off center, might be the init which messes up?
*border crash not properly detected yet
