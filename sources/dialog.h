#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <stdio.h>
#ifdef _WIN32

#define scanf_s scanf_s

#else

#define scanf_s scanf

#endif

enum TypeNPC {
	Torgovec,
	Quest1,
	Quest2,
	Provodnik
};

void dialog(TypeNPC);


#endif