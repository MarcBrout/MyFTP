/*
** replies.h for  in /home/brout_m/rendu/system/PSU_2016_myftp
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Sun May 14 16:24:03 2017 brout_m
** Last update Sun May 14 16:24:55 2017 brout_m
*/
#ifndef REPLIES_H_
# define REPLIES_H_

enum REPLIES
  {
    R110 = 0,
    R120,
    R125,
    R150,
    R200,
    R202,
    R211,
    R212,
    R213,
    R214,
    R215,
    R220,
    R221,
    R225,
    R226,
    R227,
    R230,
    R250,
    R257,
    R331,
    R332,
    R350,
    R421,
    R425,
    R426,
    R450,
    R451,
    R452,
    R500,
    R501,
    R502,
    R503,
    R504,
    R530,
    R532,
    R550,
    R551,
    R552,
    R553,
    MAX_REPLIES
  };

extern char const *replies[MAX_REPLIES];

#endif /* !REPLIES_H_ */
