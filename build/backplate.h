
//{{BLOCK(backplate)

//======================================================================
//
//	backplate, 256x192@8, 
//	+ palette 32 entries, not compressed
//	+ 62 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 64 + 3968 + 1536 = 5568
//
//	Time-stamp: 2020-12-29, 02:29:06
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKPLATE_H
#define GRIT_BACKPLATE_H

#define backplateTilesLen 3968
extern const unsigned int backplateTiles[992];

#define backplateMapLen 1536
extern const unsigned short backplateMap[768];

#define backplatePalLen 64
extern const unsigned short backplatePal[32];

#endif // GRIT_BACKPLATE_H

//}}BLOCK(backplate)
