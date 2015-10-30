#define FREE_MAYBE(foo) do { if (foo) free (foo); } while (0)
#define CLEANDUP(x) (contains_unsafe (x) ? encode_string (x) : xstrdup (x))
#define PARAMS(args) args
