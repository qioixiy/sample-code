function l() {
    echo $(date '+%Y-%m-%d %T') $(free | sed -n '2p' | awk '{print $2,$3,$4,$5,$6,$7}') srv:$(ps | grep Srv | sed -n '1p' | awk '{print $3}')
}

while [ true ]; do
    l
    sleep 1
done
