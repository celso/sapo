#define VAR_LENGTH      30
#define VAR_VALUE       20000

struct var_node {
    struct Node v_node;
    char v_name[VAR_LENGTH];
    char v_value[VAR_VALUE];
};

#define	TAG_NONE	0
#define	TAG_VAR		1<<0L
#define	TAG_REM		1<<1L
#define	TAG_IF		1<<2L
#define	TAG_ENDIF	1<<3L
#define	TAG_EXEC	1<<4L
#define	TAG_CAT		1<<5L

#define	HIGHER_THAN	1<<0L
#define	LOWER_THAN	1<<1L
#define	EQUAL		1<<2L
#define	DIFERENT	1<<3L
#define	HIGHER_EQUAL	1<<4L
#define	LOWER_EQUAL	1<<5L

#define NUMERICAL	1<<0L
#define TEXT		1<<1L

#define MAX_IF_LOOPS	100
