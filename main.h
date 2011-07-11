/*****************************************************************************
* main.h
* 
* Randy Miller
*
* Distributes the command flow
*****************************************************************************/

//METHODS-----------------------

#define REPRINT     0
#define QUIT       -1
#define ABS         1
#define BIN_SEARCH  2
#define HIGHPOW2    3
#define LOG10       4
#define LOG2        5
#define MINMAX      6
#define NEGATE      7
#define OPP_SIGNS   8
#define PARITY      9
#define POW2       10
#define SETCLEAR   11
#define SIGN       12
#define SWAP       13
#define BITS_SET   14
#define REV_SEQ    15
#define MOD_DIV    16
#define TRAILING   17
#define NEXT_HP2   18
#define TEST_RANGE 19


//DECLARATIONS OF FUNCTIONS-----------------------

int abs_bits(void);
int bits_set(void);
int binary_search(void);
int highest_pow2(void);
int log10_bits(void);
int log2_bits(void);
int minmax(void);
int negate(void);
int opp(void);
int parity(void);
int pow2(void);
int setclear(void);
int sign(void);
int swap(void);
int reverse_sequence(void);
int mod_division(void);
int count_trailing(void);
int next_hp2(void);
int test_range(void);
