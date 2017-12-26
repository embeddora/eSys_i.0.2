

#include "_vgalib.h"
#include "_vgadrv.h"
#include "_vga.h"

#include "_null.h"
#include "_true.h"


/* const unsigned long VideoMemoryStart = 0xA0000; */


/* BIOS mode 0Dh - 320x200x16 */
const unsigned char g320x200x16_regs[60] =
{
  0x2D, 0x27, 0x28, 0x90, 0x2B, 0x80, 0xBF, 0x1F, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x14, 0x00, 0x96, 0xB9, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x09, 0x0F, 0x00, 0x06,
    0x63
};

/* BIOS mode 0Eh - 640x200x16 */
const unsigned char g640x200x16_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0x63
};

/* BIOS mode 10h - 640x350x16 */
const unsigned char g640x350x16_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x83, 0x85, 0x5D, 0x28, 0x0F, 0x63, 0xBA, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xA3
};

/* BIOS mode 12h - 640x480x16 */
const unsigned char g640x480x16_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xEA, 0x8C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE3
};

/* BIOS mode 13h - 320x200x256 */
const unsigned char g320x200x256_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x41, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x0E,
    0x63
};

/* non-BIOS mode - 320x240x256 */
const unsigned char g320x240x256_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0D, 0x3E, 0x00, 0x41, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xEA, 0xAC, 0xDF, 0x28, 0x00, 0xE7, 0x06, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE3
};

/* non-BIOS mode - 320x400x256 */
const unsigned char g320x400x256_regs[60] =
{
  0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x9C, 0x8E, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0x63
};

/* non-BIOS mode - 360x480x256 */
const unsigned char g360x480x256_regs[60] =
{
  0x6B, 0x59, 0x5A, 0x8E, 0x5E, 0x8A, 0x0D, 0x3E, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xEA, 0xAC, 0xDF, 0x2D, 0x00, 0xE7, 0x06, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x41, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xE7
};

/* monochrome mode based on BIOS mode 12h - 640x480x2 */
#define g640x480x2_regs g640x480x16_regs

/* non BIOS mode - 720x348x2 based on mode 10h */
const unsigned char g720x348x2_regs[60] =
{
  0x6B, 0x59, 0x5A, 0x8E, 0x5E, 0x8A, 0xBF, 0x1F, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x83, 0x85, 0x5D, 0x2D, 0x0F, 0x63, 0xBA, 0xE3,
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F, 0x01, 0x00, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x20, 0x00, 0x00, 0x05, 0x0F, 0xFF,
    0x03, 0x01, 0x0F, 0x00, 0x06,
    0xA7
};



int __svgalib_CRT_I;			/* current CRT index register address */
int __svgalib_CRT_D;			/* current CRT data register address */
int __svgalib_IS1_R;			/* current input status register address */
static int modeinfo_mask = ~0;
unsigned char __svgalib_novga = 0;     /* Does not have VGA circuitry on board */


/* this def. from vga.h */
#define UNDEFINED	0

/* this def. from vga.h, too */
typedef struct {
	int width;
	int height;
	int bytesperpixel;
	int colors;
	int linewidth;		/* scanline width in bytes */
	int maxlogicalwidth;	/* maximum logical scanline width */
	int startaddressrange;	/* changeable bits set */
	int maxpixels;		/* video memory / bytesperpixel */
	int haveblit;		/* mask of blit functions available */
	int flags;		/* other flags */

	/* Extended fields: */

	int chiptype;		/* Chiptype detected */
	int memory;		/* videomemory in KB */
	int linewidth_unit;	/* Use only a multiple of this as parameter for set_logicalwidth and
				   set_displaystart */
	char *linear_aperture;	/* points to mmap secondary mem aperture of card (NULL if unavailable) */
	int aperture_size;	/* size of aperture in KB if size>=videomemory. 0 if unavail */
	void (*set_aperture_page) (int page);
	/* if aperture_size<videomemory select a memory page */
	void *extensions;	/* points to copy of eeprom for mach32 */
	/* depends from actual driver/chiptype.. etc. */
    } vga_modeinfo;
    



