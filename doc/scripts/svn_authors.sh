#!/usr/bin/env bash

svn_authors_1()
{
    authors=$(svn log -q | grep -e '^r' | awk 'BEGIN { FS = "|" } ; { print $2 }' | sort | uniq)
    for author in ${authors}; do
        echo "${author} = NAME <USER@DOMAIN>";
    done
}

svn_authors_2()
{
    svn log https://my-repo.url/svn/ | grep -E '^r[0-9]+' | cut -d '|' -f2 | sort | uniq | xargs -I {} echo '{} = name <email>'
}

svn_authors_3()
{
    authors=$(svn log -q $@ | grep -e '^r' | awk 'BEGIN { FS = "|" } ; { print $2 } $1 ~ /r([0-9]+000)/ { print "fetched revision " substr($1, 2) > "/dev/stderr" }' | sort | uniq)
    for author in ${authors}; do
        echo "${author} = NAME <user@domain>";
    done
}

svn_authors_4()
{
    # Use: grep -e '^r[0-9]' to help weed out all the lines that start with "r" but really aren't SVN revisions.
    svn log -q | awk '$1 ~ /^r[0-9]/ {array[$3]=1} END {for (name in array) {print name, "= name <email>"}}'
}
