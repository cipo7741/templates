#!/bin/bash
# covariance_pipeline.sh
# 2016-09-01 by biprak3+biprak5

if [ "$#" == 0 ] || [ "$1" == "-h" ]; then
    echo ""
    echo "Usage: `basename $0` [options]"
    echo ""
    echo "options:"
    echo "-h                      : prints this line"
    echo "-nocal|--no-calibrate   : skip cmbuild and cmalign"
    echo "-msai|--msafile_in      : cmbuild msafile"
    echo "-cm|--cmfile            : cmbuild cmfile (created if non existend)"
    echo "-o|--out                : output directory"
    echo "-cpu|--CPU              : num of cpus (check load before and while running)"
    echo "-gen|--genomes          : genome files"
    echo "-rex|--grep-regex       : genome file ending (default .fa$)"

    echo ""
    exit 0
fi

CALIBRATE="YES"
SKIP_SEARCH="NO"
GREP=.fa$

while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -msai|--msafile_in)
    MSA_FILE="$2"
    shift # past argument
    ;;
    -cm|--cmfile)
    CM_FILE="$2"
    shift # past argument
    ;;
    -o|--out_dir)
    OUTPUT="$2"
    shift # past argument
    ;;
    -cpu|--CPU)
    CPU="$2"
    shift # past argument
    ;;
    -gen|--genomes)
    GENOMES="$2"
    shift # past argument
    ;;
    -rex|--grep-regex)
    GREP="$2"
    shift # past argument
    ;;
    -nosearch|--skip-search)
    SKIP_SEARCH=YES
    ;;
    -nocal|--no-calibrate)
    CALIBRATE=NO
    ;;
    -bat|--use-bats)
    BAT=YES
    ;;
    *)
            # unknown option
    ;;
esac
shift # past argument or value
done
echo "MSA_FILE  : ${MSA_FILE}"
echo "CM_FILE   : ${CM_FILE}"
echo "OUTPUT    : ${OUTPUT}"
echo "CPU       : ${CPU}"
echo "GENOMES   : ${GENOMES} with ${GREP}"
echo "SKIP_SEARCH: ${SKIP_SEARCH}"
echo "Calibrate : ${CALIBRATE}"
echo "BAT       : ${BAT}"

SCRIPT=$(readlink -f "$0")

if [ "${CALIBRATE}" == "YES" ]; then
    if [ ! -e ${CM_FILE} ]; then
        echo "Building covariance model"
        cmbuild -F $CM_FILE $MSA_FILE
    else
        echo "using existing cmbuild covariance model $CM_FILE"
    fi
        echo "Calibrate cv model"
        cmcalibrate --cpu $CPU  $CM_FILE
else
    echo "no cmcalibrate"
fi

if [ "${SKIP_SEARCH}" == "NO" ]; then
    echo "Search genomes with new cv model"

    FILES=$(ls "$GENOMES" | grep "${GREP}")

    ## blast for stuff
    for f in ${FILES[@]}; do
        filename="${f##*/}"
        filenameExtensionless="${filename%.*}"
        echo "<<|<>|>> processing file: $f"
        cmsearch --cpu $CPU $CM_FILE "$GENOMES$f" > $OUTPUT/"${filenameExtensionless}.hits"
    done
    echo "cmsearch finished"

    ## remove any prior sequences
    #rm $OUTPUT/"infernal_sequences.fa"

    ## extract hit positions & sequences and make multiple fasta file
    for f in ${FILES[@]}; do
        filename="${f##*/}"
        filenameExtensionless="${filename%.*}"
        python $(dirname $SCRIPT)/extract_sequences_from_cmsearch.py $OUTPUT/"${filenameExtensionless}.hits" $OUTPUT/"infernal_sequences.fa"
    done

    if [ "${BAT}" == "YES" ]; then
        cat $(dirname $CM_FILE)/"infernal_sequences.fa" >> $OUTPUT/"infernal_sequences.fa"
    fi
fi

echo "Aligning new hits using cmalign"
# extend alignment file with new sequences
cmalign -o $OUTPUT/$(basename $CM_FILE .cm)"_realigned.stk" --cpu $CPU $CM_FILE $OUTPUT/"infernal_sequences.fa"

