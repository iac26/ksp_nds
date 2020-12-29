# ksp_nds

### utilisation de la memoire graphique

cet outil permet de designer facilement le placement dans la memoire:
https://mtheall.com/vram.html#SUB=1&T0=1&NT0=320&MB0=11&TB0=0&S0=0&T1=1&NT1=64&MB1=14&TB1=2&S1=0&T2=5&MB2=3&S2=0&T3=5&MB3=4&S3=0







### modification a faire dans GRIT

il faut modifier cette fontion dans grit/libgrit/grit_prep.cpp
pour que l'assemblage des palettes fonctionne!

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


### photo

![alt text](https://github.com/adam-p/markdown-here/raw/master/src/common/images/icon48.png "Logo Title Text 1")

