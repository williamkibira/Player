/*	Public domain	*/

#ifndef _AGAR_WIDGET_TLIST_H_
#define _AGAR_WIDGET_TLIST_H_

#include <agar/gui/scrollbar.h>
#include <agar/gui/menu.h>
#include <agar/gui/label.h>

#include <agar/gui/begin.h>

#define AG_TLIST_LABEL_MAX AG_LABEL_MAX
#define AG_TLIST_ARGS_MAX 8

typedef struct ag_tlist_popup {
	const char *iclass;		/* Apply to items of this class */
	AG_Menu *menu;
	AG_MenuItem *item;
	AG_Window *panel;
	AG_TAILQ_ENTRY(ag_tlist_popup) popups;
} AG_TlistPopup;

typedef struct ag_tlist_item {
	int selected;				/* Effective selection */
	AG_Surface *iconsrc;			/* Source icon (or NULL) */
	int icon;				/* Cached icon surface */
	void *p1;				/* User-supplied pointer */
	const char *cat;			/* User-supplied category */
	char text[AG_TLIST_LABEL_MAX];		/* Label text */
	int label;				/* Cached label surface */
	Uint8 depth;				/* Depth in tree */
	Uint8 flags;
#define AG_TLIST_EXPANDED	  0x01	/* Child items visible (tree) */
#define AG_TLIST_HAS_CHILDREN	  0x02	/* Child items exist (tree) */
#define AG_TLIST_DYNICON	  0x04	/* Use a copy of iconsrc */
#define AG_TLIST_NO_SELECT	  0x08	/* Item is not selectable */
#define AG_TLIST_NO_POPUP	  0x10	/* Disable popups for item */
#define AG_TLIST_VISIBLE_CHILDREN AG_TLIST_EXPANDED

	AG_TAILQ_ENTRY(ag_tlist_item) items;	/* Items in list */
	AG_TAILQ_ENTRY(ag_tlist_item) selitems;	/* Saved selection state */
} AG_TlistItem;

AG_TAILQ_HEAD(ag_tlist_itemq, ag_tlist_item);

typedef struct ag_tlist {
	struct ag_widget wid;
	Uint flags;
#define AG_TLIST_MULTI		0x001	/* Multiple selections (ctrl/shift) */
#define AG_TLIST_MULTITOGGLE	0x002	/* Multiple toggle-style selections */
#define AG_TLIST_POLL		0x004	/* Generate tlist-poll events */
#define AG_TLIST_TREE		0x010	/* Hack to display trees */
#define AG_TLIST_HFILL		0x020
#define AG_TLIST_VFILL		0x040
#define AG_TLIST_NOSELSTATE	0x100	/* Don't preserve sel state in poll */
#define AG_TLIST_SCROLLTOSEL	0x200	/* Scroll to initial selection */
#define AG_TLIST_REFRESH	0x400	/* Repopulate display (for polling) */
#define AG_TLIST_EXPAND		(AG_TLIST_HFILL|AG_TLIST_VFILL)

	void *selected;			/* Default `selected' binding */
	int wHint, hHint;		/* Size hint */
	int wSpace;			/* Icon/text spacing */

	int item_h;			/* Item height */
	int icon_w;			/* Item icon width */
	void *dblclicked;		/* Used by double click */
	struct ag_tlist_itemq items;	/* Current Items */
	struct ag_tlist_itemq selitems;	/* Saved item state */
	int nitems;			/* Current item count */
	int nvisitems;			/* Visible item count */
	AG_Scrollbar *sbar;		/* Vertical scrollbar */
	AG_TAILQ_HEAD_(ag_tlist_popup) popups; /* Popup menus */
	int (*compare_fn)(const AG_TlistItem *, const AG_TlistItem *);
	AG_Event *popupEv;		/* Popup menu hook */
	AG_Event *changedEv;		/* Selection change hook */
	AG_Event *dblClickEv;		/* Double click hook */
	AG_Timeout incTo, decTo;	/* Keyboard motion timers */
	Uint32 wheelTicks;		/* For wheel acceleration */
	int wRow;			/* Row width */
	AG_Rect r;			/* View area */
	AG_Timeout refreshTo;		/* Autorefresh timer */
	int rOffs;			/* Row display offset */
} AG_Tlist;

#define AG_TLIST_FOREACH(it, tl) AG_TAILQ_FOREACH(it, &(tl)->items, items)

#define AG_TLIST_FOREACH_ITEM(p, tl, it, t) for((it) = AG_TAILQ_FIRST(&(tl)->items), (p) = (it)!=NULL ? (struct t *)(it)->p1 : NULL; (it) != AG_TAILQ_END(&(tl)->children) && (it)->p1 != NULL; (it) = AG_TAILQ_NEXT((it), cobjs), (p) = (it)!=NULL ? (struct t *)(it)->p1 : NULL)

#define AG_TLIST_ITEM(n) AG_TlistSelectedItemPtr(AG_PTR(n))

