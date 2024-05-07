/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 40;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 40;       /* vert inner gap between windows */
static const unsigned int gappoh    = 40;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 40;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"SpaceMono Nerd Font:size=10"};
static const char dmenufont[]       = "SpaceMono Nerd Font:size=10";

static char normbgcolor[]       = "#3b4252";
static char normbordercolor[]       = "#434c5e";
static char normfgcolor[]       = "#eceff4";
static char selfgcolor[]       = "#eceff4";
static char selbordercolor[]        = "#88c0d0";
static char selbgcolor[]        = "#88c0d0";
static char *colors[][3]      = {
	/*               fg         bg         border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
	"slstatus", NULL,
	"picom", NULL,
	"xwallpaper","--zoom", "/home/void/.config/wallpaper", NULL,
	"xbanish", NULL,
	NULL /* terminate */
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
	{ "KeePassXC",  NULL,       NULL,       1 << 6,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 0;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	//{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webcmd[]  = { "firefox", NULL };
static const char *emojicmd[] = {"/home/void/dev/sh/emoji.sh",NULL};
static const char *bgcmd[] = {"nsxiv", "-rt", "/home/void/Pictures/bg/", NULL};
static const char *themecmd[] = {"/home/void/dev/sh/theme.sh", NULL};

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		//{ "font",               STRING,  &font },
		//{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		//{ "borderpx",          	INTEGER, &borderpx },
		//{ "snap",          		INTEGER, &snap },
		//{ "showbar",          	INTEGER, &showbar },
		//{ "topbar",          	INTEGER, &topbar },
		//{ "nmaster",          	INTEGER, &nmaster },
		//{ "resizehints",       	INTEGER, &resizehints },
		//{ "mfact",      	 	FLOAT,   &mfact },
};

#include "selfrestart.c"
#include "push.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             		XK_w, spawn,          {.v = webcmd } },
	{ MODKEY,             		XK_e, spawn,          {.v = emojicmd }},
	{ MODKEY|ShiftMask,             XK_b, spawn,          {.v = bgcmd }},
	{ MODKEY,             		XK_t, spawn,          {.v = themecmd }},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,                       XK_k,      pushdown,     {0} },
	{ MODKEY|ShiftMask,                       XK_l,      pushup,     {0} },
	{ MODKEY,                       XK_comma,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_m,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_period,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_slash,      setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_p,      setcfact,       {.f = +0.25} },
	{ MODKEY,             XK_o,      setcfact,       {.f = -0.25} },
	{ MODKEY,             XK_i,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_equal,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,    XK_minus,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,              XK_minus,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_equal,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },	
	{ MODKEY,                       XK_d,  setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,  setlayout,      {.v = &layouts[2]} },
	{ MODKEY,		XK_a,  cyclelayout,    {.i = -1 } },
	{ MODKEY,           XK_s, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_v,      setattach,      {.i = 0} },
	{ MODKEY,                       XK_c,      setattach,      {.i = 5} },
	{ MODKEY,                       XK_x,      setattach,      {.i = 4} },
	{ MODKEY,                       XK_z,      setattach,      {.i = 3} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_j,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,             XK_j,  tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY|ControlMask,                       XK_j,  focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,                       XK_semicolon, focusmon,       {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,			XK_t,		spawn,	{.v = (const char*[]){"xrdb","-load","/home/void/.Xresources", NULL} }	 },
	{ MODKEY|ShiftMask,			XK_t,		xrdb,		{.v = NULL } },
	{ MODKEY|ShiftMask,		XK_r,       self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

