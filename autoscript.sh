libtoolize --force
aclocal
autoheader
automake -c -a
autoconf
autoreconf -i
