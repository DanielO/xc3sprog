/* Jedec .jed file parser

Copyright (C) Uwe Bonnes 2009 bon@elektron.ikp.physik.tu-darmstadt.de

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

/*
 * Using a slightly corrected version from IPAL libjedec
 * Copyright (c) 2000 Stephen Williams (steve@icarus.com)
 */ 

#ifndef JEDECFILE_H
#define JEDECFILE_H

#include <string>

#define MAX_ITEM   8
#define MAX_SIZE 256
typedef unsigned char byte;

struct jedec_data {
      char device[MAX_SIZE];
      char version[MAX_SIZE];
      char date[MAX_SIZE];

      unsigned fuse_count;
      unsigned pin_count;
      unsigned vector_count;
      unsigned checksum;
      unsigned char fuse_default;

      unsigned char*fuse_list;
};
typedef struct jedec_data *jedec_data_t;

#define JED_XC95X 0
#define JED_XC2C  1
#define JED_XC95  2

class JedecFile
{
 private:
  struct jedec_data jed;
  std::string errorStr;

 public:
  JedecFile(void);
  ~JedecFile();

 public:
  int readFile(FILE *fp);
  inline unsigned int getLength(){return jed.fuse_count;}
  inline unsigned short getChecksum(){return jed.checksum;}
  char *getDevice(){return jed.device;}
  char *getVersion(){return jed.version;}
  char *getDate(){return jed.date;}
  unsigned short calcChecksum();
  void setLength(unsigned int fuse_count);
  int get_fuse(unsigned int idx);
  void set_fuse(unsigned int idx, int blow);
  void saveAsJed(const char  * device, FILE *fp);
};
#endif //JEDECFILE_H