/* Begin generated block */
__BEGIN_DECLS
extern DECLSPEC AG_WidgetClass agTlistClass;
extern DECLSPEC AG_Tlist *AG_TlistNew(void *, Uint);
extern DECLSPEC AG_Tlist *AG_TlistNewPolled(void *, Uint, AG_EventFn, const char *, ...);
extern DECLSPEC void AG_TlistSizeHint(AG_Tlist *, const char *, int);
extern DECLSPEC void AG_TlistSizeHintPixels(AG_Tlist *, int, int);
extern DECLSPEC void AG_TlistSizeHintLargest(AG_Tlist *, int);
#define AG_TlistPrescale AG_TlistSizeHint
extern DECLSPEC void AG_TlistSetItemHeight(AG_Tlist *, int);
extern DECLSPEC void AG_TlistSetIcon(AG_Tlist *, AG_TlistItem *, AG_Surface *);
extern DECLSPEC void AG_TlistSetRefresh(AG_Tlist *, int);
extern DECLSPEC void AG_TlistSetArgs(AG_TlistItem *, const char *, ...);
extern DECLSPEC void AG_TlistDel(AG_Tlist *, AG_TlistItem *);
extern DECLSPEC void AG_TlistUniq(AG_Tlist *);
extern DECLSPEC void AG_TlistClear(AG_Tlist *);
extern DECLSPEC void AG_TlistRestore(AG_Tlist *);
extern DECLSPEC AG_TlistItem *AG_TlistAdd(AG_Tlist *, AG_Surface *, const char *, ...);
extern DECLSPEC AG_TlistItem *AG_TlistAddS(AG_Tlist *, AG_Surface *, const char *);
extern DECLSPEC AG_TlistItem *AG_TlistAddHead(AG_Tlist *, AG_Surface *, const char *, ...);
extern DECLSPEC AG_TlistItem *AG_TlistAddHeadS(AG_Tlist *, AG_Surface *, const char *);
extern DECLSPEC AG_TlistItem *AG_TlistAddPtr(AG_Tlist *, AG_Surface *, const char *, void *);
extern DECLSPEC AG_TlistItem *AG_TlistAddPtrHead(AG_Tlist *, AG_Surface *, const char *, void *);
extern DECLSPEC void AG_TlistSelect(AG_Tlist *, AG_TlistItem *);
extern DECLSPEC void AG_TlistDeselect(AG_Tlist *, AG_TlistItem *);
extern DECLSPEC void AG_TlistSelectAll(AG_Tlist *);
extern DECLSPEC AG_TlistItem *AG_TlistSelectPtr(AG_Tlist *, void *);
extern DECLSPEC AG_TlistItem *AG_TlistSelectText(AG_Tlist *, const char *);
extern DECLSPEC void AG_TlistDeselectAll(AG_Tlist *);
extern DECLSPEC AG_TlistItem *AG_TlistFindByIndex(AG_Tlist *, int);
extern DECLSPEC AG_TlistItem *AG_TlistSelectedItem(AG_Tlist *);
extern DECLSPEC void *AG_TlistSelectedItemPtr(AG_Tlist *);
extern DECLSPEC void *AG_TlistFindPtr(AG_Tlist *);
extern DECLSPEC AG_TlistItem *AG_TlistFindText(AG_Tlist *, const char *);
extern DECLSPEC AG_TlistItem *AG_TlistFirstItem(AG_Tlist *);
extern DECLSPEC AG_TlistItem *AG_TlistLastItem(AG_Tlist *);
extern DECLSPEC AG_MenuItem *AG_TlistSetPopup(AG_Tlist *, const char *);
extern DECLSPEC void AG_TlistScrollToStart(AG_Tlist *);
extern DECLSPEC void AG_TlistScrollToEnd(AG_Tlist *);
extern DECLSPEC void AG_TlistSetDblClickFn(AG_Tlist *, AG_EventFn, const char *, ...);
extern DECLSPEC void AG_TlistSetPopupFn(AG_Tlist *, AG_EventFn, const char *, ...);
extern DECLSPEC void AG_TlistSetChangedFn(AG_Tlist *, AG_EventFn, const char *, ...);
extern DECLSPEC void AG_TlistSetCompareFn(AG_Tlist *, int (*)(const AG_TlistItem *, const AG_TlistItem *));
extern DECLSPEC int AG_TlistCompareStrings(const AG_TlistItem *, const AG_TlistItem *);
extern DECLSPEC int AG_TlistComparePtrs(const AG_TlistItem *, const AG_TlistItem *);
extern DECLSPEC int AG_TlistComparePtrsAndClasses(const AG_TlistItem *, const AG_TlistItem *);
#define AG_TlistBegin AG_TlistClear
#define AG_TlistEnd AG_TlistRestore

static __inline__ int
AG_TlistVisibleChildren(AG_Tlist *tl, AG_TlistItem *cit)
{
	AG_TlistItem *sit;

	AG_TAILQ_FOREACH(sit, &tl->selitems, selitems) {
		if (tl->compare_fn(sit, cit))
			break;
	}
	if (sit == NULL) { 
		return (0);			
	}
	return (sit->flags & AG_TLIST_VISIBLE_CHILDREN);
}

static __inline__ void
AG_TlistRefresh(AG_Tlist *tl)
{
	AG_ObjectLock(tl);
	tl->flags |= AG_TLIST_REFRESH;
	AG_ObjectUnlock(tl);
}
__END_DECLS
/* Close generated block */

#include <agar/gui/close.h>
#endif /* _AGAR_WIDGET_TLIST_H_ */