/* Mode table */
ModeTable vga_modes[] =
{
/* *INDENT-OFF* */
    {G640x480x2,  DISABLE_MODE},
    {G720x348x2,  DISABLE_MODE},
    {G320x200x16, g320x200x16_regs},
    {G640x200x16, g640x200x16_regs},
    {G640x350x16, g640x350x16_regs},
    {G640x480x16, g640x480x16_regs},
    {G320x200x256,g320x200x256_regs},
    {G320x240x256,g320x240x256_regs},
    {G320x400x256,g320x400x256_regs},
    {G360x480x256,g360x480x256_regs},
#ifdef G720x350x16
    {G720x350x16, g720x350x16_regs},
#endif
    END_OF_MODE_TABLE
/* *INDENT-ON* */
};




/* saved text mode palette values */
static unsigned char text_red[256];
static unsigned char text_green[256];
static unsigned char text_blue[256];

/* saved graphics mode palette values */
static unsigned char graph_red[256];
static unsigned char graph_green[256];
static unsigned char graph_blue[256];

static const unsigned char default_red[256]
=
{0, 0, 0, 0, 42, 42, 42, 42, 21, 21, 21, 21, 63, 63, 63, 63,
 0, 5, 8, 11, 14, 17, 20, 24, 28, 32, 36, 40, 45, 50, 56, 63,
 0, 16, 31, 47, 63, 63, 63, 63, 63, 63, 63, 63, 63, 47, 31, 16,
 0, 0, 0, 0, 0, 0, 0, 0, 31, 39, 47, 55, 63, 63, 63, 63,
 63, 63, 63, 63, 63, 55, 47, 39, 31, 31, 31, 31, 31, 31, 31, 31,
 45, 49, 54, 58, 63, 63, 63, 63, 63, 63, 63, 63, 63, 58, 54, 49,
 45, 45, 45, 45, 45, 45, 45, 45, 0, 7, 14, 21, 28, 28, 28, 28,
 28, 28, 28, 28, 28, 21, 14, 7, 0, 0, 0, 0, 0, 0, 0, 0,
 14, 17, 21, 24, 28, 28, 28, 28, 28, 28, 28, 28, 28, 24, 21, 17,
 14, 14, 14, 14, 14, 14, 14, 14, 20, 22, 24, 26, 28, 28, 28, 28,
 28, 28, 28, 28, 28, 26, 24, 22, 20, 20, 20, 20, 20, 20, 20, 20,
 0, 4, 8, 12, 16, 16, 16, 16, 16, 16, 16, 16, 16, 12, 8, 4,
 0, 0, 0, 0, 0, 0, 0, 0, 8, 10, 12, 14, 16, 16, 16, 16,
 16, 16, 16, 16, 16, 14, 12, 10, 8, 8, 8, 8, 8, 8, 8, 8,
 11, 12, 13, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 13, 12,
 11, 11, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0};
static const unsigned char default_green[256]
=
{0, 0, 42, 42, 0, 0, 21, 42, 21, 21, 63, 63, 21, 21, 63, 63,
 0, 5, 8, 11, 14, 17, 20, 24, 28, 32, 36, 40, 45, 50, 56, 63,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 31, 47, 63, 63, 63, 63,
 63, 63, 63, 63, 63, 47, 31, 16, 31, 31, 31, 31, 31, 31, 31, 31,
 31, 39, 47, 55, 63, 63, 63, 63, 63, 63, 63, 63, 63, 55, 47, 39,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 49, 54, 58, 63, 63, 63, 63,
 63, 63, 63, 63, 63, 58, 54, 49, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 7, 14, 21, 29, 28, 28, 28, 28, 28, 28, 28, 28, 21, 14, 7,
 14, 14, 14, 14, 14, 14, 14, 14, 14, 17, 21, 24, 28, 28, 28, 28,
 28, 28, 28, 28, 28, 24, 21, 17, 20, 20, 20, 20, 20, 20, 20, 20,
 20, 22, 24, 26, 28, 28, 28, 28, 28, 28, 28, 28, 28, 26, 24, 22,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 12, 16, 16, 16, 16,
 16, 16, 16, 16, 16, 12, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8,
 8, 10, 12, 14, 16, 16, 16, 16, 16, 16, 16, 16, 16, 14, 12, 10,
 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 13, 15, 16, 16, 16, 16,
 16, 16, 16, 16, 16, 15, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0};
