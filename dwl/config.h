/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const float bordercolor[]           = {0.639, 0.745, 0.539, 1.0};
static const float focuscolor[]            = {0.18, 0.204, 0.251, 1.0};
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.18, 0.204, 0.251, 1.0};

/* Autostart */
static const char *const autostart[] = {
        "sh", "-c", "dwlautostart", NULL,
        NULL /* terminate */
};

/* tagging - tagcount must be no greater than 31 */
#define TAGCOUNT (9)

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	{ "musicplayer",  NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	.layout = "us,in",
	.options = "grp:shift_caps_toggle",
};

static const int repeat_rate = 40;
static const int repeat_delay = 320;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 0;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 1;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    -1, KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  -1, KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,-1,SKEY,toggletag,  {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "footclient", NULL };
static const char *menucmd[] = { "bemenu-run", NULL };

/* media keys */
#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  chain,  key                 function        argument */
	{ MODKEY,                    -1, XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    -1, XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    -1, XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    -1, XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    -1, XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    -1, XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    -1, XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,                    -1, XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    -1, XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    -1, XKB_KEY_w,          killclient,     {0} },
	{ MODKEY,                    -1, XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    -1, XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    -1, XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    -1, XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    -1, XKB_KEY_e,         togglefullscreen, {0} },
	{ MODKEY,                    -1, XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    -1, XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    -1, XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT,    -1, XKB_KEY_Q,          quit,           {0} },
        { 0, 	        -1, XF86XK_AudioMute,         spawn,	SHCMD("amixer -q sset Master toggle") },
	{ 0,            -1, XF86XK_AudioRaiseVolume,  spawn,	SHCMD("amixer -q sset Master 5%+") },
	{ 0,            -1, XF86XK_AudioLowerVolume,  spawn,	SHCMD("amixer -q sset Master 5%-") },
	{ 0, 	        -1, XF86XK_AudioPrev,         spawn,	SHCMD("cmus-remote -r") },
	{ 0, 	        -1, XF86XK_AudioNext,         spawn,	SHCMD("cmus-remote -n") },
	{ 0, 	        -1, XF86XK_AudioPlay,         spawn,	SHCMD("cmus-remote -u") },
	{ 0,            -1, XF86XK_MonBrightnessUp,   spawn,	SHCMD("$WHEEL brightnessctl set 5%+") },
	{ 0,            -1, XF86XK_MonBrightnessDown, spawn,	SHCMD("$WHEEL brightnessctl set 5%-") },
	{ MODKEY|WLR_MODIFIER_SHIFT, -1, XKB_KEY_B,   spawn,	SHCMD("$BROWSER") },   
        { 0,		-1, XKB_KEY_Print,	      spawn,	SHCMD("wscreenshot scwhole") },
	{ ShiftMask,	-1, XKB_KEY_Print,	      spawn,    SHCMD("wscreenshot scselect") },
	{ MODKEY,	-1, XKB_KEY_Print,	      spawn,    SHCMD("wscreenshot scshare") },
	{ MODKEY,	XKB_KEY_r, XKB_KEY_s,	      spawn,    SHCMD("wlsunset -l 30.1 -L 78.9 -t 2400 -T 4001") },
	{ MODKEY,	XKB_KEY_r, XKB_KEY_k,	      spawn,    SHCMD("pkill wlsunset") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_e,	      spawn,    SHCMD("$NOTE") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_l,	      spawn,    SHCMD("footclient -a tfilemanager lf") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_f,	      spawn,    SHCMD("footclient -a newsfeeder newsboat") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_n,	      spawn,    SHCMD("footclient -a mail mutt") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_b,	      spawn,    SHCMD("footclient -a monitor btop") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_m,	      spawn,    SHCMD("footclient -a musicplayer cmus") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_w,	      spawn,    SHCMD("$XDG_CONFIG_HOME/swayimg/plugin/wbgsetter $HOME/Pictures/Wallpapers") },
	{ MODKEY,	XKB_KEY_o, XKB_KEY_p,	      spawn,    SHCMD("$XDG_CONFIG_HOME/swayimg/plugin/photoremover $HOME/Pictures") },
	{ MODKEY,	XKB_KEY_x, XKB_KEY_n,	      spawn,    SHCMD("wbookmark add") },
	{ MODKEY,	XKB_KEY_x, XKB_KEY_m,	      spawn,    SHCMD("wbookmark sel") },
	{ MODKEY,	XKB_KEY_x, XKB_KEY_d,	      spawn,    SHCMD("wbookmark del") },
	{ MODKEY,	XKB_KEY_x, XKB_KEY_p,	      spawn,    SHCMD("wpass") },
	{ MODKEY,	XKB_KEY_x, XKB_KEY_c,	      spawn,    SHCMD("wcalc") },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,-1,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ WLR_MODIFIER_ALT, BTN_LEFT,  moveresize,     {.ui = CurResize} },
};
