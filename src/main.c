/*! @file main.c Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 09:11:40 CST 2013

    @brief Este fichero ...

    @attention <h1><center>&copy; COPYRIGHT
    GNU GENERAL PUBLIC LICENSE Version 2, June 1991</center></h1>

    @copyright

    <h3>This file is part of PNJB program, a short 2D game.</h3>
    Copyright (C) 2013  Alvaro Denis Acosta Quesada denisacostaq\@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#include "sintactic.h"


void print_chields_and_node (struct ast_node *node)
{
    if (node->my_content)
    {
        PRINT_TOKEN (node->my_content);
    }
    if (node->chield_right)
    {
        if (node->chield_right->my_content)
        {
            PRINT_TOKEN (node->chield_right->my_content);
        }
    }
}

void print_tree (struct ast_node *ast)
{    
    if (ast)
    {
        if (ast->chield_left)
        {
            print_tree (ast->chield_left);
        }
        print_chields_and_node (ast);
    }
}




int main( int argc, char *argv[] )
{
    #ifdef ENABLE_NLS
        setlocale (LC_ALL, "");
        bindtextdomain ( GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR );
        bind_textdomain_codeset ( GETTEXT_PACKAGE, "UTF-8" );
        textdomain ( GETTEXT_PACKAGE );
    #endif

    char format[10];
    memset (format, 0, sizeof(format));
    if (argc > 1){
        switch (atoi(argv[1])) {
        case 1:
            strcat (format, KRED);
            break;
        case 2:
            strcat (format, KGRN);
            break;
        case 3:
            strcat (format, KYEL);
            break;
        case 4:
            strcat (format, KBLU);
            break;
        case 5:
            strcat (format, KMAG);
            break;
        case 6:
            strcat (format, KCYN);
            break;
        case 7:
            strcat (format, KWHT);
            break;
        case 8:
            strcat (format, KNRM);
            break;
        default:
            break;
        }
        printf ("%s", format);
    }

    while (TRUE)
    {
        printf ("\npromp>");
        line = (char*)calloc (200, sizeof(char));
        memset (line,  0, sizeof(*line));
        line = fgets (line, 1000, stdin);
        character_index = 0;        
        struct ast_node *ast = sentence ();

        print_tree (ast);

        run_on_ast (ast, NULL);

        if (ast)
        {
            free_tree (ast);
        }
        free (line);
    }
    return 0;
}
