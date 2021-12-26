#!/bin/sh

ALGO="${ALGO:-sha1}"

TO_LOWER=$(echo "$ALGO" | tr [:upper:] [:lower:])
TO_UPPER=$(echo "$ALGO" | tr [:lower:] [:upper:])

/bin/echo -n "${TO_UPPER} \"test_text
${TO_UPPER} $0
${TO_LOWER} \"Test string" | ./rhasher > ores

/bin/echo -n test_text | rhash -p "%x{${TO_LOWER}}\n" - > ogood
rhash -p "%x{${TO_LOWER}}\n" $0 >> ogood
/bin/echo -n "Test string" | rhash -p "%B{${TO_LOWER}}\n" - >> ogood

diff ores ogood
RES=$?

rm -f ores ogood
exit $RES