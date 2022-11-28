#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