static const unsigned char default_blue[256]
=
{0, 42, 0, 42, 0, 42, 0, 42, 21, 63, 21, 63, 21, 63, 21, 63,
 0, 5, 8, 11, 14, 17, 20, 24, 28, 32, 36, 40, 45, 50, 56, 63,
 63, 63, 63, 63, 63, 47, 31, 16, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 16, 31, 47, 63, 63, 63, 63, 63, 63, 63, 63, 63, 55, 47, 39,
 31, 31, 31, 31, 31, 31, 31, 31, 31, 39, 47, 55, 63, 63, 63, 63,
 63, 63, 63, 63, 63, 58, 54, 49, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 49, 54, 58, 63, 63, 63, 63, 28, 28, 28, 28, 28, 21, 14, 7,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 14, 21, 28, 28, 28, 28,
 28, 28, 28, 28, 28, 24, 21, 17, 14, 14, 14, 14, 14, 14, 14, 14,
 14, 17, 21, 24, 28, 28, 28, 28, 28, 28, 28, 28, 28, 26, 24, 22,
 20, 20, 20, 20, 20, 20, 20, 20, 20, 22, 24, 26, 28, 28, 28, 28,
 16, 16, 16, 16, 16, 12, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 4, 8, 12, 16, 16, 16, 16, 16, 16, 16, 16, 16, 14, 12, 10,
 8, 8, 8, 8, 8, 8, 8, 8, 8, 10, 12, 14, 16, 16, 16, 16,
 16, 16, 16, 16, 16, 15, 13, 12, 11, 11, 11, 11, 11, 11, 11, 11,
 11, 12, 13, 15, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0};


static unsigned char text_regs[MAX_REGS];	/* VGA registers for saved text mode */




/* this is from vga.c */
static int prv_mode = TEXT;	/* previous video mode      */
static int flip_mode = TEXT;	/* flipped video mode       */

int CM = TEXT;			/* current video mode       */
struct info CI;			/* current video parameters */
int COL;			/* current color            */



static int initialized = 0;	/* flag: initialize() called ?  */
static int flip = 0;		/* flag: executing vga_flip() ? */

/* svgalib additions: */

unsigned char *__svgalib_graph_mem;

int __svgalib_chipset = UNDEFINED;
int __svgalib_driver_report = 1;
	/* report driver used after chipset detection */
int __svgalib_videomemoryused = -1;
int __svgalib_modeX = 0;	/* true after vga_setmodeX() */
int __svgalib_modeflags = 0;	/* copy of flags for current mode */
int __svgalib_critical = 0;	/* indicates blitter is busy */
int __svgalib_screenon = 1;	/* screen visible if != 0 */
RefreshRange __svgalib_horizsync =
{31500U, 0U};			/* horz. refresh (Hz) min, max */
RefreshRange __svgalib_vertrefresh =
{50U, 70U};			/* vert. refresh (Hz) min, max */
int __svgalib_grayscale = 0;	/* grayscale vs. color mode */
int __svgalib_modeinfo_linearset = 0;	/* IS_LINEAR handled via extended vga_modeinfo */


static int lastmodenumber = __GLASTMODE;	/* Last defined mode */

static int currentlogicalwidth;
static int currentdisplaystart;



/* this is from vga.c, too */
int __svgalib_default_mode = 0;

struct info infotable[] =
{
    {80, 25, 16, 160, 0},	/* VGAlib VGA modes */
    {320, 200, 16, 40, 0},
    {640, 200, 16, 80, 0},
    {640, 350, 16, 80, 0},
    {640, 480, 16, 80, 0},
    {320, 200, 256, 320, 1},
    {320, 240, 256, 80, 0},
    {320, 400, 256, 80, 0},
    {360, 480, 256, 90, 0},
    {640, 480, 2, 80, 0},

    {640, 480, 256, 640, 1},	/* VGAlib SVGA modes */
    {800, 600, 256, 800, 1},
    {1024, 768, 256, 1024, 1},
    {1280, 1024, 256, 1280, 1},

    {320, 200, 1 << 15, 640, 2},	/* Hicolor/truecolor modes */
    {320, 200, 1 << 16, 640, 2},
    {320, 200, 1 << 24, 320 * 3, 3},
    {640, 480, 1 << 15, 640 * 2, 2},
    {640, 480, 1 << 16, 640 * 2, 2},
    {640, 480, 1 << 24, 640 * 3, 3},
    {800, 600, 1 << 15, 800 * 2, 2},
    {800, 600, 1 << 16, 800 * 2, 2},
    {800, 600, 1 << 24, 800 * 3, 3},
    {1024, 768, 1 << 15, 1024 * 2, 2},
    {1024, 768, 1 << 16, 1024 * 2, 2},
    {1024, 768, 1 << 24, 1024 * 3, 3},
    {1280, 1024, 1 << 15, 1280 * 2, 2},
    {1280, 1024, 1 << 16, 1280 * 2, 2},
    {1280, 1024, 1 << 24, 1280 * 3, 3},

