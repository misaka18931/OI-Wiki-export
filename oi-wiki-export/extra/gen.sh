#/usr/bin/env bash
OUT=`pwd`/out
SRC=src
menu=$OUT/includes.tex
mkdir -p $OUT
echo '\chapter{Extra Templates}' > $menu
for dir in $(find $SRC -type d -maxdepth 1 -mindepth 1); do
  for entry in $(find $dir -type f -name "*.cpp"); do
    base=${entry%%.cpp}
    name=${base##*/}
    target=$OUT/$name.tex
    echo generating $target
    if [ -f "$base.tex" ] ; then
      cp "$base.tex" "$target"
    else
      cat > $target << EOF
\begin{minted}[]{cpp}
%CODE%
\end{minted}
EOF
    fi
    tmp=mktemp
    cp $entry $tmp
    echo >> $tmp
    sed -i -e "/%CODE%/r $tmp" -e "/%CODE%/d" $target
    rm $tmp
    echo "\\section{$name}" >> $menu
    echo "\\input{${target%%.tex}}" >> $menu
  done
done
