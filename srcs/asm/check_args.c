/*
** check_args.c for corewar in /home/laspou_k/delivery/CPE/CPE_Corewar
** 
** Made by Kévin Laspougeas
** Login   <laspou_k@epitech.net>
** 
** Started on  Mon Mar 27 23:22:10 2017 Kévin Laspougeas
** Last update Mon Mar 27 23:30:05 2017 Kévin Laspougeas
*/

#include "asm.h"

int	is_reg(const char *str)
{
  if (str == NULL || str[0] != 'r' ||
      (str[0] == 'r' && (my_getnbr(&str[1]) <= 0 || my_getnbr(&str[1]) >
			 REG_NUMBER)))
    return (0);
  return (1):
}

int	is_dir(const char *str)
{
  if (str == NULL || str[0] != DIRECT_CHAR || my_str_isnum(&str[1]) != 1)
    return (0);
  return (1);
}

int	is_ind(const char *str)
{
  if (str == NULL || my_str_isnum(str) != 1)
    return (0);
  return (1);
}

int	is_label(const char *str)
{
  if (str == NULL || (str[0] != LABEL_CHAR && str[0] != DIRECT_CHAR) ||
      (str[0] == DIRECT_CHAR && str[1] != LABEL_CHAR))
    return (0);
  return (1);
}
