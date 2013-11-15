/*! @file sintactic_ls.h Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 12:45:40 CST 2013

    tk_comand_ls "ls"
        tk_ls_option_a "-a"
        tk_ls_option_f "-f"
        tk_ls_option_l "-l"

    #sintatic_ls.c
    <LsArgs> -> null | <LsArg>
    <LsArg> -> -l <LsArgs> | -f <LsArgs> | -a <LsArgs>

    #sintactic.c
    <Sentence> -> <Instruction> <MoreInstruction>
    <Instruction> -> <Command> <Args>
    <Command> -> tk_command_ls | tk_command_cd | tk_command_cat | tk_command_pwd
    <Args> -> !tk_end | !<Operator>
    <Operator> -> tk_operator_pipe | tk_operator_redirect
    <MoreInstruction> -> tk_end | tk_operator_pipe <Instruction> <MoreInstruction> | tk_operator_redirect tk_file

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


#ifndef SINTATIC_LS_H
#define SINTATIC_LS_H

#include "lexer.h"

/*! \brief Partucular check.
 * \brief Cuando le das ordenes a bash este no cheque por la correctitud de los parametros
 * \brief esto es responsabilidad de cada programa en particular, si asumieramos este
 * \brief comportamiento se tomarian como correctos todos los parametros que acepte el
 * \brief programa cuando solo se requieren unos pocos para este demo.
 * \return char **ls_arg, argumentos a ls.
 */
char **ls_args ();


#endif //SINTATIC_LS_H
