/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappx     = 5;        /* gap pixel between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=12" };
static const char dmenufont[]       = "terminus:size=12";
//static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";

/* my colors */
static const char col_dark_gray[]   = "#222222";
static const char col_white[]       = "#eeeeee";
static const char col_violet[]      = "#7a49a5";
static const char col_green[]       = "#49A57A";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_dark_gray, col_gray2 },
	[SchemeSel]  = { col_white, col_violet,  col_violet  },
	[SchemeHov]  = { col_white, col_green,  col_violet  },
	[SchemeHid]  = { col_violet,col_dark_gray, col_violet  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "><",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_dark_gray, "-nf", col_gray3, "-sb", col_violet, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webbrowser[] = { "chromium", NULL };
static const char *filemanager[] = { "pcmanfm", NULL };
static const char *screenshot[] = { "flameshot", "gui", NULL };
static const char *documentviewer[] = { "atril", NULL };
static const char *brupcmd[]    = { "brightnessctl", "set", "+10%", NULL};
static const char *brdowncmd[]  = { "brightnessctl", "set", "10%-", NULL};
static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+10%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-10%", NULL };
static const char *mutecmd[]    = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

#include "exitdwm.c"
#include <X11/XF86keysym.h>

static const Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_e,      spawn,          {.v = filemanager } },
        { MODKEY,                       XK_w,      spawn,          {.v = webbrowser } },
        { 0,                            XK_Print,  spawn,          {.v = screenshot } },
        { MODKEY,                       XK_n,      spawn,          {.v = documentviewer } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
        { MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Right,  focusstackhid,  {.i = +1 } },
        { MODKEY|ShiftMask,             XK_Left,   focusstackhid,  {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_s,      show,           {0} },
        { MODKEY|ShiftMask,             XK_s,      showall,        {0} },
        { MODKEY,                       XK_h,      hide,           {0} },

        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_x,      exitdwm,        {0} },
        { MODKEY,                       XK_x,      quit,           {1} }, 
        { 0,                            XF86XK_MonBrightnessUp, spawn, {.v = brupcmd } },
        { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd } },
        { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
        { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
        { 0,                            XF86XK_AudioMute, spawn, {.v = mutecmd } },

};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

