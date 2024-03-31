/* constants */
/* how tall the keyboard should be by default (can be overriden) */
#include "keyboard.h"
#include <linux/input-event-codes.h>
#define KBD_PIXEL_HEIGHT 250

/* how tall the keyboard should be by default (can be overriden) */
#define KBD_PIXEL_LANDSCAPE_HEIGHT 120

/* spacing around each key */
#define KBD_KEY_BORDER 2

/* layout declarations */
enum layout_id {
    Full = 0,
    FullWide,
    Special,
    SpecialPad,
    Simple,
    Dialer,
    Cyrillic,
    Arabic,
    Persian,
    Greek,
    Georgian,
    Hebrew,
    Emoji,
    Nav,
    Landscape,
    LandscapeSpecial,
    ComposeA,
    ComposeE,
    ComposeY,
    ComposeU,
    ComposeI,
    ComposeO,
    ComposeW,
    ComposeR,
    ComposeT,
    ComposeP,
    ComposeS,
    ComposeD,
    ComposeF,
    ComposeG,
    ComposeH,
    ComposeJ,
    ComposeK,
    ComposeL,
    ComposeZ,
    ComposeX,
    ComposeC,
    ComposeV,
    ComposeB,
    ComposeN,
    ComposeM,
    ComposeMath,
    ComposePunctuation,
    ComposeBracket,
    ComposeCyrI,
    ComposeCyrJ,
    ComposeCyrE,
    ComposeCyrL,
    ComposeCyrU,
    ComposeCyrN,
    ComposeCyrTse,
    ComposeCyrChe,
    ComposeCyrG,
    ComposeCyrK,
    Index,
    Tablet,
    TabletReverse,
    NumLayouts,
};

static struct key keys_full[], keys_full_wide[], keys_special[],
    keys_specialpad[], keys_simple[], keys_cyrillic[], keys_arabic[],
    keys_persian[], keys_georgian[], keys_greek[], keys_hebrew[], keys_emoji[],
    keys_nav[], keys_landscape[], keys_landscape_special[], keys_compose_a[],
    keys_compose_e[], keys_compose_y[], keys_compose_u[], keys_compose_i[],
    keys_compose_o[], keys_compose_w[], keys_compose_r[], keys_compose_t[],
    keys_compose_p[], keys_compose_s[], keys_compose_d[], keys_compose_f[],
    keys_compose_g[], keys_compose_h[], keys_compose_j[], keys_compose_k[],
    keys_compose_l[], keys_compose_z[], keys_compose_x[], keys_compose_c[],
    keys_compose_v[], keys_compose_b[], keys_compose_n[], keys_compose_m[],
    keys_compose_math[], keys_compose_punctuation[], keys_compose_bracket[],
    keys_compose_cyr_i[], keys_compose_cyr_j[], keys_compose_cyr_e[],
    keys_compose_cyr_u[], keys_compose_cyr_l[], keys_compose_cyr_n[],
    keys_compose_cyr_tse[], keys_compose_cyr_che[], keys_compose_cyr_g[],
    keys_compose_cyr_k[], keys_dialer[], keys_index[], keys_tablet[], keys_tablet_reverse[];

static struct layout layouts[NumLayouts] = {
    [Full] = {keys_full, "latin", "full",
              true}, // second parameter is the keymap name
                     // third parameter is the layout name
                     // last parameter indicates if it's an alphabetical/primary
                     // layout
    [FullWide] = {keys_full_wide, "latin", "fullwide", true},
    [Special] = {keys_special, "latin", "special", false},
    [SpecialPad] = {keys_specialpad, "latin", "specialpad", false},
    [Simple] = {keys_simple, "latin", "simple", true},
    [Cyrillic] = {keys_cyrillic, "cyrillic", "cyrillic", true},
    [Dialer] = {keys_dialer, "latin", "dialer", false},
    [Arabic] = {keys_arabic, "arabic", "arabic", true},
    [Persian] = {keys_persian, "persian", "persian", true},
    [Greek] = {keys_greek, "greek", "greek", true},
    [Georgian] = {keys_georgian, "georgian", "georgian", true},
    [Hebrew] = {keys_hebrew, "hebrew", "hebrew", true},
    [Emoji] = {keys_emoji, "latin", "emoji", false},
    [Nav] = {keys_nav, "latin", "nav", false},
    [Landscape] = {keys_landscape, "latin", "landscape", true},
    [LandscapeSpecial] = {keys_landscape_special, "latin", "landscapespecial",
                          true},
    [ComposeA] = {keys_compose_a, "latin"},
    [ComposeE] = {keys_compose_e, "latin"},
    [ComposeY] = {keys_compose_y, "latin"},
    [ComposeU] = {keys_compose_u, "latin"},
    [ComposeI] = {keys_compose_i, "latin"},
    [ComposeO] = {keys_compose_o, "latin"},
    [ComposeW] = {keys_compose_w, "latin"},
    [ComposeR] = {keys_compose_r, "latin"},
    [ComposeT] = {keys_compose_t, "latin"},
    [ComposeP] = {keys_compose_p, "latin"},
    [ComposeS] = {keys_compose_s, "latin"},
    [ComposeD] = {keys_compose_d, "latin"},
    [ComposeF] = {keys_compose_f, "latin"},
    [ComposeG] = {keys_compose_g, "latin"},
    [ComposeH] = {keys_compose_h, "latin"},
    [ComposeJ] = {keys_compose_j, "latin"},
    [ComposeK] = {keys_compose_k, "latin"},
    [ComposeL] = {keys_compose_l, "latin"},
    [ComposeZ] = {keys_compose_z, "latin"},
    [ComposeX] = {keys_compose_x, "latin"},
    [ComposeC] = {keys_compose_c, "latin"},
    [ComposeV] = {keys_compose_v, "latin"},
    [ComposeB] = {keys_compose_b, "latin"},
    [ComposeN] = {keys_compose_n, "latin"},
    [ComposeM] = {keys_compose_m, "latin"},
    [ComposeMath] = {keys_compose_math, "latin"},
    [ComposePunctuation] = {keys_compose_punctuation, "latin"},
    [ComposeBracket] = {keys_compose_bracket, "latin"},
    [ComposeCyrI] = {keys_compose_cyr_i, "cyrillic"},
    [ComposeCyrJ] = {keys_compose_cyr_j, "cyrillic"},
    [ComposeCyrE] = {keys_compose_cyr_e, "cyrillic"},
    [ComposeCyrU] = {keys_compose_cyr_u, "cyrillic"},
    [ComposeCyrL] = {keys_compose_cyr_l, "cyrillic"},
    [ComposeCyrN] = {keys_compose_cyr_n, "cyrillic"},
    [ComposeCyrTse] = {keys_compose_cyr_tse, "cyrillic"},
    [ComposeCyrChe] = {keys_compose_cyr_che, "cyrillic"},
    [ComposeCyrG] = {keys_compose_cyr_g, "cyrillic"},
    [ComposeCyrK] = {keys_compose_cyr_k, "cyrillic"},

    [Index] = {keys_index, "latin", "index", false},
    [Tablet] = {keys_tablet, "latin", "tablet", true},
    [TabletReverse] = {keys_tablet_reverse, "latin", "tabletreverse", true},
};

/* key layouts
 *
 * define keys like:
 *
 *  `{
 *     "label",
 *     "SHIFT_LABEL",
 *     1,
 *     [Code, Mod, Layout, EndRow, Last],
 *     [KEY_CODE, Modifier],
 *     [&layout]
 *  },`
 *
 * - label: normal label for key
 *
 * - shift_label: label for key in shifted (uppercase) layout
 *
 * - width: column width of key
 *
 * - type: what kind of action this key peforms (emit keycode, toggle modifier,
 *   switch layout, or end the layout)
 *
 * - code: key scancode or modifier name (see
 *   `/usr/include/linux/input-event-codes.h` for scancode names, and
 *   `keyboard.h` for modifiers)
 *
 * - layout: layout to switch to when key is pressed
 */


static struct key keys_tablet_reverse[] = {
    {"й", "Й", 1.0, Copy, 0x71, 0, 0x51},
    {"ц", "Ц", 1.0, Copy, 0x77, 0, 0x57},
    {"у", "У", 1.0, Copy, 0x65, 0, 0x45},
    {"к", "К", 1.0, Copy, 0x72, 0, 0x52},
    {"е", "Е", 1.0, Copy, 0x74, 0, 0x54},
    {"н", "Н", 1.0, Copy, 0x79, 0, 0x59},

    {"", "", 7, Pad},

