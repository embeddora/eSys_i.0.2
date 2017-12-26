#ifndef __VGA_H_
#define __VGA_H_

//////////////////////////////////////////////////////////////////////

/* from vgadrv.c */
extern unsigned char *__svgalib_graph_mem;
/* extern const unsigned long VideoMemoryStart; */
int vga_setmode(int);
int vga_setcolor(int);

/* from vgapix.c */
int vga_drawpixel(int, int);

//////////////////////////////////////////////////////////////////////


/* this def. from vga.h, too */
#define HAVE_RWPAGE 1		/* vga_setreadpage() / vga_setwritepage() available */

#define IS_INTERLACED 2		/* mode is interlaced */
#define IS_MODEX 4		/* ModeX style 256 colors */
#define IS_DYNAMICMODE 8	/* Dynamic defined mode */
#define CAPABLE_LINEAR 16	/* Can go to linear addressing mode. */
#define IS_LINEAR 32		/* Linear addressing enabled. */
#define HAVE_EXT_SET 256	/* vga_ext_set() available */
#define EXT_INFO_AVAILABLE 64	/* Returned modeinfo contains valid extended fields */

/* this def. from1041 vga.h, too */
#define __GLASTMODE G1600x1200x16M32
#define GLASTMODE vga_lastmodenumber()

/* this def. from vga.h, too */
#define TEXT 	     0		/* Compatible with VGAlib v1.2 */
#define G320x200x16  1
#define G640x200x16  2
#define G640x350x16  3
#define G640x480x16  4
#define G320x200x256 5
#define G320x240x256 6
#define G320x400x256 7
#define G360x480x256 8
#define G640x480x2   9

#define G640x480x256 10
#define G800x600x256 11
#define G1024x768x256 12

#define G1280x1024x256 13	/* Additional modes. */

#define G320x200x32K 14
#define G320x200x64K 15
#define G320x200x16M 16
#define G640x480x32K 17
#define G640x480x64K 18
#define G640x480x16M 19
#define G800x600x32K 20
#define G800x600x64K 21
#define G800x600x16M 22
#define G1024x768x32K 23
#define G1024x768x64K 24
#define G1024x768x16M 25
#define G1280x1024x32K 26
#define G1280x1024x64K 27
#define G1280x1024x16M 28

#define G800x600x16 29
#define G1024x768x16 30
#define G1280x1024x16 31

#define G720x348x2 32		/* Hercules emulation mode */

#define G320x200x16M32 33	/* 32-bit per pixel modes. */
#define G640x480x16M32 34
#define G800x600x16M32 35
#define G1024x768x16M32 36
#define G1280x1024x16M32 37

/* additional resolutions */
#define G1152x864x16 38
#define G1152x864x256 39
#define G1152x864x32K 40
#define G1152x864x64K 41
#define G1152x864x16M 42
#define G1152x864x16M32 43

#define G1600x1200x16 44
#define G1600x1200x256 45
#define G1600x1200x32K 46
#define G1600x1200x64K 47
#define G1600x1200x16M 48
#define G1600x1200x16M32 49


/* this def. from vga.h, too */
#ifdef EGA			/* Kernel headers may define this. */
#undef EGA
#endif

#define UNDEFINED	0
#define VGA		1
#define ET4000		2
#define CIRRUS		3
#define TVGA8900	4
#define OAK		5
#define EGA		6
#define S3		7
#define ET3000		8
#define MACH32		9
#define GVGA6400	10
#define ARK		11
#define ATI		12
#define ALI		13
#define MACH64		14
#define CHIPS		15
#define APM             16
#define NV3		17
#define ET6000		18
#define VESA		19
#define MX              20

    /* Hor. sync: */
#define MON640_60	0	/* 31.5 KHz (standard VGA) */
#define MON800_56	1	/* 35.1 KHz (old SVGA) */
#define MON1024_43I	2	/* 35.5 KHz (low-end SVGA, 8514) */
#define MON800_60	3	/* 37.9 KHz (SVGA) */
#define MON1024_60	4	/* 48.3 KHz (SVGA non-interlaced) */
#define MON1024_70	5	/* 56.0 KHz (SVGA high frequency) */
#define MON1024_72	6


#endif /* __VGA_H_ */


