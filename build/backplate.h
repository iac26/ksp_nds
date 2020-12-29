
//{{BLOCK(backplate)

//======================================================================
//
//	backplate, 256x192@8, 
//	+ palette 64 entries, not compressed
//	+ 62 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 128 + 3968 + 1536 = 5632
//
//	Time-stamp: 2020-12-29, 13:50:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKPLATE_H
#define GRIT_BACKPLATE_H

#define backplateTilesLen 3968
extern const unsigned char backplateTiles[3968];

#define backplateMapLen 1536
extern const unsigned short backplateMap[768];

#define backplatePalLen 128
extern const unsigned short backplatePal[64];

#endif // GRIT_BACKPLATE_H

//}}BLOCK(backplate)