    {"Sup", "Sup", 1.0, Mod, Super, .scheme = 1},
    {"CpL", "CpL", 1.0, Mod, CapsLock, .scheme = 1},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"Del", "Del", 1.0, Code, KEY_DELETE, .scheme = 1},
    {"⌫", "⌫", 1, Code, KEY_BACKSPACE, .scheme = 1},
    {";", ":", 1.0, Code, KEY_SEMICOLON, .scheme = 4}, //TODO поправить изменение по Shift, не надо мне его тутъ
    {",", ",", 1.0, Code, KEY_COMMA, .scheme = 4},
    {"(", "(", 1.0, Code, KEY_9, 0, Shift, .scheme = 4},
    {")", ")", 1.0, Code, KEY_0, 0, Shift, .scheme = 4},
    {"_", "_", 1, Code, KEY_MINUS, 0, Shift, .scheme = 4},       

    {"", "", 0.0, EndRow},












    {"ф", "Ф", 1.0, Copy, 0x61, 0, 0x41},
    {"ы", "Ы", 1.0, Copy, 0x73, 0, 0x53},
    {"в", "В", 1.0, Copy, 0x64, 0, 0x44},
    {"а", "А", 1.0, Copy, 0x66, 0, 0x46},
    {"п", "П", 1.0, Copy, 0x67, 0, 0x47},
    {"р", "Р", 1.0, Copy, 0x68, 0, 0x48},

    {"", "", 7.0, Pad},

    {"9", "9", 1.0, Copy, 0x39, .scheme = 2},
    {"7", "7", 1.0, Copy, 0x37, .scheme = 2},
    {"5", "5", 1.0, Copy, 0x35, .scheme = 2},
    {"3", "3", 1.0, Copy, 0x33, .scheme = 2},
    {"2", "2", 1.0, Copy, 0x32, .scheme = 2},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"1", "1", 1.0, Copy, 0x31, .scheme = 2},
    {"{", "{", 1, Code, KEY_LEFTBRACE, 0, Shift, .scheme = 4},
    {"}", "}", 1, Code, KEY_RIGHTBRACE, 0, Shift, .scheme = 4},
    {"=", "=", 1, Code, KEY_EQUAL, .scheme = 4},

    {"", "", 0.0, EndRow},











    {"я", "Я", 1.0, Copy, 0x7a, 0, 0x5a},
    {"ч", "Ч", 1.0, Copy, 0x78, 0, 0x58},
    {"c", "С", 1.0, Copy, 0x63, 0, 0x43},
    {"м", "М", 1.0, Copy, 0x76, 0, 0x56},
    {"и", "И", 1.0, Copy, 0x62, 0, 0x42},
    {"т", "Т", 1.0, Copy, 0x6e, 0, 0x4e},

    {"", "", 7, Pad},

    {"@", "@", 1.0, Code, KEY_2, 0, Shift, .scheme = 4},
    {"8", "8", 1.0, Copy, 0x38, .scheme = 2},
    {"6", "6", 1.0, Copy, 0x36, .scheme = 2},
    {"4", "4", 1.0, Copy, 0x34, .scheme = 2},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"Alt", "Alt", 1.0, Mod, Alt, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"-", "-", 1, Code, KEY_MINUS, .scheme = 4},

    {"", "", 0.0, EndRow},












    {"ё", "Ё", 1.0, Copy, 0x60, 0, 0x7e},
    {"ъ", "Ъ", 1.0, Copy, 0x5d, 0, 0x7d},
    {"г", "Г", 1.0, Copy, 0x75, 0, 0x55},
    {"ш", "Ш", 1.0, Copy, 0x69, 0, 0x49},
    {"щ", "Щ", 1.0, Copy, 0x6f, 0, 0x4f},
    {"з", "З", 1.0, Copy, 0x70, 0, 0x50},

    {"", "", 7, Pad},

    {"?", "?", 1, Code, KEY_DOT, 0, Shift, .scheme = 4},
    {"\"", "\"", 1.0, Code, KEY_APOSTROPHE, 0, Shift, .scheme = 4},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"⇧", "⇫", 1, Mod, Shift, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {".", ".", 1.0, Code, KEY_DOT, .scheme = 4},

    {"", "", 0.0, EndRow},









    {"х", "Х", 1.0, Copy, 0x5b, 0, 0x7b},
    {"о", "О", 1.0, Copy, 0x6a, 0, 0x4a},
    {"л", "Л", 1.0, Copy, 0x6b, 0, 0x4b},
    {"д", "Д", 1.0, Copy, 0x6c, 0, 0x4c},
    {"ж", "Ж", 1.0, Copy, 0x3b, 0, 0x3a},
    {"ю", "Ю", 1.0, Copy, 0x2e, 0, 0x3e},

    {"", "", 7, Pad},

    {"\\", "\\", 1.0, Code, KEY_BACKSLASH, .scheme = 4},
    {"'", "'", 1.0, Code, KEY_APOSTROPHE, .scheme = 4},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"[", "[", 1, Code, KEY_LEFTBRACE, .scheme = 4},
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"]", "]", 1, Code, KEY_RIGHTBRACE, .scheme = 4},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"/", "/", 1.0, Code, KEY_SLASH, .scheme = 1, .scheme = 4},

    {"", "", 0.0, EndRow},










    {"э", "Э", 1.0, Copy, 0x27, 0, 0x27},
    {"б", "Б", 1.0, Copy, 0x2c, 0, 0x2c},
    {"ь", "Ь", 1.0, Copy, 0x6d, 0, 0x6d},
    {"|", "|", 1.0, Code, KEY_BACKSLASH, 0, Shift, .scheme = 4},
    {"!", "!", 1, Code, KEY_1, 0, Shift, .scheme = 4},
    {"Prt", "Prt", 1, Code, KEY_PRINT, .scheme = 1},
    
    {"", "", 7, Pad},

    {"^", "^", 1.0, Code, KEY_6, 0, Shift, .scheme = 4},
    {"+", "+", 1, Code, KEY_EQUAL, 0, Shift, .scheme = 4},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"", "", 1, Code, KEY_SPACE, .scheme = 3},
    {":", ":", 1, Code, KEY_SEMICOLON, 0, Shift, .scheme = 4},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"~", "~", 1.0, Code, KEY_GRAVE, 0, Shift, .scheme = 4},

    {"", "", 0.0, EndRow},









    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"⇥", "⇥", 1.0, Code, KEY_END, .scheme = 1},
    {"⇤", "⇤", 1.0, Code, KEY_HOME, .scheme = 1},
    {"`", "`", 1.0, Code, KEY_GRAVE, .scheme = 4},

    {"", "", 8, Pad},

    {"%", "%", 1.0, Code, KEY_5, 0, Shift, .scheme = 4},
    {"*", "*", 1, Code, KEY_8, 0, Shift, .scheme = 4},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"<", "<", 1, Code, KEY_COMMA, 0, AltGr, .scheme = 4},
    {"↵", "↵", 1, Code, KEY_ENTER, .scheme = 1},
    {">", ">", 1, Code, KEY_SLASH, 0, Shift, .scheme = 4},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"0", "0", 1.0, Copy, 0x30, .scheme = 2},

    {"", "", 0.0, EndRow},








    {"", "", 13, Pad},

    {"#", "#", 1.0, Code, KEY_3, 0, Shift, .scheme = 4},
    {"&", "&", 1.0, Code, KEY_7, 0, Shift, .scheme = 4},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"$", "$", 1.0, Code, KEY_4, 0, Shift, .scheme = 4},

    {"", "", 0.0, EndRow},







    // {"App", "App", 1.0, Code, KEY_MACRO1, .scheme = 1},
    {"Mut", "Mut", 1.0, Code, KEY_MUTE, .scheme = 1},
    {"Vol-", "Vol-", 1.0, Code, KEY_VOLUMEDOWN, .scheme = 1},
    {"Vol+", "Vol+", 1.0, Code, KEY_VOLUMEUP, .scheme = 1},
    {"CL", "CL", 1.0, Copy, 0x00F1, .scheme = 1},
    {"CD", "CD", 1.0, Copy, 0x00F2, .scheme = 1},
    {"CU", "CU", 1.0, Copy, 0x00F3, .scheme = 1},
    {"CR", "CR", 1.0, Copy, 0x00F4, .scheme = 1},

    {"", "", 11, Pad},

    {"⌨͕", "⌨͔", 1, NextLayer, .scheme = 1},
    {"Brt+", "Brt+", 1.0, Code, KEY_BRIGHTNESSUP, .scheme = 1},
    {"Brt-", "Brt-", 1.0, Code, KEY_BRIGHTNESSDOWN, .scheme = 1},
    {"MBL", "MBL", 1.0, Copy, 0x00FE, .scheme = 1},
    {"MBR", "MBR", 1.0, Copy, 0x00FD, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},

};


static struct key keys_tablet[] = {
    {"й", "Й", 1.0, Copy, 0x0439, 0, 0x0419},
    {"ц", "Ц", 1.0, Copy, 0x0446, 0, 0x0426},
    {"у", "У", 1.0, Copy, 0x0443, 0, 0x0423},
    {"к", "К", 1.0, Copy, 0x043A, 0, 0x041A},
    {"е", "Е", 1.0, Copy, 0x0435, 0, 0x0415},
    {"н", "Н", 1.0, Copy, 0x043D, 0, 0x041D},

    {"", "", 7, Pad},

