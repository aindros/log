#!/bin/sh

Linux_cflags()
{
	echo -D_GNU_SOURCE
}

FreeBSD_cflags()
{
	echo -D_BSD_SOURCE
}

$(uname)_cflags

