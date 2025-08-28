# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
perl -0777 -pe 's://.*?$::mg; s:/\*.*?\*/::sg' \
  | tr -d '[:space:]' \
  | md5sum \
  | cut -c-6
