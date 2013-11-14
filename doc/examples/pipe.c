/*! @file pipe.c Brebe del fichero.
    @author Alvaro Denis Acosta Quesada denisacostaq\@gmail.com
    @date Thu Nov 14 11:03:54 CST 2013

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
 
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 1024


int main (int argc, char *argv[])
{	
	int fd[2];
	pipe(fd);	
	pid_t pid = fork ();
	if (pid == 0)
	{		
		dup2 (fd[READ_END], STDIN_FILENO);
		close (fd[READ_END]);
		execlp ("grep", "grep", "main", NULL);
		exit (EXIT_FAILURE);		
	}
	else if (pid > 0)
	{
		dup2 (fd[WRITE_END], STDOUT_FILENO);
		close (fd[WRITE_END]);
		execlp ("cat", "cat", "untitled.c", NULL);						
		exit (EXIT_FAILURE);		
	}
	else
	{
		perror ("no se creo\n\n");
	}
    return 0;
}
