/*
** main.c for corewar-asm in /home/laspou_k/delivery/CPE/CPE_Corewar
**
** Made by Kévin Laspougeas
** Login   <laspou_k@epitech.net>
**
** Started on  Mon Mar  6 18:21:54 2017 Kévin Laspougeas
** Last update Fri Mar 31 18:51:09 2017 Kévin Laspougeas
*/

#include <stdio.h>
#include "asm.h"

int	check_args(char *str, t_list *list)
{
  return (my_strncmp(str, "live ", 5) == 0 ? check_live(epu(&str[5]), list) :
	  my_strncmp(str, "ld ", 3) == 0 ? check_ld(epu(&str[3]), list, 2) :
	  my_strncmp(str, "st ", 3) == 0 ? check_st(epu(&str[3]), list) :
	  my_strncmp(str, "add ", 4) == 0 ? check_add_sub(epu(&str[4]),
							  list, 4) :
	  my_strncmp(str, "sub ", 4) == 0 ? check_add_sub(epu(&str[4]),
							  list, 5) :
	  my_strncmp(str, "and ", 4) == 0 ? check_and(epu(&str[4]), list, 6) :
	  my_strncmp(str, "or ", 3) == 0 ? check_and(epu(&str[3]), list, 7) :
	  my_strncmp(str, "xor ", 4) == 0 ? check_and(epu(&str[4]), list, 8) :
	  my_strncmp(str, "zjmp ", 5) == 0 ? check_zjmp(epu(&str[5]), list) :
	  my_strncmp(str, "ldi ", 4) == 0 ? check_ldi(epu(&str[4]), list, 10) :
	  my_strncmp(str, "sti ", 4) == 0 ? check_sti(epu(&str[4]), list, 11) :
	  my_strncmp(str, "fork ", 3) == 0 ? check_fork(epu(&str[5]),
							list, 12) :
	  my_strncmp(str, "lld ", 4) == 0 ? check_ld(epu(&str[4]), list, 13) :
	  my_strncmp(str, "lldi ", 5) == 0 ? check_ldi(epu(&str[5]),
						       list, 14) :
	  my_strncmp(str, "lfork ", 6) == 0 ? check_fork(epu(&str[6]),
							 list, 15) :
	  my_strncmp(str, "aff ", 4) == 0 ? check_aff(epu(&str[4]), list) : 0);
}

void	check_mnemo(char *str, int l)
{
  if (my_strncmp(str, "live ", 5) != 0 && my_strncmp(str, "ld ", 3) != 0 &&
      my_strncmp(str, "st ", 3) != 0 && my_strncmp(str, "add " , 4) != 0 &&
      my_strncmp(str, "sub ", 4) != 0 && my_strncmp(str, "and ", 4) != 0 &&
      my_strncmp(str, "or ", 3) != 0 && my_strncmp(str, "xor ", 4) != 0 &&
      my_strncmp(str, "zjmp ", 5) != 0 && my_strncmp(str, "ldi ", 4) != 0 &&
      my_strncmp(str, "sti ", 4) != 0 && my_strncmp(str, "fork ", 5) != 0 &&
      my_strncmp(str, "lld ", 4) != 0 && my_strncmp(str, "lldi ", 5) != 0 &&
      my_strncmp(str, "lfork ", 4) != 0 && my_strncmp(str, "aff ", 4) != 0)
    exit_error(str, l, WRG_MNEMO);
}

void	check_code(const int fd, const int fd_out, t_list *list)
{
  char		*line;
  int		lines;
  int		r;

  lines = 1;
  while ((line = rm_tab(get_next_line(fd))) != NULL)
    {
      if ((r = line_is_label(line, list)) >= 1)
	{
	  add_label(line, list, lines);
	  line = &line[r + 2];
	}
      if (line[0] != '\0' && line[0] != COMMENT_CHAR &&
	  line[my_strlen(line) - 1] != LABEL_CHAR &&
	  my_strncmp(line, NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)) != 0 &&
	  my_strncmp(line, COMMENT_CMD_STRING, my_strlen(NAME_CMD_STRING))!= 0)
	{
	  check_mnemo(line, lines);
	  if (check_args(line, list) != 1)
	    exit_error(line, lines, WRG_PAR);
	}
      lines++;
    }
}

void	usage(char *av)
{
  my_putstr("USAGE\n\t");
  my_printf("%s file_name[.s]\n\nDESCRIPTION\n\tfile_name", av);
  my_putstr("\tfile in assembly language to be converted into\n");
  my_putstr("\t\t\tfile_name.cor, an executable in the Virtual Machine.\n");
}

int	main(int ac, char **av)
{
  int		fd;
  int		fd_out;
  t_list	*list;
  header_t	head;

  if (ac == 1 || (ac == 2 && my_strcmp(av[1], "-h") == 0))
    usage(av[0]);
  else if (ac >= 2 && (fd = open(av[1], O_RDONLY)) != -1)
    {
      if ((fd_out = open("./out.cor", O_CREAT | O_RDWR | O_TRUNC, 0666)) <= 0)
	return (84);
      list = make_list();
      create_header(fd, fd_out, &head);
      check_code(fd, fd_out, list);
      fill_labels(list);
      write_it_all(list, fd_out);
      close(fd);
      close(fd_out);
      return (0);
    }
  return (84);
}
