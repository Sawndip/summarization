#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <sys/types.h>

int connect_to(int32_t s_addr, int port);
int listen_single_connect(int port);

#endif
