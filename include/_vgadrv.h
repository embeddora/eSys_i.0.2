#ifndef __DRVVGA_H_
#define __DRVVGA_H_

#define MAX_REGS 4084

enum {
    CHIPSET_SAVEREGS = 0, CHIPSET_SETREGS, CHIPSET_UNLOCK, CHIPSET_LOCK,
    CHIPSET_TEST, CHIPSET_INIT, CHIPSET_SETPAGE, CHIPSET_SETRDPAGE,
    CHIPSET_SETWRPAGE, CHIPSET_SETMODE,
    CHIPSET_MODEAVAILABLE, CHIPSET_SETDISPLAYSTART,
    CHIPSET_SETLOGICALWIDTH, CHIPSET_GETMODEINFO,
    CHIPSET_BITBLT, CHIPSET_IMAGEBLT, CHIPSET_FILLBLT,
    CHIPSET_HLINELISTBLT, CHIPSET_BLTWAIT,
    CHIPSET_EXT_SET, CHIPSET_ACCEL, CHIPSET_LINEAR
};


typedef struct {
/* refresh ranges in Hz */
    unsigned min;
    unsigned max;
} RefreshRange;

extern int __svgalib_CRT_I;
extern int __svgalib_CRT_D;
extern int __svgalib_IS1_R;
extern int __svgalib_driver_report;	/* driverreport */
extern int __svgalib_videomemoryused;	/* videomemoryused */
extern int __svgalib_critical;
extern int __svgalib_chipset;
extern int __svgalib_grayscale;
extern int __svgalib_modeinfo_linearset;
extern const int __svgalib_max_modes;

void __svgalib_read_options(char **commands, char *(*func) (int ind, int mode));

/* ----------------------------------------------------------------------
   ** A modetable holds a pair of values 
   ** for each mode :
   **
   **    <mode number> <pointer to registers>
   **
   ** the last entry is marked by 
   **  
   **    <any number>  <NULL>
 */

typedef struct {
    unsigned short mode_number;
    const unsigned char *regs;
} ModeTable;

#define DISABLE_MODE	  ((unsigned char *)1)
#define OneModeEntry(res) {G##res,g##res##_regs}
#define DisableEntry(res) {G##res,DISABLE_MODE}
#define END_OF_MODE_TABLE { 0, NULL }

const unsigned char *__svgalib_mode_in_table(const ModeTable * modes, int mode);
#define LOOKUPMODE __svgalib_mode_in_table

/* ---------------------------------------------------------------------- */

extern int __svgalib_hicolor(int dac_type, int mode);
/* Enters hicolor mode - 0 for no hi, 1 for 15 bit, 2 for 16, 3 for 24 */
/* For any modes it doesn't know about, etc, it attempts to turn hicolor off. */


#define STD_DAC		0
#define HI15_DAC	1
#define HI16_DAC	2
#define TC24_DAC	3

/* ----------------------------------------------------------------------
   ** regextr.h  -  extract graphics modes and register information
   **               from C source file
 */
 
 
#endif /* __DRVVGA_H_ */
