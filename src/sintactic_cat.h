/*! @file sintactic_cat.h Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 12:40:40 CST 2013

    tk_comand_cat "cat"
    file "any file"

    #sintatic_cat.c
    <CatArgs> -> tk_file <CatOtherFile>
    <CatOtherFile> -> null | tk_file
    if (has_next_token): elimino el segundole

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

#ifndef SINTATIC_CAT_H
#define SINTATIC_CAT_H

#include "lexer.h"

char **cat_args ();

char **cat_args2 (char **arg, int arg_index);

#endif //SINTATIC_CAT_H