    {800, 600, 16, 100, 0},	/* SVGA 16-color modes */
    {1024, 768, 16, 128, 0},
    {1280, 1024, 16, 160, 0},

    {720, 348, 2, 90, 0},	/* Hercules emulation mode */

    {320, 200, 1 << 24, 320 * 4, 4},
    {640, 480, 1 << 24, 640 * 4, 4},
    {800, 600, 1 << 24, 800 * 4, 4},
    {1024, 768, 1 << 24, 1024 * 4, 4},
    {1280, 1024, 1 << 24, 1280 * 4, 4},

    {1152, 864, 16, 144, 0},
    {1152, 864, 256, 1152, 1},
    {1152, 864, 1 << 15, 1152 * 2, 2},
    {1152, 864, 1 << 16, 1152 * 2, 2},
    {1152, 864, 1 << 24, 1152 * 3, 3},
    {1152, 864, 1 << 24, 1152 * 4, 4},

    {1600, 1200, 16, 200, 0},
    {1600, 1200, 256, 1600, 1},
    {1600, 1200, 1 << 15, 1600 * 2, 2},
    {1600, 1200, 1 << 16, 1600 * 2, 2},
    {1600, 1200, 1 << 24, 1600 * 3, 3},
    {1600, 1200, 1 << 24, 1600 * 4, 4},

    {0, 0, 0, 0, 0},		/* 16 user definable modes */
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}

};

#define MAX_MODES (sizeof(infotable) / sizeof(struct info))


/// own interface :
void disable_interrupt(void);
void enable_interrupt();
void savepalette(unsigned char *, unsigned char *,unsigned char *);
void setcoloremulation(void);





/* Fill in chipset-specific modeinfo */
void getmodeinfo(int mode, vga_modeinfo * modeinfo)
{
    if (modeinfo->bytesperpixel == 1) {		/* 320x200x256 linear mode */
	modeinfo->maxpixels = 65536;
	modeinfo->startaddressrange = 0xffff;
    } else
	switch (modeinfo->colors) {
	case 16:		/* 4-plane 16 color mode */
	    modeinfo->maxpixels = 65536 * 8;
	    modeinfo->startaddressrange = 0x7ffff;
	    break;
	case 256:		/* 4-plane 256 color mode */
	    modeinfo->maxpixels = 65536 * 4;
	    modeinfo->startaddressrange = 0x3ffff;
	    break;
	}
    modeinfo->maxlogicalwidth = 2040;
    modeinfo->haveblit = 0;
    modeinfo->flags &= ~(IS_INTERLACED | HAVE_RWPAGE);
}

void nothing(void)
{
}

int saveregs(unsigned char regs[])
{
    return 0;
}

void setregs(const unsigned char regs[], int mode)
{
}

/* Return nonzero if mode available */

int modeavailable(int mode)
{
    const unsigned char *regs;

    regs = LOOKUPMODE(vga_modes, mode);
    if (regs != NULL && regs != DISABLE_MODE)
    {
        _DisplayPuts("modeavail., returning STDVGADRV\n");
	return STDVGADRV;
    }
    _DisplayPuts("modeavail., returning 0\n");
    return 0;
}


/* Set a mode */

static int lastmode;

int setmode(int mode, int prv_mode)
{
/* standard VGA driver: setmode */
    const unsigned char *regs;

    if (mode == TEXT)
	return 0;		/* Do nothing. */

    regs = LOOKUPMODE(vga_modes, mode);
    if (regs == NULL || regs == DISABLE_MODE)
	return 1;
    lastmode = mode;
    __svgalib_setregs(regs);
    return 0;
}


