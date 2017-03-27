/*
** main.c for corewar-asm in /home/laspou_k/delivery/CPE/CPE_Corewar
**
** Made by Kévin Laspougeas
** Login   <laspou_k@epitech.net>
**
** Started on  Mon Mar  6 18:21:54 2017 Kévin Laspougeas
** Last update Tue Mar 28 01:01:42 2017 Kévin Laspougeas
*/

#include "asm.h"

int	check_args(char *str, t_list *list)
{
  return (my_strncmp(str, "live ", 5) == 0 ? check_live(&str[5], list) :
	  my_strncmp(str, "ld ", 3) == 0 ? check_ld(&str[3], list, 2) :
	  my_strncmp(str, "st ", 3) == 0 ? check_st(&str[3], list) :
	  my_strncmp(str, "add ", 4) == 0 ? check_add_sub(&str[4], list, 4) :
	  my_strncmp(str, "sub ", 4) == 0 ? check_add_sub(&str[4], list, 5) :
	  my_strncmp(str, "and ", 4) == 0 ? check_and(&str[4], list, 6) :
	  my_strncmp(str, "or ", 3) == 0 ? check_and(&str[3], list, 7) :
	  my_strncmp(str, "xor ", 4) == 0 ? check_and(&str[4], list, 8) :
	  my_strncmp(str, "zjmp ", 5) == 0 ? check_zjmp(&str[5], list) :
	  my_strncmp(str, "ldi ", 4) == 0 ? check_ldi(&str[4], list, 10) :
	  my_strncmp(str, "sti ", 4) == 0 ? check_sti(&str[4], list) :
	  my_strncmp(str, "fork ", 5) == 0 ? check_fork(&str[5], list, 12) :
	  my_strncmp(str, "lld ", 4) == 0 ? check_ld(&str[4], list, 13) :
	  my_strncmp(str, "lldi ", 5) == 0 ? check_ldi(&str[5], list, 14) :
	  my_strncmp(str, "lfork ", 6) == 0 ? check_fork(&str[6], list, 15) :
	  my_strncmp(str, "aff ", 4) == 0 ? check_aff(&str[4], list) : 0):
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
      my_strncmp(str, "lfork ", 6) != 0 && my_strncmp(str, "aff ", 4) != 0)
    exit_error(str, l, WRG_MNEMO);
}

void	check_code(const int fd, const int fd_out, t_list *list)
{
  char		*line;
  int		lines;
  int		r;

  lines = 1;
  while ((line = get_next_line(fd)) != NULL)
    {
      if ((r = line_is_label(line)) >= 1)
	{
	  add_label(line, list, lines);
	  line = &line[r + 1];
	}
      if (line[0] != COMMENT_CHAR && my_strncmp(line, NAME_CMD_STRING,
						my_strlen(NAME_CMD_STRING)) &&
	  my_strncmp(line, COMMENT_CMD_STRING,
		     my_strlen(COMMENT_CMD_STRING)) &&
	  line[my_strlen(line) - 1] != LABEL_CHAR)
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
  t_list	list;

  if (ac == 1 || (ac == 2 && my_strcmp(av[1], "-h") == 0))
    usage(av[0]);
  else if (ac >= 2 && (fd = open(av[1], O_RDONLY)) != -1)
    {
      if ((fd_out = open("./out.cor", O_CREAT | O_RDWR | O_TRUNC, 0666)) <= 0)
	return (84);
      list = make_list();
      check_code(fd, fd_out, &list);
      close(fd);
      close(fd_out);
      return (0);
    }
  return (84);
}