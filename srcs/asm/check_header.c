/*
** check_header.c for  in /home/joubert/delivery/CPE_2016_corewar
** 
** Made by Joubert Miguel
** Login   <miguel.joubert@epitech.eu>
** 
** Started on  Sat Apr  1 15:39:28 2017 Joubert Miguel
** Last update Sun Apr  2 22:12:22 2017 Joubert Miguel
*/

#include "asm.h"

int		check_header_quotes(char *str)
{
  int		i;
  int		count;

  if (!str)
    return (-1);
  count = 0;
  i = -1;
  while (str[++i]) {
    if (str[i] == '"')
      count++;
  }
  return (count);
}

int		check_header(char *line, int lines)
{
  static int	count = 0;
  static int	name = 0;
  static int	cmnt = 0;

  count++;
  if (!(my_strncmp(COMMENT_CMD_STRING, line, 8))) {
    cmnt++;
    if (check_header_quotes(line) != 2
	|| my_strlen(my_str_sep(line, '"')[1]) > COMMENT_LENGTH + 1
	|| *my_str_sep(line, '"')[2]
	|| my_strcmp(my_str_cat(COMMENT_CMD_STRING, " "),
		     my_str_sep(line, '"')[0]))
      exit_error(line, lines, WRG_PAR);
  }
  if (!(my_strncmp(NAME_CMD_STRING, line, 5))) {
    name++;
    if (check_header_quotes(line) != 2
	|| my_strlen(my_str_sep(line, '"')[1]) > PROG_NAME_LENGTH + 1
	|| *my_str_sep(line, '"')[2]
	|| my_strcmp(my_str_cat(NAME_CMD_STRING, " "), my_str_sep(line, '"')[0]))
      exit_error(line, lines, WRG_PAR);
  }
  if (count > 2 || name > 1 || cmnt > 1)
    exit_error(line, lines, WRG_PAR);
  return (count);
}
