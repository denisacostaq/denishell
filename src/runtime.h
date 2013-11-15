/*! @file runtime.h Brebe del fichero.
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

#ifndef RUNTIME_H
#define RUNTIME_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

#include "lexer.h"

  struct ast_node
  {
        struct ast_node *chield_left;
        token *my_content;
        struct ast_node *chield_right;
        char **args;
  };




  /*! \brief Sush as bash this is an internal command.
 * \brief Cuando quieres cambiar el \"working directory\" en bash no se ejecuta un
 * \brief comando externo, este es un comando interno del propio bash ya que necesita
 * \brief ser el mismo quien ejecute esta accion de lo contrario seria le comando externo
 * \brief quien cambiaria su working directory. Para ver lo poco frecuente que ocurre esto
 * \brief mientas usas tu shell ejecuta whereis [ y te dira donde esta el programa \"[\"
 * \param void
 */
void execute_cd (struct ast_node *ast);

/*! \brief wow
 * \brief para ver ejemplos de comndos revisar <a href="example.dsh"><b>estos</b></a>
 * \brief ejemplos.
 * \param ast
 * \param args
 * \return
 */
char** run_on_ast (struct ast_node *ast, char **args);

/*! \example example.dsh
 * \brief Ejemplos de comandos que puedes ejecutar.
 * \return
 */


char **run_syncronous_command_on_ast(struct ast_node *ast);

void run_command_on_ast(struct ast_node *ast);

void run_finalize_on_ast (struct ast_node *ast);

void run_operator_on_ast (struct ast_node *ast);

char **run_pipe_on_node (struct ast_node *ast);

#define READ_END 0
#define WRITE_END 1

/*! \brief Simula un pipe.
 * \warning Para el conjunto de intrucciones que se tienen para este pequenno demo no
 * \warning resulta muy util ejecutar un pipe real por lo que los he emulado cambiando
 * \warning incluso el concepto de pipe con lo que debes tener cuidado no confundirte
 * \warning la idea consiste en que las dos aplicaciones no se conectan mediante un pipe
 * \warning sino que que la salida de una se convierte en la entrada de la otra seria exactamente
 * \warning lo que hace bash en la sustitucion de variables ej:
 * \warning <strong>1. ls = ls<br>2. ls | ls = ls \$(ls)<br>3. ls | ls | ls = ls \$(ls \$(ls))<br>.<br>.<br>.</strong>

 * \brief Para ver un ejemplo real de implementacion de un pipe ver <a href="pipe.c"><b>este</b></a> ejemplo.
 * \param ast
 * \param args
 * \return void
 */
char **run_syncronous_pipe(struct ast_node *ast, char **args);
/*! \example pipe.c
 * \brief Este es un ejemplo de como crear un pipe.
 */



char** push_back_and_free_origin (char** dest, char **origin);

/*! \brief Simulate a pipe
 * \brief run_asynchronous_pipe
 * \param ast
 * \return
 */
char **run_asynchronous_pipe (struct ast_node *ast);

/*! \brief libera la memoria del arbol completo de forma recursiva.
 * \warning en caso de ast ser null causa un crash.
 * \param ast, no debe ser null.
 */
void free_tree (struct ast_node *ast);

void free_node (struct ast_node *node);

#endif //RUNTIME_H
