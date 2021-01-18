
//{{BLOCK(backplate)

//======================================================================
//
//	backplate, 256x192@8, 
//	Transparent color : 00,00,00
//	+ palette 64 entries, not compressed
//	+ 139 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 128 + 8896 + 1536 = 10560
//
//	Time-stamp: 2021-01-18, 20:44:17
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKPLATE_H
#define GRIT_BACKPLATE_H

#define backplateTilesLen 8896
extern const unsigned char backplateTiles[8896];

#define backplateMapLen 1536
extern const unsigned short backplateMap[768];

#define backplatePalLen 128
extern const unsigned short backplatePal[64];

#endif // GRIT_BACKPLATE_H

//}}BLOCK(backplate)
