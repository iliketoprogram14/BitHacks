/*****************************************************************************
* main.h
* 
* Randy Miller
*
* Distributes the command flow
*****************************************************************************/

//METHODS-----------------------

#define REPRINT    0
#define QUIT      -1
#define ABS        1
#define BIN_SEARCH 2
#define HIGHPOW2   3
#define LOG10      4
#define LOG2       5
#define MINMAX     6
#define NEGATE     7
#define OPP_SIGNS  8
#define PARITY     9
#define POW2      10
#define SETCLEAR  11
#define SIGN      12
#define SWAP      13

//DECLARATIONS OF FUNCTIONS-----------------------

int abs(void);
int binary_search(void);
int highest_pow2(void);
int log10(void);
int log2(void);
int minmax(void);
int negate(void);
int opp(void);
int parity(void);
int pow2(void);
int setclear(void);
int sign(void);
int swap(void);
