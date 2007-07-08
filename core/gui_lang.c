#include "conf.h"
#include "lang.h"
#include "gui_lang.h"

//-------------------------------------------------------------------
static char* gui_lang_default = \
"  1 \"Main Menu\"\n"

"  2 \"RAW parameters ->\"\n"
"  3 \"OSD parameters ->\"\n"
"  4 \"Histogram parameters ->\"\n"
"  5 \"Zebra parameters ->\"\n"
"  6 \"Scripting parameters ->\"\n"
"  7 \"Visual settings ->\"\n"
"  8 \"Miscellaneous stuff ->\"\n"
"  9 \"Debug parameters ->\"\n"
" 10 \"Reset options to default...\"\n"
" 11 \"Save options now...\"\n"

" 12 \"<- Back\"\n"


" 13 \"RAW\"\n"

" 14 \"Save RAW\"\n"
" 16 \"Only first RAW in series\"\n"
" 17 \"RAW file in dir with JPEG\"\n"
" 18 \"RAW file prefix\"\n"
" 19 \"RAW file extension\"\n"


" 20 \"OSD\"\n"

" 21 \"Show OSD\"\n"
" 22 \"Show RAW/EXP state\"\n"
" 23 \"Show misc values\"\n"
" 24 \"Zoom value\"\n"
" 25 \"Show DOF calculator\"\n"
" 26 \"Show clock\"\n"
" 27 \"OSD layout editor\"\n"
" 28 \"Battery parameters ->\"\n"


" 29 \"Histogram\"\n"

" 30 \"Show live histogram\"\n"
" 31 \"Histogram layout\"\n"
" 32 \"Histogram mode\"\n"
" 33 \"Show histogram over/under EXP\"\n"
" 34 \"Ignore boundary peaks\"\n"
" 35 \"Auto magnify\"\n"


" 36 \"Zebra\"\n"

" 37 \"Draw Zebra\"\n"
" 38 \"Zebra mode\"\n"
" 39 \"UnderExposure threshold\"\n"
" 40 \"OverExposure threshold\"\n"
" 41 \"Restore original screen\"\n"
" 42 \"Restore OSD\"\n"
" 43 \"Draw over zebra\"\n"


" 44 \"Script\"\n"

" 45 \"Load script from file...\"\n"
" 46 \"Script shoot delay (.1s)\"\n"
" 47 \"Current script\"\n"
" 48 \"Script parameters\"\n"


" 49 \"Visual settings\"\n"

" 50 \"Language...\"\n"
" 51 \"OSD codepage\"\n"
" 52 \"Menu RBF font...\"\n"
" 53 \"Colors\"\n"
" 54 \"OSD text\"\n"
" 55 \"OSD background\"\n"
" 56 \"Histogram\"\n"
" 57 \"Histogram background\"\n"
" 58 \"Histogram border\"\n"
" 59 \"Histogram EXP markers\"\n"
" 60 \"Zebra Underexposure\"\n"
" 61 \"Zebra Overexposure\"\n"
" 62 \"Battery icon\"\n"
" 63 \"Menu text\"\n"
" 64 \"Menu background\"\n"
" 65 \"Text reader text\"\n"
" 66 \"Text reader background\"\n"


" 67 \"Miscellaneous\"\n"

" 68 \"File browser\"\n"
" 69 \"Calendar\"\n"
" 70 \"Text file reader ->\"\n"
" 71 \"Games ->\"\n"
" 72 \"Flash-light\"\n"
" 73 \"Show splash screen on load\"\n"
" 74 \"Use zoom buttons for MF\"\n"
" 75 \"<ALT> mode button\"\n"
" 76 \"Draw palette\"\n"
" 77 \"Show build info\"\n"
" 78 \"Show memory info\"\n"


" 79 \"Debug\"\n"

" 80 \"Show PropCases\"\n"
" 81 \"PropCase page\"\n"
" 82 \"Show misc. values\"\n"
" 83 \"Memory browser\"\n"
" 84 \"Dump RAM on ALT +/- press\"\n"
" 85 \"Make card bootable...\"\n"


" 86 \"Battery\"\n"

" 87 \"Voltage MAX\"\n"
" 88 \"Voltage MIN\"\n"
" 89 \"25+ step\"\n"
" 90 \"Show percent\"\n"
" 91 \"Show volts\"\n"
" 92 \"Show icon\"\n"


" 93 \"Text file reader\"\n"

" 94 \"Open new file...\"\n"
" 95 \"Open last opened file\"\n"
" 96 \"Select RBF font\"\n"
" 97 \"Codepage\"\n"
" 98 \"Wrap by words\"\n"
" 99 \"Enable autoscroll\"\n"
"100 \"Autoscroll delay (sec)\"\n"


"101 \"Games\"\n"

"102 \"Reversi\"\n"
"103 \"Sokoban\"\n"

