/*
** my_str_isnum.c for CPool_Day06 in /home/laspou_k/delivery/CPool_Day06
**
** Made by Kévin Laspougeas
** Login   <laspou_k@epitech.net>
**
** Started on  Tue Oct 11 11:08:31 2016 Kévin Laspougeas
** Last update Mon Nov  7 16:06:40 2016 Kévin Laspougeas
*/

#include "my.h"

int	my_str_isnum(char *str)
{
  int	i;

  i = 0;
  if (str)
    {
      while (str[i])
	{
	  if (str[i] < '0' || str[i] > '9')
	    return (0);
	  i++;
	}
      return (1);
    }
  return (1);
}