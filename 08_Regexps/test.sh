#!/bin/bash

regexp="$1"
substitution="$2"
string="$3"

echo "$string" | sed -E "s/${regexp}/${substitution}/"
echo ./esub "${regexp}" "${substitution}" "${string}"
diff <(echo "$string" | sed -E "s/${regexp}/${substitution}/") <(./esub "${regexp}" "${substitution}" "${string}")