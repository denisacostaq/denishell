/*! @file lexer.c Brebe del fichero.
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

#include "lexer.h"


char get_next_character (void)
{
    if (line[character_index] != '\n')
    {
        return line[character_index++];
    }
    return line[character_index];
}


token* get_next_token (token *current_tk)
{
    if (current_tk)
    {
        if (current_tk->id == tk_end)
        {
            //FIXME: aun persisten problemas de memoria return current_tk;
        }
    }
    char current_char = get_next_character();
    while (current_char == ' ' || current_char == '\t')
    {
        current_char = get_next_character ();
    }

    token *tk = NULL;
    char tk_str[100];
    memset (tk_str, 0, sizeof(tk_str));
    if (is_separator(current_char))
    {
        tk_str[0] = current_char;
        tk_str[1] = 0;
        get_next_character ();
        tk = get_new_token (get_type(tk_str), tk_str);
    }
    else
    {
        int leng = 0;
        do {
            tk_str[leng++] = current_char;
            current_char = get_next_character ();
        } while (!isspace(current_char) && !is_separator(current_char));
        tk_str[leng] = 0;
        tk = get_new_token (get_type(tk_str), tk_str);
    }    
    return tk;
}

token* get_new_token (token_type id, char *value)
{
    token *tk = (token*)malloc (sizeof(token));
    tk->id = id;
    memset (tk->tk_value, 0, sizeof(tk->tk_value));
    strcat (tk->tk_value, value);
    switch (tk->id)
    {
        case tk_exit:
        case tk_end:
            tk->family = tk_family_finalize;
            break;
        case tk_comand_cat:
        case tk_comand_ls:
        case tk_comand_pwd:
        case tk_comand_cd:
            tk->family = tk_family_commands;
            break;
        case tk_ls_option_a:
        case tk_ls_option_f:
        case tk_ls_option_l:
            tk->family = tk_family_options;
            break;
        case tk_operator_pipe:
        case tk_operator_redirect:
            tk->family = tk_family_operators;
            break;
        default:
            tk->family = tk_family_unknown;
            break;
    }
    return tk;
}

BOOL is_separator (char ch)
{
    switch (ch) {
    case '|':
    case '>':
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}


token_type get_type (char *str_tk)
{
    if (!strcmp (str_tk, "pwd")) return tk_comand_pwd;
    else if (!strcmp(str_tk, "cat")) return tk_comand_cat;
    else if (!strcmp(str_tk, "cd")) return tk_comand_cd;
    else if (!strcmp(str_tk, "ls")) return tk_comand_ls;
    else if (!strcmp(str_tk, "-a")) return tk_ls_option_a;
    else if (!strcmp(str_tk, "-f")) return tk_ls_option_f;
    else if (!strcmp(str_tk, "-l")) return tk_ls_option_l;
    else if (!strcmp(str_tk, "|")) return tk_operator_pipe;
    else if (!strcmp(str_tk, ">")) return tk_operator_redirect;
    else if (!strcmp(str_tk, "\n")) return tk_end;
    else if (!strcmp(str_tk, "exit")) return tk_exit;
    else return tk_unknown;
}

void msg_err (char* msg)
{
    printf ("%s\n", _(msg));
}

#ifdef TRACE_TOKENS
void print_token (token* tk)
{
    char str_tk[100];
    memset (str_tk, 0, sizeof(str_tk));        
    switch (tk->id)
    {
        case tk_comand_pwd:
            strcat (str_tk, "tk_comand_pwd");            
            break;
        case tk_comand_cat:
            strcat (str_tk, "tk_comand_cat");
            break;
        case tk_comand_cd:
            strcat (str_tk, "tk_comand_cd");
            break;
        case tk_comand_ls:
            strcat (str_tk, "tk_comand_ls");
            break;
        case tk_ls_option_a:
            strcat (str_tk, "tk_ls_option_a");
            break;
        case tk_ls_option_f:
            strcat (str_tk, "tk_ls_option_f");
            break;
        case tk_ls_option_l:
            strcat (str_tk, "tk_ls_option_l");
            break;
        case tk_operator_pipe:
            strcat (str_tk, "tk_operator_pipe");            
            break;
        case tk_operator_redirect:
            strcat (str_tk, "tk_operator_redirect");
            break;
        case tk_end:
            strcat (str_tk, "tk_end");            
            break;
        case tk_exit:
            strcat (str_tk, "tk_exit");
            break;
        case tk_unknown:
            strcat (str_tk, "tk_unknown");            
            break;
        default:            
            break;
    }

    char str_family[100];
    memset (str_family, 0, sizeof(str_family));
    switch (tk->family)
    {
        case tk_family_commands:
            strcat (str_family, "tk_family_commands");
            break;
        case tk_family_options:
            strcat (str_family, "tk_family_options");
            break;
        case tk_family_operators:
            strcat (str_family, "tk_family_operators");
            break;
        case tk_family_finalize:
            strcat (str_family, "tk_family_finalize");
            break;
        case tk_family_unknown:
            strcat (str_family, "tk_family_unknown");
            break;
        default:
            break;
    }

    printf ("\n\n--------------------------------------------------------------------\n");
    printf ("tk-id: %d - %s   family: %d - %s   tk-str: %s\n", tk->id, str_tk, tk->family, str_family, tk->tk_value);
    printf ("--------------------------------------------------------------------\n\n");
}
#endif
