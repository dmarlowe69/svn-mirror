#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joyport.h"

/* found definitions */
#define UNKNOWN  -1
#define FOUND_MENU_ID 0
#define FOUND_FILE_MENU 1
#define FOUND_EDIT_MENU 120
#define FOUND_OPTIONS_MENU 130
#define FOUND_SETTINGS_MENU 200
#define FOUND_EXPANSION_MENU 350
#define FOUND_HELP_MENU 900

static char line_buffer[512];

int vice_getline(FILE *file)
{
    char c = 0;
    int counter = 0;

    while (c != '\n' && !feof(file) && counter < 511) {
        c = fgetc(file);
        if (c != 0xd) {
            line_buffer[counter++] = c;
        }
    }
    line_buffer[counter] = 0;

    if (counter >= 4 && !strncmp(line_buffer, "MENU", 4)) {
        line_buffer[counter - 1] = 0;
        return FOUND_MENU_ID;
    }
    if (counter >= 4 && strstr(line_buffer, "File")) {
        return FOUND_FILE_MENU;
    }
    if (counter >= 4 && strstr(line_buffer, "Edit")) {
        return FOUND_EDIT_MENU;
    }
    if (counter >= 7 && strstr(line_buffer, "Options")) {
        return FOUND_OPTIONS_MENU;
    }
    if (counter >= 8 && strstr(line_buffer, "Settings")) {
        return FOUND_SETTINGS_MENU;
    }
    if (counter >= 9 && strstr(line_buffer, "Expansion")) {
        return FOUND_EXPANSION_MENU;
    }
    if (counter >= 4 && strstr(line_buffer, "Help")) {
        return FOUND_HELP_MENU;
    }

    return UNKNOWN;
}

int main(int argc, char *argv[])
{
    FILE *infile, *outfile;
    int found = UNKNOWN;
    int counter = 0;

    if (argc < 2) {
        printf("too few arguments\n");
        exit(1);
    }

    infile = fopen(argv[1], "rb");
    if (infile == NULL) {
        printf("cannot open %s for reading\n", argv[1]);
        exit(1);
    }

    outfile = fopen(argv[2], "wb");
    if (outfile == NULL) {
        printf("cannot open %s for writing\n", argv[2]);
        fclose(infile);
        exit(1);
    }

    fprintf(outfile, "/*\n");
    fprintf(outfile, " * constants.h - BeOS constans for menus, messages, ...\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " * Autogenerated by genconstants, DO NOT EDIT !!!\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " * Written by\n");
    fprintf(outfile, " *  Marcus Sutton <loggedoubt@gmail.com>\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " * Based on old code by\n");
    fprintf(outfile, " *  Andreas Matthies <andreas.matthies@gmx.net>\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " * This file is part of VICE, the Versatile Commodore Emulator.\n");
    fprintf(outfile, " * See README for copyright notice.\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " *  This program is free software; you can redistribute it and/or modify\n");
    fprintf(outfile, " *  it under the terms of the GNU General Public License as published by\n");
    fprintf(outfile, " *  the Free Software Foundation; either version 2 of the License, or\n");
    fprintf(outfile, " *  (at your option) any later version.\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " *  This program is distributed in the hope that it will be useful,\n");
    fprintf(outfile, " *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
    fprintf(outfile, " *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
    fprintf(outfile, " *  GNU General Public License for more details.\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " *  You should have received a copy of the GNU General Public License\n");
    fprintf(outfile, " *  along with this program; if not, write to the Free Software\n");
    fprintf(outfile, " *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA\n");
    fprintf(outfile, " *  02111-1307  USA.\n");
    fprintf(outfile, " *\n");
    fprintf(outfile, " */\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "#ifndef VICE_CONSTANTS_H\n");
    fprintf(outfile, "#define VICE_CONSTANTS_H\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "// Use system typedef for uint32\n");
    fprintf(outfile, "#include <SupportDefs.h>\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "// Messages for window interaction with application\n");
    fprintf(outfile, "const uint32 WINDOW_CLOSED                        = 'WRcl';\n");
    fprintf(outfile, "const uint32 MESSAGE_ATTACH_READONLY              = 'MARO';\n");
    fprintf(outfile, "const uint32 MESSAGE_SET_RESOURCE                 = 'MASR';\n");
    fprintf(outfile, "\n");
    fprintf(outfile, "const uint32 PLAY_VSID                            = 'MA00';\n");
    fprintf(outfile, "const uint32 ATTACH_C64_CART                      = 'MA01';\n");
    fprintf(outfile, "const uint32 ATTACH_VIC20_CART                    = 'MA02';\n");
    fprintf(outfile, "\n");

    /* Use MJ00 as base for joyport 1 */
    fprintf(outfile, "const uint32 MENU_JOYPORT1 = 'MJ00';\n");

    /* Use MK00 as base for joyport 2 */
    fprintf(outfile, "const uint32 MENU_JOYPORT2 = 'MK00';\n");

    /* Use ML00 as base for joyport 3 */
    fprintf(outfile, "const uint32 MENU_JOYPORT3 = 'ML00';\n");

    /* Use MM00 as base for joyport 4 */
    fprintf(outfile, "const uint32 MENU_JOYPORT4 = 'MM00';\n");

    /* Use MN00 as base for joyport 5 */
    fprintf(outfile, "const uint32 MENU_JOYPORT5 = 'MN00';\n");
    fprintf(outfile, "\n");

    /* Use MO00 as base for generic carts */
    fprintf(outfile, "const uint32 MENU_GENERIC_CARTS = 'MO00';\n");

    /* Use MP00 as base for ram expansion carts */
    fprintf(outfile, "const uint32 MENU_RAMEX_CARTS = 'MP00';\n");

    /* Use MQ00 as base for freezer carts */
    fprintf(outfile, "const uint32 MENU_FREEZER_CARTS = 'MQ00';\n");

    /* Use MR00 as base for game carts */
    fprintf(outfile, "const uint32 MENU_GAME_CARTS = 'MR00';\n");

    /* Use MS00 as base for util carts */
    fprintf(outfile, "const uint32 MENU_UTIL_CARTS = 'MS00';\n");
    fprintf(outfile, "const uint32 MENU_END_CARTS = 'MT00';\n");
    fprintf(outfile, "\n");

    while (!feof(infile)) {
        found = vice_getline(infile);
        if (found == FOUND_MENU_ID) {
            fprintf(outfile, "const uint32 %-36s = 'M%03d';\n", line_buffer, counter++);
        } else {
            if (!feof(infile)) {
                fprintf(outfile, "%s", line_buffer);
            }
            if (found > counter) {
                counter = found;
            }
        }
    }
    fprintf(outfile, "\n");
    fprintf(outfile, "#endif\n");

    fclose(infile);
    fclose(outfile);
    return 0;
}
