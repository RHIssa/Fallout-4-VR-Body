#ifndef	F4VRBODY_VERSION_INCLUDED
#define F4VRBODY_VERSION_INCLUDED

#define MAKE_STR_HELPER(a_str) #a_str
#define MAKE_STR(a_str) MAKE_STR_HELPER(a_str)

#define F4VRBODY_VERSION_MAJOR	0
#define F4VRBODY_VERSION_MINOR	1
#define F4VRBODY_VERSION_PATCH	0
#define F4VRBODY_VERSION_BETA	4
#define F4VRBODY_VERSION_VERSTRING	MAKE_STR(F4VRBODY_VERSION_MAJOR) "." MAKE_STR(F4VRBODY_VERSION_MINOR) "." MAKE_STR(F4VRBODY_VERSION_PATCH) "." MAKE_STR(F4VRBODY_VERSION_BETA)

#endif
