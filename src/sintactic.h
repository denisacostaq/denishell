/*! @file sintactic.h Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 10:03:40 CST 2013

    tk_comand_pwd "pwd"
    tk_comand_cat "cat"
    tk_comand_cd "cd"
    tk_comand_ls "ls"
        tk_ls_option_a "-a"
        tk_ls_option_f "-f"
        tk_ls_option_l "-l"
    tk_operator_pipe "|"
    tk_operator_redirect ">"

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

#ifndef SINTATIC_H
#define SINTATIC_H

#include "glob.h"

#include "runtime.h"
#include "sintactic_ls.h"
#include "sintactic_cat.h"

#define number_of_args 100
#define leng_for_each_arg 100


token *current_token;

/*! \brief <Sentence> -> <Instruction> <MoreInstruction>
 * \brief sentence
 * \return
 */
struct ast_node *sentence ();

/*! \brief <Instruction> -> <Command> <Args>
 * \brief instruction
 * \return
 */
struct ast_node *instruction();

/*! \brief <Command> -> tk_command_ls | tk_command_cd | tk_command_cat | tk_command_pwd
 * \brief command
 * \return
 */
struct ast_node *command();

/*! \brief <Args> -> !tk_end | !<Operator>
 * \brief args
 * \return
 */
char **args ();

/*!
 * \brief cd_args
 * \return
 */
char** cd_args ();

/*! \brief Only pwd
 * \brief pwd_args
 * \return
 */
char **pwd_args ();

/*! \brief <MoreInstruction> -> tk_end | tk_operator_pipe <Instruction> <MoreInstruction> | tk_operator_redirect tk_file
 * \brief more_instructions
 * \param ast_left
 * \return
 */
struct ast_node *more_instructions(struct ast_node *ast_left);



/*!
 * \brief create_as_node_with_current_tk
 * \return
 */
struct ast_node* create_as_node_with_current_tk ();

/*!
 * \brief bash_panic
 */
void bash_panic ();

/*!
 * \brief rescue_panic_mode
 */
void rescue_panic_mode();

#endif //SINTATIC_H
