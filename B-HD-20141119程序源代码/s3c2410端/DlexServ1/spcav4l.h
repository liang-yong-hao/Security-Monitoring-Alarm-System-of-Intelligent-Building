#ifndef SPCAV4L_H
#define SPCAV4L_H 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <stdarg.h>
#include <linux/types.h>
#include <linux/videodev.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

/* V4L1 extension API */
#define VIDEO_PALETTE_JPEG  21
/* in case default setting */
#define WIDTH 352
#define HEIGHT 288
#define BPPIN 8
/* ITU-R-BT.601 PAL/NTSC */
#define MASQ 1
#define VGA MASQ
#define PAL (MASQ << 1)
#define SIF (MASQ << 2)
#define CIF (MASQ << 3)
#define QPAL (MASQ << 4)
#define QSIF (MASQ << 5)
#define QCIF (MASQ << 6)
/* fourcc palette check in preference order*/
#define JPG MASQ
#define YUV420P (MASQ << 1)
#define RGB24 (MASQ << 2)
#define RGB565 (MASQ << 3)
#define RGB32 (MASQ << 4)


/* specific for the spca5xx webcam */
enum {
	BRIDGE_SPCA505 = 0,
        BRIDGE_SPCA506,
	BRIDGE_SPCA501,
	BRIDGE_SPCA508,
	BRIDGE_SPCA504,
	BRIDGE_SPCA500,
	BRIDGE_SPCA504B,
	BRIDGE_SPCA533,
	BRIDGE_SPCA504C,
	BRIDGE_SPCA561,
	BRIDGE_SPCA536,
	BRIDGE_SONIX,
	BRIDGE_ZR364XX,
	BRIDGE_ZC3XX,
	BRIDGE_CX11646,
	BRIDGE_TV8532,
	BRIDGE_ETOMS,
	BRIDGE_SN9CXXX,
	BRIDGE_MR97311,
	BRIDGE_UNKNOW,
	MAX_BRIDGE,
};
enum {
	JPEG = 0,
	YUVY,
	YYUV,
	YUYV,
	GREY,
	GBRG,
	SN9C,
	GBGR,
	UNOW,
};

struct palette_list {
	int num;
	const char *name;
};

struct bridge_list {
	int num;
	const char *name;
};


	
struct vdIn {
	int fd;
	char *videodevice ;
	struct video_mmap vmmap;
	struct video_capability videocap;
	int mmapsize;
	struct video_mbuf videombuf;
	struct video_picture videopict;
	struct video_window videowin;
	struct video_channel videochan;	
	int cameratype ;
	char *cameraname;
	char bridge[9];
	int sizenative; // available size in jpeg
	int sizeothers;	// others palette 
	int palette; // available palette
	int norme ; // set spca506 usb video grabber
	int channel ; // set spca506 usb video grabber
	int grabMethod ;
	unsigned char *pFramebuffer;
	unsigned char *ptframe[4];
	int framelock[4];
	pthread_mutex_t grabmutex;
	int framesizeIn ;
	volatile int frame_cour;
	int bppIn;
	int  hdrwidth;
	int  hdrheight;
	int  formatIn;
	int signalquit;	
	};
	
int
init_videoIn(struct vdIn *vd,char *device,int width,int height,int format,int grabmethod);
int v4lGrab (struct vdIn *vd );
int close_v4l (struct vdIn *vd);
int setPalette (struct vdIn *vd);
int changeSize (struct vdIn *vd);

__u8 SpcaGetBrightness ( struct vdIn *vdin);
void SpcaSetBrightness ( struct vdIn *vdin, __u8 bright);
__u8 SpcaGetContrast ( struct vdIn *vdin);
void SpcaSetContrast ( struct vdIn *vdin, __u8 contrast);
__u8 SpcaGetColors ( struct vdIn *vdin);
void SpcaSetColors ( struct vdIn *vdin, __u8 colors);
__u8 SpcaGetNorme ( struct vdIn *vdin);
void SpcaSetNorme (struct vdIn *vdin,__u8 norme);
__u8 SpcaGetChannel (struct vdIn *vdin);
void SpcaSetChannel( struct vdIn * vdin,__u8 channel);

unsigned short upbright( struct vdIn *vdin);
unsigned short downbright( struct vdIn *vdin);
unsigned short upcontrast( struct vdIn *vdin);
unsigned short downcontrast( struct vdIn *vdin);

#endif /* SPCAV4L_H */
