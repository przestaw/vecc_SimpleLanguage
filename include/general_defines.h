#ifndef PRZESTAW_GENERAL_DEFINES_H
#define PRZESTAW_GENERAL_DEFINES_H

#ifndef CONSOLE_COLORS_POSIX
#if (defined(WIN32) || defined(__WIN32__) || defined(_WIN32) \
     || defined(_MSC_VER))
#define CONSOLE_COLORS_POSIX WIN
#else
#define CONSOLE_COLORS_POSIX UNIX
#endif
#endif

#if CONSOLE_COLORS_POSIX == UNIX

/* RESET ALL */
#define RST "\x1B[0m"

/* FOREGROUND */
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

/* BACKGROUND */
#define TRED "\x1B[41m"
#define TGRN "\x1B[42m"
#define TYEL "\x1B[43m"
#define TBLU "\x1B[44m"
#define TMAG "\x1B[45m"
#define TCYN "\x1B[46m"
#define TWHT "\x1B[47m"

#define BRED(x) TRED x RST
#define BGRN(x) TGRN x RST
#define BYEL(x) TYEL x RST
#define BBLU(x) TBLU x RST
#define BMAG(x) TMAG x RST
#define BCYN(x) TCYN x RST
#define BWHT(x) TWHT x RST

/* FONT */
#define BOLD(x) "\x1B[1m" x "\x1B[21m"
#define DIM(x)  "\x1B[2m" x "\x1B[22m"
#define UNDL(x) "\x1B[4m" x "\x1B[24m"

/* INVERSE */
#define INV(x) "\x1B[7m" x "\x1B[27m"

// define all as "empty"
#else

#define RST
#define KRED
#define KGRN
#define KYEL
#define KBLU
#define KMAG
#define KCYN
#define KWHT
#define FRED(x) x
#define FGRN(x) x
#define FYEL(x) x
#define FBLU(x) x
#define FMAG(x) x
#define FCYN(x) x
#define FWHT(x) x
#define TRED
#define TGRN
#define TYEL
#define TBLU
#define TMAG
#define TCYN
#define TWHT
#define BRED(x) x
#define BGRN(x) x
#define BYEL(x) x
#define BBLU(x) x
#define BMAG(x) x
#define BCYN(x) x
#define BWHT(x) x
#define BOLD(x) x
#define DIM(x)  x
#define UNDL(x) x
#define INV(x)  x

#endif

#endif // PRZESTAW_GENERAL_DEFINES_H