vga_modeinfo *vga_getmodeinfo(int mode)
{
    static vga_modeinfo modeinfo;
    int is_modeX = (CM == mode) && MODEX;

    modeinfo.linewidth = infotable[mode].xbytes;
    __svgalib_getchipset();
    if (mode > vga_lastmodenumber())
	return NULL;
    modeinfo.width = infotable[mode].xdim;
    modeinfo.height = infotable[mode].ydim;
    modeinfo.bytesperpixel = infotable[mode].bytesperpixel;
    modeinfo.colors = infotable[mode].colors;
    if (is_modeX) {
	modeinfo.linewidth = modeinfo.width / 4;
	modeinfo.bytesperpixel = 0;
    }
    if (mode == TEXT) {
	modeinfo.flags = HAVE_EXT_SET;
	return &modeinfo;
    }
    modeinfo.flags = 0;
    if ((STDVGAMODE(mode) && mode != G320x200x256) || is_modeX)
//	__svgalib_vga_driverspecs.getmodeinfo(mode, &modeinfo);
	getmodeinfo(mode, &modeinfo);
    else
	/* Get chipset specific info for SVGA modes and */
	/* 320x200x256 (chipsets may support more pages) */
	chipset_getmodeinfo(mode, &modeinfo);

    if (modeinfo.colors == 256 && modeinfo.bytesperpixel == 0)
	modeinfo.flags |= IS_MODEX;
    if (mode > __GLASTMODE)
	modeinfo.flags |= IS_DYNAMICMODE;

    /* Maskout CAPABLE_LINEAR if requested by config file */
    modeinfo.flags &= modeinfo_mask;

    /* If all needed info is here, signal if linear support has been enabled */
    if ((modeinfo.flags & (CAPABLE_LINEAR | EXT_INFO_AVAILABLE)) ==
	(CAPABLE_LINEAR | EXT_INFO_AVAILABLE)) {
	modeinfo.flags |= __svgalib_modeinfo_linearset;
    }

#ifdef BACKGROUND
    if (__svgalib_runinbackground) /* these cannot be provided if we are really in background */
	modeinfo.flags &= ~HAVE_RWPAGE;
#endif

    return &modeinfo;
}


/* Set display start */
void setdisplaystart(int address)
{
    vga_modeinfo *modeinfo;
    modeinfo = vga_getmodeinfo(lastmode);
    if (modeinfo->bytesperpixel == 0)	/* not 320x200x256 linear */
	switch (modeinfo->colors) {
	case 16:		/* planar 16-color mode */
	    inb(0x3da);
	    outb(0x3c0, 0x13 + 0x20);
	    outb(0x3c0, (inb(0x3c1) & 0xf0) | (address & 7));
	    /* write sa0-2 to bits 0-2 */
	    address >>= 3;
	    break;
	case 256:		/* planar 256-color mode */
	    inb(0x3da);
	    outb(0x3c0, 0x13 + 0x20);
	    outb(0x3c0, (inb(0x3c1) & 0xf0) | ((address & 3) << 1));
	    /* write sa0-1 to bits 1-2 */
	    address >>= 2;
	    break;
	}
    outw(0x3d4, 0x0d + (address & 0x00ff) * 256);	/* sa0-sa7 */
    outw(0x3d4, 0x0c + (address & 0xff00));	/* sa8-sa15 */
}

void setlogicalwidth(int width)
{
    outw(0x3d4, 0x13 + (width >> 3) * 256);	/* lw3-lw11 */
}

// substitute 
int vgadrv_init(int _x, int _y, int _z)
{
    return 0;
};


const unsigned char *  __svgalib_mode_in_table(const ModeTable * modes, int mode)
{
    while (modes->regs != NULL)
	{
_DisplayPuts("modes->regs != NULL, modenumber = 0x");
_DisplayWriteHexOfDepth(modes->mode_number, 4);

	if (modes->mode_number == mode)
	    return modes->regs;
	modes++;
	}

    {
_DisplayPuts("modes->regs == NULL ");
    }
    return NULL;
}



int vga_lastmodenumber(void)
{
    __svgalib_getchipset();
    return lastmodenumber;
}

void __svgalib_delay(void)
{
    int i;
    for (i = 0; i < 10; i++);
}

int __svgalib_getchipset(void)
{


    if (CHIPSET == UNDEFINED) {
	CHIPSET = VGA;		/* Protect against recursion */
	
// here was .. 

	if (vga_test())
	    CHIPSET = VGA;
	else
	    /* else */
	{
	    _DisplayPuts("svgalib: Cannot find EGA or VGA graphics device.\n");
	    for ( ; ; ) ;
	}
#if (0)	
	__svgalib_setpage = __svgalib_setpage;
	__svgalib_setrdpage = __svgalib_setrdpage;
	__svgalib_setwrpage = __svgalib_setwrpage;
#endif /* (0) */
    }
    return CHIPSET;
}


int vga_test(void)
{
    unsigned char save, back;

    /* Check if a DAC is present */
    save = inb(PEL_IW);
    __svgalib_delay();
    outb(PEL_IW, ~save);
    __svgalib_delay();
    back = inb(PEL_IW);
    __svgalib_delay();
    outb(PEL_IW, save);
    save = ~save;
    if (back == save) {
	vgadrv_init(0, 0, 0);
	return 1;
    }
    return 0;
}






