/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const int focusonwheel       = 0;
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11","WenQuanYi Micro Hei:size=11:type=Regular:antialias=true:autohint=true","Noto sans CJK SC:size=11","Symbols Nerd Font:pixelsize=14:type2048-em:antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=11";

/* nord colorscheme */
static const char col_gray1[]       = "#2e3440";	/* black */
static const char col_gray2[]       = "#4c566a";	/* gray */
static const char col_gray3[]       = "#d8dee9";	/* white */
static const char col_gray4[]       = "#eceff4"; 	/* bright white */
static const char col_cyan[]        = "#98B4D4"; 	/* Cerulean Blue */

/* default */
/*static const char *colors[][3]      = { */
	/*               fg         bg         border   */
/*	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 }, */
/*	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  }, */
/* }; */


static const char *colors[][3]      = {
		/*               fg         bg         border   */
		[SchemeNorm] = { col_gray4, col_gray1, col_gray1 },
		[SchemeSel]  = { col_gray4, col_gray2, col_cyan },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "ﳜ", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       2>>9,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask //win key
#define TAGKEYS(KEY,TAG) \
		{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
		{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
		{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "shift-tools.c"
#include <X11/XF86keysym.h> 
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_dollar,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_n,	   shiftview,      { .i = +1 } },
	{ MODKEY,                       XK_p,	   shiftview,      { .i = -1 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
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
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_ampersand,                     0)
	TAGKEYS(                        XK_eacute,                        1)
	TAGKEYS(                        XK_quotedbl,                      2)
	TAGKEYS(                        XK_apostrophe,                    3)
	TAGKEYS(                        XK_parenleft,                     4)
	TAGKEYS(                        XK_minus,                         5)
	TAGKEYS(                        XK_egrave,                        6)
	TAGKEYS(                        XK_underscore,                    7)
	TAGKEYS(                        XK_ccedilla,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_s,                togglesticky,   {0} },
	//capture d'éran
	{0,			XK_Print,  spawn,	   SHCMD("flameshot gui")}, 
	//Ouvrir un navigateur
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("pcmanfm") },
	//son
	{0,			XF86XK_AudioLowerVolume,  spawn,	SHCMD("amixer sset Master 5%- unmute")}, 
	{0,			XF86XK_AudioRaiseVolume,  spawn,	SHCMD("amixer sset Master 5%+ unmute")}, 
	{0,			XF86XK_AudioMute,  spawn,	   SHCMD("amixer sset Master toggle")}, 
	//micro
	{ControlMask,		XF86XK_AudioLowerVolume,  spawn,	SHCMD("amixer sset Capture 5%- unmute")}, 
	{ControlMask,		XF86XK_AudioRaiseVolume,  spawn,	SHCMD("amixer sset Capture 5%+ unmute")}, 
	{ControlMask,		XF86XK_AudioMute,  spawn,	   SHCMD("amixer sset Capture toggle")}, 
	//luminosité
	{0,			XF86XK_MonBrightnessDown,  spawn,	SHCMD("xbacklight -dec 10")}, 
	{0,			XF86XK_MonBrightnessUp,  spawn,	SHCMD("xbacklight -inc 10")}, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

