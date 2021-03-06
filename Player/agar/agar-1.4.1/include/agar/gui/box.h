/*	Public domain	*/

#ifndef _AGAR_WIDGET_BOX_H_
#define _AGAR_WIDGET_BOX_H_

#include <agar/gui/widget.h>

#include <agar/gui/begin.h>

enum ag_box_type {
	AG_BOX_HORIZ,
	AG_BOX_VERT
};

typedef struct ag_box {
	struct ag_widget wid;
	enum ag_box_type type;
	Uint flags;
#define AG_BOX_HOMOGENOUS	0x01	/* Divide space evenly */
#define AG_BOX_HFILL		0x02	/* Expand to fill available width */
#define AG_BOX_VFILL		0x04	/* Expand to fill available height */
#define AG_BOX_FRAME		0x08	/* Display a frame by default */
#define AG_BOX_EXPAND		(AG_BOX_HFILL|AG_BOX_VFILL)
	int padding;			/* Padding around widgets */
	int spacing;			/* Spacing between widgets */
	int depth;			/* Depth of frame (for AG_BOX_FRAME) */
	char *caption;			/* Caption text */
	int  sCaption;			/* Caption text surface */
	AG_Rect rCaption;		/* Caption text location */
} AG_Box;

#define AGBOX(p) ((AG_Box *)(p))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_WidgetClass agBoxClass;
extern DECLSPEC AG_Box *AG_BoxNew(void *, enum ag_box_type, Uint);
extern DECLSPEC void AG_BoxSetLabel(AG_Box *, const char *, ...);
extern DECLSPEC void AG_BoxSetLabelS(AG_Box *, const char *);
extern DECLSPEC void AG_BoxSetHomogenous(AG_Box *, int);
extern DECLSPEC void AG_BoxSetPadding(AG_Box *, int);
extern DECLSPEC void AG_BoxSetSpacing(AG_Box *, int);
extern DECLSPEC void AG_BoxSetDepth(AG_Box *, int);
extern DECLSPEC void AG_BoxSetType(AG_Box *, enum ag_box_type);
#define AG_BoxNewHoriz(p,f) AG_BoxNew((p),AG_BOX_HORIZ,(f))
#define AG_BoxNewVert(p,f) AG_BoxNew((p),AG_BOX_VERT,(f))

static __inline__ AG_Box *
AG_BoxNewHorizNS(void *p, Uint flags)
{
	AG_Box *hBox = AG_BoxNewHoriz(p, flags);
	AG_BoxSetSpacing(hBox, 0);
	AG_BoxSetPadding(hBox, 0);
	return (hBox);
}

static __inline__ AG_Box *
AG_BoxNewVertNS(void *p, Uint flags)
{
	AG_Box *vBox = AG_BoxNewVert(p, flags);
	AG_BoxSetSpacing(vBox, 0);
	AG_BoxSetPadding(vBox, 0);
	return (vBox);
}
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_WIDGET_BOX_H_ */
