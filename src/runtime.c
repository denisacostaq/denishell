/*! @file runtime.c Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Tue Nov 12 10:20:40 CST 2013

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

#include "runtime.h"



//TODO: ni siquiera en bash esto es un comando externo, [ si lo es
void execute_cd (struct ast_node *ast)
{
    char directory[1000];
    memset (directory, 0, sizeof (directory));
    strcat (directory, ast->args[1]);
    int index = 0;
    int i = 0;
    int j = 0;

    if (directory[index] == '/')
    {
        free (ast->args[i]);
        ast->args[i] = (char*)calloc (100, sizeof(char));
        ast->args[i][j++] = '/';
        ast->args[i++][j++] = 0;
        index++;
    }

    BOOL finished = directory[index] == 0;
    while (!finished)
    {
        j = 0;
        free (ast->args[i]);
        ast->args[i] = (char*)calloc (100, sizeof(char));
        memset (ast->args[i], 0, sizeof(*ast->args[i]));
        while (directory[index] != '/' &&
               directory[index] != '\n')
        {
            ast->args[i][j++] = directory[index];
            if (directory[index++] == 0)
            {
                finished = TRUE;
                break;
            }
        }
        index++;
        i++;
    }
    if (directory[strlen(directory)-1] == '/')
    {
        i--;
    }

    for (j = 0; j < i; j++)
    {
        if (chdir (ast->args[j]) == -1)
        {
            perror ("Working directory not changed\n");
            return;
        }
    }
}

char** run_on_ast (struct ast_node *ast, char **args)
{
    if (ast)
    {
        if (ast->my_content)
        {
            if (ast->my_content->family == tk_family_operators)
            {
                run_operator_on_ast (ast);
            }
            else if (ast->my_content->family == tk_family_commands ||
                     ast->my_content->family == tk_family_finalize)
            {
                run_command_on_ast (ast);
            }
        }
    }


return NULL;

//    if (ast)
//    {
//        if (ast->my_content)
//        {
//            if (args)
//            {
//                push_back_and_free_origin (ast->args, args);
//            }
//            if (ast->my_content->family == tk_family_operators)
//            {
//                if (ast->my_content->id == tk_operator_pipe)
//                {
//                    return run_on_ast (ast->chield_right,
//                                run_on_ast (ast->chield_left, args));
//                }
//                else if (ast->my_content->id == tk_operator_redirect)
//                {
//                }
//            }
//            else if (ast->my_content->family == tk_family_commands ||
//                     ast->my_content->family == tk_family_finalize)
//            {
//                char **f = run_command_on_ast (ast);
//                int t = 0;
//                while (f[t])
//                {
//                    printf ("[%s]\n", f[t++]);
//                }
//                printf ("----------------------------------------------\n");
//                return f;
//            }
//        }
//    }
//    return NULL;
}

char** run_syncronous_command_on_ast (struct ast_node *ast)
{
    if (ast->my_content->id == tk_comand_cd)
    {
        execute_cd (ast);
    }
    else
    {
        if (ast->my_content->id == tk_comand_cat ||
            ast->my_content->id == tk_comand_ls ||
            ast->my_content->id == tk_comand_pwd)
        {
            int fd[2];
            pipe (fd);
            pid_t pid = fork();
            if (pid > 0)
            {
                int status = -1;
                if(waitpid (pid, &status, 0) != pid);
                int old = dup (STDIN_FILENO);
                dup2 (fd[READ_END], STDIN_FILENO);
                close (fd[READ_END]);
                char **T = (char**) calloc (1000, sizeof(char*));

                for (int i = 0; ; i++)
                {
                    T[i] = (char*) calloc (100, sizeof(char));
                    T[i+1] = NULL;
                    for (int j = 0; ; j++)
                    {
                        char ch = getchar ();
                        if (ch == EOF)
                        {
                            T[i-1] = NULL;//FIXME: esto no deberia ser
                            dup2 (old, STDIN_FILENO);
                            return T;
                        }
                        else if (isspace(ch))
                        {
                            T[i][j] = 0;
                            break;
                        }
                        T[i][j] = ch;
                    }
                }
            }
            else if (pid==0)
            {
                dup2 (fd[WRITE_END], STDOUT_FILENO);
                close (fd[WRITE_END]);
                pid_t pid2 = fork ();
                if (pid2 > 0)
                {
                    execvp (ast->args[0], ast->args);
                    printf ("Run command %s faulery\n", ast->args[0]);
                    //NOTE: exit (EXIT_FAILURE);
                }
                else if (pid2 == 0)
                {
                    setsid(); //SID para el nuevo proceso
                    int parent_pid = getppid();
                    while(getppid() == parent_pid);//wait for the parent process die
                    printf ("%c", EOF);//do { }while (y[i++]!=EOF);
                    exit (EXIT_SUCCESS);
                }
                else
                {
                    perror ("The subchield process has not been created\n");
                }
            }
            else
            {
                perror ("The chield process has not been created\n");
            }
        }
    }
    return NULL;
}

void run_command_on_ast(struct ast_node *ast)
{
    if (ast->my_content->family == tk_family_finalize)
    {
        if (ast->my_content->id == tk_exit)
        {
            exit (EXIT_SUCCESS);
        }
    }
    else
    {
        if (ast->my_content->id == tk_comand_cd)
        {
            execute_cd (ast);
        }
        else
        {
            if (ast->my_content->id == tk_comand_cat ||
                    ast->my_content->id == tk_comand_ls ||
                    ast->my_content->id == tk_comand_pwd)
            {
                pid_t pid = fork();
                if (pid > 0)
                {
                    int status = -1;
                    if(waitpid (pid, &status, 0) != pid);
                }
                else if (pid==0)
                {
                    PRINT_TOKEN (ast->my_content);
                    execvp (ast->args[0], ast->args);
                    printf ("Run command %s faulery\n", ast->args[0]);
                    //NOTE: exit (EXIT_FAILURE);
                }
                else
                {
                    perror ("The chield process has not been created\n");
                }
            }
        }
    }
}

void run_finalize_on_ast (struct ast_node *ast)
{
    switch (ast->my_content->id)
    {
        case tk_end:
            msg_err ("ERROR: run_finalize_on_ast\n");
            exit (EXIT_FAILURE);
            break;
        case tk_exit:
            exit (EXIT_SUCCESS);
        break;
        default:
            break;
    }
}

void run_operator_on_ast (struct ast_node *ast)
{
    pid_t pid = -1;
    switch (ast->my_content->id)
    {
        case tk_operator_pipe:
            run_pipe_on_node (ast);
            break;
        case tk_operator_redirect:
            pid = fork ();
            if (pid == 0)
            {
                freopen (ast->args[1], "w", stdout);
                run_on_ast (ast->chield_left, NULL);
                free (ast);
                exit (EXIT_SUCCESS);
            }
            else if (pid > 0)
            {
                int status = -1;
                if(waitpid (pid, &status, 0) != pid);
            }
            else
            {
                perror ("Chield no created\n");
            }
            break;
        default:
            break;
    }
}

char ** run_pipe_on_node (struct ast_node *ast)
{
    if (ast)
    {
        if (ast->chield_left && ast->chield_right)
        {
            if (TRUE)
            {
                char **f = run_syncronous_pipe (ast, NULL);
                int t = 0;
                while (f[t])
                {
                    printf ("[%s]\n", f[t++]);
                }
            }
            else
            {
                run_asynchronous_pipe (ast);
            }
        }
    }
    return NULL;
}

//NOTE: ls = ls, ls | ls = ls $(ls), ls | ls | ls = ls $(ls $(ls))
char **run_syncronous_pipe(struct ast_node *ast, char **args)
{
    if (ast)
    {
        if (ast->my_content)
        {
            if (args)
            {
                push_back_and_free_origin (ast->args, args);
            }
            if (ast->my_content->family == tk_family_operators)
            {
                if (ast->my_content->id == tk_operator_pipe)
                {
                    return run_syncronous_pipe (ast->chield_right,
                                run_syncronous_pipe (ast->chield_left, args));
                }
                else if (ast->my_content->id == tk_operator_redirect)
                {
                }
            }
            else if (ast->my_content->family == tk_family_commands ||
                     ast->my_content->family == tk_family_finalize)
            {
                return run_syncronous_command_on_ast (ast);
            }
        }
    }
    return NULL;
}

char** push_back_and_free_origin (char** dest, char **origin)
{    
    int index_dest = -1;
    while (dest[++index_dest]);

    int i = 1;
    while (origin[i])
    {
        dest[index_dest] = (char*) calloc (100, sizeof(char));
        memset (dest[index_dest], 0, sizeof(*dest[index_dest]));
        strcat (dest[index_dest++], origin[i++]);
        //printf ("%d %s\n", index_dest-1, dest[index_dest-1]);
        //free (origin[i++]);
    }

    return dest;
}

char **run_asynchronous_pipe(struct ast_node *ast)
{
    int fd[2];
    pipe (fd);
    pid_t pid = fork ();
    if (pid == 0)//chiel
    {
        dup2 (fd[READ_END], STDIN_FILENO);
        close (fd[READ_END]);
        execlp ("grep", "grep", "main", NULL);
        exit (EXIT_FAILURE);
    }
    else if (pid > 0)//parent
    {
        dup2 (fd[WRITE_END], STDOUT_FILENO);
        close (fd[WRITE_END]);
        if (ast->chield_left)
        {
            if (ast->chield_left->my_content)
            {
                if (ast->chield_left->my_content->id == tk_operator_pipe)
                {
                    run_asynchronous_pipe (ast->chield_left);
                }
                else if (ast->chield_left->my_content->family == tk_family_commands)
                {
                    run_syncronous_command_on_ast (ast->chield_left);
                    //execlp ("cat", "cat", "untitled.c", NULL);
                    exit (EXIT_FAILURE);
                }
                else
                {
                    printf ("DLFJKSLJFKSL\n");
                    exit (EXIT_FAILURE);
                }
            }
        }
        if (ast->chield_right)
        {
            if (ast->chield_right->my_content)
            {
                if (ast->chield_right->my_content->family == tk_family_commands)
                {
                    run_syncronous_command_on_ast (ast->chield_right);
                    //execlp ("cat", "cat", "untitled.c", NULL);
                    exit (EXIT_FAILURE);
                }
                else
                {
                    printf ("DLFJKSLJFKSL\n");
                    exit (EXIT_FAILURE);
                }
            }
        }
    }
    else//error
    {
        perror (_("no se creo\n\n"));
    }
    return NULL;
}

char **run_command_on_node (struct ast_node* node)
{
    return NULL;
}

void free_tree (struct ast_node *ast)
{
    if (ast->chield_left)
    {
        //free_tree (ast->chield_left);
    }
    else
    {
        //free_node (ast->chield_left);
    }
}

void free_node (struct ast_node *node)
{
    if (node->my_content)
    {
        free (node->my_content) ;
    }
    free (node);
}



/*
// main.c
//
// Copyright 2013 docencia <docencia@LD02-000-00L>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 1024
int
main (int argc, char **argv)
{
    pid_t pid;
    int fd[2];
    pipe(fd);
    pid=fork();
    if (pid==0)
    {
        dup2(fd[WRITE_END], STDOUT_FILENO);
        close(fd[WRITE_END]);
        pid_t pid3 = fork();
        if (pid3 > 0)
        {
            execlp("ls", "ls", "main.c", "main", NULL);
            exit (EXIT_FAILURE);
        }
        else if (pid3 == 0)//chield
        {
            setsid(); //SID para el nuevo proceso
            int parent_pid = getppid();
            while(getppid() == parent_pid);//wait for the parent process die
            printf ("%c", EOF);//do { }while (y[i++]!=EOF);
        }
        else
        {
        perror ("no se creo\n\n");
        }
    }
    else if (pid > 0)
    {
        int pid2=fork();
        if (pid2==0)
        {
            dup2(fd[READ_END], STDIN_FILENO);
            close(fd[READ_END]);//close(fd[WRITE_END]);
            char **lines = (char**)calloc (100, sizeof(char*));
            int i;
            for (i = 0; i < 100; i++)
            {
                lines[i] = (char*)calloc (100, sizeof(char));
                memset (lines[i], 0, sizeof(lines[i][0]));
            }
            i = 0;
            strcat (lines[i++], "grep");
            strcat (lines[i++], "main");
            int jj;
            while (1)
            {
                char ch = getchar ();
                if (ch == EOF)
                {
                break;
                }

                jj = 0;
                do
                {
                lines[i][jj++] = ch;
                ch = getchar ();
                } while (ch != '\n');
                lines[i][jj+1] = 0;
                printf ("%s", lines[i]);
                i++;
            }
            lines[i]=NULL;
            execvp(lines[0], lines);
            exit (EXIT_FAILURE);
        }
        else if (pid2 > 0)
        {
            int status;
            if(waitpid (pid, &status, 0) != pid);
            if(waitpid (pid2, &status, 0) != pid);
        }
        else
        {
            perror ("no se creo\n\n");
        }
    }
    else
    {
        perror ("no se creo\n\n");
    }
    return 0;
}
*/
