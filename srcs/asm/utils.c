/*
** utils.c for  in /home/joubert/delivery/CPE_2016_corewar
** 
** Made by Joubert Miguel
** Login   <miguel.joubert@epitech.eu>
** 
** Started on  Mon Mar 27 22:35:07 2017 Joubert Miguel
** Last update Sun Apr  2 17:05:22 2017 Joubert Miguel
*/

#include <stdlib.h>
#include "asm.h"

int	my_sign(char *str)
{
  int   i;

  i = 0;
  if (!str)
    return (0);
  while (str[i] == '-')
    i++;
  return (i % 2);
}

int	my_get_nbr(char *str)
{
  int   i;
  int   sign;
  int   nb;

  if (!str)
    return (0);
  if (!*str)
    return (0);
  i = nb = sign = 0;
  while ((str[i] < '0' || str[i] > '9') && str[i])
    i++;
  while ((str[i] >= '0' && str[i] <= '9') && str[i])
    {
      nb += str[i] - 48;
      nb *= 10;
      i++;
    }
  nb /= 10;
  if (sign == 1) nb *= -1;
  return (nb);
}

char	*my_memset(int size)
{
  char  *str;
  int   i;

  if ((str = malloc(sizeof(char) * size)) == NULL)
    return (NULL);
  i = -1;
  while (++i < size)
    str[i] = 0;
  return (str);
}

char	*my_str_cat(char *dest, char *src)
{
  char  *res;
  int   i;
  int   j;
  int   write;

  if (dest == NULL)
    return (src);
  if (src == NULL)
    return (dest);
  j = i = 0;
  while (dest[i])
    i++;
  while (src[j])
    j++;
  if ((res = malloc(sizeof(char) * ((i + j + 1) * 100))) == NULL)
    return (NULL);
  i = -1;
  write = 0;
  while (dest[++i])
    res[write++] = dest[i];
  i = -1;
  while (src[++i])
    res[write++] = src[i];
  res[write] = '\0';
  return (res);
}

char	*my_char_cat(char *src, char c)
{
  int	i;
  char	*res;

  i = -1;
  res = my_memset(100);
  while (src[++i])
    res[i] = src[i];
  res[i] = c;
  return (res);
}
