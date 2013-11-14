/*! @file sintactic_ls.c Brebe del fichero.
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

#include "sintactic_ls.h"
#include "sintactic.h"

//FIXME:memset (arg[0], 0, sizeof(arg[0]));
//TODO: esto no suele ser responsabilidad de bash perooo, de hecho revisar que todos los parametros pinchan
char **ls_args ()
{
    char **arg = (char**)calloc(number_of_args, sizeof(char*));
    int arg_count = 0;
    arg[arg_count] = (char*)calloc(leng_for_each_arg, sizeof(char));
    strcat (arg[arg_count], "ls");
    arg[++arg_count] = NULL;
    BOOL remaining = TRUE;
    do
    {
        current_token = get_next_token();
        switch (current_token->id)
        {
        case tk_ls_option_a:
            arg[arg_count] = (char*) calloc (leng_for_each_arg, sizeof(char));
            strcat (arg[arg_count], "-a");
            arg[++arg_count] = NULL;
            break;
        case tk_ls_option_f:
            arg[arg_count] = (char*) calloc (leng_for_each_arg, sizeof(char));
            strcat (arg[arg_count], "-f");
            arg[++arg_count] = NULL;
            break;
        case tk_ls_option_l:
            arg[arg_count] = (char*) calloc (leng_for_each_arg, sizeof(char));
            strcat (arg[arg_count], "-l");
            arg[++arg_count] = NULL;
            break;
        default:
            remaining = FALSE;
        }
    }while (remaining);
    return arg;
}
