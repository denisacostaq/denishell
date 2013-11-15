/*! @file sintactic.c Brebe del fichero.
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

    #sintatic_ls.c
    <LsArgs> -> null | <LsArg>
    <LsArg> -> -l <LsArgs> | -f <LsArgs> | -a <LsArgs>

    #sintatic_cat.c
    <CatArgs> -> tk_file <CatOtherFile>
    <CatOtherFile> -> null | tk_file
    if (has_next_token): elimino el segundo

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

#include "sintactic.h"


struct ast_node *sentence ()
{
    current_token = get_next_token (current_token);
    struct ast_node *ast = instruction ();
    struct ast_node *ast_parent = more_instructions (ast);    
    if (ast_parent)
    {
        return ast_parent;
    }
    return ast;
}


struct ast_node * instruction ()
{
    struct ast_node* ast = NULL;
    if (current_token->family == tk_family_commands)
    {
        ast = command();
    }
    else if (current_token->family == tk_family_finalize)
    {
        ast = create_as_node_with_current_tk ();
        current_token = get_next_token (current_token);
    }
    else
    {
        char msg[200];
        memset (msg, 0, sizeof (msg));
        strcat (msg, "_Unexpected instrcution, expectect command beafore \"");
        strcat (msg, current_token->tk_value);
        strcat (msg, "\"\n");
        msg_err (msg);
        rescue_panic_mode ();
        ast = instruction ();
    }
    return ast;
}

struct ast_node * command ()
{
    struct ast_node *ast = create_as_node_with_current_tk ();
    ast->args = args ();
    return ast;
}

char **args ()
{
    char **arg = NULL;
    switch (current_token->id)
    {
    case tk_comand_cd:
        arg = cd_args ();
        break;
    case tk_comand_ls:
        arg = ls_args ();
        break;
    case tk_comand_cat:
        arg = cat_args ();
        break;
    case tk_comand_pwd:
        arg  = pwd_args ();
        break;
    default:
        arg = NULL;
        break;
    };
    return arg;
}



char **cd_args ()
{
    char **arg = (char**)calloc(number_of_args, sizeof(char*));
    int arg_count = 0;
    arg[arg_count] = (char*)calloc(leng_for_each_arg, sizeof(char));
    memset (arg[arg_count], 0, sizeof(*arg[0]));
    strcat (arg[arg_count], "cd");
    arg[++arg_count] = NULL;

    arg[arg_count] = (char*)calloc(leng_for_each_arg, sizeof(char));
    memset (arg[arg_count], 0, sizeof(*arg[arg_count]));

    current_token = get_next_token(current_token);
    if (current_token->family != tk_family_finalize &&
            current_token->family != tk_family_operators)
    {
        strcat (arg[arg_count], current_token->tk_value);
        current_token = get_next_token (current_token);
        arg[++arg_count] = NULL;
    }
    else
    {
        glob_t glob_var;
        glob ("~", GLOB_TILDE, NULL, &glob_var);
        strcat (arg[arg_count], glob_var.gl_pathv[0]);
        arg[++arg_count] = NULL;
    }
    return arg;
}

char** pwd_args ()
{
    char **arg = (char**)calloc(number_of_args, sizeof(char*));
    int arg_count = 0;
    arg[arg_count] = (char*)calloc(leng_for_each_arg, sizeof(char));
    memset (arg[arg_count], 0, sizeof(*arg[0]));
    strcat (arg[arg_count], "pwd");
    arg[++arg_count] = NULL;
    current_token = get_next_token (current_token);
    return arg;
}

struct ast_node *more_instructions (struct ast_node *ast_left)
{    
    if (current_token->id == tk_operator_pipe)
    {
        struct ast_node *ast = create_as_node_with_current_tk ();
        ast->chield_left = ast_left;
        current_token = get_next_token (current_token);
        if (current_token->family == tk_family_commands)
        {
            ast->chield_right = instruction ();
            return more_instructions (ast);
        }
        else
        {
            if (current_token->id == tk_end)
            {
                msg_err (_("_Unexpected end, expectect command beafore end\n"));
                free_node (ast);
                return ast_left;
            }
            char msg[150];
            memset (msg, 0, sizeof(msg));
            strcat (msg, _("_Unexpected end, expectect command beafore "));
            strcat (msg, current_token->tk_value);
            strcat (msg, "\n");
            msg_err (msg);
            rescue_panic_mode ();
        }
    }
    else if (current_token->id == tk_operator_redirect)
    {
        struct ast_node *ast = create_as_node_with_current_tk ();
        ast->chield_left = ast_left;
        ast->chield_right = NULL;
        ast->args = cd_args ();
        strcat (ast->args[0], "cat");
        return ast;
    }
    else if (current_token->id == tk_end)
    {
        //FIXME: y a current token quien lo elimina
        return ast_left;
    }
    else
    {
        char msg[150];
        memset (msg, 0, sizeof(msg));
        strcat (msg, _("_Unexpected token, expectect operator beafore "));
        strcat (msg, current_token->tk_value);
        strcat (msg, "\n");
        msg_err (msg);

        while (current_token->family != tk_family_operators &&
                  current_token->id != tk_end)
        {
            free (current_token);
            current_token = get_next_token (current_token);
        }
        return more_instructions (ast_left);
    }
    return NULL;
}

struct ast_node* create_as_node_with_current_tk ()
{
    struct ast_node *ast = NULL;
    switch (current_token->family)
    {
    case tk_family_commands:
    case tk_family_operators:
    case tk_family_options:
    case tk_family_finalize:
        ast = (struct ast_node*)malloc (sizeof(struct ast_node));
        ast->args = NULL;
        ast->chield_left = NULL;
        ast->chield_right = NULL;
        ast->my_content = current_token;
        break;
    default://TODO:
        printf ("struct ast_node* create_as_node_with_current_tk ()\n");
        exit (EXIT_FAILURE);
        break;
    }
    return ast;
}

void bash_panic ()
{
    fprintf ( stderr, _("my-shell panic\n"));
    //FIXME free_tree (ast);
    exit (EXIT_FAILURE);
}




void rescue_panic_mode()
{
    while (current_token->family != tk_family_commands
           && current_token->family != tk_family_finalize)
    {
        free (current_token);
        current_token = get_next_token (current_token);
    }
}
