
//{{BLOCK(backplate)

//======================================================================
//
//	backplate, 256x192@8, 
//	Transparent color : 00,00,00
//	+ palette 64 entries, not compressed
//	+ 82 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 128 + 5248 + 1536 = 6912
//
//	Time-stamp: 2020-12-29, 15:29:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKPLATE_H
#define GRIT_BACKPLATE_H

#define backplateTilesLen 5248
extern const unsigned char backplateTiles[5248];

#define backplateMapLen 1536
extern const unsigned short backplateMap[768];

#define backplatePalLen 128
extern const unsigned short backplatePal[64];

#endif // GRIT_BACKPLATE_H

//}}BLOCK(backplate)
