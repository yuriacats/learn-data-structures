#!/bin/bash

# 実行時間が2秒を超えるまで、Nを増やしながら繰り返し実行時間を計測する。
#
# usage:
#   ./test-performance
#     「n: t」 のリストが表示される
#     tは実行時間 time (sec)
#
#   ./test-performance EXPR="t/n"
#     「n: (t/n)」のリストが表示される
#
#   ./test-performance EXPR="e(1/3 * l(t))/n"
#     「n: tの3乗根をnで割ったもの」のリストが表示される
#
#   ./test-perfirmance EXPR="l(t)/n"
#      「n: tの対数をnで割ったもの」のリストが表示される

number=10
expr=${EXPR:-'t'}

printf "N               (%s)\n" $EXPR >&2

while :;do
  duration=$(N=${number} /usr/bin/time -f "%e" ./dist/main 2>&1 > /dev/null)
  value=$(echo $expr | sed "s/n/$number/g" | sed "s/t/$duration/g" | bc -l)

  printf "%-15d %.20f\n" ${number} ${value}

  if [ "$(echo "${duration} > 2" | bc)" -eq 1 ]; then
    exit 0
  else
    number=$(printf "%.0f" $(echo "$number * 1.2" | bc))
  fi
done