    {"Sup", "Sup", 1.0, Mod, Super, .scheme = 1},
    {"CpL", "CpL", 1.0, Mod, CapsLock, .scheme = 1},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"Del", "Del", 1.0, Code, KEY_DELETE, .scheme = 1},
    {"⌫", "⌫", 1, Code, KEY_BACKSPACE, .scheme = 1},
    {";", ":", 1.0, Code, KEY_SEMICOLON, .scheme = 4}, //TODO поправить изменение по Shift, не надо мне его тутъ
    {",", ",", 1.0, Code, KEY_COMMA, .scheme = 4},
    {"(", "(", 1.0, Code, KEY_9, 0, Shift, .scheme = 4},
    {")", ")", 1.0, Code, KEY_0, 0, Shift, .scheme = 4},
    {"_", "_", 1, Code, KEY_MINUS, 0, Shift, .scheme = 4},       

    {"", "", 0.0, EndRow},












    {"ф", "Ф", 1.0, Copy, 0x0444, 0, 0x0424},
    {"ы", "Ы", 1.0, Copy, 0x044B, 0, 0x042B},
    {"в", "В", 1.0, Copy, 0x0432, 0, 0x0412},
    {"а", "А", 1.0, Copy, 0x0430, 0, 0x0410},
    {"п", "П", 1.0, Copy, 0x043F, 0, 0x041F},
    {"р", "Р", 1.0, Copy, 0x0440, 0, 0x0420},

    {"", "", 7.0, Pad},

    {"9", "9", 1.0, Copy, 0x39, .scheme = 2},
    {"7", "7", 1.0, Copy, 0x37, .scheme = 2},
    {"5", "5", 1.0, Copy, 0x35, .scheme = 2},
    {"3", "3", 1.0, Copy, 0x33, .scheme = 2},
    {"2", "2", 1.0, Copy, 0x32, .scheme = 2},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"1", "1", 1.0, Copy, 0x31, .scheme = 2},
    {"{", "{", 1, Code, KEY_LEFTBRACE, 0, Shift, .scheme = 4},
    {"}", "}", 1, Code, KEY_RIGHTBRACE, 0, Shift, .scheme = 4},
    {"=", "=", 1, Code, KEY_EQUAL, .scheme = 4},

    {"", "", 0.0, EndRow},











    {"я", "Я", 1.0, Copy, 0x044F, 0, 0x042F},
    {"ч", "Ч", 1.0, Copy, 0x0447, 0, 0x0427},
    {"c", "С", 1.0, Copy, 0x0441, 0, 0x0421},
    {"м", "М", 1.0, Copy, 0x043C, 0, 0x041C},
    {"и", "И", 1.0, Copy, 0x0438, 0, 0x0418},
    {"т", "Т", 1.0, Copy, 0x0442, 0, 0x0422},

    {"", "", 7, Pad},

    {"@", "@", 1.0, Code, KEY_2, 0, Shift, .scheme = 4},
    {"8", "8", 1.0, Copy, 0x38, .scheme = 2},
    {"6", "6", 1.0, Copy, 0x36, .scheme = 2},
    {"4", "4", 1.0, Copy, 0x34, .scheme = 2},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"Alt", "Alt", 1.0, Mod, Alt, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"-", "-", 1, Code, KEY_MINUS, .scheme = 4},

    {"", "", 0.0, EndRow},












    {"ё", "Ё", 1.0, Copy, 0x0451, 0, 0x0401},
    {"ъ", "Ъ", 1.0, Copy, 0x044A, 0, 0x042A},
    {"г", "Г", 1.0, Copy, 0x0433, 0, 0x0413},
    {"ш", "Ш", 1.0, Copy, 0x0448, 0, 0x0428},
    {"щ", "Щ", 1.0, Copy, 0x0449, 0, 0x0429},
    {"з", "З", 1.0, Copy, 0x0437, 0, 0x0417},

    {"", "", 7, Pad},

    {"?", "?", 1, Code, KEY_DOT, 0, Shift, .scheme = 4},
    {"\"", "\"", 1.0, Code, KEY_APOSTROPHE, 0, Shift, .scheme = 4},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"⇧", "⇫", 1, Mod, Shift, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {".", ".", 1.0, Code, KEY_DOT, .scheme = 4},

    {"", "", 0.0, EndRow},









    {"х", "Х", 1.0, Copy, 0x0445, 0, 0x0425},
    {"о", "О", 1.0, Copy, 0x043E, 0, 0x041E},
    {"л", "Л", 1.0, Copy, 0x043B, 0, 0x041B},
    {"д", "Д", 1.0, Copy, 0x0434, 0, 0x0414},
    {"ж", "Ж", 1.0, Copy, 0x0436, 0, 0x0416},
    {"ю", "Ю", 1.0, Copy, 0x044E, 0, 0x042E},

    {"", "", 7, Pad},

    {"\\", "\\", 1.0, Code, KEY_BACKSLASH, .scheme = 4},
    {"'", "'", 1.0, Code, KEY_APOSTROPHE, .scheme = 4},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"[", "[", 1, Code, KEY_LEFTBRACE, .scheme = 4},
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"]", "]", 1, Code, KEY_RIGHTBRACE, .scheme = 4},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"/", "/", 1.0, Code, KEY_SLASH, .scheme = 1, .scheme = 4},

    {"", "", 0.0, EndRow},










    {"э", "Э", 1.0, Copy, 0x044D, 0, 0x042D},
    {"б", "Б", 1.0, Copy, 0x0431, 0, 0x0411},
    {"ь", "Ь", 1.0, Copy, 0x044C, 0, 0x042C},
    {"|", "|", 1.0, Code, KEY_BACKSLASH, 0, Shift, .scheme = 4},
    {"!", "!", 1, Code, KEY_1, 0, Shift, .scheme = 4},
    {"Prt", "Prt", 1, Code, KEY_PRINT, .scheme = 1},
    
    {"", "", 7, Pad},

    {"^", "^", 1.0, Code, KEY_6, 0, Shift, .scheme = 4},
    {"+", "+", 1, Code, KEY_EQUAL, 0, Shift, .scheme = 4},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"", "", 1, Code, KEY_SPACE, .scheme = 3},
    {":", ":", 1, Code, KEY_SEMICOLON, 0, Shift, .scheme = 4},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"~", "~", 1.0, Code, KEY_GRAVE, 0, Shift, .scheme = 4},

    {"", "", 0.0, EndRow},









    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"⇥", "⇥", 1.0, Code, KEY_END, .scheme = 1},
    {"⇤", "⇤", 1.0, Code, KEY_HOME, .scheme = 1},
    {"`", "`", 1.0, Code, KEY_GRAVE, .scheme = 4},

    {"", "", 8, Pad},

    {"%", "%", 1.0, Code, KEY_5, 0, Shift, .scheme = 4},
    {"*", "*", 1, Code, KEY_8, 0, Shift, .scheme = 4},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"<", "<", 1, Code, KEY_COMMA, 0, AltGr, .scheme = 4},
    {"↵", "↵", 1, Code, KEY_ENTER, .scheme = 1},
    {">", ">", 1, Code, KEY_SLASH, 0, Shift, .scheme = 4},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"0", "0", 1.0, Copy, 0x30, .scheme = 2},

    {"", "", 0.0, EndRow},








    {"", "", 13, Pad},

    {"#", "#", 1.0, Code, KEY_3, 0, Shift, .scheme = 4},
    {"&", "&", 1.0, Code, KEY_7, 0, Shift, .scheme = 4},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"$", "$", 1.0, Code, KEY_4, 0, Shift, .scheme = 4},

    {"", "", 0.0, EndRow},







    // {"App", "App", 1.0, Code, KEY_MACRO1, .scheme = 1},
    {"Mut", "Mut", 1.0, Code, KEY_MUTE, .scheme = 1},
    {"Vol-", "Vol-", 1.0, Code, KEY_VOLUMEDOWN, .scheme = 1},
    {"Vol+", "Vol+", 1.0, Code, KEY_VOLUMEUP, .scheme = 1},
    {"CL", "CL", 1.0, Copy, 0x00F1, .scheme = 1},
    {"CD", "CD", 1.0, Copy, 0x00F2, .scheme = 1},
    {"CU", "CU", 1.0, Copy, 0x00F3, .scheme = 1},
    {"CR", "CR", 1.0, Copy, 0x00F4, .scheme = 1},

    {"", "", 11, Pad},

    {"⌨͕", "⌨͔", 1, NextLayer, .scheme = 1},
    {"Brt+", "Brt+", 1.0, Code, KEY_BRIGHTNESSUP, .scheme = 1},
    {"Brt-", "Brt-", 1.0, Code, KEY_BRIGHTNESSDOWN, .scheme = 1},
    {"MBL", "MBL", 1.0, Copy, 0x00FE, .scheme = 1},
    {"MBR", "MBR", 1.0, Copy, 0x00FD, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_full[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE, &layouts[ComposeBracket]},
    {"-", "_", 1.0, Code, KEY_MINUS, &layouts[ComposeMath]},
    {"/", ">", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation]},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"", "", 0.0, EndRow},

    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"", "", 0.0, EndRow},

    {"", "", 0.5, Pad},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"", "", 0.5, Pad},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.5, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {"", "Tab", 4.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 1.5, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_full_wide[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE, &layouts[ComposeBracket]},
    {";", ":", 1.0, Code, KEY_SEMICOLON, &layouts[ComposePunctuation]},
    {"/", ">", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation]},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"-", "_", 1.0, Code, KEY_MINUS, &layouts[ComposeMath]},
    {"=", "+", 1.0, Code, KEY_EQUAL, &layouts[ComposeMath]},
    {"", "", 0.0, EndRow},

    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"", "", 0.0, EndRow},

    {"", "", 0.5, Pad},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"", "", 0.5, Pad},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.5, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {"", "Tab", 4.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 1.5, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_special[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"Alt", "Alt", 1.0, Mod, Alt, .scheme = 1},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {"⇤", "⇤", 1.0, Code, KEY_HOME, .scheme = 1},
    {"⇥", "⇥", 1.0, Code, KEY_END, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"", "", 0.0, EndRow},

    {"CpL", "CpL", 1.0, Mod, CapsLock, .scheme = 1},
    {"Sup", "Sup", 1.0, Mod, Super, .scheme = 1},
    {"`", "~", 1.0, Code, KEY_GRAVE},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE},
    {"-", "_", 1.0, Code, KEY_MINUS},
    {"=", "+", 1.0, Code, KEY_EQUAL},
    {"[", "{", 1.0, Code, KEY_LEFTBRACE},
    {"]", "}", 1.0, Code, KEY_RIGHTBRACE},
    {"\\", "|", 1.0, Code, KEY_BACKSLASH},
    {"Del", "Del", 1.0, Code, KEY_DELETE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 2.0, Mod, Shift, .scheme = 1},
    {";", ":", 1.0, Code, KEY_SEMICOLON},
    {"/", ">", 1.0, Code, KEY_SLASH},
    {"<", "«", 1.0, Code, KEY_COMMA, 0, AltGr},
    {">", "»", 1.0, Code, KEY_DOT, 0, AltGr},
    {"¡", "¿", 1.0, Code, KEY_MENU},
    {"🙂", "🙂", 1.0, Layout, 0, &layouts[Emoji]},
    {"AGr", "AGr", 1.0, Mod, AltGr, .scheme = 1},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {"", "Tab", 4.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_specialpad[] = {
    {"⎋", "⎋", 1.0, Code, KEY_ESC, .scheme = 1},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"`", "~", 1.0, Code, KEY_GRAVE},
    {"\\", "|", 1.0, Code, KEY_BACKSLASH},
    {"/", ">", 1.0, Code, KEY_SLASH},
    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"⌦", "⌦", 1.0, Code, KEY_DELETE, .scheme = 1},
    {"", "", 0.0, EndRow},
    //{"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"", "↹", 1.0, Code, KEY_SPACE},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {".", "?", 1.0, Code, KEY_DOT},
    {"[", "{", 1.0, Code, KEY_LEFTBRACE},
    {"]", "}", 1.0, Code, KEY_RIGHTBRACE},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.0, Mod, Shift, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {";", ":", 1.0, Code, KEY_SEMICOLON},
    {"<", "«", 1.0, Code, KEY_COMMA, 0, AltGr},
    {">", "»", 1.0, Code, KEY_DOT, 0, AltGr},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"Alt", "Alt", 1.0, Mod, Alt, .scheme = 1},
    {"Sup", "Sup", 1.0, Mod, Super, .scheme = 1},

    {"⇤", "⇤", 1.0, Code, KEY_HOME, .scheme = 1},
    {"⇥", "⇥", 1.0, Code, KEY_END, .scheme = 1},
    {"-", "_", 1.0, Code, KEY_MINUS},
    {"0", ")", 1.0, Code, KEY_0},
    {"=", "+", 1.0, Code, KEY_EQUAL},
    {"↵", "↵", 1.0, Code, KEY_ENTER, .scheme = 1},
    //{",", "'", 1.0, Code, KEY_COMMA},
    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_simple[] = {
    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"", "", 0.0, EndRow},

    {"", "", 0.5, Pad},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"", "", 0.5, Pad},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"-", "_", 0.75, Code, KEY_MINUS, &layouts[ComposeMath]},
    {",", "'", 0.75, Code, KEY_COMMA, &layouts[ComposeBracket]},
    {"", "Tab", 3.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 1.5, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_dialer[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC},
    {"+", "+", 1.0, Code, KEY_KPPLUS},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE},
    {"", "", 0.0, EndRow},
    {"1", "1", 1.0, Code, KEY_1},
    {"2", "2", 1.0, Code, KEY_2},
    {"3", "3", 1.0, Code, KEY_3},
    {"", "", 0.0, EndRow},
    {"4", "4", 1.0, Code, KEY_4},
    {"5", "5", 1.0, Code, KEY_5},
    {"6", "6", 1.0, Code, KEY_6},
    {"", "", 0.0, EndRow},
    {"7", "7", 1.0, Code, KEY_7},
    {"8", "8", 1.0, Code, KEY_8},
    {"9", "9", 1.0, Code, KEY_9},
    {"", "", 0.0, EndRow},
    {"*", "*", 1.0, Code, KEY_KPASTERISK},
    {"0", "0", 1.0, Code, KEY_0},
    {"#", "#", 1.0, Code, KEY_3, 0, Shift},
    {"", "", 0.0, EndRow},
    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_cyrillic[] = {
    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", ";", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", ":", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"ю", "Ю", 1.0, Code, KEY_DOT},
    {"э", "Э", 1.0, Code, KEY_APOSTROPHE, &layouts[ComposeCyrE]},
    {"ё", "Ё", 1.0, Code, KEY_GRAVE, &layouts[ComposeCyrE]},
    {"", "", 0.0, EndRow},

    {"й", "Й", 1.0, Code, KEY_Q, &layouts[ComposeCyrJ]},
    {"ц", "Ц", 1.0, Code, KEY_W, &layouts[ComposeCyrTse]},
    {"у", "У", 1.0, Code, KEY_E},
    {"к", "К", 1.0, Code, KEY_R, &layouts[ComposeCyrK]},
    {"е", "Е", 1.0, Code, KEY_T, &layouts[ComposeCyrE]},
    {"н", "Н", 1.0, Code, KEY_Y},
    {"г", "Г", 1.0, Code, KEY_U, &layouts[ComposeCyrG]},
    {"ш", "ш", 1.0, Code, KEY_I},
    {"щ", "щ", 1.0, Code, KEY_O},
    {"з", "з", 1.0, Code, KEY_P},
    {"х", "Х", 1.0, Code, KEY_LEFTBRACE},
    {"ъ", "Ъ", 0.5, Code, KEY_RIGHTBRACE},
    {"", "", 0.0, EndRow},

    {"ф", "Ф", 1.0, Code, KEY_A},
    {"ы", "Ы", 1.0, Code, KEY_S, &layouts[ComposeCyrI]},
    {"в", "В", 1.0, Code, KEY_D},
    {"а", "А", 1.0, Code, KEY_F},
    {"п", "П", 1.0, Code, KEY_G},
    {"р", "Р", 1.0, Code, KEY_H},
    {"о", "О", 1.0, Code, KEY_J},
    {"л", "Л", 1.0, Code, KEY_K, &layouts[ComposeCyrL]},
    {"д", "Д", 1.0, Code, KEY_L},
    {"ж", "Ж", 1.0, Code, KEY_SEMICOLON},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"я", "Я", 1.0, Code, KEY_Z},
    {"ч", "Ч", 1.0, Code, KEY_X, &layouts[ComposeCyrChe]},
    {"c", "С", 1.0, Code, KEY_C},
    {"м", "М", 1.0, Code, KEY_V},
    {"и", "И", 1.0, Code, KEY_B, &layouts[ComposeCyrI]},
    {"т", "Т", 1.0, Code, KEY_N},
    {"ь", "Ь", 1.0, Code, KEY_M},
    {"б", "Б", 1.0, Code, KEY_COMMA},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},

    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {",", "'", 1.0, Code, KEY_EQUAL, &layouts[ComposeMath]},
    {"", "Tab", 4.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_arabic[] = {
    {"١", "!", 1.0, Code, KEY_1},
    {"٢", "@", 1.0, Code, KEY_2},
    {"٣", "#", 1.0, Code, KEY_3},
    {"٤", ";", 1.0, Code, KEY_4},
    {"٥", "%", 1.0, Code, KEY_5},
    {"٦", ":", 1.0, Code, KEY_6},
    {"٧", "&", 1.0, Code, KEY_7},
    {"٨", "*", 1.0, Code, KEY_8},
    {"٩", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"٠", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"", "", 0.0, EndRow},

    {"ض", "ـَ", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"ص", "ـً", 1.0, Code, KEY_W},
    {"ث", "ـُ", 1.0, Code, KEY_E},
    {"ق", "ـٌ", 1.0, Code, KEY_R},
    {"ف", "ﻹ", 1.0, Code, KEY_T},
    {"غ", "إ", 1.0, Code, KEY_Y},
    {"ع", "`", 1.0, Code, KEY_U},
    {"ه", "", 1.0, Code, KEY_I},
    {"خ", ";", 1.0, Code, KEY_O},
    {"ح", "", 1.0, Code, KEY_P},
    {"ج", "<", 1.0, Code, KEY_LEFTBRACE},
    {"", "", 0.0, EndRow},

    {"ش", "ـِ", 1.0, Code, KEY_A},
    {"س", "ـٍ", 1.0, Code, KEY_S},
    {"ي", "]", 1.0, Code, KEY_D},
    {"ب", "[", 1.0, Code, KEY_F},
    {"ل", "ﻷ", 1.0, Code, KEY_G},
    {"ا", "أ", 1.0, Code, KEY_H},
    {"ت", "ـ", 1.0, Code, KEY_J},
    {"ن", "،", 1.0, Code, KEY_K},
    {"م", "/", 1.0, Code, KEY_L},
    {"ك", ":", 1.0, Code, KEY_SEMICOLON},
    {"ط", "\"", 1.0, Code, KEY_APOSTROPHE},
    {"", "", 0.0, EndRow},

    {"ذ", "~", 1.0, Code, KEY_Z},
    {"ء", "ـْ", 1.0, Code, KEY_X},
    {"ؤ", "}", 1.0, Code, KEY_C},
    {"ر", "{", 1.0, Code, KEY_V},
    {"ى", "ﻵ", 1.0, Code, KEY_B},
    {"ة", "'", 1.0, Code, KEY_N},
    {"و", ",", 1.0, Code, KEY_M},
    {"ز", "؟", 1.0, Code, KEY_COMMA},
    {"ظ", ".", 1.0, Code, KEY_DOT},
    {"د", ">", 1.0, Code, KEY_RIGHTBRACE},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},

    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"⇧", "⇫", 1.0, Mod, Shift, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {"", "Tab", 5.0, Code, KEY_SPACE},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_georgian[] = {
    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", ";", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", ":", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"", "", 0.0, EndRow},

    {"ქ", "Q", 1.0, Code, KEY_Q},
    {"წ", "ჭ", 1.0, Code, KEY_W},
    {"ე", "E", 1.0, Code, KEY_E},
    {"რ", "ღ", 1.0, Code, KEY_R},
    {"ტ", "თ", 1.0, Code, KEY_T},
    {"ყ", "Y", 1.0, Code, KEY_Y},
    {"უ", "U", 1.0, Code, KEY_U},
    {"ი", "I", 1.0, Code, KEY_I},
    {"ო", "O", 1.0, Code, KEY_O},
    {"პ", "P", 1.0, Code, KEY_P},
    {"", "", 0.0, EndRow},

    {"ა", "A", 1.0, Code, KEY_A},
    {"ს", "შ", 1.0, Code, KEY_S},
    {"დ", "D", 1.0, Code, KEY_D},
    {"ფ", "F", 1.0, Code, KEY_F},
    {"გ", "G", 1.0, Code, KEY_G},
    {"ჰ", "H", 1.0, Code, KEY_H},
    {"ჯ", "ჟ", 1.0, Code, KEY_J},
    {"კ", "K", 1.0, Code, KEY_K},
    {"ლ", "L", 1.0, Code, KEY_L},
    {";", ":", 1.0, Code, KEY_SEMICOLON, &layouts[ComposePunctuation]},
    {"", "", 0.0, EndRow},

    {"ზ", "ძ", 1.0, Code, KEY_Z},
    {"ხ", "X", 1.0, Code, KEY_X},
    {"ც", "ჩ", 1.0, Code, KEY_C},
    {"ვ", "V", 1.0, Code, KEY_V},
    {"ბ", "B", 1.0, Code, KEY_B},
    {"ნ", "N", 1.0, Code, KEY_N},
    {"მ", "M", 1.0, Code, KEY_M},
    {",", "<", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {".", ">", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},

    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"⇧", "⇫", 1.0, Mod, Shift, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {"", "Tab", 5.0, Code, KEY_SPACE},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_persian[] = {
    {"۱", "|", 1.0, Code, KEY_1},
    {"۲", "٬", 1.0, Code, KEY_2},
    {"۳", "#", 1.0, Code, KEY_3},
    {"۴", "﷼", 1.0, Code, KEY_4},
    {"۵", "٪", 1.0, Code, KEY_5},
    {"۶", "×", 1.0, Code, KEY_6},
    {"۷", "/", 1.0, Code, KEY_7},
    {"۸", "*", 1.0, Code, KEY_8},
    {"۹", ")", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"۰", "(", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"-", "_", 1.0, Code, KEY_MINUS, &layouts[ComposeMath]},
    {"=", "+", 1.0, Code, KEY_EQUAL, &layouts[ComposeMath]},
    {"", "", 0.0, EndRow},

    {"ض", "ﹿ", 1.0, Code, KEY_Q},
    {"ص", "ـٌ", 1.0, Code, KEY_W},
    {"ث", "ـٍ", 1.0, Code, KEY_E},
    {"ق", "ـً", 1.0, Code, KEY_R},
    {"ف", "ـُ", 1.0, Code, KEY_T},
    {"غ", "ـِ", 1.0, Code, KEY_Y},
    {"ع", "ـَ", 1.0, Code, KEY_U},
    {"ه", "ﹽ", 1.0, Code, KEY_I},
    {"خ", "]", 1.0, Code, KEY_O},
    {"ح", "[", 1.0, Code, KEY_P},
    {"ج", "}", 1.0, Code, KEY_LEFTBRACE},
    {"چ", "{", 1.0, Code, KEY_RIGHTBRACE},
    {"", "", 0.0, EndRow},

    {"ش", "ؤ", 1.0, Code, KEY_A},
    {"س", "ئ", 1.0, Code, KEY_S},
    {"ی", "ي", 1.0, Code, KEY_D},
    {"ب", "إ", 1.0, Code, KEY_F},
    {"ل", "أ", 1.0, Code, KEY_G},
    {"ا", "آ", 1.0, Code, KEY_H},
    {"ت", "ة", 1.0, Code, KEY_J},
    {"ن", "»", 1.0, Code, KEY_K},
    {"م", "«", 1.0, Code, KEY_L},
    {"ک", ":", 1.0, Code, KEY_SEMICOLON},
    {"گ", "؛", 1.0, Code, KEY_APOSTROPHE},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"ظ", "ك", 1.0, Code, KEY_Z},
    {"ط", "ـٓ", 1.0, Code, KEY_X},
    {"ژ", ">", 1.0, Code, KEY_BACKSLASH},
    {"ز", "<", 1.0, Code, KEY_C},
    {"ر", "ـٰ", 1.0, Code, KEY_V},
    {"ذ", "⇑", 1.0, Code, KEY_B},
    {"د", "ـٔ", 1.0, Code, KEY_N},
    {"پ", "ء", 1.0, Code, KEY_M},
    {"و", "\\", 1.0, Code, KEY_COMMA},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {".", "،", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"", "Tab", 4.0, Code, KEY_SPACE},
    {"⥣", "↥", 1.0, Code, KEY_GRAVE},
    {"؟", "!", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_greek[] = {
    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"-", "_", 1.0, Code, KEY_MINUS, &layouts[ComposeMath]},
    {"=", "+", 1.0, Code, KEY_EQUAL, &layouts[ComposeMath]},
    {"", "", 0.0, EndRow},

    {";", ":", 1.0, Code, KEY_Q, &layouts[ComposePunctuation]},
    {"ς", "Σ", 1.0, Code, KEY_W},
    {"ε", "Ε", 1.0, Code, KEY_E},
    {"ρ", "Ρ", 1.0, Code, KEY_R},
    {"τ", "Τ", 1.0, Code, KEY_T},
    {"υ", "Υ", 1.0, Code, KEY_Y},
    {"θ", "Θ", 1.0, Code, KEY_U},
    {"ι", "Ι", 1.0, Code, KEY_I},
    {"ο", "Ο", 1.0, Code, KEY_O},
    {"π", "Π", 1.0, Code, KEY_P},
    {"", "", 0.0, EndRow},

    {"α", "A", 1.0, Code, KEY_A},
    {"σ", "Σ", 1.0, Code, KEY_S},
    {"δ", "Δ", 1.0, Code, KEY_D},
    {"φ", "Φ", 1.0, Code, KEY_F},
    {"γ", "Γ", 1.0, Code, KEY_G},
    {"η", "Η", 1.0, Code, KEY_H},
    {"ξ", "Ξ", 1.0, Code, KEY_J},
    {"κ", "Κ", 1.0, Code, KEY_K},
    {"λ", "Λ", 1.0, Code, KEY_L},
    {"΄", "¨", 1.0, Code, KEY_SEMICOLON, &layouts[ComposeBracket]},
    {"", "", 0.0, EndRow},

    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"ζ", "Ζ", 1.0, Code, KEY_Z},
    {"χ", "Χ", 1.0, Code, KEY_X},
    {"ψ", "Ψ", 1.0, Code, KEY_C},
    {"ω", "Ω", 1.0, Code, KEY_V},
    {"β", "Β", 1.0, Code, KEY_B},
    {"ν", "Ν", 1.0, Code, KEY_N},
    {"μ", "Μ", 1.0, Code, KEY_M},
    {"/", "\\", 1.0, Code, KEY_SLASH},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.5, NextLayer, .scheme = 1},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {"", "Tab", 5, Code, KEY_SPACE},
    {".", "\"", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 2, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_hebrew[] = {
    {"/", "/", 1.0, Code, KEY_Q},
    {"'", "'", 1.0, Code, KEY_W, &layouts[ComposeBracket]},
    {"ק", "ק", 1.0, Code, KEY_E},
    {"ר", "ר", 1.0, Code, KEY_R},
    {"א", "א", 1.0, Code, KEY_T},
    {"ט", "ט", 1.0, Code, KEY_Y},
    {"ו", "ו", 1.0, Code, KEY_U},
    {"ן", "ן", 1.0, Code, KEY_I},
    {"ם", "ם", 1.0, Code, KEY_O},
    {"פ", "פ", 1.0, Code, KEY_P},
    {"", "", 0.0, EndRow},

    {"ש", "ש", 1.0, Code, KEY_A},
    {"ד", "ד", 1.0, Code, KEY_S},
    {"ג", "ג", 1.0, Code, KEY_D},
    {"כ", "כ", 1.0, Code, KEY_F},
    {"ע", "ע", 1.0, Code, KEY_G},
    {"י", "י", 1.0, Code, KEY_H},
    {"ח", "ח", 1.0, Code, KEY_J},
    {"ל", "ל", 1.0, Code, KEY_K},
    {"ך", "ך", 1.0, Code, KEY_L},
    {"ף", "ף", 1.0, Code, KEY_SEMICOLON},
    {"", "", 0.0, EndRow},

    {"ז", "ז", 1.0, Code, KEY_Z},
    {"ס", "ס", 1.0, Code, KEY_X},
    {"ב", "ב", 1.0, Code, KEY_C},
    {"ה", "ה", 1.0, Code, KEY_V},
    {"נ", "נ", 1.0, Code, KEY_B},
    {"מ", "מ", 1.0, Code, KEY_N},
    {"צ", "צ", 1.0, Code, KEY_M},
    {"ת", "ת", 1.0, Code, KEY_COMMA},
    {"ץ", "ץ", 1.0, Code, KEY_DOT},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},

    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {",", "\"", 1.0, Code, KEY_APOSTROPHE, &layouts[ComposeMath]},
    {"", "Tab", 3.5, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation]},
    {"?", "?", 1.0, Code, KEY_SLASH, &layouts[ComposePunctuation], Shift},
    {"Enter", "Enter", 1.5, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_compose_a[] = {
    {"à", "À", 1.0, Copy, 0x00E0, 0, 0x00C0},
    {"á", "Á", 1.0, Copy, 0x00E1, 0, 0x00C1},
    {"â", "Â", 1.0, Copy, 0x00E2, 0, 0x00C2},
    {"ã", "Ã", 1.0, Copy, 0x00E3, 0, 0x00C3},
    {"ä", "Ä", 1.0, Copy, 0x00E4, 0, 0x00C4},
    {"å", "Å", 1.0, Copy, 0x00E5, 0, 0x00C5},
    {"æ", "Æ", 1.0, Copy, 0x00E7, 0, 0x00C6},
    {"ā", "Ā", 1.0, Copy, 0x0101, 0, 0x0100},
    {"ă", "Ă", 1.0, Copy, 0x0103, 0, 0x0102},
    {"ą", "Ą", 1.0, Copy, 0x0105, 0, 0x0104},
    {"", "", 0.0, EndRow},
    {"α", "Α", 1.0, Copy, 0x03B1, 0, 0x0391},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_e[] = {
    {"è", "È", 1.0, Copy, 0x00E8, 0, 0x00C8},
    {"é", "É", 1.0, Copy, 0x00E9, 0, 0x00C9},
    {"ê", "Ê", 1.0, Copy, 0x00EA, 0, 0x00CA},
    {"ë", "Ë", 1.0, Copy, 0x00EB, 0, 0x00CB},
    {"ē", "Ē", 1.0, Copy, 0x0113, 0, 0x0112},
    {"ĕ", "Ĕ", 1.0, Copy, 0x0115, 0, 0x0114},
    {"ė", "Ė", 1.0, Copy, 0x0117, 0, 0x0116},
    {"ę", "Ę", 1.0, Copy, 0x0119, 0, 0x0118},
    {"ě", "Ě", 1.0, Copy, 0x011B, 0, 0x011A},
    {"", "", 1.0, Pad},
    {"", "", 0.0, EndRow},
    {"ε", "Ε", 1.0, Copy, 0x03B5, 0, 0x0395},
    {"ǝ", "Ə", 1.0, Copy, 0x0259, 0, 0x018F},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_y[] = {
    {"ý", "Ý", 1.0, Copy, 0x00FD, 0, 0x00DD},
    {"ÿ", "Ÿ", 1.0, Copy, 0x00FF, 0, 0x0178},
    {"ŷ", "Ŷ", 1.0, Copy, 0x0177, 0, 0x0176},
    {"", "", 7.0, Pad},
    {"", "", 0.0, EndRow},
    {"υ", "Υ", 1.0, Copy, 0x03C5, 0, 0x03A5},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_u[] = {
    {"ù", "Ù", 1.0, Copy, 0x00F9, 0, 0x00D9},
    {"ú", "Ú", 1.0, Copy, 0x00FA, 0, 0x00DA},
    {"û", "Û", 1.0, Copy, 0x00FB, 0, 0x00DB},
    {"ü", "Ü", 1.0, Copy, 0x00FC, 0, 0x00DC},
    {"ũ", "Ũ", 1.0, Copy, 0x0169, 0, 0x0168},
    {"ū", "Ū", 1.0, Copy, 0x016B, 0, 0x016A},
    {"ŭ", "Ŭ", 1.0, Copy, 0x016D, 0, 0x016C},
    {"ů", "Ů", 1.0, Copy, 0x016F, 0, 0x016E},
    {"ű", "Ű", 1.0, Copy, 0x0171, 0, 0x0170},
    {"ų", "Ų", 1.0, Copy, 0x0173, 0, 0x0172},
    {"", "", 0.0, EndRow},
    {"υ", "Υ", 1.0, Copy, 0x03C5, 0, 0x03A5},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_o[] = {
    {"ò", "Ò", 1.0, Copy, 0x00F2, 0, 0x00D2},
    {"ó", "Ó", 1.0, Copy, 0x00F3, 0, 0x00D3},
    {"ô", "Ô", 1.0, Copy, 0x00F4, 0, 0x00D4},
    {"õ", "Õ", 1.0, Copy, 0x00F5, 0, 0x00D5},
    {"ö", "Ö", 1.0, Copy, 0x00F6, 0, 0x00D6},
    {"ø", "Ø", 1.0, Copy, 0x00F8, 0, 0x00D8},
    {"ō", "Ō", 1.0, Copy, 0x014D, 0, 0x014C},
    {"ŏ", "Ŏ", 1.0, Copy, 0x014F, 0, 0x014E},
    {"ő", "Ő", 1.0, Copy, 0x0151, 0, 0x0150},
    {"œ", "Œ", 1.0, Copy, 0x0153, 0, 0x0152},
    {"", "", 0.0, EndRow},
    {"ο", "Ο", 1.0, Copy, 0x03BF, 0, 0x039F},
    {"ω", "Ο", 1.0, Copy, 0x03C9, 0, 0x03A9},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_i[] = {
    {"ì", "Ì", 1.0, Copy, 0x00EC, 0, 0x00CC},
    {"í", "Í", 1.0, Copy, 0x00ED, 0, 0x00CD},
    {"î", "Î", 1.0, Copy, 0x00EE, 0, 0x00CE},
    {"ï", "Ï", 1.0, Copy, 0x00EF, 0, 0x00CF},
    {"ĩ", "Ĩ", 1.0, Copy, 0x0129, 0, 0x0128},
    {"ī", "Ī", 1.0, Copy, 0x012B, 0, 0x012A},
    {"ĭ", "Ĭ", 1.0, Copy, 0x012D, 0, 0x012C},
    {"į", "Į", 1.0, Copy, 0x012F, 0, 0x012E},
    {"ı", "I", 1.0, Copy, 0x0131, 0, 0x0049},
    {"i", "İ", 1.0, Copy, 0x0069, 0, 0x0130},
    {"", "", 0.0, EndRow},
    {"ι", "Ι", 1.0, Copy, 0x03B9, 0, 0x0399},
    {"η", "Η", 1.0, Copy, 0x03B7, 0, 0x0397},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_emoji[] = {
    {"🙂", "🙏", 1.0, Copy, 0x1f642, 0, 0x1f64f}, // Emojis
    {"😀", "🙋", 1.0, Copy, 0x1f600, 0, 0x1f64b},
    {"😁", "✋", 1.0, Copy, 0x1f601, 0, 0x270B},
    {"😂", "🙇", 1.0, Copy, 0x1f602, 0, 0x1f647},
    {"😃", "👨", 1.0, Copy, 0x1f603, 0, 0x1f468},
    {"😄", "👩", 1.0, Copy, 0x1f604, 0, 0x1f469},
    {"😅", "👶", 1.0, Copy, 0x1f605, 0, 0x1f476},
    {"😆", "👻", 1.0, Copy, 0x1f606, 0, 0x1f47b},
    {"😇", "✨", 1.0, Copy, 0x1f607, 0, 0x2728},
    {"🤣", "💰", 1.0, Copy, 0x1f923, 0, 0x1f4b0},
    {"", "", 0.0, EndRow},
    {"😉", "🐕", 1.0, Copy, 0x1f609, 0, 0x1f415},
    {"😊", "🐈", 1.0, Copy, 0x1f60a, 0, 0x1f408},
    {"😋", "🐧", 1.0, Copy, 0x1f60b, 0, 0x1f427},
    {"😌", "🐇", 1.0, Copy, 0x1f60c, 0, 0x1f407},
    {"😍", "💔", 1.0, Copy, 0x1f60d, 0, 0x1f494},
    {"😘", "💕", 1.0, Copy, 0x1f618, 0, 0x1f495},
    {"😎", "❤", 1.0, Copy, 0x1f60e, 0, 0x2764},
    {"😐", "😏", 1.0, Copy, 0x1f610, 0, 0x1f60f},
    {"😒", "👀", 1.0, Copy, 0x1f612, 0, 0x1f440},
    {"😓", "💀", 1.0, Copy, 0x1f613, 0, 0x1f480},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.0, Mod, Shift, .scheme = 1},
    {"😛", "😜", 1.0, Copy, 0x1f61b, 0, 0x1f61c},
    {"😮", "😝", 1.0, Copy, 0x1f62e, 0, 0x1f61d},
    {"😟", "😞", 1.0, Copy, 0x1f61f, 0, 0x1f61e},
    {"😠", "🥺", 1.0, Copy, 0x1f620, 0, 0x1f97a},
    {"😢", "👿", 1.0, Copy, 0x1f622, 0, 0x1f47f},
    {"😭", "😯", 1.0, Copy, 0x1f62d, 0, 0x1f62f},
    {"😳", "😕", 1.0, Copy, 0x1f633, 0, 0x1f615},
    {"😴", "😵", 1.0, Copy, 0x1f634, 0, 0x1f635},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"👆", "👊", 1.0, Copy, 0x1f446, 0, 0x1f44a},
    {"👇", "👌", 1.0, Copy, 0x1f447, 0, 0x1f44c},
    {"👈", "👏", 1.0, Copy, 0x1f448, 0, 0x1f44f},
    {"👉", "👐", 1.0, Copy, 0x1f449, 0, 0x1f450},
    {"👋", "🙌", 1.0, Copy, 0x1f44b, 0, 0x1f64c},
    {"👍", "✅", 1.0, Copy, 0x1f44d, 0, 0x2705},
    {"👎", "💪", 1.0, Copy, 0x1f44e, 0, 0x1f4aa},
    {"Enter", "Enter", 1.0, Code, KEY_ENTER, .scheme = 1},
    {"", "", 0.0, Last},
};

static struct key keys_nav[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"⌫", "⌫", 1.0, Code, KEY_BACKSPACE, .scheme = 1},
    {"↑", "↑", 1.0, Code, KEY_UP, .scheme = 1},
    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"q", "q", 1.0, Code, KEY_Q, .scheme = 1},
    {"←", "←", 1.0, Code, KEY_LEFT, .scheme = 1},
    {"Enter", "Enter", 1.0, Code, KEY_ENTER, .scheme = 1},
    {"→", "→", 1.0, Code, KEY_RIGHT, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"", "↹", 1.0, Code, KEY_SPACE, .scheme = 1},
    {"↓", "↓", 1.0, Code, KEY_DOWN, .scheme = 1},
    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {"", "", 0.0, Last},
};

static struct key keys_index[] = {
    {"Full", "Full", 1.0, Layout, 0, &layouts[Full], .scheme = 1},
    {"Wide", "Wide", 0.75, Layout, 0, &layouts[Full]},
    {"Landscape", "Landscape", 1.5, Layout, 0, &layouts[Landscape],
     .scheme = 1},
    {"Simple", "Simple", 1.0, Layout, 0, &layouts[Simple], .scheme = 1},
    {"Dial", "Dial", 0.75, Layout, 0, &layouts[Dialer]},
    {"", "", 0.0, EndRow},

    {"Special", "Special", 1.5, Layout, 0, &layouts[Special], .scheme = 1},
    {"LandSc", "LandSc", 1.0, Layout, 0, &layouts[LandscapeSpecial]},
    {"Pad", "Pad", 1.0, Layout, 0, &layouts[SpecialPad]},
    {"Nav", "Nav", 1.0, Layout, 0, &layouts[Nav], .scheme = 1},
    {"123", "123", 1.0, Layout, 0, &layouts[Dialer], .scheme = 1},
    {"🙂", "🙂", 1.0, Layout, 0, &layouts[Emoji], .scheme = 1},
    {"", "", 0.0, EndRow},

    {"Абв", "Абв", 1.0, Layout, 0, &layouts[Cyrillic], .scheme = 1},
    {"αβγ", "αβγ", 1.0, Layout, 0, &layouts[Greek], .scheme = 1},
    {"ابج", "ابج", 1.0, Layout, 0, &layouts[Arabic], .scheme = 1},
    {"فر", "فر", 1.0, Layout, 0, &layouts[Persian], .scheme = 1},
    {"აბგ", "აბგ", 1.0, Layout, 0, &layouts[Georgian], .scheme = 1},
    {"א", "א", 1.0, Layout, 0, &layouts[Hebrew], .scheme = 1},
    {"", "", 0.0, Last},
};

static struct key keys_landscape[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"", "", 0.5, Pad, .scheme = 1},
    {"q", "Q", 1.0, Code, KEY_Q, &layouts[Emoji]},
    {"w", "W", 1.0, Code, KEY_W, &layouts[ComposeW]},
    {"e", "E", 1.0, Code, KEY_E, &layouts[ComposeE]},
    {"r", "R", 1.0, Code, KEY_R, &layouts[ComposeR]},
    {"t", "T", 1.0, Code, KEY_T, &layouts[ComposeT]},
    {"y", "Y", 1.0, Code, KEY_Y, &layouts[ComposeY]},
    {"u", "U", 1.0, Code, KEY_U, &layouts[ComposeU]},
    {"i", "I", 1.0, Code, KEY_I, &layouts[ComposeI]},
    {"o", "O", 1.0, Code, KEY_O, &layouts[ComposeO]},
    {"p", "P", 1.0, Code, KEY_P, &layouts[ComposeP]},
    {"", "", 0.5, Pad, .scheme = 1},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"↑", "↑", 0.75, Code, KEY_UP, .scheme = 1},
    {"↓", "↓", 0.75, Code, KEY_DOWN, .scheme = 1},
    {"", "", 0.5, Pad, .scheme = 1},
    {"a", "A", 1.0, Code, KEY_A, &layouts[ComposeA]},
    {"s", "S", 1.0, Code, KEY_S, &layouts[ComposeS]},
    {"d", "D", 1.0, Code, KEY_D, &layouts[ComposeD]},
    {"f", "F", 1.0, Code, KEY_F, &layouts[ComposeF]},
    {"g", "G", 1.0, Code, KEY_G, &layouts[ComposeG]},
    {"h", "H", 1.0, Code, KEY_H, &layouts[ComposeH]},
    {"j", "J", 1.0, Code, KEY_J, &layouts[ComposeJ]},
    {"k", "K", 1.0, Code, KEY_K, &layouts[ComposeK]},
    {"l", "L", 1.0, Code, KEY_L, &layouts[ComposeL]},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE, &layouts[ComposeBracket]},
    {"/", ">", 1.0, Code, KEY_SLASH},
    {"", "", 0.0, EndRow},

    {"←", "←", 0.75, Code, KEY_LEFT, .scheme = 1},
    {"→", "→", 0.75, Code, KEY_RIGHT, .scheme = 1},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"z", "Z", 1.0, Code, KEY_Z, &layouts[ComposeZ]},
    {"x", "X", 1.0, Code, KEY_X, &layouts[ComposeX]},
    {"c", "C", 1.0, Code, KEY_C, &layouts[ComposeC]},
    {"v", "V", 1.0, Code, KEY_V, &layouts[ComposeV]},
    {"b", "B", 1.0, Code, KEY_B, &layouts[ComposeB]},
    {"n", "N", 1.0, Code, KEY_N, &layouts[ComposeN]},
    {"m", "M", 1.0, Code, KEY_M, &layouts[ComposeM]},
    {"", "", 0.5, Pad, .scheme = 1},
    {"-", "_", 1.0, Code, KEY_MINUS, &layouts[ComposeBracket]},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Cmp", "Cmp", 1.0, Compose, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {"", "Tab", 5.0, Code, KEY_SPACE},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_landscape_special[] = {
    {"Esc", "Esc", 1.0, Code, KEY_ESC, .scheme = 1},
    {"", "", 0.5, Pad, .scheme = 1},
    {"1", "!", 1.0, Code, KEY_1},
    {"2", "@", 1.0, Code, KEY_2},
    {"3", "#", 1.0, Code, KEY_3},
    {"4", "$", 1.0, Code, KEY_4},
    {"5", "%", 1.0, Code, KEY_5},
    {"6", "^", 1.0, Code, KEY_6},
    {"7", "&", 1.0, Code, KEY_7},
    {"8", "*", 1.0, Code, KEY_8},
    {"9", "(", 1.0, Code, KEY_9, &layouts[ComposeBracket]},
    {"0", ")", 1.0, Code, KEY_0, &layouts[ComposeBracket]},
    {"", "", 0.5, Pad, .scheme = 1},
    {"Tab", "Tab", 1.0, Code, KEY_TAB, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⇈", "⇈", 1.0, Code, KEY_PAGEUP, .scheme = 1},
    {"⇊", "⇊", 1.0, Code, KEY_PAGEDOWN, .scheme = 1},
    {"CpL", "CpL", 1.0, Mod, CapsLock, .scheme = 1},
    {"🙂", "🙂", 1.0, Layout, 0, &layouts[Emoji]},
    {"`", "~", 1.0, Code, KEY_GRAVE},
    {"'", "\"", 1.0, Code, KEY_APOSTROPHE},
    {"-", "_", 1.0, Code, KEY_MINUS},
    {"=", "+", 1.0, Code, KEY_EQUAL},
    {"[", "{", 1.0, Code, KEY_LEFTBRACE},
    {"]", "}", 1.0, Code, KEY_RIGHTBRACE},
    {"\\", "|", 1.0, Code, KEY_BACKSLASH},
    {"/", ">", 1.0, Code, KEY_SLASH},
    {"Del", "Del", 1.0, Code, KEY_DELETE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"⇤", "⇤", 1.0, Code, KEY_HOME, .scheme = 1},
    {"⇥", "⇥", 1.0, Code, KEY_END, .scheme = 1},
    {"⇧", "⇫", 2.0, Mod, Shift, .scheme = 1},
    {";", ":", 1.0, Code, KEY_SEMICOLON},
    {"<", "«", 1.0, Code, KEY_COMMA, 0, AltGr},
    {">", "»", 1.0, Code, KEY_DOT, 0, AltGr},
    {"¡", "¿", 1.0, Code, KEY_MENU},
    {",", "'", 1.0, Code, KEY_COMMA, &layouts[ComposeMath]},
    {".", "?", 1.0, Code, KEY_DOT, &layouts[ComposePunctuation]},
    {"/", ">", 1.0, Code, KEY_SLASH},
    {"", "", 0.5, Pad, .scheme = 1},
    {"⌫", "⌫", 1.5, Code, KEY_BACKSPACE, .scheme = 1},
    {"", "", 0.0, EndRow},

    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"⌨͕", "⌨͔", 1.0, NextLayer, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"Sup", "Sup", 1.0, Mod, Super, .scheme = 1},
    {"", "Tab", 5.0, Code, KEY_SPACE},
    {"Alt", "Alt", 1.0, Mod, Alt, .scheme = 1},
    {"AGr", "AGr", 1.0, Mod, AltGr, .scheme = 1},
    {"Enter", "Enter", 2.0, Code, KEY_ENTER, .scheme = 1},

    /* end of layout */
    {"", "", 0.0, Last},
};