static void initialize(void)
{
    int i;


_DisplayPuts("1:  initialize()\n");
    disable_interrupt();	/* Is reenabled later by set_texttermio */

    __svgalib_getchipset();		/* make sure a chipset has been selected */
    
//    chipset_unlock();

//    __vga_mmap();

// here he checks allocated graph. mem. range 
//    if ((long) GM < 0) {
//	_DisplayPuts("svgalib: mmap error \n");
//	for ( ; ; ) ;
//    }


_DisplayPuts("2:  initialize()\n"); 


    /* disable video */
    vga_screenoff();
    
_DisplayPuts("3:  initialize()\n"); 

    /* Sanity check: (from painful experience) */
//!!!    i = __svgalib_saveregs(text_regs); // it's  getting dark here 
    
    if (i > MAX_REGS) {
	_DisplayPuts("svgalib: FATAL internal error:");
	for ( ; ; ) ;
    }
    
_DisplayPuts("4:  initialize()\n");
    /* save text mode palette - first select palette index 0 */
    if(!__svgalib_novga)
	port_out(0, PEL_IR);

    /* read RGB components - index is autoincremented */
    savepalette(text_red, text_green, text_blue);

    /* shift to color emulation */
    setcoloremulation();

    
    initialized = 1;

#if (0)
WHATS THIS 
    /* do our own interrupt handling */
    for (i = 0; i < sizeof(sig2catch); i++) {
	siga.sa_handler = signal_handler;
	siga.sa_flags = 0;
	zero_sa_mask(&(siga.sa_mask));
	sigaction((int) sig2catch[i], &siga, old_signal_handler + i);
    }
#endif /* (0) */    

    /* vga_unlockvc(); */
}



void disable_interrupt(void)
{


    // cli ... 
}

void enable_interrupt(void)
{

    // sti .. 
}



int vga_setcolor(int color)
{
    switch (CI.colors) {
    case 2:
	if (color != 0)
	    color = 15;
    case 16:			/* update set/reset register */
	port_out(0x00, GRA_I);
	port_out((color & 15), GRA_D);
	break;
    default:
	COL = color;
	break;
    }
    return 0;
}

int vga_screenoff(void)
{
    int tmp = 0;

    SCREENON = 0;


//+++ ATTENTION: here was an unclear copndition @
    if (0) {
	tmp = screenoff();
    } else {
	/* turn off screen for faster VGA memory acces */
	/* Disable video output */
    }

    return tmp;
}


int vga_screenon(void)
{
    int tmp = 0;

    SCREENON = 1;
    if(__svgalib_novga) return 0; 

//+++ ATTENTION: here was an unclear copndition @

    if (0) {
	tmp = screenon();
    } else {
	/* turn screen back on */
	if (CHIPSET != EGA) {
	    port_out(0x01, SEQ_I);
	    port_out(port_in(SEQ_D) & 0xDF, SEQ_D);
	}
/* #ifdef DISABLE_VIDEO_OUTPUT */
	/* enable video output */
	port_in(__svgalib_IS1_R);
	__svgalib_delay();
	port_out(0x20, ATT_IW);
/* #endif */
    }


    return 0;
}


int __svgalib_saveregs(unsigned char *regs)
{
    int i;

    /* save VGA registers */
    for (i = 0; i < CRT_C; i++) {
	port_out(i, __svgalib_CRT_I);
	regs[CRT + i] = port_in(__svgalib_CRT_D);
    }
    for (i = 0; i < ATT_C; i++) {
	port_in(__svgalib_IS1_R);
	__svgalib_delay();
	port_out(i, ATT_IW);
	__svgalib_delay();
	regs[ATT + i] = port_in(ATT_R);
	__svgalib_delay();
    }
    for (i = 0; i < GRA_C; i++) {
	port_out(i, GRA_I);
	regs[GRA + i] = port_in(GRA_D);
    }
    for (i = 0; i < SEQ_C; i++) {
	port_out(i, SEQ_I);
	regs[SEQ + i] = port_in(SEQ_D);
    }
    regs[MIS] = port_in(MIS_R);

    i = chipset_saveregs(regs);	/* save chipset-specific registers */
    /* i : additional registers */
    if (!SCREENON) {		/* We turned off the screen */
	port_in(__svgalib_IS1_R);
	__svgalib_delay();
	port_out(0x20, ATT_IW);
    }
    return CRT_C + ATT_C + GRA_C + SEQ_C + 1 + i;
}


