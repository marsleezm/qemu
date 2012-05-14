/*
 *  Copyright (C) 2005  Anthony Liguori <anthony@codemonkey.ws>
 *
 *  Network Block Device
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; under version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu-common.h"
#include "block.h"
#include "nbd.h"

#include <stdarg.h>
#include <stdio.h>
#include <getopt.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <signal.h>
#include <libgen.h>
#include <pthread.h>

#define SOCKET_PATH    "/var/lock/qemu-nbd-%s"

static NBDExport *exp;
static int verbose;
static char *srcpath;
static char *sockpath;
static bool sigterm_reported;
static bool nbd_started;
static int NBDshared = 1;
static int nb_fds;
static int NBDport = 10809;
static bool NBDServerRunning = false;
static int socketFD ;


struct partition_record
{
    uint8_t bootable;
    uint8_t start_head;
    uint32_t start_cylinder;
    uint8_t start_sector;
    uint8_t system;
    uint8_t end_head;
    uint8_t end_cylinder;
    uint8_t end_sector;
    uint32_t start_sector_abs;
    uint32_t nb_sectors_abs;
};

//int initNbd(char* filename);
//int finalizeNbd(char* filename);
