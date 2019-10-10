#!/usr/bin/env bash
# get_gutenberg_book.sh

adress=$1
bookname=$2
last_chapter_num=$3


#if $adress =~ 'http.*'; then
#  $bookname=


pattern='http://'
if [[ $adress =~ $pattern ]]; then
  echo "hi";
fi

#if test-commands; then
#  consequent-commands;
#[elif more-test-commands; then
#  more-consequents;]
#[else alternate-consequents;]
#fi

#wget --execute robots=off --wait=3 --random-wait --convert-links --user-agent=Mozilla http://gutenberg.spiegel.de/buch/niels-holgersens-wunderbare-reise-mit-den-wildgansen-zweiter-teil-7011/{1..29}