int __svgalib_setregs(const unsigned char *regs)
{
    int i;

    if(__svgalib_novga) return 1;

    /* update misc output register */
    port_out(regs[MIS], MIS_W);

    /* synchronous reset on */
    port_out(0x00, SEQ_I);
    port_out(0x01, SEQ_D);

    /* write sequencer registers */
    port_out(1, SEQ_I);
    port_out(regs[SEQ + 1] | 0x20, SEQ_D);
    for (i = 2; i < SEQ_C; i++) {
	port_out(i, SEQ_I);
	port_out(regs[SEQ + i], SEQ_D);
    }

    /* synchronous reset off */
    port_out(0x00, SEQ_I);
    port_out(0x03, SEQ_D);

    if (__svgalib_chipset != EGA) {
	/* deprotect CRT registers 0-7 */
	port_out(0x11, __svgalib_CRT_I);
	port_out(port_in(__svgalib_CRT_D) & 0x7F, __svgalib_CRT_D);
    }
    /* write CRT registers */
    for (i = 0; i < CRT_C; i++) {
	port_out(i, __svgalib_CRT_I);
	port_out(regs[CRT + i], __svgalib_CRT_D);
    }

    /* write graphics controller registers */
    for (i = 0; i < GRA_C; i++) {
	port_out(i, GRA_I);
	port_out(regs[GRA + i], GRA_D);
    }

    /* write attribute controller registers */
    for (i = 0; i < ATT_C; i++) {
	port_in(__svgalib_IS1_R);		/* reset flip-flop */
	__svgalib_delay();
	port_out(i, ATT_IW);
	__svgalib_delay();
	port_out(regs[ATT + i], ATT_IW);
	__svgalib_delay();
    }

    return 0;
}


void savepalette(unsigned char *red, unsigned char *green,
			unsigned char *blue)
{
    int i;

//... here was 

    /* save graphics mode palette - first select palette index 0 */
    port_out(0, PEL_IR);

    /* read RGB components - index is autoincremented */
    for (i = 0; i < 256; i++)
    {
	__svgalib_delay();
	*(red++) = port_in(PEL_D);
	__svgalib_delay();
	*(green++) = port_in(PEL_D);
	__svgalib_delay();
	*(blue++) = port_in(PEL_D);
    }
}


void restorepalette(const unsigned char *red,
		   const unsigned char *green, const unsigned char *blue)
{
    int i;

    /* restore saved palette */
    port_out(0, PEL_IW);

    /* read RGB components - index is autoincremented */
    for (i = 0; i < 256; i++) {
	__svgalib_delay();
	port_out(*(red++), PEL_D);
	__svgalib_delay();
	port_out(*(green++), PEL_D);
	__svgalib_delay();
	port_out(*(blue++), PEL_D);
    }
}

void setcoloremulation(void)
{
    /* shift to color emulation */
    __svgalib_CRT_I = CRT_IC;
    __svgalib_CRT_D = CRT_DC;
    __svgalib_IS1_R = IS1_RC;
    if (CHIPSET != EGA && !__svgalib_novga)  
	port_out(port_in(MIS_R) | 0x01, MIS_W);
}



int vga_clear(void)
{
    vga_screenoff();
    if (MODEX)
	goto modeX;
    switch (CM) {
    case G320x200x256:
    case G320x240x256:
    case G320x400x256:
    case G360x480x256:
      modeX:
        
	/* write to all planes */
	port_out(0x02, SEQ_I);
	port_out(0x0F, SEQ_D);

	/* clear video memory */
	memset(GM, 0, 65536);
	break;

    default:
	switch (CI.colors) {
	case 2:
	case 16:
	    vga_setcolor(0);

	    /* write to all bits */
	    port_out(0x08, GRA_I);
	    port_out(0xFF, GRA_D);

	default:
	    {
		int i;
		int pages = (CI.ydim * CI.xbytes + 65535) >> 16;
#if defined(CONFIG_ALPHA_JENSEN)
		int j;
#endif

		for (i = 0; i < pages; ++i) {
//		    vga_setpage(i);

#if defined(CONFIG_ALPHA_JENSEN)
		    for (j = 0; j < 65536; j += 2)
			gr_writew(0, j);
#else
		    /* clear video memory */
		    memset(GM, 0, 65536);
#endif
		}
	    }
	    break;
	}
	break;
    }

    vga_setcolor(15);
    vga_screenon();

    return 0;
}


