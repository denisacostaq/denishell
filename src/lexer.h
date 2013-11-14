/*! @file lexer.h Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 10:13:40 CST 2013

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

#ifndef LEXER_H
#define LEXER_H
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "deni-sh_i18n.h"

char *line;
int character_index;

typedef char BOOL;

#define TRUE 1
#define FALSE 0

typedef enum
{
    tk_comand_pwd = 1,
    tk_comand_cat,
    tk_dir_file,
    tk_comand_cd,
    tk_comand_ls,
        tk_ls_option_a,
        tk_ls_option_f,
        tk_ls_option_l,
    tk_operator_pipe,
    tk_operator_redirect,
    tk_end,
    tk_exit,
    tk_unknown
} token_type;

typedef enum
{
    tk_family_operators = 1,
    tk_family_commands,
    tk_family_options,
    tk_family_finalize,
    tk_family_unknown
}token_family;

typedef struct
{
    token_type id;
    token_family family;
    char tk_value[100];
} token;

char get_next_character (void);

token* get_next_token ();

token* get_new_token (token_type id, char* value);

BOOL is_separator (char ch);

token_type get_type (char *str_tk);

void msg_err (char* msg);

#define TRACE
#ifdef TRACE
#define PRINT_TOKEN(TK) print_token (TK)
void print_token (token *tk);
#else
#define PRINT_TOKEN(TK)
#endif


#endif //LEXER_H
