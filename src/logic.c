#include "logic.h"
#include "config.h"
	
#define FALSE 0
#define TRUE 1

#define TIMEGAP 35

static char* getNumber(int number, int asHour) {
  switch(number) {
    case 1:
    case 13:
      return asHour?"μία":"ένα";
    case 2:
    case 14:
      return "δύο";
    case 3:
    case 15:
      return asHour?"τρεις":"τρία";
    case 4:
    case 16:
      return asHour?"τέσσερις":"τέσσερα";
    case 5:
    case 17:
      return "πέντε";
    case 6:
    case 18:
      return "έξι";
    case 7:
    case 19:
      return "επτά";
    case 8:
    case 20:
      return "οκτώ";
    case 9:
    case 21:
      return getLangFormal() ? "εννέα" : "εννιά";
    case 10:
    case 22:
      return "δέκα";
    case 11:
    case 23:
      return getLangFormal() ? "ένδεκα" : "έντεκα";
    case 0:    
    case 12:
    case 24:
      return "δώδεκα";
	default:
      return "?λάθος";
  }
}

char* getHour(int hour, int min) {
  return getNumber(min>=TIMEGAP?hour+1:hour,TRUE);
}

char* getTimeBridge(int minute) {
  if (minute==0)
    return getLangFormal() ? "ακριβώς" : "νταν";
  else if (minute>=6 && minute<=9)
	  return getLangFormal() ? "και" : "κι";
  else if (minute>=TIMEGAP)
    return "παρά";
  else
    return "και";
}

char* getMin1(int minute) {
  if (minute==0)
    return "";
  else if (minute==15||minute==45)
    return "τέταρτο";
  else if (minute==30)
    return "μισή";
  else if (minute>=TIMEGAP)
    minute = 60-minute;
  if (minute>30)
    return "τριάντα";
  else if (minute>=20)
    return "είκοσι";
  else if (getLangFormal() && minute==13)
	return "δεκατρία";
  else if (getLangFormal() && minute==16)
    return "δεκάξι";
  else if (minute>13)
    return "δέκα";
  else
    return getNumber(minute, FALSE);
}

char* getMin2(int minute) {
  if ((minute%10)==0||(minute%15)==0)
    return "";
  else if (minute>=TIMEGAP)
    minute = 60-minute;
  if (minute<=12)
	  return "";
  if ( getLangFormal() &&(minute==13 || minute==16))
    return "";
  else if (minute>30)
    minute -= 30;
  else if (minute>20)
    minute-=20;
  else if (minute>10)
    minute-=10;
  return getNumber(minute,FALSE);
}