
//{{BLOCK(backplate)

//======================================================================
//
//	backplate, 256x192@8, 
//	Transparent color : 00,00,00
//	+ palette 64 entries, not compressed
//	+ 104 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 128 + 6656 + 1536 = 8320
//
//	Time-stamp: 2021-01-13, 22:45:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKPLATE_H
#define GRIT_BACKPLATE_H

#define backplateTilesLen 6656
extern const unsigned char backplateTiles[6656];

#define backplateMapLen 1536
extern const unsigned short backplateMap[768];

#define backplatePalLen 128
extern const unsigned short backplatePal[64];

#endif // GRIT_BACKPLATE_H

//}}BLOCK(backplate)
