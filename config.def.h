/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const int showbar                  = 0;
static const int topbar                   = 0;
static const int swallowfloating          = 1;        /* 1 means swallow floating windows */
static const unsigned int borderpx        = 1;  /* border pixel of windows */
static const unsigned int snap            = 32; /* snap pixel */
static const char *fonts[]                = { "monospace:size=10" };
static const char col_gray1[]             = "#000000";
static const char col_gray2[]             = "#444444";
static const char col_gray3[]             = "#bbbbbb";
static const char col_cyan[]              = "#005577";
static const char *colors[][3]            = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray2, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3" };

static const Rule rules[] = {
      /* class       instance  title   tags mask  isfloating  isterminal  noswallow  monitor */
       { "Alacritty", NULL, 	NULL,   0,          0,          1,           0,        -1 },
       { "Gimp",      NULL,     NULL,   0,    	    1,          0,           0,        -1 },
       { "Firefox",   NULL,     NULL,   0,   	    0,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },   
        { "M",        monocle },
        { "F",        NULL },
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
static const char *menucmd[] = { "rofi", "-show", "drun", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *termcmd[] = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        			function        argument */
        { MODKEY,                       XK_p,      			spawn,          {.v = menucmd } },
	{ MODKEY,			XK_w,				spawn,		{.v = browser } },
	{ MODKEY,		        XK_Return, 			spawn,          {.v = termcmd } },
	{ 0, 				XF86XK_AudioRaiseVolume, 	spawn, 		SHCMD("wpctl set-volume @DEFAULT_SINK@ 0.05+") },
	{ 0, 				XF86XK_AudioLowerVolume, 	spawn, 		SHCMD("wpctl set-volume @DEFAULT_SINK@ 0.05-") },
	{ 0, 				XF86XK_AudioMute,		spawn, 		SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle") },
	{ MODKEY, 			XK_f,				setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_Return, 			zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      			killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_0,      			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      			tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_j,           		focusstack,     {.i = +1 } }, // focus on the next client in the stack
	{ MODKEY,                       XK_k,           		focusstack,     {.i = -1 } }, // focus on the previous client in the stack
	{ MODKEY,                       XK_i,           		incnmaster,     {.i = +1 } }, // decrease the number of clients in the master area
	{ MODKEY,                       XK_d,           		incnmaster,     {.i = -1 } }, // increase the number of clients in the master area
	{ MODKEY,                       XK_h,           		setmfact,       {.f = -0.05} }, // decrease the size of the master area compared to the stack area(s)
	{ MODKEY,                       XK_l,           		setmfact,       {.f = +0.05} }, // increase the size of the master area compared to the stack area(s)
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
        { MODKEY|ShiftMask,             XK_m,           		togglefullscr,	{0} },
	{ MODKEY,                       XK_m,           		togglefloating, {0} }, // toggles between tiled and floating arrangement for the currently focused client
	{ MODKEY,                       XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      			                0)
	TAGKEYS(                        XK_2,      			                1)
	TAGKEYS(                        XK_3,      			                2)
	{ MODKEY|ShiftMask,             XK_q,      			quit,           {0} }, 
};	

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