"104 \"*** Reset options ***\"\n"
"105 \"Are you SURE to reset\\noptions to default?\"\n"

"106 \"*** Build Info ***\"\n"
"107 \"CHDK Ver: %s, #%s\\nDate:    %s\\nTime:    %s\\nCamera:  %s\\nFW Vers: %s\"\n"

"108 \"*** Memory Info ***\"\n"
"109 \"Free memory: %d bytes\"\n"

"110 \"*** Information ***\"\n"
"111 \"Please switch your camera\\nto PLAY mode\\nand try again. :)\"\n"

"112 \"File Browser\"\n"
"113 \"Select script file\"\n"
"114 \"Select text file\"\n"
"115 \"Select RBF-font file\"\n"
"116 \"Select language file\"\n"

"117 \"January\"\n"
"118 \"February\"\n"
"119 \"March\"\n"
"120 \"April\"\n"
"121 \"May\"\n"
"122 \"June\"\n"
"123 \"July\"\n"
"124 \"August\"\n"
"125 \"September\"\n"
"126 \"October\"\n"
"127 \"November\"\n"
"128 \"December\"\n"

"129 \"Mon\"\n"
"130 \"Tue\"\n"
"131 \"Wed\"\n"
"132 \"Thu\"\n"
"133 \"Fri\"\n"
"134 \"Sat\"\n"
"135 \"Sun\"\n"

"136 \"Today:\"\n"

"137 \"Ok\"\n"
"138 \"Yes\"\n"
"139 \"No\"\n"
"140 \"Cancel\"\n"

"141 \"Histogram\"\n"
"142 \"DOF calc\"\n"
"143 \"RAW/EXP\"\n"
"144 \"Misc values\"\n"
"145 \"Batt icon\"\n"
"146 \"Batt text\"\n"
"147 \"Clock\"\n"

"148 \"Press SET to draw particular color\"\n"
"149 \"       Press MENU to exit         \"\n"
"150 \"Color\"\n"
"151 \"Use %s to select color\"\n"

"152 \"*** Game Results ***\"\n"
"153 \"You won the game! :)\"\n"
"154 \"You lost the game! :(\"\n"
"155 \"Draw! :/\"\n"

"156 \"*** Wrong move ***\"\n"
"157 \"You can't place here!\"\n"
"158 \"This cell is not empty!\"\n"

"159 \"Move: You     \"\n"
"160 \"Move: Computer\"\n"
"161 \"  GAME  OVER  \"\n"
"162 \" White  Black \"\n"

"163 \"*** About ***\"\n"

"164 \"  Level\"\n"
"165 \"  Moves\"\n"
"166 \"*** Finished ***\"\n"
"167 \"YES!\\n  You did it!  \"\n"

"168 \"*** STARTED ***\"\n"
"169 \"*** INTERRUPTED ***\"\n"
"170 \"*** FINISHED ***\"\n"

"171 \"*** Erase directory ***\"\n"
"172 \"Are you SURE to delete\\nALL files from\\nselected directory?\"\n"
"173 \"*** Delete file ***\"\n"
"174 \"Are you SURE to delete\\nselected file?\"\n"

"175 \"Benchmark\"\n"
"176 \"Calculating...\"\n"
"177 \"Camera benchmark   Press [set] to start\"\n"
"178 \"Screen\"\n"
"179 \"Write       :\"\n"
"180 \"Read        :\"\n"
"181 \"Memory\"\n"
"182 \"Flash-card\"\n"
"183 \"Write (RAW) :\"\n"
"184 \"Write (Mem) :\"\n"
"185 \"Write (64k) :\"\n"
"186 \"Read  (64k) :\"\n"

"187 \"Disable LCD off\"\n"

"188 \"Cut\"\n"
"189 \"Copy\"\n"
"190 \"Paste\"\n"
"191 \"Delete\"\n"
"192 \"Select inverse\"\n"
"193 \"*** Cut files ***\"\n"
"194 \"Are you SURE to cut\\n%d selected files\\nfrom %s/?\"\n"
"195 \"*** Copy files ***\"\n"
"196 \"Are you SURE to copy\\n%d selected files\\nfrom %s/?\"\n"
"197 \"*** Delete files ***\"\n"
"198 \"Are you SURE to delete\\n%d selected files?\"\n"
"199 \"Please wait...\"\n"

"200 \"Show grid lines\"\n"
"201 \"Load grid from file...\"\n"
"202 \"Grid lines\"\n"
"203 \"Grid settings ->\"\n"
"204 \"Select grid file\"\n"
"205 \"Current grid\"\n"

"206 \"Noise reduction\"\n"

;

//-------------------------------------------------------------------
void gui_lang_init() {
    lang_init(GUI_LANG_ITEMS);
    lang_load_from_mem(gui_lang_default);
    if (conf.lang_file && *conf.lang_file) {
        lang_load_from_file(conf.lang_file);
    }
}

//-------------------------------------------------------------------
