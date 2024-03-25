echo "GOING TO ERASE THE klee FOLDER AND REGENERATE IT"
read -p "Are you sure? [Y/N] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
  rm -rf klee
  cp -R gillian klee

for filename in $(find "./klee" -name "*.h"); do
    echo "transforming $filename"
    sed -i '' -e 's/#include <gillian-c\/gillian-c.h>/#include <klee\/klee.h> /' $filename
    comby 'int :[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'int :[x]; klee_make_symbolic(&:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'char :[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'char :[x]; klee_make_symbolic(&:[x], sizeof(char), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'char :[[x]] = (char)__builtin_annot_intval("symb_int", :[[x]]);' 'char :[x]; klee_make_symbolic(&:[x], sizeof(char), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby ':[[type]] X = (:[[type]])__builtin_annot_intval("symb_int", :[[x]])' ':[type] :[x]; klee_make_symbolic(&:[x], sizeof(:[type]), ":[x]")' -d $(dirname $filename) $(basename $filename) -i
    comby ':[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'klee_make_symbolic(&:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i # FIXME: timeout
    comby '*:[[x]] = __builtin_annot_intval("symb_int", *:[[x]]);' 'klee_make_symbolic(:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSERT(:[assertion]);' 'klee_assert(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSUME(:[assertion]);' 'klee_assume(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSUME (:[assertion]);' 'klee_assume(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
  done

for filename in $(find "./klee" -name "*.c"); do
    echo "transforming $filename"
    sed -i '' -e 's/#include <gillian-c\/gillian-c.h>/#include <klee\/klee.h> /' $filename
    comby 'int :[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'int :[x]; klee_make_symbolic(&:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'char :[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'char :[x]; klee_make_symbolic(&:[x], sizeof(char), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'char :[[x]] = (char)__builtin_annot_intval("symb_int", :[[x]]);' 'char :[x]; klee_make_symbolic(&:[x], sizeof(char), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby ':[[type]] X = (:[[type]])__builtin_annot_intval("symb_int", :[[x]])' ':[type] :[x]; klee_make_symbolic(&:[x], sizeof(:[type]), ":[x]")' -d $(dirname $filename) $(basename $filename) -i
    comby ':[[x]] = __builtin_annot_intval("symb_int", :[[x]]);' 'klee_make_symbolic(&:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i # FIXME: timeout
    comby '*:[[x]] = __builtin_annot_intval("symb_int", *:[[x]]);' 'klee_make_symbolic(:[x], sizeof(int), ":[x]");' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSERT(:[assertion]);' 'klee_assert(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSUME(:[assertion]);' 'klee_assume(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
    comby 'ASSUME (:[assertion]);' 'klee_assume(:[assertion]);' -d $(dirname $filename) $(basename $filename) -i
  done
fi