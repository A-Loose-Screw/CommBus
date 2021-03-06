#!/usr/bin/env bash

#
# Copyright 2018 Staysail Systems, Inc. <info@staysail.tech>
# Copyright 2018 Capitar IT Group BV <info@capitar.com>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

NNGCAT=${NNGCAT:=$1}
NNGCAT=${NNGCAT:-./nngcat}

echo -n "Verify nngcat help: "
if ${NNGCAT} --help >/dev/null 2>&1
then
	echo "Failed: help didn't return 1"
	exit 1
fi
x=$(${NNGCAT} --help 2>&1)
if [[ ${x} =~ "Usage:" ]]
then
	echo "pass"
	exit 0
fi

echo "Failed: usage did not match"
echo "Output:"
echo "$x"
exit 1