int vga_setmode(int mode)
{

_DisplayPuts("1:  vga_setmode()\n");
    if (!initialized)
	initialize();
_DisplayPuts("2:  vga_setmode()\n");
    if (mode != TEXT && !chipset_modeavailable(mode))
       {
	return -1;
       }
       
_DisplayPuts("3:  vga_setmode()\n");;
/*    if (!flip)
   vga_lockvc(); */
    disable_interrupt();

    prv_mode = CM;
    CM = mode;

    /* disable video */
    vga_screenoff();

_DisplayPuts("4:  vga_setmode()\n");
    if(!__svgalib_novga)
    {
    /* Should be more robust (eg. grabbed X modes) */
	if (__svgalib_getchipset() == ET4000
	     && prv_mode != G640x480x256
	     && SVGAMODE(prv_mode))
	    chipset_setmode(G640x480x256, prv_mode);

	/* This is a hack to get around the fact that some C&T chips
	 * are programmed to ignore syncronous resets. So if we are
	 * a C&T wait for retrace start
	 */
	if (__svgalib_getchipset() == CHIPS) {
	   while (((port_in(__svgalib_IS1_R)) & 0x08) == 0x08 );/* wait VSync off */
	   while (((port_in(__svgalib_IS1_R)) & 0x08) == 0 );   /* wait VSync on  */
	   port_outw(0x07,0x3C4);         /* reset hsync - just in case...  */
	}
    }

_DisplayPuts("5:  vga_setmode()\n");
    {
	/* Setting a graphics mode. */


	if (SVGAMODE(prv_mode)) {
	    /* The current mode is an SVGA mode, and we now want to */
	    /* set a standard VGA mode. Make sure the extended regs */
	    /* are restored. */
	    /* Also used when setting another SVGA mode to hopefully */
	    /* eliminate lock-ups. */
//	    vga_setpage(0);
	    chipset_setregs(text_regs, mode);
	    /* restore old extended regs */
	}
	/* shift to color emulation */
	setcoloremulation();

_DisplayPuts("6:  vga_setmode()\n");

	CI.xdim = infotable[mode].xdim;
	CI.ydim = infotable[mode].ydim;
	CI.colors = infotable[mode].colors;
	CI.xbytes = infotable[mode].xbytes;
	CI.bytesperpixel = infotable[mode].bytesperpixel;

	chipset_setmode(mode, prv_mode);
	MODEX = 0;

_DisplayPuts("7:  vga_setmode()\n");
	/* Set default claimed memory (moved here from initialize - Michael.) */
	if (mode == G320x200x256)
	    VMEM = 65536;
	else if (STDVGAMODE(mode))
	    VMEM = 256 * 1024;	/* Why always 256K ??? - Michael */
	else {
	    vga_modeinfo *modeinfo;

	    modeinfo = vga_getmodeinfo(mode);
	    VMEM = modeinfo->linewidth * modeinfo->height;
            CI.xbytes = modeinfo->linewidth;
	}
_DisplayPuts("8:  vga_setmode()\n");
	if (!flip) {
	    /* set default palette */
	    if (CI.colors <= 256)
		restorepalette(default_red, default_green, default_blue);

	    /* clear screen (sets current color to 15) */
//	    __svgalib_currentpage = -1;
	    vga_clear();

	    if (SVGAMODE(__svgalib_cur_mode))
//		vga_setpage(0);
		;
	}
_DisplayPuts("9:  vga_setmode()\n");	
//	__svgalib_currentpage = -1;
	currentlogicalwidth = CI.xbytes;
	currentdisplaystart = 0;
#if (0)
#define MODESWITCHDELAY 150000
	usleep(MODESWITCHDELAY);	/* wait for signal to stabilize */
#else
	{
	    unsigned long i,k;
	    i = 20;
	    while(i--)
	    {
		k = 20;
		while(k--)
		{
		    ;
		}
	    }	
	}
_DisplayPuts("10:  vga_setmode()\n");		
#endif /* (0) */

	/* enable video */
	if (!flip)
	    vga_screenon();

	{
	    vga_modeinfo *modeinfo;
	    modeinfo = vga_getmodeinfo(mode);
	    MODEX = ((MODEFLAGS = modeinfo->flags) & IS_MODEX);
	}
_DisplayPuts("11:  vga_setmode()\n");		
	    
    }

_DisplayPuts("12:  vga_setmode()\n");		

/*    if (!flip)
   vga_unlockvc(); */
    return 0;
}

