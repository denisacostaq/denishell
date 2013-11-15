/*! @file sintactic_cat.c Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 12:40:40 CST 2013

    #sintatic_cat.c
    <CatArgs> -> tk_file <CatOtherFile>
    <CatOtherFile> -> null | tk_file
    if (has_next_token): elimino el segundo



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

#include "sintactic_cat.h"
#include "sintactic.h"

char **cat_args ()
{
    char **cat_arg = (char**)calloc(number_of_args, sizeof(char*));
    int arg_index = 0;
    cat_arg[arg_index] = (char*)calloc(leng_for_each_arg, sizeof(char));
    memset (cat_arg[arg_index], 0, sizeof(*cat_arg[arg_index]));
    strcat (cat_arg[arg_index], "cat");
    cat_arg[++arg_index] = NULL;

    current_token = get_next_token (current_token);
    if (current_token->family != tk_family_operators &&
        current_token->family != tk_family_finalize)
    {
        cat_arg[arg_index] = (char*)calloc(leng_for_each_arg, sizeof(char));
        memset (cat_arg[arg_index], 0, sizeof(*cat_arg[arg_index]));
        strcat (cat_arg[arg_index], current_token->tk_value);
        cat_arg[++arg_index] = NULL;
        cat_args2 (cat_arg, arg_index);
    }
    return cat_arg;
}

char **cat_args2 (char **cat_arg, int arg_index)
{
    current_token = get_next_token (current_token);
    if (current_token->family != tk_family_operators &&
        current_token->family != tk_family_finalize)
    {
        cat_arg[arg_index] = (char*)calloc(leng_for_each_arg, sizeof(char));
        memset (cat_arg[arg_index], 0, sizeof(*cat_arg[arg_index]));
        strcat (cat_arg[arg_index], current_token->tk_value);
        cat_arg[++arg_index] = NULL;
        current_token = get_next_token (current_token);
        while (current_token->family == tk_family_finalize &&
            current_token->family == tk_family_operators)
        {
            current_token = get_next_token (current_token);
        }
    }
    return cat_arg;
}
