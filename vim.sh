#!/usr/bin/env sh
set -eu

cd "$(dirname "$0")"

exec vim -u ./vimrc.icpc "$@"