static struct key keys_compose_w[] = {
    {"ŵ", "Ŵ", 1.0, Copy, 0x0175, 0, 0x0174},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_r[] = {
    {"ŕ", "Ŕ", 1.0, Copy, 0x0155, 0, 0x0154},
    {"ŗ", "Ŗ", 1.0, Copy, 0x0157, 0, 0x0156},
    {"ř", "Ř", 1.0, Copy, 0x0159, 0, 0x0158},
    {"", "", 7.0, Pad},
    {"", "", 0.0, EndRow},
    {"ρ", "Ρ", 1.0, Copy, 0x03C1, 0, 0x03A1},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_t[] = {
    {"ț", "Ț", 1.0, Copy, 0x021B, 0, 0x021A},
    {"ť", "Ť", 1.0, Copy, 0x0165, 0, 0x0164},
    {"ŧ", "Ŧ", 1.0, Copy, 0x0167, 0, 0x0166},
    {"þ", "Þ", 1.0, Copy, 0x00FE, 0, 0x00DE},
    {"", "", 6.0, Pad},
    {"", "", 0.0, EndRow},
    {"τ", "Τ", 1.0, Copy, 0x03C4, 0, 0x03A4},
    {"θ", "Θ", 1.0, Copy, 0x03B8, 0, 0x0398},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_p[] = {
    {"π", "Π", 1.0, Copy, 0x03C0, 0, 0x03A0},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_s[] = {
    {"ś", "Ś", 1.0, Copy, 0x015B, 0, 0x015A},
    {"ŝ", "Ŝ", 1.0, Copy, 0x015D, 0, 0x015C},
    {"ş", "Ş", 1.0, Copy, 0x015F, 0, 0x015E},
    {"š", "Š", 1.0, Copy, 0x0161, 0, 0x0160},
    {"ß", "ẞ", 1.0, Copy, 0x00DF, 0, 0x1E9E},
    {"", "", 5.0, Pad},
    {"", "", 0.0, EndRow},
    {"σ", "Σ", 1.0, Copy, 0x03C3, 0, 0x03A3},
    {"ς", "Σ", 1.0, Copy, 0x03C2, 0, 0x03A3},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_d[] = {
    {"ð", "Ð", 1.0, Copy, 0x00F0, 0, 0x00D0},
    {"ď", "Ď", 1.0, Copy, 0x010F, 0, 0x010E},
    {"đ", "Đ", 1.0, Copy, 0x0111, 0, 0x0110},
    {"", "", 7.0, Pad},
    {"", "", 0.0, EndRow},
    {"δ", "Δ", 1.0, Copy, 0x03B4, 0, 0x0394},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_f[] = {
    {"φ", "Φ", 1.0, Copy, 0x03C6, 0, 0x03A6},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_g[] = {
    {"ĝ", "Ĝ", 1.0, Copy, 0x011D, 0, 0x011C},
    {"ğ", "Ğ", 1.0, Copy, 0x011F, 0, 0x011E},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"γ", "Γ", 1.0, Copy, 0x03B3, 0, 0x0393},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_h[] = {
    {"ĥ", "Ĥ", 1.0, Copy, 0x0125, 0, 0x0124},
    {"ħ", "Ħ", 1.0, Copy, 0x0127, 0, 0x0126},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"η", "Η", 1.0, Copy, 0x03B7, 0, 0x0397},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_j[] = {
    {"ĵ", "Ĵ", 1.0, Copy, 0x0135, 0, 0x0134},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 10.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_k[] = {
    {"ķ", "Ķ", 1.0, Copy, 0x0137, 0, 0x0136},
    {"ǩ", "Ǩ", 1.0, Copy, 0x01E9, 0, 0x01E8},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"κ", "Κ", 1.0, Copy, 0x03BA, 0, 0x039A},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_l[] = {
    {"ľ", "Ľ", 1.0, Copy, 0x013E, 0, 0x013D},
    {"ŀ", "Ŀ", 1.0, Copy, 0x0140, 0, 0x013F},
    {"ł", "Ł", 1.0, Copy, 0x0142, 0, 0x0141},
    {"", "", 7.0, Pad},
    {"", "", 0.0, EndRow},
    {"λ", "Λ", 1.0, Copy, 0x03BB, 0, 0x039B},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_z[] = {
    {"ź", "Ź", 1.0, Copy, 0x017A, 0, 0x0179},
    {"ż", "Ż", 1.0, Copy, 0x017C, 0, 0x017B},
    {"ž", "Ž", 1.0, Copy, 0x017E, 0, 0x017D},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"ζ", "Ζ", 1.0, Copy, 0x03B6, 0, 0x0396},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_x[] = {
    {"χ", "Χ", 1.0, Copy, 0x03C7, 0, 0x03A7},
    {"ξ", "Ξ", 1.0, Copy, 0x03BE, 0, 0x039E},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_c[] = {
    {"ç", "Ç", 1.0, Copy, 0x00E7, 0, 0x00C7},
    {"ć", "Ć", 1.0, Copy, 0x0107, 0, 0x0106},
    {"ĉ", "Ĉ", 1.0, Copy, 0x0109, 0, 0x0108},
    {"ċ", "Ċ", 1.0, Copy, 0x010B, 0, 0x010A},
    {"č", "Č", 1.0, Copy, 0x010D, 0, 0x010C},
    {"", "", 5.0, Pad},
    {"", "", 0.0, EndRow},
    {"χ", "Χ", 1.0, Copy, 0x03C7, 0, 0x03A7},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_v[] = {
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_b[] = {
    {"β", "Β", 1.0, Copy, 0x03B2, 0, 0x0392},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_n[] = {
    {"ñ", "Ñ", 1.0, Copy, 0x00F1, 0, 0x00D1},
    {"ń", "Ń", 1.0, Copy, 0x0144, 0, 0x0143},
    {"ņ", "Ņ", 1.0, Copy, 0x0146, 0, 0x0145},
    {"ň", "Ň", 1.0, Copy, 0x0148, 0, 0x0147},
    {"ŋ", "Ŋ", 1.0, Copy, 0x014B, 0, 0x014A},
    {"", "", 5.0, Pad},
    {"", "", 0.0, EndRow},
    {"ν", "Ν", 1.0, Copy, 0x03BD, 0, 0x039D},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_m[] = {
    {"μ", "Μ", 1.0, Copy, 0x03BC, 0, 0x039C},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_i[] = {
    {"і", "І", 1.0, Copy, 0x0456, 0, 0x0406},
    {"ї", "Ї", 1.0, Copy, 0x0457, 0, 0x0407},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_j[] = {
    {"ј", "Ј", 1.0, Copy, 0x0458, 0, 0x0408},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_e[] = {
    {"є", "Є", 1.0, Copy, 0x0454, 0, 0x0404},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_u[] = {
    {"ў", "Ў", 1.0, Copy, 0x045E, 0, 0x040E},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_l[] = {
    {"љ", "Љ", 1.0, Copy, 0x0459, 0, 0x0409},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_n[] = {
    {"њ", "Њ", 1.0, Copy, 0x045A, 0, 0x040A},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_che[] = {
    {"ћ", "Ћ", 1.0, Copy, 0x045B, 0, 0x040B},
    {"ђ", "Ђ", 1.0, Copy, 0x0452, 0, 0x0402},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_tse[] = {
    {"џ", "Џ", 1.0, Copy, 0x045F, 0, 0x040F},
    {"ѕ", "Ѕ", 1.0, Copy, 0x0455, 0, 0x0405},
    {"", "", 8.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_g[] = {
    {"ѓ", "Ѓ", 1.0, Copy, 0x0453, 0, 0x0403},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_cyr_k[] = {
    {"ќ", "Ќ", 1.0, Copy, 0x0453, 0, 0x040C},
    {"", "", 9.0, Pad},
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 8.5, Pad},
    {"", "", 0.0, EndRow},
    {"Абв", "Абв", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_math[] = {
    {"", "", 0.0, EndRow},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"+", "+", 1, Code, KEY_EQUAL, 0, Shift},
    {"/", "/", 1, Code, KEY_SLASH},
    {"*", "*", 1, Code, KEY_8, 0, Shift},
    {"-", "-", 1, Code, KEY_MINUS},
    {"=", "=", 1, Code, KEY_EQUAL},
    {"_", "_", 1, Code, KEY_MINUS, 0, Shift},
    {"—", "—", 1, Copy, 0x2014, 0, 0x2014},
    {"", "", 1.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_punctuation[] = {
    {"", "", 0.0, EndRow},
    {"", "", 4.5, Pad},
    {".", ".", 1, Code, KEY_DOT},
    {"…", "…", 1, Copy, 0x2026, 0, 0x2026},
    {":", ":", 1, Code, KEY_SEMICOLON, 0, Shift},
    {";", ";", 1, Code, KEY_SEMICOLON, 0},
    {"⍽", "⍽", 1, Copy, 0x202F, 0, 0x00A0},
    {"", "", 0.5, Pad},
    {"", "", 0.0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"", "", 3, Pad},
    {"!", "!", 1, Code, KEY_1, 0, Shift},
    {"?", "?", 1, Code, KEY_DOT, 0, Shift},
    {"·", "·", 1, Copy, 0x2027, 0, 0x2027},
    {",", ",", 1, Code, KEY_COMMA},
    {"", "", 1.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"", "", 9, Pad},
    {"", "", 0.0, Last},
};

static struct key keys_compose_bracket[] = {
    {"", "", 0, EndRow},
    {"", "", 1.5, Pad},
    {"{", "{", 1, Code, KEY_LEFTBRACE, 0, Shift},
    {"}", "}", 1, Code, KEY_RIGHTBRACE, 0, Shift},
    {"[", "[", 1, Code, KEY_LEFTBRACE},
    {"]", "]", 1, Code, KEY_RIGHTBRACE},
    {"", "", 4.5, Pad},
    {"", "", 0, EndRow},
    {"⇧", "⇫", 1.5, Mod, Shift, .scheme = 1},
    {"<", "<", 1, Code, KEY_COMMA, 0, AltGr},
    {">", ">", 1, Code, KEY_SLASH, 0, Shift},
    {"`", "`", 1, Code, KEY_GRAVE},
    {"\"", "\"", 1, Code, KEY_APOSTROPHE, 0, Shift},
    {"'", "'", 1, Code, KEY_APOSTROPHE},
    {"", "", 3.5, Pad},
    {"", "", 0.0, EndRow},
    {"Abc", "Abc", 1.0, BackLayer, .scheme = 1},
    {"Ctr", "Ctr", 1.0, Mod, Ctrl, .scheme = 1},
    {"", "", 8, Pad},
    {"", "", 0.0, Last},
};
