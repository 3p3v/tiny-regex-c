/*
 *
 * Mini regex-module inspired by Rob Pike's regex code described in:
 *
 * http://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
 *
 *
 *
 * Supports:
 * ---------
 *   '.'        Dot, matches any character
 *   '^'        Start anchor, matches beginning of string
 *   '$'        End anchor, matches end of string
 *   '*'        Asterisk, match zero or more (greedy)
 *   '+'        Plus, match one or more (greedy)
 *   '?'        Question, match zero or one (non-greedy)
 *   '[abc]'    Character class, match if one of {'a', 'b', 'c'}
 *   '[^abc]'   Inverted class, match if NOT one of {'a', 'b', 'c'} -- NOTE: feature is currently broken!
 *   '[a-zA-Z]' Character ranges, the character set of the ranges { a-z | A-Z }
 *   '\s'       Whitespace, \t \f \r \n \v and spaces
 *   '\S'       Non-whitespace
 *   '\w'       Alphanumeric, [a-zA-Z0-9_]
 *   '\W'       Non-alphanumeric
 *   '\d'       Digits, [0-9]
 *   '\D'       Non-digits
 *
 *
 */

#ifndef _TINY_REGEX_C
#define _TINY_REGEX_C


#ifndef RE_DOT_MATCHES_NEWLINE
/* Define to 0 if you DON'T want '.' to match '\r' + '\n' */
#define RE_DOT_MATCHES_NEWLINE 1
#endif

#ifdef __cplusplus
extern "C"{
#endif

/* Definitions: */
#define MAX_REGEXP_OBJECTS      30    /* Max number of regex symbols in expression. */
#define MAX_CHAR_CLASS_LEN      40    /* Max length of character-class buffer in.   */

typedef struct regex_t
{
  unsigned char  type;   /* CHAR, STAR, etc.                      */
  union
  {
    unsigned char  ch;   /*      the character itself             */
    unsigned char* ccl;  /*  OR  a pointer to characters in class */
  } u;
} regex_t;

/* Typedef'd pointer to get abstract datatype. */
typedef struct regex_t* re_t;

/* Struct for storing pattern and buffer together */
typedef struct regex_tuple_t
{
#ifndef REGEX_ALLOC
    /* Do not allocate any data */
    regex_t pattern[MAX_REGEXP_OBJECTS];
    unsigned char buf[MAX_CHAR_CLASS_LEN];
#else
    /* Use heap allocation */
    regex_t *pattern;
#endif
} regex_tuple_t;

/* Typedef'd pointer to get abstract datatype. */
typedef struct regex_tuple_t* re_tuple_t;

/* Compile regex string pattern to a regex_t-array. */
re_tuple_t re_compile(const char* pattern, re_tuple_t re_pattern);


/* Find matches of the compiled pattern inside text. */
int re_matchp(re_tuple_t re_pattern, const char* text, unsigned int* matchlength);


/* Find matches of the txt pattern inside text (will compile automatically first). */
int re_match(const char* pattern, const char* text, unsigned int* matchlength);


/* Find matches of the compiled pattern inside text. */
int re_matchpn(re_tuple_t re_pattern, const char* text, size_t textlength, unsigned int* matchlength);


/* Find matches of the txt pattern inside text (will compile automatically first). */
int re_matchn(const char* pattern, const char* text, size_t textlength, unsigned int* matchlength);


#ifdef __cplusplus
}
#endif

#endif /* ifndef _TINY_REGEX_C */
