//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h> /* Added for the nonblocking socket */
#include <errno.h> /* Added for the nonblocking socket */
#include <string.h>

#define os_memset memset
#define os_malloc malloc
#define os_free free
